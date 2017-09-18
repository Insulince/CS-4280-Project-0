#ifndef P0_NODE_H
#define P0_NODE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const static int ROOT_LEVEL = 0;

class EBSTNode {
private:
    const char digit;
    const EBSTNode *parentNode = nullptr;
    const int level;
    EBSTNode *leftChild = nullptr;
    EBSTNode *rightChild = nullptr;
    vector<string> matchingStrings;
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

    const vector<string> &getMatchingStrings() const;

    const void setMatchingStrings(const vector<string> &matchingStrings);

    const string toString() const;
};

#endif //P0_NODE_H
