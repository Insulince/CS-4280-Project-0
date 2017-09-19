#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "EBSTNode.h"
#include "EBST.h"

using namespace std;

static int QUANTITY_DEFAULT_ARGUMENTS = 1;

int main(int quantityCommandLineArguments, char *commandLineArguments[]) {
    int quantityCommandLineArgumentsWithoutDefaultArgument = quantityCommandLineArguments - QUANTITY_DEFAULT_ARGUMENTS;

    if (quantityCommandLineArgumentsWithoutDefaultArgument == 0) {
        auto *tree = new EBST();
        string rawKeyboardData;
        vector<string> keyboardData;
        string keyboardDatum;

        getline(cin, rawKeyboardData);
        istringstream streamedRawKeyboardData = istringstream(rawKeyboardData);

        while (getline(streamedRawKeyboardData, keyboardDatum, ' ')) {
            try {
                keyboardData.push_back(keyboardDatum);
            } catch (invalid_argument &e) { //TODO: Name and implementation
                cout << "Cannot convert string \"" + keyboardDatum + "\" to integer! Ignoring and continuing."
                     << "\n"; //TODO need appropriate name
                return 1; //TODO
            }
        }

        for (auto keyboardDatum : keyboardData) {
            char lastChar = keyboardDatum[keyboardDatum.length() - 1];

            if (tree->digitIsInTreeFromThisNode(lastChar, tree->getRoot())) {
                cout << "\nInserting \"" << lastChar << "\" into already existing node.\n";
                EBSTNode *nodeContainingDigit = tree->nodeContainingDigit(lastChar, tree->getRoot());
                vector<string> matchingStringsInNodeContainingDigit = nodeContainingDigit->getMatchingStrings();
                matchingStringsInNodeContainingDigit.push_back(keyboardDatum);
                nodeContainingDigit->setMatchingStrings(matchingStringsInNodeContainingDigit);
            } else {
                cout << "\nInserting \"" << lastChar << "\" into new node.\n";
                tree->insertNewNodeWithDigit(lastChar, tree->getRoot(), 0);

                EBSTNode *nodeContainingDigit = tree->nodeContainingDigit(lastChar, tree->getRoot());
                vector<string> matchingStringsInNodeContainingDigit = nodeContainingDigit->getMatchingStrings();
                matchingStringsInNodeContainingDigit.push_back(keyboardDatum);
                nodeContainingDigit->setMatchingStrings(matchingStringsInNodeContainingDigit);
            }
        }

        ofstream tempFile;

        string preorderTraversal = tree->toString(PREORDER);
        tempFile.open("out.preorder");
        tempFile << preorderTraversal;
        tempFile.close();
        cout << "PREORDER:\n" << preorderTraversal;

        string inorderTraversal = tree->toString(INORDER);
        tempFile.open("out.inorder");
        tempFile << inorderTraversal;
        tempFile.close();
        cout << "INORDER:\n" << inorderTraversal;

        string postorderTraversal = tree->toString(POSTORDER);
        tempFile.open("out.postorder");
        tempFile << postorderTraversal;
        tempFile.close();
        cout << "POSTORDER:\n" << postorderTraversal;

    } else if (quantityCommandLineArgumentsWithoutDefaultArgument == 1) {
        cout << commandLineArguments[1];
        //TODO
    } else {

    }

    return 0;
}