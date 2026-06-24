#ifndef CONSOLE_IMAGE_EDITOR_ADD_H
#define CONSOLE_IMAGE_EDITOR_ADD_H

#include <string>
#include "Action.h"


class Add : public Action{
private:
    std::string filePath;

public:
    explicit Add(const std::string& filePath);

    Add(const Add& other) = default;

    Add& operator=(const Add& other) = default;

    ~Add() override = default;

    const std::string& getFilePath() const;

    void handle(ActionHandler* actionHandler) override;
};


#endif //CONSOLE_IMAGE_EDITOR_ADD_H
