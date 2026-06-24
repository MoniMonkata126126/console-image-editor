#ifndef CONSOLE_IMAGE_EDITOR_IMAGEFILEHELPER_H
#define CONSOLE_IMAGE_EDITOR_IMAGEFILEHELPER_H

#include <iostream>
#include <string>
#include "image/Image.h"

class ImageFileHelper {
public:
    static bool isSpace(char ch);

    static char toLowerChar(char ch);

    static std::string makeLowercase(const std::string& text);

    static std::string getExtension(const std::string& path);

    static std::string getDirectory(const std::string& path);

    static std::string getFileNameWithoutExtension(const std::string& path);

    static std::string getFullFileName(const std::string& path);

    static int parseNumber(const std::string& token, bool& isValidNumber);

    static bool readToken(std::istream& is, std::string& token);

    static unsigned char normalizeColorValue(int value, int maxValue);

    static unsigned char getGrayValue(const Pixel& pixel);

    static unsigned char readNetpbmColorValue(std::istream& is, int maxValue, bool& isValidNumber);
};

#endif //CONSOLE_IMAGE_EDITOR_IMAGEFILEHELPER_H
