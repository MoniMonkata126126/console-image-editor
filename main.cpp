#include <iostream>
#include <string>
#include "receive/ConsoleActionParser.h"
#include "Error.h"


int main() {

    const ConsoleActionParser parser;

    const std::string str = parser.deserializeAction();

    ConsoleActionParser::serializeError(std::cout, Error(str));

    return 0;
}