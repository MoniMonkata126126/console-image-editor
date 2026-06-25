#include "image/format/BMPFormat.h"

#include <fstream>
#include <vector>

/*
 * I have used Gemini during the writing process of the Image format classes but this one in particular.
 * I needed it because I felt like I was always missing and forgetting some details about the image format,
 * especially the format having multiple different variations of the format ( the header specifically )
 * I believe not every variation is covered in the code as I have not intended to grant support for very old formats.
 */

static unsigned short readTwoByteNumber(std::istream& is) {
    unsigned char bytes[2] = {};
    is.read(reinterpret_cast<char*>(bytes), 2);
    return static_cast<unsigned short>(bytes[0] | (bytes[1] << 8));
}

static unsigned int readFourByteNumber(std::istream& is) {
    unsigned char bytes[4] = {};
    is.read(reinterpret_cast<char*>(bytes), 4);
    return static_cast<unsigned int>(bytes[0] |
                                     (bytes[1] << 8) |
                                     (bytes[2] << 16) |
                                     (bytes[3] << 24));
}

static int readSignedFourByteNumber(std::istream& is) {
    return static_cast<int>(readFourByteNumber(is));
}

static void writeTwoByteNumber(std::ostream& os, unsigned short value) {
    unsigned char bytes[2];
    bytes[0] = static_cast<unsigned char>(value & 255);
    bytes[1] = static_cast<unsigned char>((value >> 8) & 255);
    os.write(reinterpret_cast<const char*>(bytes), 2);
}

static void writeFourByteNumber(std::ostream& os, unsigned int value) {
    unsigned char bytes[4];
    bytes[0] = static_cast<unsigned char>(value & 255);
    bytes[1] = static_cast<unsigned char>((value >> 8) & 255);
    bytes[2] = static_cast<unsigned char>((value >> 16) & 255);
    bytes[3] = static_cast<unsigned char>((value >> 24) & 255);
    os.write(reinterpret_cast<const char*>(bytes), 4);
}

bool BMPFormat::load(const std::string& path, Image& image, std::string& error) {
    std::ifstream file(path.c_str(), std::ios::binary);
    if (!file.is_open()) {
        error = "Cannot open BMP file: " + path;
        return false;
    }

    char signature[2] = {};
    file.read(signature, 2);
    if (!file || signature[0] != 'B' || signature[1] != 'M') {
        error = "Invalid BMP signature in: " + path;
        return false;
    }

    readFourByteNumber(file);
    readTwoByteNumber(file);
    readTwoByteNumber(file);
    unsigned int pixelDataStart = readFourByteNumber(file);
    unsigned int bitmapHeaderSize = readFourByteNumber(file);
    if (bitmapHeaderSize < 40) {
        error = "Unsupported BMP header in: " + path;
        return false;
    }

    int width = readSignedFourByteNumber(file);
    int storedHeight = readSignedFourByteNumber(file);
    unsigned short colorPlanes = readTwoByteNumber(file);
    unsigned short bitsPerPixel = readTwoByteNumber(file);
    unsigned int compressionType = readFourByteNumber(file);
    readFourByteNumber(file);
    readFourByteNumber(file);
    readFourByteNumber(file);
    readFourByteNumber(file);
    readFourByteNumber(file);

    if (colorPlanes != 1 || compressionType != 0 || (bitsPerPixel != 24 && bitsPerPixel != 32)) {
        error = "Only uncompressed 24bit and 32bit BMP files are supported: " + path;
        return false;
    }

    if (width <= 0 || storedHeight == 0) {
        error = "Invalid BMP dimensions in: " + path;
        return false;
    }

    bool isStoredTopDown = storedHeight < 0;
    int height = isStoredTopDown ? -storedHeight : storedHeight;
    int bytesPerPixel = bitsPerPixel / 8;
    int bytesPerRow = ((width * bitsPerPixel + 31) / 32) * 4;

    std::vector<Pixel> pixels;
    pixels.resize(static_cast<size_t>(width * height));

    file.seekg(static_cast<std::streamoff>(pixelDataStart), std::ios::beg);
    std::vector<unsigned char> row(static_cast<size_t>(bytesPerRow));
    for (int currentFileRow = 0; currentFileRow < height; currentFileRow++) {
        file.read(reinterpret_cast<char*>(&row[0]), bytesPerRow);
        if (!file) {
            error = "Invalid BMP pixel data in: " + path;
            return false;
        }

        int y = isStoredTopDown ? currentFileRow : height - 1 - currentFileRow;
        for (int x = 0; x < width; x++) {
            int pixelByteIndex = x * bytesPerPixel;
            pixels[static_cast<size_t>(y * width + x)] = Pixel(row[static_cast<size_t>(pixelByteIndex + 2)],
                                                               row[static_cast<size_t>(pixelByteIndex + 1)],
                                                               row[static_cast<size_t>(pixelByteIndex)]);
        }
    }

    image.setData(path, ImageFormat::BMP, width, height, 255, pixels);
    return true;
}

bool BMPFormat::save(const Image& image, const std::string& path, std::string& error) {
    std::ofstream file(path.c_str(), std::ios::binary);
    if (!file.is_open()) {
        error = "Cannot open output BMP file: " + path;
        return false;
    }

    int width = image.getWidth();
    int height = image.getHeight();
    int bytesPerRow = ((width * 24 + 31) / 32) * 4;
    unsigned int pixelDataByteCount = static_cast<unsigned int>(bytesPerRow * height);
    unsigned int fileByteCount = 54 + pixelDataByteCount;

    file.put('B');
    file.put('M');
    writeFourByteNumber(file, fileByteCount);
    writeTwoByteNumber(file, 0);
    writeTwoByteNumber(file, 0);
    writeFourByteNumber(file, 54);
    writeFourByteNumber(file, 40);
    writeFourByteNumber(file, static_cast<unsigned int>(width));
    writeFourByteNumber(file, static_cast<unsigned int>(height));
    writeTwoByteNumber(file, 1);
    writeTwoByteNumber(file, 24);
    writeFourByteNumber(file, 0);
    writeFourByteNumber(file, pixelDataByteCount);
    writeFourByteNumber(file, 2835);
    writeFourByteNumber(file, 2835);
    writeFourByteNumber(file, 0);
    writeFourByteNumber(file, 0);

    std::vector<unsigned char> row(static_cast<size_t>(bytesPerRow), 0);
    for (int y = height - 1; y >= 0; y--) {
        for (int i = 0; i < bytesPerRow; i++) {
            row[static_cast<size_t>(i)] = 0;
        }

        for (int x = 0; x < width; x++) {
            const Pixel& pixel = image.pixelAt(x, y);
            int pixelByteIndex = x * 3;
            row[static_cast<size_t>(pixelByteIndex)] = pixel.blue;
            row[static_cast<size_t>(pixelByteIndex + 1)] = pixel.green;
            row[static_cast<size_t>(pixelByteIndex + 2)] = pixel.red;
        }
        file.write(reinterpret_cast<const char*>(&row[0]), bytesPerRow);
    }

    if (!file.good()) {
        error = "Failed writing BMP file: " + path;
        return false;
    }

    return true;
}
