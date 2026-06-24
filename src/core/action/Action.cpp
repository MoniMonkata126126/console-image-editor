#include "Action.h"

Action::Action(ActionType type) : type(type) {
}

ActionType Action::getType() const {
    return this->type;
}