#ifndef P0_EBST_H
#define P0_EBST_H

#include "EBSTNode.h"

class EBST {
private:
    EBSTNode *root = nullptr;
    int height;
public:
    EBST();

    ~EBST();

    EBSTNode *getRoot() const;

    const void setRoot(EBSTNode *root);

    const int getHeight() const;

    const void setHeight(const int height);

    const bool digitIsInTreeFromThisNode(const char digit, const EBSTNode *currentNode) const;

    EBSTNode *nodeContainingDigit(const char digit, EBSTNode *currentNode) const;

    const void *insertNewNodeWithDigit(const char digit, EBSTNode *currentNode, const int level);

    const std::string toString(const TRAVERSAL traversal) const;
};

#endif //P0_EBST_H
