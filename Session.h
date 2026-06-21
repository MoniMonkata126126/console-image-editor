//
// Created by simeon on 6/22/26.
//

#ifndef CONSOLE_IMAGE_EDITOR_SESSION_H
#define CONSOLE_IMAGE_EDITOR_SESSION_H

#include "CustomVector.h"
#include "CustomQueue.h"
#include "Transformation.h"
#include "Image.h"


class Session {
private:
    CustomVector<Transformation*> transformations;
    CustomQueue<Transformation*> undoneTransformations;
    CustomVector<Image*> images;
};


#endif //CONSOLE_IMAGE_EDITOR_SESSION_H
