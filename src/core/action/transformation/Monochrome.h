#ifndef CONSOLE_IMAGE_EDITOR_MONOCHROME_H
#define CONSOLE_IMAGE_EDITOR_MONOCHROME_H
#include "../Transformer.h"


class Monochrome : public Transformer{
public:
    Monochrome();

    Monochrome(ActionType type, bool isFilter);

    Monochrome(const Monochrome& other) = default;

    Monochrome& operator=(const Monochrome& other) = default;

    ~Monochrome() override = default;

    void handle(ActionHandler* actionHandler) override;

    Image& transform(Image& img) const override;

    Transformer* clone() const override;
};


#endif //CONSOLE_IMAGE_EDITOR_MONOCHROME_H
