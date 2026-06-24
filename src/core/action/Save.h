#ifndef CONSOLE_IMAGE_EDITOR_SAVE_H
#define CONSOLE_IMAGE_EDITOR_SAVE_H
#include "Action.h"


class Save : public Action {
public:
    Save();

    Save(const Save& other) = default;

    Save& operator=(const Save& other) = default;

    virtual ~Save() override = default;

    void handle(ActionHandler* actionHandler) override;
};


#endif //CONSOLE_IMAGE_EDITOR_SAVE_H
