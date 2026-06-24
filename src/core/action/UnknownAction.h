#ifndef CONSOLE_IMAGE_EDITOR_UNKNOWNACTION_H
#define CONSOLE_IMAGE_EDITOR_UNKNOWNACTION_H

#include <string>
#include "Action.h"


class UnknownAction : public Action {
private:
    std::string command;

public:
    explicit UnknownAction(const std::string& command);

    const std::string& getCommand() const;

    void handle(ActionHandler* actionHandler) override;
};


#endif //CONSOLE_IMAGE_EDITOR_UNKNOWNACTION_H
