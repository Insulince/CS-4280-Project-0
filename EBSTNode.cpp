#include "EBSTNode.h"

using namespace std;

EBSTNode::EBSTNode(const char digit, const EBSTNode *parentNode, const int level) : digit(digit),
                                                                                    parentNode(parentNode),
                                                                                    level(level) {
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

const string EBSTNode::toString(const TRAVERSAL traversal) const { //TODO: Implement traversals here
    string output = "";

    switch (traversal) {
        case PREORDER:
            output += processMatchingStrings();
            output += processLeftChildsMatchingStrings(traversal);
            output += processRightChildsMatchingStrings(traversal);
            break;
        case INORDER:
            output += processLeftChildsMatchingStrings(traversal);
            output += processMatchingStrings();
            output += processRightChildsMatchingStrings(traversal);
            break;
        case POSTORDER:
            output += processLeftChildsMatchingStrings(traversal);
            output += processRightChildsMatchingStrings(traversal);
            output += processMatchingStrings();
            break;
        default:
            break;
    }

    return output;
}

const string EBSTNode::processMatchingStrings() const {
    const string TAB = "   ";
    string output = "";

    for (auto i = 0; i < getLevel(); i++) {
        output += TAB;
    }

    for (const auto &matchingString : getMatchingStrings()) {
        output += matchingString + " ";
    }

    output += "\n";

    return output;
}

const string EBSTNode::processLeftChildsMatchingStrings(const TRAVERSAL traversal) const {
    string output = "";

    if (getLeftChild() != nullptr) {
        output += getLeftChild()->toString(traversal);
    }

    return output;
}

const string EBSTNode::processRightChildsMatchingStrings(const TRAVERSAL traversal) const {
    string output = "";

    if (getRightChild() != nullptr) {
        output += getRightChild()->toString(traversal);
    }

    return output;
}