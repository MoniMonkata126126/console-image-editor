#ifndef CONSOLE_IMAGE_EDITOR_ACTIONHANDLER_H
#define CONSOLE_IMAGE_EDITOR_ACTIONHANDLER_H

#include "action/Transformer.h"

class Application;


class ActionHandler {
protected:
    Application* application;

    explicit ActionHandler(Application* application);

    friend class Application;

public:
    ActionHandler(const ActionHandler& other) = delete;

    ActionHandler& operator=(const ActionHandler& other) = delete;

    virtual ~ActionHandler();

    virtual void handleAction(Transformer* transformer);

    virtual void handleAction(Undo* undo);

    virtual void handleAction(Redo* redo);

    virtual void handleAction(Add* add);

    void handleAction(Paste* paste);

    void handleAction(Load* load);

    void handleAction(Save* save);

    void handleAction(ListSession* listSession);

    void handleAction(Switch* actSwitch);

    void handleAction(Close* close);

    void handleAction(Exit* exit);
};


#endif //CONSOLE_IMAGE_EDITOR_ACTIONHANDLER_H
