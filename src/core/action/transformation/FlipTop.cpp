#include "FlipTop.h"

#include "ActionHandler.h"

FlipTop::FlipTop() : Transformer(ActionType::FLIP_TOP, false) {
}

void FlipTop::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & FlipTop::transform(Image &img) const {
    int height = img.getHeight();
    int width = img.getWidth();

    for (int y = 0; y < height / 2; y++) {
        int oppositeY = height - 1 - y;
        for (int x = 0; x < width; x++) {
            Pixel tmp = img.pixelAt(x, y);
            img.pixelAt(x, y) = img.pixelAt(x, oppositeY);
            img.pixelAt(x, oppositeY) = tmp;
        }
    }

    return img;
}

FlipTop * FlipTop::clone() const {
    return new FlipTop(*this);
}
