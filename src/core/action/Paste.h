#ifndef CONSOLE_IMAGE_EDITOR_PASTE_H
#define CONSOLE_IMAGE_EDITOR_PASTE_H

#include <string>
#include "Action.h"


class Paste : public Action {
private:
    std::string sourceName;
    std::string destinationName;
    int posX;
    int posY;

public:
    Paste(const std::string& sourceName, const std::string& destinationName, int posX, int posY);

    Paste(const Paste& other) = default;

    Paste& operator=(const Paste& other) = default;

    ~Paste() override = default;

    const std::string& getSourceName() const;

    const std::string& getDestinationName() const;

    int getPosX() const;

    int getPosY() const;

    void handle(ActionHandler* actionHandler) override;
};


#endif //CONSOLE_IMAGE_EDITOR_PASTE_H
