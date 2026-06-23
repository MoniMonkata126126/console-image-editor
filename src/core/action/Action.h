#ifndef CONSOLE_IMAGE_EDITOR_ACTION_H
#define CONSOLE_IMAGE_EDITOR_ACTION_H

#include "ActionType.h"
#include "ActionHandler.h"

class Action {
private:
    ActionType type;

public:
    explicit Action(ActionType type);

    Action(const Action& other);

    Action& operator=(const Action& other);

    virtual ~Action() = default;

    virtual void handle(ActionHandler* actionHandler) = 0;

};


#endif //CONSOLE_IMAGE_EDITOR_ACTION_H
