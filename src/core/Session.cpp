#include "Session.h"

#include "action/transformation/FlipLeft.h"
#include "action/transformation/FlipTop.h"
#include "action/transformation/RotateLeft.h"
#include "action/transformation/RotateRight.h"

SessionImage::SessionImage(Image* image, size_t firstTransformationIndex) :
    image(image), firstTransformationIndex(firstTransformationIndex) {
}

Session::Session(unsigned int id) : id(id), hasUnsavedWork(false) {
}

Session::~Session() {
    for (size_t i = 0; i < transformations.size(); i++) {
        delete transformations[i];
    }

    for (size_t i = 0; i < undoneTransforms.size(); i++) {
        delete undoneTransforms[i];
    }

    for (size_t i = 0; i < images.size(); i++) {
        delete images[i].image;
    }
}

unsigned int Session::getId() const {
    return this->id;
}

bool Session::getHasUnsavedWork() const {
    return this->hasUnsavedWork;
}

void Session::clearUndoneTransforms() {
    for (size_t i = 0; i < undoneTransforms.size(); i++) {
        delete undoneTransforms[i];
    }
    undoneTransforms.clear();
}

void Session::applyTransformations(Image& image, size_t firstTransformationIndex) const {
    std::vector<Transformer*> geometricTransformations;
    std::vector<Transformer*> filterTransformations;
    splitTransformations(firstTransformationIndex, geometricTransformations, filterTransformations);

    int finalState = calculateFinalGeometricState(geometricTransformations);
    applyFinalGeometricState(image, finalState);

    for (size_t i = 0; i < filterTransformations.size(); i++) {
        filterTransformations[i]->transform(image);
    }
}

void Session::splitTransformations(size_t firstTransformationIndex,
                                   std::vector<Transformer*>& geometricTransformations,
                                   std::vector<Transformer*>& filterTransformations) const {
    for (size_t i = firstTransformationIndex; i < transformations.size(); i++) {
        if (transformations[i]->getIsFilter()) {
            filterTransformations.push_back(transformations[i]);
        } else {
            geometricTransformations.push_back(transformations[i]);
        }
    }
}

int Session::getGeometricTransformationColumn(ActionType type) const {
    if (type == ActionType::ROTATE_RIGHT) {
        return 0;
    }

    if (type == ActionType::ROTATE_LEFT) {
        return 1;
    }

    if (type == ActionType::FLIP_TOP) {
        return 2;
    }

    if (type == ActionType::FLIP_LEFT) {
        return 3;
    }

    return -1;
}


/* The states of this matrix are hard coded to represent these values:
 * Columns: 0) rotate right; 1) rotate left; 2) flip top; 3) flip left;
 * Rows: 0) identity; 1) rotate right 90 deg; 2) rotate right 180 deg; 3) rotate left 90 deg;
 *       4) flipped top; 5) flipped left; 6) rotate right 90 deg + flipped top; 7) rotate right 90 deg + flipped left;
 */
int Session::calculateFinalGeometricState(const std::vector<Transformer*>& geometricTransformations) const {
    const int identity = 0;
    const int stateMatrix[8][4] = {
        {1, 3, 4, 5},
        {2, 0, 6, 7},
        {3, 1, 5, 4},
        {0, 2, 7, 6},
        {7, 6, 0, 2},
        {6, 7, 2, 0},
        {4, 5, 1, 3},
        {5, 4, 3, 1}
    };

    int currentState = identity;
    for (size_t i = 0; i < geometricTransformations.size(); i++) {
        int column = getGeometricTransformationColumn(geometricTransformations[i]->getType());
        if (column >= 0) {
            currentState = stateMatrix[currentState][column];
        }
    }

    return currentState;
}

void Session::applyFinalGeometricState(Image& image, int finalState) const {
    RotateRight rotateRight;
    RotateLeft rotateLeft;
    FlipTop flipTop;
    FlipLeft flipLeft;

    switch (finalState) {
        case 0:
            break;
        case 1:
            rotateRight.transform(image);
            break;
        case 2:
            rotateRight.transform(image);
            rotateRight.transform(image);
            break;
        case 3:
            rotateLeft.transform(image);
            break;
        case 4:
            flipTop.transform(image);
            break;
        case 5:
            flipLeft.transform(image);
            break;
        case 6:
            rotateRight.transform(image);
            flipTop.transform(image);
            break;
        case 7:
            rotateRight.transform(image);
            flipLeft.transform(image);
            break;
        default:
            break;
    }
}

int Session::findImageIndex(const std::string& name) const {
    for (size_t i = 0; i < images.size(); i++) {
        if (images[i].image->matchesName(name)) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

bool Session::addImage(const std::string& filePath, std::string& error) {
    Image* image = new Image();
    if (!image->loadFromFile(filePath, error)) {
        delete image;
        return false;
    }

    images.push_back(SessionImage(image, transformations.size()));
    return true;
}

bool Session::addTransformation(Transformer* transformer) {
    clearUndoneTransforms();
    transformations.push_back(transformer);
    hasUnsavedWork = true;
    return true;
}

bool Session::undo(std::string& message) {
    if (transformations.empty()) {
        message = "Nothing to undo\n";
        return false;
    }

    undoneTransforms.push_back(transformations.back());
    transformations.pop_back();
    hasUnsavedWork = true;
    message = "Undo completed\n";
    return true;
}

bool Session::redo(std::string& message) {
    if (undoneTransforms.empty()) {
        message = "Nothing to redo\n";
        return false;
    }

    /*
     * I would rather use std::queue so this task is optimized and is O(1), not O(n) but it is not allowed
     * I also thought about writing my own queue with a double-linked linked list, but it felt like overkill
     * as we have not studied data structures and algorithms and I may make a mistake while implementing it
    */
    transformations.push_back(undoneTransforms.front());
    undoneTransforms.erase(undoneTransforms.begin());
    hasUnsavedWork = true;
    message = "Redo completed\n";
    return true;
}

bool Session::paste(const std::string& sourceName, const std::string& destinationName, int posX, int posY, std::string& message) {
    int sourceIndex = findImageIndex(sourceName);
    int destinationIndex = findImageIndex(destinationName);

    if (sourceIndex < 0) {
        message = "Source image not found: " + sourceName;
        return false;
    }

    if (destinationIndex < 0) {
        message = "Destination image not found: " + destinationName;
        return false;
    }

    Image source = *images[static_cast<size_t>(sourceIndex)].image;
    Image destination = *images[static_cast<size_t>(destinationIndex)].image;

    applyTransformations(source, images[static_cast<size_t>(sourceIndex)].firstTransformationIndex);
    applyTransformations(destination, images[static_cast<size_t>(destinationIndex)].firstTransformationIndex);

    std::string error;
    if (!destination.paste(source, posX, posY, error)) {
        message = error;
        return false;
    }

    *images[static_cast<size_t>(destinationIndex)].image = destination;
    images[static_cast<size_t>(destinationIndex)].firstTransformationIndex = transformations.size();
    hasUnsavedWork = true;
    return true;
}

bool Session::save(std::string& message) {
    if (!hasUnsavedWork) {
        message = "Session is already saved\n";
        return false;
    }

    if (images.empty()) {
        message = "Session has no images\n";
        return false;
    }

    bool allSaved = true;
    message.clear();

    for (size_t i = 0; i < images.size(); i++) {
        Image copy = *images[i].image;
        applyTransformations(copy, images[i].firstTransformationIndex);

        std::string savedPath;
        std::string error;
        if (copy.saveWithTimestamp(savedPath, error)) {
            message += "Saved: " + savedPath + "\n";
        } else {
            allSaved = false;
            message += error + "\n";
        }
    }

    if (allSaved) {
        hasUnsavedWork = false;
    }

    return allSaved;
}

void Session::printInfo(std::ostream& os, std::string& error) const {
    error.clear();
    if (!os.good()) {
        error += "Internal error: Bad output stream\n";
        return;
    }
    os << "Files in session with ID " << id << ":\n";
    for (size_t i = 0; i < images.size(); i++) {
        os << images[i].image->getNameWithoutExtension()
           << " - " << images[i].image->getFormatName()
           << " (" << images[i].image->getWidth()
           << "x" << images[i].image->getHeight() << ")\n";
    }
    os << "Pending transformations: " << transformations.size() << "\n";
}
