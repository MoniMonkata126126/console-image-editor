#include "RotateLeft.h"

#include "ActionHandler.h"

RotateLeft::RotateLeft(): Transformer(ActionType::ROTATE_LEFT, false) {
}

void RotateLeft::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & RotateLeft::transform(Image &img) const {
    //to do
}
