#ifndef CONSOLE_IMAGE_EDITOR_PGMFORMAT_H
#define CONSOLE_IMAGE_EDITOR_PGMFORMAT_H

#include <string>
#include "image/Image.h"

class PGMFormat {
public:
    static bool load(const std::string& path, Image& image, std::string& error);

    static bool save(const Image& image, const std::string& path, std::string& error);
};

#endif //CONSOLE_IMAGE_EDITOR_PGMFORMAT_H
