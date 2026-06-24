#ifndef CONSOLE_IMAGE_EDITOR_ADD_H
#define CONSOLE_IMAGE_EDITOR_ADD_H
#include "Action.h"


class Add : public Action{
public:
    Add();

    Add(const Add& other) = default;

    Add& operator=(const Add& other) = default;

    virtual ~Add() override = default;

    void handle(ActionHandler* actionHandler) override;

};


#endif //CONSOLE_IMAGE_EDITOR_ADD_H
