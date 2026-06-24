#include "../Negative.h"

#include "ActionHandler.h"
#include "CustomExceptions.h"

Negative::Negative(ActionType type, bool isFilter) : Transformer(type, isFilter) {
    if (!isFilter) {
        throw CustomExceptions::ACTION_TYPE_IS_FILTER;
    }
}

void Negative::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & Negative::transform(Image &img) const {
    //to do
}
