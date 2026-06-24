#include "image/format/PPMFormat.h"

#include <fstream>
#include <vector>
#include "image/format/ImageFileHelper.h"

bool PPMFormat::load(const std::string& path, Image& image, std::string& error) {
    std::ifstream file(path.c_str(), std::ios::binary);
    if (!file.is_open()) {
        error = "Cannot open PPM file: " + path;
        return false;
    }

    std::string token;
    if (!ImageFileHelper::readToken(file, token)) {
        error = "Empty PPM file: " + path;
        return false;
    }

    bool ascii = true;
    if (token == "P3") {
        ascii = true;
    } else if (token == "P6") {
        ascii = false;
    } else {
        error = "Invalid PPM magic number in: " + path;
        return false;
    }

    bool isValidNumber = false;
    if (!ImageFileHelper::readToken(file, token)) {
        error = "Missing PPM width in: " + path;
        return false;
    }
    int width = ImageFileHelper::parseNumber(token, isValidNumber);
    if (!isValidNumber || width <= 0) {
        error = "Invalid PPM width in: " + path;
        return false;
    }

    if (!ImageFileHelper::readToken(file, token)) {
        error = "Missing PPM height in: " + path;
        return false;
    }
    int height = ImageFileHelper::parseNumber(token, isValidNumber);
    if (!isValidNumber || height <= 0) {
        error = "Invalid PPM height in: " + path;
        return false;
    }

    if (!ImageFileHelper::readToken(file, token)) {
        error = "Missing PPM max color value in: " + path;
        return false;
    }
    int maxValue = ImageFileHelper::parseNumber(token, isValidNumber);
    if (!isValidNumber || maxValue <= 0 || maxValue > 65535) {
        error = "Invalid PPM max color value in: " + path;
        return false;
    }

    std::vector<Pixel> pixels;
    pixels.resize(static_cast<size_t>(width * height));

    if (ascii) {
        for (size_t i = 0; i < pixels.size(); i++) {
            int values[3];
            for (int j = 0; j < 3; j++) {
                if (!ImageFileHelper::readToken(file, token)) {
                    error = "Missing PPM pixel data in: " + path;
                    return false;
                }

                values[j] = ImageFileHelper::parseNumber(token, isValidNumber);
                if (!isValidNumber || values[j] < 0 || values[j] > maxValue) {
                    error = "Invalid PPM pixel value in: " + path;
                    return false;
                }
            }

            pixels[i] = Pixel(ImageFileHelper::normalizeColorValue(values[0], maxValue),
                              ImageFileHelper::normalizeColorValue(values[1], maxValue),
                              ImageFileHelper::normalizeColorValue(values[2], maxValue));
        }
    } else {
        for (size_t i = 0; i < pixels.size(); i++) {
            unsigned char red = ImageFileHelper::readNetpbmColorValue(file, maxValue, isValidNumber);
            if (!isValidNumber) {
                error = "Invalid binary PPM red channel in: " + path;
                return false;
            }

            unsigned char green = ImageFileHelper::readNetpbmColorValue(file, maxValue, isValidNumber);
            if (!isValidNumber) {
                error = "Invalid binary PPM green channel in: " + path;
                return false;
            }

            unsigned char blue = ImageFileHelper::readNetpbmColorValue(file, maxValue, isValidNumber);
            if (!isValidNumber) {
                error = "Invalid binary PPM blue channel in: " + path;
                return false;
            }

            pixels[i] = Pixel(red, green, blue);
        }
    }

    image.setData(path, ImageFormat::PPM, width, height, maxValue, pixels);
    return true;
}

bool PPMFormat::save(const Image& image, const std::string& path, std::string& error) {
    std::ofstream file(path.c_str(), std::ios::out);
    if (!file.is_open()) {
        error = "Cannot open output PPM file: " + path;
        return false;
    }

    file << "P3\n" << image.getWidth() << " " << image.getHeight() << "\n255\n";
    for (int y = 0; y < image.getHeight(); y++) {
        for (int x = 0; x < image.getWidth(); x++) {
            const Pixel& pixel = image.pixelAt(x, y);
            file << static_cast<int>(pixel.red) << " "
                 << static_cast<int>(pixel.green) << " "
                 << static_cast<int>(pixel.blue) << " ";
        }
        file << "\n";
    }

    if (!file.good()) {
        error = "Failed writing PPM file: " + path;
        return false;
    }

    return true;
}
