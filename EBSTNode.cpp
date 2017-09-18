#include "EBSTNode.h"

EBSTNode::EBSTNode(const char digit, const EBSTNode *parentNode, const int level) : digit(digit), parentNode(parentNode), level(level) {
}

EBSTNode::~EBSTNode() = default;

const int EBSTNode::getDigit() const {
    return digit;
}

const EBSTNode *EBSTNode::getParentNode() const {
    return parentNode;
}

const int EBSTNode::getLevel() const {
    return level;
}

EBSTNode *EBSTNode::getLeftChild() const {
    return leftChild;
}

const void EBSTNode::setLeftChild(EBSTNode *leftChild) {
    EBSTNode::leftChild = leftChild;
}

EBSTNode *EBSTNode::getRightChild() const {
    return rightChild;
}

const void EBSTNode::setRightChild(EBSTNode *rightChild) {
    EBSTNode::rightChild = rightChild;
}

const vector<string> &EBSTNode::getMatchingStrings() const {
    return matchingStrings;
}

const void EBSTNode::setMatchingStrings(const vector<string> &matchingStrings) {
    EBSTNode::matchingStrings = matchingStrings;
}

const string EBSTNode::toString() const {
    string str;

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
