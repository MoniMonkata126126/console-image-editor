#include "../RotateLeft.h"

#include "ActionHandler.h"
#include "CustomExceptions.h"

RotateLeft::RotateLeft(ActionType type, bool isFilter): Transformer(type, isFilter) {
    if (isFilter) {
        throw CustomExceptions::ACTION_TYPE_NOT_FILTER;
    }
}

void RotateLeft::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & RotateLeft::transform(Image &img) const {
    //to do
}
