#include "ActionParser.h"

ActionParser::ActionParser(std::istream &is) : is(is) {
}

std::string ActionParser::deserializeAction() {
}

bool ActionParser::serializeAction(std::ostream &os, Action *action) {
}

bool ActionParser::serializeAction(std::ostream &os, Error *error) {
}
