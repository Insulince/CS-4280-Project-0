#include "EBST.h"

using namespace std;

EBST::EBST() = default;

EBST::~EBST() = default;

EBSTNode *EBST::getRoot() const {
    return root;
}

const void EBST::setRoot(EBSTNode *root) {
    EBST::root = root;
}

const int EBST::getHeight() const {
    return height;
}

const void EBST::setHeight(const int height) {
    EBST::height = height;
}

const bool EBST::digitIsInTreeFromThisNode(const char digit, const EBSTNode *currentNode) const {
    if (currentNode == nullptr) {
        return false;
    } else if (currentNode->getDigit() == digit) {
        return true;
    } else if (digit < currentNode->getDigit()) {
        return digitIsInTreeFromThisNode(digit, currentNode->getLeftChild());
    } else {
        return digitIsInTreeFromThisNode(digit, currentNode->getRightChild());
    }
}

EBSTNode *EBST::nodeContainingDigit(const char digit, EBSTNode *currentNode) const {
    if (currentNode == nullptr) {
        return nullptr;
    } else if (currentNode->getDigit() == digit) {
        return currentNode;
    } else if (digit < currentNode->getDigit()) {
        return nodeContainingDigit(digit, currentNode->getLeftChild());
    } else {
        return nodeContainingDigit(digit, currentNode->getRightChild());
    }
}

const void *EBST::insertNewNodeWithDigit(const char digit, EBSTNode *currentNode, const int level) {
    if (currentNode == nullptr) {
        setRoot(new EBSTNode(digit, nullptr, ROOT_LEVEL));
    } else if (digit < currentNode->getDigit()) {
        if (currentNode->getLeftChild() == nullptr) {
            auto *newNode = new EBSTNode(digit, currentNode, level + 1);
            currentNode->setLeftChild(newNode);
        } else {
            insertNewNodeWithDigit(digit, currentNode->getLeftChild(), level + 1);
        }
    } else {
        if (currentNode->getRightChild() == nullptr) {
            auto *newNode = new EBSTNode(digit, currentNode, level + 1);
            currentNode->setRightChild(newNode);
        } else {
            insertNewNodeWithDigit(digit, currentNode->getRightChild(), level + 1);
        }
    }
}

const string EBST::toString(const TRAVERSAL traversal) const {
    return getRoot()->toString(traversal);
}
