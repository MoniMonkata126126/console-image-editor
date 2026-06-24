#include "Load.h"

#include "ActionHandler.h"


Load::Load(const std::vector<std::string>& filePaths) : Action(ActionType::LOAD), filePaths(filePaths) {
}

const std::vector<std::string>& Load::getFilePaths() const {
    return filePaths;
}

void Load::handle(ActionHandler* actionHandler) {
    actionHandler->handleAction(this);
}
