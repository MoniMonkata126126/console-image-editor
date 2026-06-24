#ifndef CONSOLE_IMAGE_EDITOR_EXIT_H
#define CONSOLE_IMAGE_EDITOR_EXIT_H

#include "Action.h"


class Exit : public Action {
public:
    Exit();

    void handle(ActionHandler* actionHandler) override;
};


#endif //CONSOLE_IMAGE_EDITOR_EXIT_H
