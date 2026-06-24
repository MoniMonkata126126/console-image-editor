#include "Grayscale.h"
#include "ActionHandler.h"

Grayscale::Grayscale() : Transformer(ActionType::GRAYSCALE, true) {
}

void Grayscale::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & Grayscale::transform(Image &img) const {
    //to do
}
