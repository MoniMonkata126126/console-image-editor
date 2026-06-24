#ifndef CONSOLE_IMAGE_EDITOR_ACTION_H
#define CONSOLE_IMAGE_EDITOR_ACTION_H

#include "ActionType.h"

class ActionHandler;

class Action {
private:
    ActionType type;

public:
    explicit Action(ActionType type);

    Action(const Action& other) = default;

    Action& operator=(const Action& other) = default;

    virtual ~Action() = default;

    ActionType getType() const;

    virtual void handle(ActionHandler* actionHandler) = 0;

};


#endif //CONSOLE_IMAGE_EDITOR_ACTION_H
