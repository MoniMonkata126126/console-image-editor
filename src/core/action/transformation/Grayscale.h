#ifndef CONSOLE_IMAGE_EDITOR_GRAYSCALE_H
#define CONSOLE_IMAGE_EDITOR_GRAYSCALE_H

#include "../Transformer.h"


class Grayscale : public Transformer{
public:
    Grayscale();

    Grayscale(const Grayscale& other) = default;

    Grayscale& operator=(const Grayscale& other) = default;

    ~Grayscale() override = default;

    void handle(ActionHandler* actionHandler) override;

    Image& transform(Image& img) const override;

    Grayscale* clone() const override;

};


#endif //CONSOLE_IMAGE_EDITOR_GRAYSCALE_H
