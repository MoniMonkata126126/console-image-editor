#include "FlipLeft.h"

#include "ActionHandler.h"

FlipLeft::FlipLeft() : Transformer(ActionType::FLIP_LEFT, false) {
}


void FlipLeft::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & FlipLeft::transform(Image &img) const {
    int height = img.getHeight();
    int width = img.getWidth();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width / 2; x++) {
            int oppositeX = img.getWidth() - 1 - x;
            Pixel tmp = img.pixelAt(x, y);
            img.pixelAt(x, y) = img.pixelAt(oppositeX, y);
            img.pixelAt(oppositeX, y) = tmp;
        }
    }

    return img;
}

FlipLeft * FlipLeft::clone() const {
    return new FlipLeft(*this);
}
