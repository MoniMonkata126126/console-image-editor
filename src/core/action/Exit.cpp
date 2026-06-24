#include "Exit.h"

#include "ActionHandler.h"


Exit::Exit() : Action(ActionType::EXIT) {
}

void Exit::handle(ActionHandler* actionHandler) {
    actionHandler->handleAction(this);
}
