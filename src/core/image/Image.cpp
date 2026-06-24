#include "Image.h"

#include <ctime>
#include "image/format/BMPFormat.h"
#include "image/format/ImageFileHelper.h"
#include "image/format/PBMFormat.h"
#include "image/format/PGMFormat.h"
#include "image/format/PPMFormat.h"

Pixel::Pixel() : red(255), green(255), blue(255) {
}

Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue) : red(red), green(green), blue(blue) {
}

Image::Image() : format(ImageFormat::UNKNOWN), width(0), height(0), maxValue(255) {
}

Image::Image(const std::string& path) : format(ImageFormat::UNKNOWN), width(0), height(0), maxValue(255) {
    std::string error;
    loadFromFile(path, error);
}

bool Image::loadFromFile(const std::string& path, std::string& error) {
    std::string extension = ImageFileHelper::getExtension(path);

    if (extension == "pbm") {
        return PBMFormat::load(path, *this, error);
    }

    if (extension == "pgm") {
        return PGMFormat::load(path, *this, error);
    }

    if (extension == "ppm") {
        return PPMFormat::load(path, *this, error);
    }

    if (extension == "bmp") {
        return BMPFormat::load(path, *this, error);
    }

    error = "Unsupported image format: " + path;
    return false;
}

bool Image::saveToFile(const std::string& path, std::string& error) const {
    if (!getIsLoaded()) {
        error = "Cannot save an empty image";
        return false;
    }

    if (format == ImageFormat::PBM) {
        return PBMFormat::save(*this, path, error);
    }

    if (format == ImageFormat::PGM) {
        return PGMFormat::save(*this, path, error);
    }

    if (format == ImageFormat::PPM) {
        return PPMFormat::save(*this, path, error);
    }

    if (format == ImageFormat::BMP) {
        return BMPFormat::save(*this, path, error);
    }

    error = "Unknown image format";
    return false;
}

bool Image::saveWithTimestamp(std::string& savedPath, std::string& error) const {
    std::string directory = ImageFileHelper::getDirectory(filePath);
    std::string baseName = ImageFileHelper::getFileNameWithoutExtension(filePath);
    std::string extension = ImageFileHelper::getExtension(filePath);

    if (extension.empty()) {
        if (format == ImageFormat::PBM) {
            extension = "pbm";
        } else if (format == ImageFormat::PGM) {
            extension = "pgm";
        } else if (format == ImageFormat::PPM) {
            extension = "ppm";
        } else if (format == ImageFormat::BMP) {
            extension = "bmp";
        }
    }

    char timeText[32] = {};
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    if (localTime != nullptr) {
        std::strftime(timeText, sizeof(timeText), "%Y%m%d_%H%M%S", localTime);
    } else {
        std::string fallback = "modified";
        for (size_t i = 0; i < fallback.size() && i + 1 < sizeof(timeText); i++) {
            timeText[i] = fallback[i];
        }
    }

    savedPath = directory + baseName + "_" + timeText + "." + extension;
    return saveToFile(savedPath, error);
}

const std::string& Image::getFilePath() const {
    return filePath;
}

std::string Image::getFileName() const {
    return ImageFileHelper::getFullFileName(filePath);
}

std::string Image::getNameWithoutExtension() const {
    return ImageFileHelper::getFileNameWithoutExtension(filePath);
}

std::string Image::getFormatName() const {
    if (format == ImageFormat::PBM) {
        return "portable bitmap format";
    }
    if (format == ImageFormat::PGM) {
        return "portable graymap format";
    }
    if (format == ImageFormat::PPM) {
        return "portable pixmap format";
    }
    if (format == ImageFormat::BMP) {
        return "24bit Bitmap";
    }
    return "unknown image format";
}

ImageFormat Image::getFormat() const {
    return format;
}

int Image::getMaxValue() const {
    return maxValue;
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

bool Image::getIsLoaded() const {
    return width > 0 && height > 0 && !pixels.empty();
}

bool Image::isColorImage() const {
    return !isGrayscaleImage();
}

bool Image::isGrayscaleImage() const {
    for (size_t i = 0; i < pixels.size(); i++) {
        if (pixels[i].red != pixels[i].green || pixels[i].green != pixels[i].blue) {
            return false;
        }
    }
    return true;
}

bool Image::isMonochromeImage() const {
    for (size_t i = 0; i < pixels.size(); i++) {
        bool black = pixels[i].red == 0 && pixels[i].green == 0 && pixels[i].blue == 0;
        bool white = pixels[i].red == 255 && pixels[i].green == 255 && pixels[i].blue == 255;
        if (!black && !white) {
            return false;
        }
    }
    return true;
}

bool Image::matchesName(const std::string& name) const {
    return filePath == name || getFileName() == name || getNameWithoutExtension() == name;
}

Pixel& Image::pixelAt(int x, int y) {
    return pixels[static_cast<size_t>(y * width + x)];
}

const Pixel& Image::pixelAt(int x, int y) const {
    return pixels[static_cast<size_t>(y * width + x)];
}

void Image::setData(const std::string& newFilePath,
                    ImageFormat newFormat,
                    int newWidth,
                    int newHeight,
                    int newMaxValue,
                    const std::vector<Pixel>& newPixels) {
    filePath = newFilePath;
    format = newFormat;
    width = newWidth;
    height = newHeight;
    maxValue = newMaxValue;
    pixels = newPixels;
}

void Image::replacePixels(int newWidth, int newHeight, const std::vector<Pixel>& newPixels) {
    width = newWidth;
    height = newHeight;
    pixels = newPixels;
}

bool Image::paste(const Image& source, int posX, int posY, std::string& error) {
    if (posX < 0 || posY < 0) {
        error = "Paste position must be non-negative";
        return false;
    }

    if (!source.getIsLoaded() || !getIsLoaded()) {
        error = "Cannot paste with empty images";
        return false;
    }

    int neededWidth = posX + source.getWidth();
    int neededHeight = posY + source.getHeight();
    int newWidth = neededWidth > width ? neededWidth : width;
    int newHeight = neededHeight > height ? neededHeight : height;

    if (newWidth != width || newHeight != height) {
        std::vector<Pixel> expanded(static_cast<size_t>(newWidth * newHeight), Pixel(255, 255, 255));
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                expanded[static_cast<size_t>(y * newWidth + x)] = pixelAt(x, y);
            }
        }
        pixels = expanded;
        width = newWidth;
        height = newHeight;
    }

    for (int y = 0; y < source.getHeight(); y++) {
        for (int x = 0; x < source.getWidth(); x++) {
            pixelAt(posX + x, posY + y) = source.pixelAt(x, y);
        }
    }

    return true;
}
