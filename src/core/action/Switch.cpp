#include "Switch.h"

#include "ActionHandler.h"


Switch::Switch(unsigned int sessionId) : Action(ActionType::SWITCH), sessionId(sessionId) {
}

unsigned int Switch::getSessionId() const {
    return sessionId;
}

void Switch::handle(ActionHandler* actionHandler) {
    actionHandler->handleAction(this);
}
