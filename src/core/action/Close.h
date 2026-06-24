#ifndef CONSOLE_IMAGE_EDITOR_CLOSE_H
#define CONSOLE_IMAGE_EDITOR_CLOSE_H

#include "Action.h"


class Close : public Action {
private:
    unsigned int sessionId;

public:
    explicit Close(unsigned int sessionId);

    unsigned int getSessionId() const;

    void handle(ActionHandler* actionHandler) override;
};


#endif //CONSOLE_IMAGE_EDITOR_CLOSE_H
