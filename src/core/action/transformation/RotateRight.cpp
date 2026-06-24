#include "RotateRight.h"

#include "ActionHandler.h"


RotateRight::RotateRight() : Transformer(ActionType::ROTATE_RIGHT, false) {
}

void RotateRight::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & RotateRight::transform(Image &img) const {
    //to do
}
