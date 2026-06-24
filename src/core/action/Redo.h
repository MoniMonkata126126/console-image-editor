#ifndef CONSOLE_IMAGE_EDITOR_REDO_H
#define CONSOLE_IMAGE_EDITOR_REDO_H

#include "Action.h"


class Redo : public Action {
public:
    Redo();

    Redo(const Redo& other) = default;

    Redo& operator=(const Redo& other) = default;

    ~Redo() override = default;

    void handle(ActionHandler* actionHandler) override;
};


#endif //CONSOLE_IMAGE_EDITOR_REDO_H
