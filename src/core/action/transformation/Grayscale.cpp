#include "Grayscale.h"
#include "ActionHandler.h"
#include "CustomExceptions.h"

static unsigned char grayOf(const Pixel& pixel) {
    return static_cast<unsigned char>((static_cast<int>(pixel.red) +
                                       static_cast<int>(pixel.green) +
                                       static_cast<int>(pixel.blue)) / 3);
}

Grayscale::Grayscale() : Transformer(ActionType::GRAYSCALE, true) {
}

Grayscale::Grayscale(ActionType type, bool isFilter) : Transformer(type, isFilter) {
    if (!isFilter) {
        throw CustomExceptions::ACTION_TYPE_IS_FILTER;
    }
}

void Grayscale::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & Grayscale::transform(Image &img) const {
    if (img.isGrayscaleImage()) {
        return img;
    }

    for (int y = 0; y < img.getHeight(); y++) {
        for (int x = 0; x < img.getWidth(); x++) {
            Pixel& pixel = img.pixelAt(x, y);
            unsigned char gray = grayOf(pixel);
            pixel = Pixel(gray, gray, gray);
        }
    }

    return img;
}

Transformer * Grayscale::clone() const {
    return new Grayscale(*this);
}
