//
// Created by simeon on 6/22/26.
//

#ifndef CONSOLE_IMAGE_EDITOR_CUSTOMVECTOR_H
#define CONSOLE_IMAGE_EDITOR_CUSTOMVECTOR_H

#include <utility>

template <typename T>
class CustomVector {
private:
    T* data;
    std::size_t size;
    std::size_t capacity;

    void resize();

public:
    CustomVector();

    explicit CustomVector(std::size_t capacity);

    CustomVector(const T* data, std::size_t size);

    CustomVector(const CustomVector& other);

    CustomVector(CustomVector&& other) noexcept;

    CustomVector& operator=(const CustomVector& other);

    CustomVector& operator=(CustomVector&& other) noexcept;

    const T& operator[](std::size_t index) const;

    void pushBack(const T& newData);

    T* popBack(std::size_t index);
};


#endif //CONSOLE_IMAGE_EDITOR_CUSTOMVECTOR_H
