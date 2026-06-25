#include "Negative.h"

#include "ActionHandler.h"


Negative::Negative() : Transformer(ActionType::NEGATIVE, true) {
}


void Negative::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & Negative::transform(Image &img) const {
    int height = img.getHeight();
    int width = img.getWidth();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Pixel& pixel = img.pixelAt(x, y);
            pixel.red = static_cast<unsigned char>(255 - pixel.red);
            pixel.green = static_cast<unsigned char>(255 - pixel.green);
            pixel.blue = static_cast<unsigned char>(255 - pixel.blue);
        }
    }

    return img;
}

Negative * Negative::clone() const {
    return new Negative(*this);
}
