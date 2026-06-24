#include "Add.h"

#include "ActionHandler.h"


Add::Add(const std::string& filePath) : Action(ActionType::ADD), filePath(filePath) {
}

const std::string& Add::getFilePath() const {
    return filePath;
}

void Add::handle(ActionHandler* actionHandler) {
    actionHandler->handleAction(this);
}
