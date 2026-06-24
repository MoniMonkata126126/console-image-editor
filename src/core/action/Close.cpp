#include "Close.h"

#include "ActionHandler.h"


Close::Close(unsigned int sessionId) : Action(ActionType::CLOSE), sessionId(sessionId) {
}

unsigned int Close::getSessionId() const {
    return sessionId;
}

void Close::handle(ActionHandler* actionHandler) {
    actionHandler->handleAction(this);
}
