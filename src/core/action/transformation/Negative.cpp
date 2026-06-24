#include "Negative.h"

#include "ActionHandler.h"

Negative::Negative() : Transformer(ActionType::NEGATIVE, true) {
}

void Negative::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & Negative::transform(Image &img) const {
    //to do
}
