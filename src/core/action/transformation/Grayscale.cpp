#include "Grayscale.h"
#include "ActionHandler.h"


static unsigned char grayOf(const Pixel& pixel) {
    return static_cast<unsigned char>((static_cast<int>(pixel.red) +
                                       static_cast<int>(pixel.green) +
                                       static_cast<int>(pixel.blue)) / 3);
}

Grayscale::Grayscale() : Transformer(ActionType::GRAYSCALE, true) {
}


void Grayscale::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & Grayscale::transform(Image &img) const {
    if (img.isGrayscaleImage()) {
        return img;
    }

    int height = img.getHeight();
    int width = img.getWidth();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Pixel& pixel = img.pixelAt(x, y);
            unsigned char gray = grayOf(pixel);
            pixel = Pixel(gray, gray, gray);
        }
    }

    return img;
}

Grayscale * Grayscale::clone() const {
    return new Grayscale(*this);
}
