#ifndef CONSOLE_IMAGE_EDITOR_LOAD_H
#define CONSOLE_IMAGE_EDITOR_LOAD_H
#include "Action.h"


class Load : public Action {
public:
    Load();

    Load(const Load& other) = default;

    Load& operator=(const Load& other) = default;

    virtual ~Load() override = default;

    void handle(ActionHandler* actionHandler) override;
};


#endif //CONSOLE_IMAGE_EDITOR_LOAD_H
