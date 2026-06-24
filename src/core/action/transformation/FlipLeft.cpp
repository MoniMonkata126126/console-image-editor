#include "../FlipLeft.h"

#include "ActionHandler.h"
#include "CustomExceptions.h"

FlipLeft::FlipLeft(ActionType type, bool isFilter) : Transformer(type, isFilter) {
    if (isFilter) {
        throw CustomExceptions::ACTION_TYPE_NOT_FILTER;
    }
}

void FlipLeft::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & FlipLeft::transform(Image &img) const {
    //to do
}
