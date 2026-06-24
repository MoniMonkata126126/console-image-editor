#include "RotateLeft.h"

#include <vector>
#include "ActionHandler.h"
#include "CustomExceptions.h"

RotateLeft::RotateLeft() : Transformer(ActionType::ROTATE_LEFT, false) {
}

RotateLeft::RotateLeft(ActionType type, bool isFilter): Transformer(type, isFilter) {
    if (isFilter) {
        throw CustomExceptions::ACTION_TYPE_NOT_FILTER;
    }
}

void RotateLeft::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & RotateLeft::transform(Image &img) const {
    int width = img.getWidth();
    int height = img.getHeight();
    std::vector<Pixel> rotated(static_cast<size_t>(width * height));
    int newWidth = height;
    int newHeight = width;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int newX = y;
            int newY = width - 1 - x;
            rotated[static_cast<size_t>(newY * newWidth + newX)] = img.pixelAt(x, y);
        }
    }

    img.replacePixels(newWidth, newHeight, rotated);
    return img;
}

Transformer * RotateLeft::clone() const {
    return new RotateLeft(*this);
}
