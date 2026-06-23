#ifndef CONSOLE_IMAGE_EDITOR_ACTIONHANDLER_H
#define CONSOLE_IMAGE_EDITOR_ACTIONHANDLER_H


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

    virtual void handleTransformation();

    virtual void handleUndo();

    virtual void handleRedo();

    virtual void handleAdd();

    void handlePaste();

    void handleLoad();

    void handleSave();

    void handleListSession();

    void handleSwitch();

    void handleClose();

    void handleExit();
};


#endif //CONSOLE_IMAGE_EDITOR_ACTIONHANDLER_H
