#ifndef CONSOLE_IMAGE_EDITOR_MONOCHROME_H
#define CONSOLE_IMAGE_EDITOR_MONOCHROME_H
#include "action/Transformer.h"


class Monochrome : public Transformer{
public:
    Monochrome();

    Monochrome(const Monochrome& other) = default;

    Monochrome& operator=(const Monochrome& other) = default;

    ~Monochrome() override = default;

    void handle(ActionHandler* actionHandler) override;

    Image& transform(Image& img) const override;
};


#endif //CONSOLE_IMAGE_EDITOR_MONOCHROME_H
