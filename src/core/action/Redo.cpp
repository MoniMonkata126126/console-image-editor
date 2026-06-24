#include "Redo.h"

#include "ActionHandler.h"

Redo::Redo() : Action(ActionType::REDO) {
}

void Redo::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}
