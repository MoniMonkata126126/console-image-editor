#ifndef CONSOLE_IMAGE_EDITOR_APPLICATION_H
#define CONSOLE_IMAGE_EDITOR_APPLICATION_H

#include <vector>
#include "ActionReceiver.h"
#include "ActionHandler.h"
#include "Session.h"


class Application {
private:
    ActionReceiver* actionReceiver;
    ActionHandler* actionHandler;
    std::vector<Session*> sessions;
    Session* currentSession;

    friend class ActionHandler;

public:
    explicit Application(ActionReceiver* actionReceiver);

    Application(const Application& other) = delete;

    Application& operator=(const Application& other) = delete;

    ~Application();

    void run();

};


#endif //CONSOLE_IMAGE_EDITOR_APPLICATION_H
