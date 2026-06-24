#include "Transformer.h"
#include "CustomExceptions.h"


Transformer::Transformer(ActionType type, bool isFilter) : Action(type), isFilter(isFilter) {
    int actionType = static_cast<int>(type);

    if (actionType < 0 || actionType > 6) {
        throw CustomExceptions::INCOMPATIBLE_ACTION_TYPES;
    }

    if (actionType > 2 && isFilter) {
        throw CustomExceptions::ACTION_TYPE_NOT_FILTER;
    }
}

bool Transformer::getIsFilter() const {
    return this->isFilter;
}
