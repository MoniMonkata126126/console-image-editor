#ifndef CONSOLE_IMAGE_EDITOR_SESSION_H
#define CONSOLE_IMAGE_EDITOR_SESSION_H

#include <iostream>
#include <string>
#include <vector>
#include "action/Transformer.h"
#include "image/Image.h"

struct SessionImage {
    Image* image;
    size_t firstTransformationIndex;

    SessionImage(Image* image, size_t firstTransformationIndex);
};

class Session {
private:
    unsigned int id;
    std::vector<Transformer*> transformations;
    std::vector<Transformer*> undoneTransforms;
    std::vector<SessionImage> images;
    bool hasUnsavedWork;

    void clearUndoneTransforms();

    void applyTransformations(Image& image, size_t firstTransformationIndex) const;

    void splitTransformations(size_t firstTransformationIndex,
                              std::vector<Transformer*>& geometricTransformations,
                              std::vector<Transformer*>& filterTransformations) const;

    int getGeometricTransformationColumn(ActionType type) const;

    int calculateFinalGeometricState(const std::vector<Transformer*>& geometricTransformations) const;

    void applyFinalGeometricState(Image& image, int finalState) const;

    int findImageIndex(const std::string& name) const;

public:
    explicit Session(unsigned int id);

    Session(const Session& other) = delete;

    Session& operator=(const Session& other) = delete;

    ~Session();

    unsigned int getId() const;

    bool getHasUnsavedWork() const;

    bool addImage(const std::string& filePath, std::string& error);

    bool addTransformation(Transformer* transformer);

    bool undo(std::string& message);

    bool redo(std::string& message);

    bool paste(const std::string& sourceName, const std::string& destinationName, int posX, int posY, std::string& message);

    bool save(std::string& message);

    void printInfo(std::ostream& os) const;
};


#endif //CONSOLE_IMAGE_EDITOR_SESSION_H
