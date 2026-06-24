#include "../Grayscale.h"
#include "ActionHandler.h"
#include "CustomExceptions.h"

Grayscale::Grayscale(ActionType type, bool isFilter) : Transformer(type, isFilter) {
    if (!isFilter) {
        throw CustomExceptions::ACTION_TYPE_IS_FILTER;
    }
}

void Grayscale::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}

Image & Grayscale::transform(Image &img) const {
    //to do
}
