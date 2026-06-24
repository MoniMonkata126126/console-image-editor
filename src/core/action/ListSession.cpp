#include "ListSession.h"

#include "ActionHandler.h"


ListSession::ListSession() : Action(ActionType::LIST_SESSION) {
}

void ListSession::handle(ActionHandler* actionHandler) {
    actionHandler->handleAction(this);
}
