#ifndef CONSOLE_IMAGE_EDITOR_IMAGE_H
#define CONSOLE_IMAGE_EDITOR_IMAGE_H

#include <string>
#include <vector>

enum class ImageFormat : char {
    UNKNOWN = -1,
    PBM,
    PGM,
    PPM,
    BMP
};

struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    Pixel();

    Pixel(unsigned char red, unsigned char green, unsigned char blue);
};

class Image {
private:
    std::string filePath;
    ImageFormat format;
    int width;
    int height;
    int maxValue;
    std::vector<Pixel> pixels;

public:
    Image();

    explicit Image(const std::string& path);

    bool loadFromFile(const std::string& path, std::string& error);

    bool saveToFile(const std::string& path, std::string& error) const;

    bool saveWithTimestamp(std::string& savedPath, std::string& error) const;

    const std::string& getFilePath() const;

    std::string getFileName() const;

    std::string getNameWithoutExtension() const;

    std::string getFormatName() const;

    ImageFormat getFormat() const;

    int getMaxValue() const;

    int getWidth() const;

    int getHeight() const;

    bool getIsLoaded() const;

    bool isColorImage() const;

    bool isGrayscaleImage() const;

    bool isMonochromeImage() const;

    bool matchesName(const std::string& name) const;

    Pixel& pixelAt(int x, int y);

    const Pixel& pixelAt(int x, int y) const;

    void setData(const std::string& newFilePath,
                 ImageFormat newFormat,
                 int newWidth,
                 int newHeight,
                 int newMaxValue,
                 const std::vector<Pixel>& newPixels);

    void replacePixels(int newWidth, int newHeight, const std::vector<Pixel>& newPixels);

    bool paste(const Image& source, int posX, int posY, std::string& error);

};


#endif //CONSOLE_IMAGE_EDITOR_IMAGE_H
