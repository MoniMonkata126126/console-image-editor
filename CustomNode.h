//
// Created by simeon on 6/22/26.
//

#ifndef CONSOLE_IMAGE_EDITOR_CUSTOMNODE_H
#define CONSOLE_IMAGE_EDITOR_CUSTOMNODE_H


template <typename T>
class CustomNode {
private:
    T data;
    CustomNode* nextNode;
};


#endif //CONSOLE_IMAGE_EDITOR_CUSTOMNODE_H
