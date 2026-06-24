#include "UnknownAction.h"

#include "ActionHandler.h"


UnknownAction::UnknownAction(const std::string& command) : Action(ActionType::UNKNOWN), command(command) {
}

const std::string& UnknownAction::getCommand() const {
    return command;
}

void UnknownAction::handle(ActionHandler* actionHandler) {
    actionHandler->handleAction(this);
}
