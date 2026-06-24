#include "Monochrome.h"
#include "ActionHandler.h"
#include "CustomExceptions.h"

static unsigned char grayOf(const Pixel& pixel) {
    return static_cast<unsigned char>((static_cast<int>(pixel.red) +
                                       static_cast<int>(pixel.green) +
                                       static_cast<int>(pixel.blue)) / 3);
}

Monochrome::Monochrome() : Transformer(ActionType::MONOCHROME, true) {
}

Monochrome::Monochrome(ActionType type, bool isFilter) : Transformer(type, isFilter) {
    if (!isFilter) {
        throw CustomExceptions::ACTION_TYPE_IS_FILTER;
    }
}

void Monochrome::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & Monochrome::transform(Image &img) const {
    if (img.isMonochromeImage()) {
        return img;
    }

    for (int y = 0; y < img.getHeight(); y++) {
        for (int x = 0; x < img.getWidth(); x++) {
            unsigned char gray = grayOf(img.pixelAt(x, y));
            unsigned char value = gray < 128 ? 0 : 255;
            img.pixelAt(x, y) = Pixel(value, value, value);
        }
    }

    return img;
}

Transformer * Monochrome::clone() const {
    return new Monochrome(*this);
}
