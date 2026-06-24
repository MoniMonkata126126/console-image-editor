#include "FlipTop.h"

#include "ActionHandler.h"

FlipTop::FlipTop() : Transformer(ActionType::FLIP_TOP, false) {
}

void FlipTop::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & FlipTop::transform(Image &img) const {
    //to do
}
