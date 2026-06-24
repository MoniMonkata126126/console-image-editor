#ifndef CONSOLE_IMAGE_EDITOR_FLIPTOP_H
#define CONSOLE_IMAGE_EDITOR_FLIPTOP_H
#include "../Transformer.h"


class FlipTop : public Transformer {
public:
    FlipTop(ActionType type, bool isFilter);

    FlipTop(const FlipTop& other) = default;

    FlipTop& operator=(const FlipTop& other) = default;

    ~FlipTop() override = default;

    void handle(ActionHandler* actionHandler) override;

    Image& transform(Image& img) const override;
};


#endif //CONSOLE_IMAGE_EDITOR_FLIPTOP_H
