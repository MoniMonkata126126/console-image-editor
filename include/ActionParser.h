#ifndef CONSOLE_IMAGE_EDITOR_ACTIONPARSER_H
#define CONSOLE_IMAGE_EDITOR_ACTIONPARSER_H

#include <iostream>
#include "Error.h"

class ActionParser {
private:
    std::istream& is;

public:
    explicit ActionParser(std::istream& is);

    ActionParser(const ActionParser& other) = default;

    ActionParser& operator=(const ActionParser& other) = delete;

    ~ActionParser() = default;

    std::string deserializeAction() const;

    static bool serializeAction(std::ostream& os, const Action& action);

    static bool serializeError(std::ostream& os, const Error& error);

};


#endif //CONSOLE_IMAGE_EDITOR_ACTIONPARSER_H
