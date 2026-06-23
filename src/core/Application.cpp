#include "Application.h"

Application::Application(ActionReceiver *actionReceiver) : actionReceiver(actionReceiver), actionHandler(nullptr),
    currentSession(nullptr) {
    actionHandler = new ActionHandler(this);
    
}

Application::~Application() {
}

void Application::run() {
}
