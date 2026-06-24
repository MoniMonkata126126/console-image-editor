#include "ActionHandler.h"

#include "Application.h"

ActionHandler::ActionHandler(Application *application) : application(application) {
}

ActionHandler::~ActionHandler() {
    application = nullptr;
}

void ActionHandler::handleAction(Transformer *transformer) {
    this->application->currentSession->addTransformation(transformer);
}
