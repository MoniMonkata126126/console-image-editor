//
// Created by simeon on 6/24/26.
//

#include "../FlipTop.h"

#include "ActionHandler.h"
#include "CustomExceptions.h"

FlipTop::FlipTop(ActionType type, bool isFilter) : Transformer(type, isFilter) {
    if (isFilter) {
        throw CustomExceptions::ACTION_TYPE_NOT_FILTER;
    }
}

void FlipTop::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & FlipTop::transform(Image &img) const {
    //to do
}
