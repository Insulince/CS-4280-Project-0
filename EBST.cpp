#include "EBST.h"

EBST::EBST() = default;

EBST::~EBST() = default;

EBSTNode *EBST::getRoot() const {
    return root;
}

void EBST::setRoot(EBSTNode *root) {
    EBST::root = root;
}

int EBST::getHeight() const {
    return height;
}

void EBST::setHeight(int height) {
    EBST::height = height;
}

bool EBST::digitIsInTreeFromThisNode(char digit, EBSTNode *currentNode) {
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

EBSTNode *EBST::nodeContainingDigit(char digit, EBSTNode *currentNode) {
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

void *EBST::insertNewNodeWithDigit(char digit, EBSTNode *currentNode, int level) {
    if (currentNode == nullptr) {
        auto *root = new EBSTNode(digit, nullptr, level);
        setRoot(root);
    } else if (digit < currentNode->getDigit()) {
        if (currentNode->getLeftChild() == nullptr) {
            auto *newNode = new EBSTNode(digit, currentNode, ++level);
            currentNode->setLeftChild(newNode);
        } else {
            insertNewNodeWithDigit(digit, currentNode->getLeftChild(), ++level);
        }
    } else {
        if (currentNode->getRightChild() == nullptr) {
            auto *newNode = new EBSTNode(digit, currentNode, ++level);
            currentNode->setRightChild(newNode);
        } else {
            insertNewNodeWithDigit(digit, currentNode->getRightChild(), ++level);
        }
    }
}

string EBST::toString() {
    return getRoot()->toString();
}
