#include "Paste.h"

#include "ActionHandler.h"


Paste::Paste(const std::string& sourceName, const std::string& destinationName, int posX, int posY) :
    Action(ActionType::PASTE), sourceName(sourceName), destinationName(destinationName), posX(posX), posY(posY) {
    if (posX < 0 || posY < 0) {
        throw "Invalid position";
    }
}

const std::string& Paste::getSourceName() const {
    return sourceName;
}

const std::string& Paste::getDestinationName() const {
    return destinationName;
}

int Paste::getPosX() const {
    return posX;
}

int Paste::getPosY() const {
    return posY;
}

void Paste::handle(ActionHandler* actionHandler) {
    actionHandler->handleAction(this);
}
