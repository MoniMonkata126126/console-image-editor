#ifndef CONSOLE_IMAGE_EDITOR_SESSION_H
#define CONSOLE_IMAGE_EDITOR_SESSION_H

#include <vector>
#include "action/Action.h"
#include "CustomQueue.h"
#include "image/Image.h"


class Session {
private:
    std::vector<Action*> transformations;
    CustomQueue<Action*> undoneTransformations;
    std::vector<Image*> images;
};


#endif //CONSOLE_IMAGE_EDITOR_SESSION_H
