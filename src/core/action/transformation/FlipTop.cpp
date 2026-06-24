#include "FlipTop.h"

#include "ActionHandler.h"
#include "CustomExceptions.h"

FlipTop::FlipTop() : Transformer(ActionType::FLIP_TOP, false) {
}

FlipTop::FlipTop(ActionType type, bool isFilter) : Transformer(type, isFilter) {
    if (isFilter) {
        throw CustomExceptions::ACTION_TYPE_NOT_FILTER;
    }
}

void FlipTop::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & FlipTop::transform(Image &img) const {
    for (int y = 0; y < img.getHeight() / 2; y++) {
        int oppositeY = img.getHeight() - 1 - y;
        for (int x = 0; x < img.getWidth(); x++) {
            Pixel tmp = img.pixelAt(x, y);
            img.pixelAt(x, y) = img.pixelAt(x, oppositeY);
            img.pixelAt(x, oppositeY) = tmp;
        }
    }

    return img;
}

Transformer * FlipTop::clone() const {
    return new FlipTop(*this);
}
