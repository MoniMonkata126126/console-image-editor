#ifndef CONSOLE_IMAGE_EDITOR_NEGATIVE_H
#define CONSOLE_IMAGE_EDITOR_NEGATIVE_H
#include "../Transformer.h"


class Negative : public Transformer{
public:
    Negative(ActionType type, bool isFilter);

    Negative(const Negative& other) = default;

    Negative& operator=(const Negative& other) = default;

    ~Negative() override = default;

    void handle(ActionHandler* actionHandler) override;

    Image& transform(Image& img) const override;
};


#endif //CONSOLE_IMAGE_EDITOR_NEGATIVE_H
