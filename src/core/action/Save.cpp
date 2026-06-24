#include "Save.h"

#include "ActionHandler.h"


Save::Save() : Action(ActionType::SAVE) {
}

void Save::handle(ActionHandler* actionHandler) {
    actionHandler->handleAction(this);
}
