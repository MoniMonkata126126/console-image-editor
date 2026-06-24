#include "FlipLeft.h"

#include "ActionHandler.h"

FlipLeft::FlipLeft() : Transformer(ActionType::FLIP_LEFT, false) {
}

void FlipLeft::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & FlipLeft::transform(Image &img) const {
    //to do
}
