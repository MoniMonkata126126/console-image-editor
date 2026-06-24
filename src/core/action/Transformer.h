#ifndef CONSOLE_IMAGE_EDITOR_TRANSFORMER_H
#define CONSOLE_IMAGE_EDITOR_TRANSFORMER_H

#include "Action.h"
#include "image/Image.h"

class Transformer : public Action{
protected:
    bool isFilter;

public:
    Transformer(ActionType type, bool isFilter);

    Transformer(const Transformer& other) = default;

    Transformer& operator=(const Transformer& other) = default;

    virtual ~Transformer() override = default;

    virtual Image& transform(Image& img) const = 0;

    bool getIsFilter() const;
};


#endif //CONSOLE_IMAGE_EDITOR_TRANSFORMER_H
