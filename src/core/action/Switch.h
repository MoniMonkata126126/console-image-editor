#ifndef CONSOLE_IMAGE_EDITOR_SWITCH_H
#define CONSOLE_IMAGE_EDITOR_SWITCH_H

#include "Action.h"


class Switch : public Action {
private:
    unsigned int sessionId;

public:
    explicit Switch(unsigned int sessionId);

    unsigned int getSessionId() const;

    void handle(ActionHandler* actionHandler) override;
};


#endif //CONSOLE_IMAGE_EDITOR_SWITCH_H
