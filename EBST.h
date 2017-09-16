#ifndef P0_EBST_H
#define P0_EBST_H

#include "EBSTNode.h"

class EBST {
private:
    EBSTNode *root = nullptr;
    int height;
public:
    explicit EBST();

    virtual ~EBST();

    EBSTNode *getRoot() const;

    void setRoot(EBSTNode *root);

    int getHeight() const;

    void setHeight(int height);

    bool digitIsInTreeFromThisNode(char digit, EBSTNode *currentNode);

    EBSTNode *nodeContainingDigit(char digit, EBSTNode *currentNode);

    void *insertNewNodeWithDigit(char digit, EBSTNode *currentNode, int level);

    string toString();
};

#endif //P0_EBST_H
