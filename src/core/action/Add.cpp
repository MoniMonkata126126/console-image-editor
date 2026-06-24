#include "Add.h"

#include "ActionHandler.h"

Add::Add() : Action(ActionType::ADD) {
}

void Add::handle(ActionHandler *actionHandler) {
    actionHandler->handleAction(this);
}
