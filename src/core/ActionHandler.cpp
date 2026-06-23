#include "ActionHandler.h"

ActionHandler::ActionHandler(Application *application) : application(application) {
}

ActionHandler::~ActionHandler() {
    application = nullptr;
}

void ActionHandler::handleTransformation() {
}

void ActionHandler::handleUndo() {
}

void ActionHandler::handleRedo() {
}

void ActionHandler::handleAdd() {
}

void ActionHandler::handlePaste() {
}

void ActionHandler::handleLoad() {
}

void ActionHandler::handleSave() {
}

void ActionHandler::handleListSession() {
}

void ActionHandler::handleSwitch() {
}

void ActionHandler::handleClose() {
}

void ActionHandler::handleExit() {
}
