#ifndef CONSOLE_IMAGE_EDITOR_ERROR_H
#define CONSOLE_IMAGE_EDITOR_ERROR_H

#include <string>
#include <action/Action.h>

class Error {
private:
    std::string errorMessage;

public:
    explicit Error(std::string error);

    explicit Error(Action* action);

    Error(const Error& other) = default;

    Error& operator=(const Error& other) = default;

    Error(Error&& other) = default;

    Error& operator=(Error&& other) = default;

    const std::string& getErrorMessage() const;
};

#endif //CONSOLE_IMAGE_EDITOR_ERROR_H
