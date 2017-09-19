#ifndef P0_NODE_H
#define P0_NODE_H

#include <iostream>
#include <string>
#include <vector>
#include "traversals.h"

const static int ROOT_LEVEL = 0;

class EBSTNode {
private:
    const char digit;
    const EBSTNode *parentNode = nullptr;
    const int level;
    EBSTNode *leftChild = nullptr;
    EBSTNode *rightChild = nullptr;
    std::vector<std::string> matchingStrings;
public:
    EBSTNode(const char digit, const EBSTNode *parentNode, const int level);

    ~EBSTNode();

    const int getDigit() const;

    const EBSTNode *getParentNode() const;

    const int getLevel() const;

    EBSTNode *getLeftChild() const;

    const void setLeftChild(EBSTNode *leftChild);

    EBSTNode *getRightChild() const;

    const void setRightChild(EBSTNode *rightChild);

    const std::vector<std::string> &getMatchingStrings() const;

    const void setMatchingStrings(const std::vector<std::string> &matchingStrings);

    const std::string toString(const TRAVERSAL traversal) const;

    const std::string processMatchingStrings() const;

    const std::string processLeftChildsMatchingStrings(const TRAVERSAL traversal) const;

    const std::string processRightChildsMatchingStrings(const TRAVERSAL traversal) const;
};

#endif //P0_NODE_H
