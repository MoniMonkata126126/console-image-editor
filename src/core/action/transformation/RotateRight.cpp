#include "RotateRight.h"

#include <vector>
#include "ActionHandler.h"
#include "CustomExceptions.h"

RotateRight::RotateRight() : Transformer(ActionType::ROTATE_RIGHT, false) {
}


void RotateRight::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & RotateRight::transform(Image &img) const {
    int width = img.getWidth();
    int height = img.getHeight();
    std::vector<Pixel> rotated(static_cast<size_t>(width * height));
    int newWidth = height;
    int newHeight = width;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int newX = height - 1 - y;
            int newY = x;
            rotated[static_cast<size_t>(newY * newWidth + newX)] = img.pixelAt(x, y);
        }
    }

    img.replacePixels(newWidth, newHeight, rotated);
    return img;
}

RotateRight * RotateRight::clone() const {
    return new RotateRight(*this);
}
