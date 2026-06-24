#include "ActionReceiver.h"

Action * ActionReceiver::createAction(std::string parsedAction) {
}

ActionReceiver::ActionReceiver(ActionParser parser) : parser(parser) {
}

Action * ActionReceiver::listen() const {
}
