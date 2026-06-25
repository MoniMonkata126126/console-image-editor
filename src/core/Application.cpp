#include "Application.h"

#include <iostream>

Application::Application(ActionReceiver *actionReceiver) : actionReceiver(actionReceiver), actionHandler(nullptr),
    currentSession(nullptr), nextSessionId(1), isRunning(true) {
    actionHandler = new ActionHandler(this);
}

Application::~Application() {
    for (size_t i = 0; i < sessions.size(); i++) {
        delete sessions[i];
    }
    sessions.clear();
    currentSession = nullptr;
    delete actionHandler;
    actionHandler = nullptr;
}

void Application::run() {
    while (isRunning) {
        std::cout << "> ";
        Action* action = actionReceiver->listen();
        if (action == nullptr) {
            continue;
        }

        action->handle(actionHandler);
        delete action;
    }
}

Session* Application::findSession(unsigned int sessionId) const {
    for (size_t i = 0; i < sessions.size(); i++) {
        if (sessions[i]->getId() == sessionId) {
            return sessions[i];
        }
    }

    return nullptr;
}

bool Application::askForSave(Session* session) {
    if (session == nullptr || !session->getHasUnsavedWork()) {
        return true;
    }

    std::cout << "Session " << session->getId() << " contains unsaved work. Save it now (y/n)?\n> ";
    std::string answer;
    std::getline(std::cin, answer);

    if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") {
        std::string message;
        bool result = session->save(message);
        std::cout << message;
        return result;
    }

    return true;
}

void Application::printUnknownCommand(const std::string& command) const {
    if (command.empty()) {
        return;
    }
    std::cout << "Unknown command: " << command << "\n";
}

void Application::startSession(const std::vector<std::string>& filePaths) {
    if (filePaths.empty()) {
        std::cout << "Load command requires at least one image file\n";
        return;
    }

    Session* session = new Session(nextSessionId++);
    std::string errors;
    unsigned int loadedCount = 0;

    for (size_t i = 0; i < filePaths.size(); i++) {
        std::string error;
        if (session->addImage(filePaths[i], error)) {
            loadedCount++;
        } else {
            errors += error + "\n";
        }
    }

    if (loadedCount == 0) {
        std::cout << "No images were loaded\n" << errors;
        delete session;
        return;
    }

    sessions.push_back(session);
    currentSession = session;
    std::cout << "Session with ID: " << session->getId() << " started\n";
    if (!errors.empty()) {
        std::cout << errors;
    }
}

void Application::addTransformationToCurrent(const Transformer* transformer) {
    if (currentSession == nullptr) {
        std::cout << "No active session\n";
        return;
    }

    if (currentSession->addTransformation(transformer->clone())) {
        std::cout << "Transformation added\n";
    } else {
        std::cout << "Transformation was not added\n";
    }
}

void Application::addImageToCurrent(const std::string& filePath) const {
    if (currentSession == nullptr) {
        std::cout << "No active session\n";
        return;
    }

    std::string error;
    if (currentSession->addImage(filePath, error)) {
        std::cout << "Image added\n";
    } else {
        std::cout << error << "\n";
    }
}

void Application::undoCurrent() const {
    if (currentSession == nullptr) {
        std::cout << "No active session\n";
        return;
    }

    std::string message;
    currentSession->undo(message);
    std::cout << message;
}

void Application::redoCurrent() const {
    if (currentSession == nullptr) {
        std::cout << "No active session\n";
        return;
    }

    std::string message;
    currentSession->redo(message);
    std::cout << message;
}

void Application::pasteInCurrent(const std::string& sourceName, const std::string& destinationName, int posX, int posY) const {
    if (currentSession == nullptr) {
        std::cout << "No active session\n";
        return;
    }

    std::string message;
    if (currentSession->paste(sourceName, destinationName, posX, posY, message)) {
        std::cout << "Paste completed\n";
    } else {
        std::cout << message << "\n";
    }
}

void Application::saveCurrent() const {
    if (currentSession == nullptr) {
        std::cout << "No active session\n";
        return;
    }

    std::string message;
    currentSession->save(message);
    std::cout << message;
}

void Application::listCurrentSession() const {
    if (currentSession == nullptr) {
        std::cout << "No active session\n";
        return;
    }

    std::string error;
    currentSession->printInfo(std::cout, error);

    if (!error.empty()) {
        std::cerr << error;
    }
}

void Application::switchSession(unsigned int sessionId) {
    Session* session = findSession(sessionId);
    if (session == nullptr) {
        std::cout << "No session with ID: " << sessionId << "\n";
        return;
    }

    currentSession = session;
    std::cout << "Switched to session with ID: " << sessionId << "\n";
}

void Application::closeSession(unsigned int sessionId) {
    for (size_t i = 0; i < sessions.size(); i++) {
        if (sessions[i]->getId() == sessionId) {
            if (!askForSave(sessions[i])) {
                std::cout << "Session was not closed\n";
                return;
            }

            bool isCurrentSession = currentSession != nullptr && currentSession->getId() == sessionId;
            delete sessions[i];
            sessions.erase(sessions.begin() + static_cast<long>(i));
            if (isCurrentSession) {
                currentSession = sessions.empty() ? nullptr : sessions[0];
            }
            std::cout << "Session " << sessionId << " closed\n";
            return;
        }
    }

    std::cout << "No session with ID: " << sessionId << "\n";
}

void Application::exitApplication() {
    for (size_t i = 0; i < sessions.size(); i++) {
        askForSave(sessions[i]);
    }
    isRunning = false;
}
