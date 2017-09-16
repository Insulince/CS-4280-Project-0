#ifndef P0_NODE_H
#define P0_NODE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int ROOT = 0;

class EBSTNode {
private:
    int level;
    char digit;
    EBSTNode *parentNode = nullptr;
    EBSTNode *leftChild = nullptr;
    EBSTNode *rightChild = nullptr;
    vector<string> matchingStrings;
public:
    explicit EBSTNode(char digit, EBSTNode *parentNode, int level);

    virtual ~EBSTNode();

    int getLevel() const;

    void setLevel(int level);

    char getDigit() const;

    void setDigit(char digit);

    EBSTNode *getLeftChild() const;

    void setLeftChild(EBSTNode *leftChild);

    EBSTNode *getRightChild() const;

    void setRightChild(EBSTNode *rightChild);

    const vector<string> &getMatchingStrings() const;

    void setMatchingStrings(const vector<string> &matchingStrings);

    EBSTNode *getParentNode() const;

    void setParentNode(EBSTNode *parentNode);

    string toString();
};

#endif //P0_NODE_H
