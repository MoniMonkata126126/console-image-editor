#ifndef CONSOLE_IMAGE_EDITOR_FLIPLEFT_H
#define CONSOLE_IMAGE_EDITOR_FLIPLEFT_H
#include "../Transformer.h"


class FlipLeft : public Transformer {
public:
    FlipLeft();

    FlipLeft(ActionType type, bool isFilter);

    FlipLeft(const FlipLeft& other) = default;

    FlipLeft& operator=(const FlipLeft& other) = default;

    ~FlipLeft() override = default;

    void handle(ActionHandler* actionHandler) override;

    Image& transform(Image& img) const override;

    Transformer* clone() const override;
};


#endif //CONSOLE_IMAGE_EDITOR_FLIPLEFT_H
