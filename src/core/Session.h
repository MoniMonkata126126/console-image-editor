#ifndef CONSOLE_IMAGE_EDITOR_SESSION_H
#define CONSOLE_IMAGE_EDITOR_SESSION_H

#include <vector>
#include "Transformation.h"
#include "CustomQueue.h"
#include "Image.h"


class Session {
private:
    std::vector<Transformation*> transformations;
    CustomQueue<Transformation*> undoneTransformations;
    std::vector<Image*> images;
};


#endif //CONSOLE_IMAGE_EDITOR_SESSION_H
