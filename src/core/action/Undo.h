#ifndef CONSOLE_IMAGE_EDITOR_UNDO_H
#define CONSOLE_IMAGE_EDITOR_UNDO_H
#include "Action.h"


class Undo : public Action{
public:
    Undo();

    Undo(const Undo& other) = default;

    Undo& operator=(const Undo& other) = default;

    virtual ~Undo() override = default;

    void handle(ActionHandler* actionHandler) override;
};


#endif //CONSOLE_IMAGE_EDITOR_UNDO_H
