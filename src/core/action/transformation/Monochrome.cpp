#include "../Monochrome.h"
#include "ActionHandler.h"
#include "CustomExceptions.h"

Monochrome::Monochrome(ActionType type, bool isFilter) : Transformer(type, isFilter) {
    if (!isFilter) {
        throw CustomExceptions::ACTION_TYPE_IS_FILTER;
    }
}

void Monochrome::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & Monochrome::transform(Image &img) const {
    //to do
}
