#include "Monochrome.h"
#include "ActionHandler.h"

Monochrome::Monochrome() : Transformer(ActionType::MONOCHROME, true) {
}

void Monochrome::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & Monochrome::transform(Image &img) const {
    //to do
}
