#ifndef CONSOLE_IMAGE_EDITOR_PASTE_H
#define CONSOLE_IMAGE_EDITOR_PASTE_H
#include "Action.h"


class Paste : public Action {
public:
    Paste();

    Paste(const Paste& other) = default;

    Paste& operator=(const Paste& other) = default;

    virtual ~Paste() override = default;

    void handle(ActionHandler* actionHandler) override;
};


#endif //CONSOLE_IMAGE_EDITOR_PASTE_H
