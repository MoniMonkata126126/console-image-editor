#include "ActionHandler.h"

#include "Application.h"
#include "action/Add.h"
#include "action/Close.h"
#include "action/Load.h"
#include "action/Paste.h"
#include "action/Switch.h"
#include "action/UnknownAction.h"

ActionHandler::ActionHandler(Application *application) : application(application) {
}

ActionHandler::~ActionHandler() {
    application = nullptr;
}

void ActionHandler::handleAction(UnknownAction *unknownAction) {
    this->application->printUnknownCommand(unknownAction->getCommand());
}

void ActionHandler::handleAction(Transformer *transformer) {
    this->application->addTransformationToCurrent(transformer);
}

void ActionHandler::handleAction(Undo *undo) {
    this->application->undoCurrent();
}

void ActionHandler::handleAction(Redo *redo) {
    this->application->redoCurrent();
}

void ActionHandler::handleAction(Add *add) {
    this->application->addImageToCurrent(add->getFilePath());
}

void ActionHandler::handleAction(Paste *paste) {
    this->application->pasteInCurrent(paste->getSourceName(), paste->getDestinationName(), paste->getPosX(), paste->getPosY());
}

void ActionHandler::handleAction(Load *load) {
    this->application->startSession(load->getFilePaths());
}

void ActionHandler::handleAction(Save *save) {
    this->application->saveCurrent();
}

void ActionHandler::handleAction(ListSession *listSession) {
    this->application->listCurrentSession();
}

void ActionHandler::handleAction(Switch *actSwitch) {
    this->application->switchSession(actSwitch->getSessionId());
}

void ActionHandler::handleAction(Close *close) {
    this->application->closeSession(close->getSessionId());
}

void ActionHandler::handleAction(Exit *exit) {
    this->application->exitApplication();
}
