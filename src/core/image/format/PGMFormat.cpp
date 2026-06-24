#include "image/format/PGMFormat.h"

#include <fstream>
#include <vector>
#include "image/format/ImageFileHelper.h"

bool PGMFormat::load(const std::string& path, Image& image, std::string& error) {
    std::ifstream file(path.c_str(), std::ios::binary);
    if (!file.is_open()) {
        error = "Cannot open PGM file: " + path;
        return false;
    }

    std::string token;
    if (!ImageFileHelper::readToken(file, token)) {
        error = "Empty PGM file: " + path;
        return false;
    }

    bool ascii = true;
    if (token == "P2") {
        ascii = true;
    } else if (token == "P5") {
        ascii = false;
    } else {
        error = "Invalid PGM magic number in: " + path;
        return false;
    }

    bool isValidNumber = false;
    if (!ImageFileHelper::readToken(file, token)) {
        error = "Missing PGM width in: " + path;
        return false;
    }
    int width = ImageFileHelper::parseNumber(token, isValidNumber);
    if (!isValidNumber || width <= 0) {
        error = "Invalid PGM width in: " + path;
        return false;
    }

    if (!ImageFileHelper::readToken(file, token)) {
        error = "Missing PGM height in: " + path;
        return false;
    }
    int height = ImageFileHelper::parseNumber(token, isValidNumber);
    if (!isValidNumber || height <= 0) {
        error = "Invalid PGM height in: " + path;
        return false;
    }

    if (!ImageFileHelper::readToken(file, token)) {
        error = "Missing PGM max color value in: " + path;
        return false;
    }
    int maxValue = ImageFileHelper::parseNumber(token, isValidNumber);
    if (!isValidNumber || maxValue <= 0 || maxValue > 65535) {
        error = "Invalid PGM max color value in: " + path;
        return false;
    }

    std::vector<Pixel> pixels;
    pixels.resize(static_cast<size_t>(width * height));

    if (ascii) {
        for (size_t i = 0; i < pixels.size(); i++) {
            if (!ImageFileHelper::readToken(file, token)) {
                error = "Missing PGM pixel data in: " + path;
                return false;
            }

            int value = ImageFileHelper::parseNumber(token, isValidNumber);
            if (!isValidNumber || value < 0 || value > maxValue) {
                error = "Invalid PGM pixel value in: " + path;
                return false;
            }

            unsigned char gray = ImageFileHelper::normalizeColorValue(value, maxValue);
            pixels[i] = Pixel(gray, gray, gray);
        }
    } else {
        for (size_t i = 0; i < pixels.size(); i++) {
            unsigned char gray = ImageFileHelper::readNetpbmColorValue(file, maxValue, isValidNumber);
            if (!isValidNumber) {
                error = "Invalid binary PGM data in: " + path;
                return false;
            }
            pixels[i] = Pixel(gray, gray, gray);
        }
    }

    image.setData(path, ImageFormat::PGM, width, height, maxValue, pixels);
    return true;
}

bool PGMFormat::save(const Image& image, const std::string& path, std::string& error) {
    std::ofstream file(path.c_str(), std::ios::out);
    if (!file.is_open()) {
        error = "Cannot open output PGM file: " + path;
        return false;
    }

    file << "P2\n" << image.getWidth() << " " << image.getHeight() << "\n255\n";
    for (int y = 0; y < image.getHeight(); y++) {
        for (int x = 0; x < image.getWidth(); x++) {
            file << static_cast<int>(ImageFileHelper::getGrayValue(image.pixelAt(x, y))) << " ";
        }
        file << "\n";
    }

    if (!file.good()) {
        error = "Failed writing PGM file: " + path;
        return false;
    }

    return true;
}
