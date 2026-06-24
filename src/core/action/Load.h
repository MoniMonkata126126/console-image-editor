#ifndef CONSOLE_IMAGE_EDITOR_LOAD_H
#define CONSOLE_IMAGE_EDITOR_LOAD_H

#include <string>
#include <vector>
#include "Action.h"


class Load : public Action {
private:
    std::vector<std::string> filePaths;

public:
    explicit Load(const std::vector<std::string>& filePaths);

    Load(const Load& other) = default;

    Load& operator=(const Load& other) = default;

    ~Load() override = default;

    const std::vector<std::string>& getFilePaths() const;

    void handle(ActionHandler* actionHandler) override;
};


#endif //CONSOLE_IMAGE_EDITOR_LOAD_H
