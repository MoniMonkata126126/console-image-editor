#ifndef CONSOLE_IMAGE_EDITOR_ACTIONHANDLER_H
#define CONSOLE_IMAGE_EDITOR_ACTIONHANDLER_H

#include "action/Transformer.h"

class Application;
class UnknownAction;
class Undo;
class Redo;
class Add;
class Paste;
class Load;
class Save;
class ListSession;
class Switch;
class Close;
class Exit;


class ActionHandler {
protected:
    Application* application;

    explicit ActionHandler(Application* application);

    friend class Application;

public:
    ActionHandler(const ActionHandler& other) = delete;

    ActionHandler& operator=(const ActionHandler& other) = delete;

    virtual ~ActionHandler();

    virtual void handleAction(UnknownAction* unknownAction);

    virtual void handleAction(Transformer* transformer);

    virtual void handleAction(Undo* undo);

    virtual void handleAction(Redo* redo);

    virtual void handleAction(Add* add);

    virtual void handleAction(Paste* paste);

    virtual void handleAction(Load* load);

    virtual void handleAction(Save* save);

    virtual void handleAction(ListSession* listSession);

    virtual void handleAction(Switch* actSwitch);

    virtual void handleAction(Close* close);

    virtual void handleAction(Exit* exit);
};


#endif //CONSOLE_IMAGE_EDITOR_ACTIONHANDLER_H
