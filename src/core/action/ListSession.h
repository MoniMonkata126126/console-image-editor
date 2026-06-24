#ifndef CONSOLE_IMAGE_EDITOR_LISTSESSION_H
#define CONSOLE_IMAGE_EDITOR_LISTSESSION_H

#include "Action.h"


class ListSession : public Action {
public:
    ListSession();

    void handle(ActionHandler* actionHandler) override;
};


#endif //CONSOLE_IMAGE_EDITOR_LISTSESSION_H
