#include "Negative.h"

#include "ActionHandler.h"
#include "CustomExceptions.h"

Negative::Negative() : Transformer(ActionType::NEGATIVE, true) {
}

Negative::Negative(ActionType type, bool isFilter) : Transformer(type, isFilter) {
    if (!isFilter) {
        throw CustomExceptions::ACTION_TYPE_IS_FILTER;
    }
}

void Negative::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & Negative::transform(Image &img) const {
    for (int y = 0; y < img.getHeight(); y++) {
        for (int x = 0; x < img.getWidth(); x++) {
            Pixel& pixel = img.pixelAt(x, y);
            pixel.red = static_cast<unsigned char>(255 - pixel.red);
            pixel.green = static_cast<unsigned char>(255 - pixel.green);
            pixel.blue = static_cast<unsigned char>(255 - pixel.blue);
        }
    }

    return img;
}

Transformer * Negative::clone() const {
    return new Negative(*this);
}
