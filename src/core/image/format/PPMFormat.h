#ifndef CONSOLE_IMAGE_EDITOR_PPMFORMAT_H
#define CONSOLE_IMAGE_EDITOR_PPMFORMAT_H

#include <string>
#include "image/Image.h"

class PPMFormat {
public:
    static bool load(const std::string& path, Image& image, std::string& error);

    static bool save(const Image& image, const std::string& path, std::string& error);
};

#endif //CONSOLE_IMAGE_EDITOR_PPMFORMAT_H
