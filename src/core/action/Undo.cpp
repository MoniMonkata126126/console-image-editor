#include "Undo.h"

#include "ActionHandler.h"


Undo::Undo() : Action(ActionType::UNDO) {
}

void Undo::handle(ActionHandler* actionHandler) {
    actionHandler->handleAction(this);
}
