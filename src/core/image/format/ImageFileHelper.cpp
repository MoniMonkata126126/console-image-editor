#include "image/format/ImageFileHelper.h"

#include <cstdlib>

bool ImageFileHelper::isSpace(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || ch == '\v' || ch == '\f';
}

char ImageFileHelper::toLowerChar(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return static_cast<char>(ch - 'A' + 'a');
    }
    return ch;
}

std::string ImageFileHelper::makeLowercase(const std::string& text) {
    std::string result = text;
    for (size_t i = 0; i < result.size(); i++) {
        result[i] = toLowerChar(result[i]);
    }
    return result;
}

std::string ImageFileHelper::getExtension(const std::string& path) {
    size_t slashPos = path.find_last_of("/\\");
    size_t dotPos = path.find_last_of('.');

    if (dotPos == std::string::npos || (slashPos != std::string::npos && dotPos < slashPos)) {
        return std::string{};
    }

    return makeLowercase(path.substr(dotPos + 1));
}

std::string ImageFileHelper::getDirectory(const std::string& path) {
    size_t slashPos = path.find_last_of("/\\");
    if (slashPos == std::string::npos) {
        return std::string{};
    }
    return path.substr(0, slashPos + 1);
}

std::string ImageFileHelper::getFileNameWithoutExtension(const std::string& path) {
    size_t slashPos = path.find_last_of("/\\");
    size_t start = slashPos == std::string::npos ? 0 : slashPos + 1;
    size_t dotPos = path.find_last_of('.');

    if (dotPos == std::string::npos || dotPos < start) {
        return path.substr(start);
    }

    return path.substr(start, dotPos - start);
}

std::string ImageFileHelper::getFullFileName(const std::string& path) {
    size_t slashPos = path.find_last_of("/\\");
    if (slashPos == std::string::npos) {
        return path;
    }
    return path.substr(slashPos + 1);
}

int ImageFileHelper::parseNumber(const std::string& token, bool& isValidNumber) {
    char* endPtr = nullptr;
    long value = std::strtol(token.c_str(), &endPtr, 10);
    isValidNumber = token.size() > 0 && endPtr != nullptr && *endPtr == '\0';
    return static_cast<int>(value);
}

bool ImageFileHelper::readToken(std::istream& is, std::string& token) {
    token.clear();
    char ch;

    while (is.get(ch)) {
        if (isSpace(ch)) {
            continue;
        }

        if (ch == '#') {
            while (is.get(ch) && ch != '\n') {
            }
            continue;
        }

        token += ch;
        break;
    }

    while (is.get(ch)) {
        if (isSpace(ch)) {
            break;
        }

        if (ch == '#') {
            while (is.get(ch) && ch != '\n') {
            }
            break;
        }

        token += ch;
    }

    return !token.empty();
}

unsigned char ImageFileHelper::normalizeColorValue(int value, int maxValue) {
    if (maxValue <= 0) {
        return 0;
    }

    if (value < 0) {
        value = 0;
    }

    if (value > maxValue) {
        value = maxValue;
    }

    return static_cast<unsigned char>((value * 255) / maxValue);
}

unsigned char ImageFileHelper::getGrayValue(const Pixel& pixel) {
    return static_cast<unsigned char>((static_cast<int>(pixel.red) +
                                       static_cast<int>(pixel.green) +
                                       static_cast<int>(pixel.blue)) / 3);
}

unsigned char ImageFileHelper::readNetpbmColorValue(std::istream& is, int maxValue, bool& isValidNumber) {
    isValidNumber = false;

    if (maxValue <= 255) {
        unsigned char value = 0;
        is.read(reinterpret_cast<char*>(&value), 1);
        isValidNumber = static_cast<bool>(is);
        return normalizeColorValue(static_cast<int>(value), maxValue);
    }

    unsigned char high = 0;
    unsigned char low = 0;
    is.read(reinterpret_cast<char*>(&high), 1);
    is.read(reinterpret_cast<char*>(&low), 1);
    isValidNumber = static_cast<bool>(is);

    int value = (static_cast<int>(high) << 8) | static_cast<int>(low);
    return normalizeColorValue(value, maxValue);
}
