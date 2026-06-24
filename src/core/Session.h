#ifndef CONSOLE_IMAGE_EDITOR_SESSION_H
#define CONSOLE_IMAGE_EDITOR_SESSION_H

#include <vector>
#include "action/Transformer.h"
#include "CustomQueue.h"
#include "image/Image.h"


class Session {
private:
    std::vector<Transformer*> transformations;
    CustomQueue<Transformer*> undoneTransforms;
    std::vector<Image*> images;

public:
    bool addTransformation(Transformer* transformer);
};


#endif //CONSOLE_IMAGE_EDITOR_SESSION_H
