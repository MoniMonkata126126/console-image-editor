#include "ActionParser.h"

#include <iostream>

ActionParser::ActionParser(std::istream &is) : is(is) {
}

std::string ActionParser::deserializeAction() const {
    std::string line;

    std::getline(this->is, line);

    if (this->is.eof() || this->is.fail()) {
        if (this->is.eof()) {
            std::cerr << "Failed reading: End of file reached\n";
        }
        else
            std::cerr << "Failed reading: Command too long\n";
        this->is.clear();
        return std::string{};
    }

    if (line.size() > 100) {
        std::cout << "Invalid Command: Command too long";
        return std::string{};
    }

    return line;
}

bool ActionParser::serializeAction(std::ostream &os, const Action& action) {
    switch (action.getType()) {
        case ActionType::UNKNOWN:
            os << "Unknown action";
            break;
        case ActionType::GRAYSCALE:
            os << "Grayscale";
            break;
        case ActionType::MONOCHROME:
            os << "Monochrome";
            break;
        case ActionType::NEGATIVE:
            os << "Negative";
            break;
        case ActionType::ROTATE_RIGHT:
            os << "Rotate right";
            break;
        case ActionType::ROTATE_LEFT:
            os << "Rotate left";
            break;
        case ActionType::FLIP_TOP:
            os << "Flip top";
            break;
        case ActionType::FLIP_LEFT:
            os << "Flip left";
            break;
        case ActionType::UNDO:
            os << "Undo";
            break;
        case ActionType::REDO:
            os << "Redo";
            break;
        case ActionType::ADD:
            os << "Add";
            break;
        case ActionType::PASTE:
            os << "Paste";
            break;
        case ActionType::LOAD:
            os << "Load";
            break;
        case ActionType::SAVE:
            os << "Save";
            break;
        case ActionType::LIST_SESSION:
            os << "List session";
            break;
        case ActionType::SWITCH:
            os << "Switch";
            break;
        case ActionType::CLOSE:
            os << "Close";
            break;
        case ActionType::EXIT:
            os << "Exit";
            break;
        case ActionType::ACTION_COUNT:
            os << "Action count: " << static_cast<int>(ActionType::ACTION_COUNT);
            break;
    }

    if (os.good())
        return true;
    os.clear();
    return false;
}

bool ActionParser::serializeError(std::ostream &os, const Error& error) {
    os << error.getErrorMessage();
    if (os.good())
        return true;
    os.clear();
    return false;
}
