#ifndef CONSOLE_IMAGE_EDITOR_ROTATERIGHT_H
#define CONSOLE_IMAGE_EDITOR_ROTATERIGHT_H
#include "action/Transformer.h"


class RotateRight : public Transformer {
public:
    RotateRight();

    RotateRight(const RotateRight& other) = default;

    RotateRight& operator=(const RotateRight& other) = default;

    ~RotateRight() override = default;

    void handle(ActionHandler* actionHandler) override;

    Image& transform(Image& img) const override;
};


#endif //CONSOLE_IMAGE_EDITOR_ROTATERIGHT_H
