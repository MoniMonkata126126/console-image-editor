#ifndef CONSOLE_IMAGE_EDITOR_APPLICATION_H
#define CONSOLE_IMAGE_EDITOR_APPLICATION_H

#include <vector>
#include <string>
#include "ActionReceiver.h"
#include "ActionHandler.h"
#include "Session.h"


class Application {
private:
    ActionReceiver* actionReceiver;
    ActionHandler* actionHandler;
    std::vector<Session*> sessions;
    Session* currentSession;
    unsigned int nextSessionId;
    bool isRunning;

    friend class ActionHandler;

    Session* findSession(unsigned int sessionId) const;

    bool askForSave(Session* session);

public:
    explicit Application(ActionReceiver* actionReceiver);

    Application(const Application& other) = delete;

    Application& operator=(const Application& other) = delete;

    ~Application();

    void run();

    void printUnknownCommand(const std::string& command) const;

    void startSession(const std::vector<std::string>& filePaths);

    void addTransformationToCurrent(const Transformer* transformer);

    void addImageToCurrent(const std::string& filePath) const;

    void undoCurrent() const;

    void redoCurrent() const;

    void pasteInCurrent(const std::string& sourceName, const std::string& destinationName, int posX, int posY) const;

    void saveCurrent() const;

    void listCurrentSession() const;

    void switchSession(unsigned int sessionId);

    void closeSession(unsigned int sessionId);

    void exitApplication();

};


#endif //CONSOLE_IMAGE_EDITOR_APPLICATION_H
