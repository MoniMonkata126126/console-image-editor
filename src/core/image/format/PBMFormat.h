#ifndef CONSOLE_IMAGE_EDITOR_PBMFORMAT_H
#define CONSOLE_IMAGE_EDITOR_PBMFORMAT_H

#include <string>
#include "image/Image.h"

class PBMFormat {
public:
    static bool load(const std::string& path, Image& image, std::string& error);

    static bool save(const Image& image, const std::string& path, std::string& error);
};

#endif //CONSOLE_IMAGE_EDITOR_PBMFORMAT_H
