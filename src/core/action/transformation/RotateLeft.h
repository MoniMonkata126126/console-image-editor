#ifndef CONSOLE_IMAGE_EDITOR_ROTATELEFT_H
#define CONSOLE_IMAGE_EDITOR_ROTATELEFT_H
#include "../Transformer.h"


class RotateLeft : public Transformer{
public:
    RotateLeft(ActionType type, bool isFilter);

    RotateLeft(const RotateLeft& other) = default;

    RotateLeft& operator=(const RotateLeft& other) = default;

    ~RotateLeft() override = default;

    void handle(ActionHandler* actionHandler) override;

    Image& transform(Image& img) const override;
};


#endif //CONSOLE_IMAGE_EDITOR_ROTATELEFT_H
