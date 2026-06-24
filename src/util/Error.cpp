#include "Error.h"

Error::Error(const std::string& error) {
    this->errorMessage = error;
}

Error::Error(const Action *action) {
    switch (action->getType()) {
        case ActionType::UNKNOWN:
            this->errorMessage = "Unknown action";
            break;
        case ActionType::GRAYSCALE:
            this->errorMessage = "Grayscale";
            break;
        case ActionType::MONOCHROME:
            this->errorMessage = "Monochrome";
            break;
        case ActionType::NEGATIVE:
            this->errorMessage = "Negative";
            break;
        case ActionType::ROTATE_RIGHT:
            this->errorMessage = "Rotate right";
            break;
        case ActionType::ROTATE_LEFT:
            this->errorMessage = "Rotate left";
            break;
        case ActionType::FLIP_TOP:
            this->errorMessage = "Flip top";
            break;
        case ActionType::FLIP_LEFT:
            this->errorMessage = "Flip left";
            break;
        case ActionType::UNDO:
            this->errorMessage = "Undo";
            break;
        case ActionType::REDO:
            this->errorMessage = "Redo";
            break;
        case ActionType::ADD:
            this->errorMessage = "Add";
            break;
        case ActionType::PASTE:
            this->errorMessage = "Paste";
            break;
        case ActionType::LOAD:
            this->errorMessage = "Load";
            break;
        case ActionType::SAVE:
            this->errorMessage = "Save";
            break;
        case ActionType::LIST_SESSION:
            this->errorMessage = "List session";
            break;
        case ActionType::SWITCH:
            this->errorMessage = "Switch";
            break;
        case ActionType::CLOSE:
            this->errorMessage = "Close";
            break;
        case ActionType::EXIT:
            this->errorMessage = "Exit";
            break;
        default:
            this->errorMessage = "";
            break;
    }
}

const std::string& Error::getErrorMessage() const {
    return this->errorMessage;
}
