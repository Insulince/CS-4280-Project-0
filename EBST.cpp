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

bool EBST::digitIsInTreeFromThisNode(int digit, EBSTNode *currentNode) {
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

EBSTNode *EBST::nodeContainingDigit(int digit, EBSTNode *currentNode) {
    if (currentNode == nullptr) {
        return nullptr;
    } else if (currentNode->getDigit() == digit) {
        return currentNode;
    } else if (digit < currentNode->getLeftChild()->getDigit()) {
        return nodeContainingDigit(digit, currentNode->getLeftChild());
    } else {
        return nodeContainingDigit(digit, currentNode->getRightChild());
    }
}

void *EBST::insertNewNodeWithDigit(char digit, EBSTNode *currentNode, int level) {
    if (currentNode == nullptr) {
        EBSTNode *root = new EBSTNode(digit, currentNode, level);
        setRoot(root);
    } else if (digit < currentNode->getDigit()) {
        if (currentNode->getLeftChild() == nullptr) {
            EBSTNode *newNode = new EBSTNode(digit, currentNode, ++level);
            currentNode->setLeftChild(newNode);
        } else {
            insertNewNodeWithDigit(digit, currentNode->getLeftChild(), ++level);
        }
    } else {
        if (currentNode->getRightChild() == nullptr) {
            EBSTNode *newNode = new EBSTNode(digit, currentNode, ++level);
            currentNode->setLeftChild(newNode);
        } else {
            insertNewNodeWithDigit(digit, currentNode->getRightChild(), ++level);
        }
    }
}

string EBST::toString() {
    return std::__cxx11::string();
}
