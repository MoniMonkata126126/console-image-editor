#include "FlipLeft.h"

#include "ActionHandler.h"
#include "CustomExceptions.h"

FlipLeft::FlipLeft() : Transformer(ActionType::FLIP_LEFT, false) {
}

FlipLeft::FlipLeft(ActionType type, bool isFilter) : Transformer(type, isFilter) {
    if (isFilter) {
        throw CustomExceptions::ACTION_TYPE_NOT_FILTER;
    }
}

void FlipLeft::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & FlipLeft::transform(Image &img) const {
    for (int y = 0; y < img.getHeight(); y++) {
        for (int x = 0; x < img.getWidth() / 2; x++) {
            int oppositeX = img.getWidth() - 1 - x;
            Pixel tmp = img.pixelAt(x, y);
            img.pixelAt(x, y) = img.pixelAt(oppositeX, y);
            img.pixelAt(oppositeX, y) = tmp;
        }
    }

    return img;
}

Transformer * FlipLeft::clone() const {
    return new FlipLeft(*this);
}
