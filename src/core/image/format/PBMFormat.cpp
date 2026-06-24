#include "image/format/PBMFormat.h"

#include <fstream>
#include <vector>
#include "image/format/ImageFileHelper.h"

bool PBMFormat::load(const std::string& path, Image& image, std::string& error) {
    std::ifstream file(path.c_str(), std::ios::binary);
    if (!file.is_open()) {
        error = "Cannot open PBM file: " + path;
        return false;
    }

    std::string token;
    if (!ImageFileHelper::readToken(file, token)) {
        error = "Empty PBM file: " + path;
        return false;
    }

    bool ascii = true;
    if (token == "P1") {
        ascii = true;
    } else if (token == "P4") {
        ascii = false;
    } else {
        error = "Invalid PBM magic number in: " + path;
        return false;
    }

    bool isValidNumber = false;
    if (!ImageFileHelper::readToken(file, token)) {
        error = "Missing PBM width in: " + path;
        return false;
    }
    int width = ImageFileHelper::parseNumber(token, isValidNumber);
    if (!isValidNumber || width <= 0) {
        error = "Invalid PBM width in: " + path;
        return false;
    }

    if (!ImageFileHelper::readToken(file, token)) {
        error = "Missing PBM height in: " + path;
        return false;
    }
    int height = ImageFileHelper::parseNumber(token, isValidNumber);
    if (!isValidNumber || height <= 0) {
        error = "Invalid PBM height in: " + path;
        return false;
    }

    std::vector<Pixel> pixels;
    pixels.resize(static_cast<size_t>(width * height));

    if (ascii) {
        for (size_t i = 0; i < pixels.size(); i++) {
            if (!ImageFileHelper::readToken(file, token)) {
                error = "Missing PBM pixel data in: " + path;
                return false;
            }

            int value = ImageFileHelper::parseNumber(token, isValidNumber);
            if (!isValidNumber || (value != 0 && value != 1)) {
                error = "Invalid PBM pixel value in: " + path;
                return false;
            }

            unsigned char color = value == 0 ? 255 : 0;
            pixels[i] = Pixel(color, color, color);
        }
    } else {
        int bytesPerRow = (width + 7) / 8;
        std::vector<unsigned char> row(static_cast<size_t>(bytesPerRow));

        for (int y = 0; y < height; y++) {
            file.read(reinterpret_cast<char*>(&row[0]), bytesPerRow);
            if (!file) {
                error = "Invalid binary PBM data in: " + path;
                return false;
            }

            for (int x = 0; x < width; x++) {
                int byteIndex = x / 8;
                int bitIndex = 7 - (x % 8);
                bool black = ((row[static_cast<size_t>(byteIndex)] >> bitIndex) & 1) != 0;
                unsigned char color = black ? 0 : 255;
                pixels[static_cast<size_t>(y * width + x)] = Pixel(color, color, color);
            }
        }
    }

    image.setData(path, ImageFormat::PBM, width, height, 1, pixels);
    return true;
}

bool PBMFormat::save(const Image& image, const std::string& path, std::string& error) {
    std::ofstream file(path.c_str(), std::ios::out);
    if (!file.is_open()) {
        error = "Cannot open output PBM file: " + path;
        return false;
    }

    file << "P1\n" << image.getWidth() << " " << image.getHeight() << "\n";
    for (int y = 0; y < image.getHeight(); y++) {
        for (int x = 0; x < image.getWidth(); x++) {
            const Pixel& pixel = image.pixelAt(x, y);
            file << (ImageFileHelper::getGrayValue(pixel) < 128 ? 1 : 0) << " ";
        }
        file << "\n";
    }

    if (!file.good()) {
        error = "Failed writing PBM file: " + path;
        return false;
    }

    return true;
}
