#include "../RotateRight.h"

#include "ActionHandler.h"
#include "CustomExceptions.h"

RotateRight::RotateRight(ActionType type, bool isFilter) : Transformer(type, isFilter) {
    if (isFilter) {
        throw CustomExceptions::ACTION_TYPE_NOT_FILTER;
    }
}

void RotateRight::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & RotateRight::transform(Image &img) const {
    //to do
}
