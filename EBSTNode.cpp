#include "EBSTNode.h"

EBSTNode::EBSTNode(char digit, EBSTNode *parentNode, int level) : digit(digit), parentNode(parentNode), level(level) {
}

EBSTNode::~EBSTNode() = default;

int EBSTNode::getLevel() const {
    return level;
}

void EBSTNode::setLevel(int level) {
    EBSTNode::level = level;
}

char EBSTNode::getDigit() const {
    return digit;
}

void EBSTNode::setDigit(char digit) {
    EBSTNode::digit = digit;
}

EBSTNode *EBSTNode::getLeftChild() const {
    return leftChild;
}

void EBSTNode::setLeftChild(EBSTNode *leftChild) {
    EBSTNode::leftChild = leftChild;
}

EBSTNode *EBSTNode::getRightChild() const {
    return rightChild;
}

void EBSTNode::setRightChild(EBSTNode *rightChild) {
    EBSTNode::rightChild = rightChild;
}

const vector<string> &EBSTNode::getMatchingStrings() const {
    return matchingStrings;
}

void EBSTNode::setMatchingStrings(const vector<string> &matchingStrings) {
    EBSTNode::matchingStrings = matchingStrings;
}

EBSTNode *EBSTNode::getParentNode() const {
    return parentNode;
}

void EBSTNode::setParentNode(EBSTNode *parentNode) {
    EBSTNode::parentNode = parentNode;
}

string EBSTNode::toString() {
    string str = "";

    for (auto i = 0; i < getLevel(); i++) {
        str += "    ";
    }

    for (auto s : getMatchingStrings()) {
        str += s + " ";
    }

    str += "\n";

    if (getLeftChild() != nullptr) {
        str += getLeftChild()->toString();
    }
    if (getRightChild() != nullptr) {
        str += getRightChild()->toString();
    }

    return str;
}

