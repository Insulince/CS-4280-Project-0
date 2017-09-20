#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "EBSTNode.h"
#include "EBST.h"

using namespace std;

const static int EXIT_CODE_ILLEGAL_QUANTITY_ARGUMENTS = 1;
const static char *ERROR_MESSAGE_ILLEGAL_QUANTITY_ARGUMENTS = "Invalid quantity of command line arguments encountered, pass either zero arguments for keyboard input, or one argument for file input.";

const static int QUANTITY_DEFAULT_ARGUMENTS = 1;

const static char *KEYBOARD_MODE_OUTPUT_FILE_NAME = "out";
const static char *IMPLICIT_INPUT_FILE_EXTENSION = ".fs17";
const static char *PREORDER_OUTPUT_FILE_EXTENSION = ".preorder";
const static char *INORDER_OUTPUT_FILE_EXTENSION = ".inorder";
const static char *POSTORDER_OUTPUT_FILE_EXTENSION = ".postorder";

bool noArgumentsPassed(int quantityCommandLineArgumentsWithoutDefaultArgument);

void runForKeyboardInput();

bool oneArgumentPassed(int quantityCommandLineArgumentsWithoutDefaultArgument);

void runForFileInput(char *const *commandLineArguments);

string getRawKeyboardData();

void processData(const string &rawData, const string &fileName);

string getRawInputFileData(const string &inputFileName);

vector<string> getDataVectorFromRawData(const string &rawData);

EBST *buildTreeFromDataVector(const vector<string> &dataVector);

void writeTraversalFiles(const EBST *tree, const string &outputFileName);

istringstream streamRawData(const string &rawData);

vector<string> getDataVectorFromStreamedRawData(istringstream &streamedRawData);

void addDatumToTreeNode(const EBST *tree, const string &datum, char lastCharInDatum);

void addNewNodeToTree(EBST *tree, char lastCharInDatum);

void writePreorderTraversalFile(const EBST *tree, const string &outputFileName);

void writeInorderTraversalFile(const EBST *tree, const string &outputFileName);

void writePostorderTraversalFile(const EBST *tree, const string &outputFileName);

int main(int quantityCommandLineArguments, char *commandLineArguments[]) {
    int quantityCommandLineArgumentsWithoutDefaultArgument = quantityCommandLineArguments - QUANTITY_DEFAULT_ARGUMENTS;

    if (noArgumentsPassed(quantityCommandLineArgumentsWithoutDefaultArgument)) {
        runForKeyboardInput();
    } else if (oneArgumentPassed(quantityCommandLineArgumentsWithoutDefaultArgument)) {
        runForFileInput(commandLineArguments);
    } else {
        cout << ERROR_MESSAGE_ILLEGAL_QUANTITY_ARGUMENTS << endl;
        return EXIT_CODE_ILLEGAL_QUANTITY_ARGUMENTS;
    }

    return 0;
}

bool noArgumentsPassed(int quantityCommandLineArgumentsWithoutDefaultArgument) {
    return quantityCommandLineArgumentsWithoutDefaultArgument == 0;
}

void runForKeyboardInput() {
    string rawKeyboardData = getRawKeyboardData();
    processData(rawKeyboardData, KEYBOARD_MODE_OUTPUT_FILE_NAME);
}

string getRawKeyboardData() {
    string rawKeyboardData;

    getline(cin, rawKeyboardData);

    return rawKeyboardData;
}

bool oneArgumentPassed(int quantityCommandLineArgumentsWithoutDefaultArgument) {
    return quantityCommandLineArgumentsWithoutDefaultArgument == 1;
}

void runForFileInput(char *const *commandLineArguments) {
    string inputFileName = commandLineArguments[1];
    string rawInputFileData = getRawInputFileData(inputFileName);
    processData(rawInputFileData, inputFileName);
}

string getRawInputFileData(const string &inputFileName) {
    ifstream inputFile;
    string rawInputFileData;

    inputFile.open(inputFileName + IMPLICIT_INPUT_FILE_EXTENSION);
    getline(inputFile, rawInputFileData);
    inputFile.close();

    return rawInputFileData;
}

void processData(const string &rawData, const string &fileName) {
    vector<string> dataVector = getDataVectorFromRawData(rawData);
    EBST *tree = buildTreeFromDataVector(dataVector);
    writeTraversalFiles(tree, fileName);
}

vector<string> getDataVectorFromRawData(const string &rawData) {
    istringstream streamedRawData = streamRawData(rawData);
    vector<string> dataVector = getDataVectorFromStreamedRawData(streamedRawData);

    return dataVector;
}

istringstream streamRawData(const string &rawData) {
    return istringstream(rawData);
}

vector<string> getDataVectorFromStreamedRawData(istringstream &streamedRawData) {
    vector<string> data;
    string datum;

    while (getline(streamedRawData, datum, ' ')) {
        data.push_back(datum);
    }

    return data;
}

EBST *buildTreeFromDataVector(const vector<string> &dataVector) {
    auto *tree = new EBST();

    for (auto datum : dataVector) {
        char lastCharInDatum = datum[datum.length() - 1];

        if (tree->digitIsInTreeFromThisNode(lastCharInDatum, tree->getRoot())) {
            addDatumToTreeNode(tree, datum, lastCharInDatum);
        } else {
            addNewNodeToTree(tree, lastCharInDatum);
            addDatumToTreeNode(tree, datum, lastCharInDatum);
        }
    }

    return tree;
}

void addNewNodeToTree(EBST *tree, char lastCharInDatum) {
    tree->insertNewNodeWithDigit(lastCharInDatum, tree->getRoot(), 0);
}

void addDatumToTreeNode(const EBST *tree, const string &datum, char lastCharInDatum) {
    EBSTNode *nodeContainingDigit = tree->nodeContainingDigit(lastCharInDatum, tree->getRoot());
    vector<string> matchingStringsInNodeContainingDigit = nodeContainingDigit->getMatchingStrings();
    matchingStringsInNodeContainingDigit.push_back(datum);
    nodeContainingDigit->setMatchingStrings(matchingStringsInNodeContainingDigit);
}

void writeTraversalFiles(const EBST *tree, const string &outputFileName) {
    writePreorderTraversalFile(tree, outputFileName);
    writeInorderTraversalFile(tree, outputFileName);
    writePostorderTraversalFile(tree, outputFileName);
}

void writePreorderTraversalFile(const EBST *tree, const string &outputFileName) {
    ofstream preorderTraversalFile;

    preorderTraversalFile.open(outputFileName + PREORDER_OUTPUT_FILE_EXTENSION);
    preorderTraversalFile << tree->toString(PREORDER);
    preorderTraversalFile.close();
}

void writeInorderTraversalFile(const EBST *tree, const string &outputFileName) {
    ofstream inorderTraversalFile;

    inorderTraversalFile.open(outputFileName + INORDER_OUTPUT_FILE_EXTENSION);
    inorderTraversalFile << tree->toString(INORDER);
    inorderTraversalFile.close();
}

void writePostorderTraversalFile(const EBST *tree, const string &outputFileName) {
    ofstream postorderTraversalFile;

    postorderTraversalFile.open(outputFileName + POSTORDER_OUTPUT_FILE_EXTENSION);
    postorderTraversalFile << tree->toString(POSTORDER);
    postorderTraversalFile.close();
}
