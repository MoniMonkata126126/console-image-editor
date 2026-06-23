#ifndef CONSOLE_IMAGE_EDITOR_ACTIONCONTROLLER_H
#define CONSOLE_IMAGE_EDITOR_ACTIONCONTROLLER_H

#include <string>
#include "ActionParser.h"


class ActionReceiver {
protected:
    ActionParser parser;

    static Action* createAction(std::string parsedAction);

public:
    explicit ActionReceiver(ActionParser parser);

    ActionReceiver(const ActionReceiver& other) = delete;

    ActionReceiver& operator=(const ActionReceiver& other) = delete;

    virtual ~ActionReceiver() = default;

    Action* listen() const;
};


#endif //CONSOLE_IMAGE_EDITOR_ACTIONCONTROLLER_H
