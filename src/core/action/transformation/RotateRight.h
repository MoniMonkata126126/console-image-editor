#ifndef CONSOLE_IMAGE_EDITOR_ROTATERIGHT_H
#define CONSOLE_IMAGE_EDITOR_ROTATERIGHT_H
#include "../Transformer.h"


class RotateRight : public Transformer {
public:
    RotateRight();

    RotateRight(ActionType type, bool isFilter);

    RotateRight(const RotateRight& other) = default;

    RotateRight& operator=(const RotateRight& other) = default;

    ~RotateRight() override = default;

    void handle(ActionHandler* actionHandler) override;

    Image& transform(Image& img) const override;

    Transformer* clone() const override;
};


#endif //CONSOLE_IMAGE_EDITOR_ROTATERIGHT_H
