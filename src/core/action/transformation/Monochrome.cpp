#include "Monochrome.h"
#include "ActionHandler.h"


static unsigned char grayOf(const Pixel& pixel) {
    return static_cast<unsigned char>((static_cast<int>(pixel.red) +
                                       static_cast<int>(pixel.green) +
                                       static_cast<int>(pixel.blue)) / 3);
}

Monochrome::Monochrome() : Transformer(ActionType::MONOCHROME, true) {
}


void Monochrome::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & Monochrome::transform(Image &img) const {
    if (img.isMonochromeImage()) {
        return img;
    }

    int height = img.getHeight();
    int width = img.getWidth();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char gray = grayOf(img.pixelAt(x, y));
            unsigned char value = gray < 128 ? 0 : 255;
            img.pixelAt(x, y) = Pixel(value, value, value);
        }
    }

    return img;
}

Monochrome * Monochrome::clone() const {
    return new Monochrome(*this);
}
