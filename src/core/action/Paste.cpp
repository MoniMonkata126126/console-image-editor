#include "Paste.h"

#include "ActionHandler.h"

Paste::Paste() : Action(ActionType::PASTE) {
}

void Paste::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}
