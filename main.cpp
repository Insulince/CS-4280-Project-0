#include <iostream>
#include <vector>
#include <sstream>
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

        string x = tree->toString();
        cout << endl << "X:\n" << x << endl;

        const int PREORDER = 0;
        const int INORDER = 1;
        const int POSTORDER = 2;
        int traversal = INORDER;
        switch (traversal) {
            case PREORDER:
                break;
            case INORDER:
                break;
            case POSTORDER:
                break;
            default:
                break;
        }
    } else if (quantityCommandLineArgumentsWithoutDefaultArgument == 1) {
        cout << commandLineArguments[1];
        //TODO
    }

    return 0;
}