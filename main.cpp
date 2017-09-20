#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "EBSTNode.h"
#include "EBST.h"

using namespace std;

const static int EXIT_CODE_ILLEGAL_QUANTITY_ARGUMENTS = 1;
const static char *ERROR_MESSAGE_ILLEGAL_QUANTITY_ARGUMENTS = "Invalid quantity of command line arguments encountered, pass either zero arguments for keyboard input, or one argument for file input.\n";
const static char *ERROR_MESSAGE_NO_SUCH_FILE = "No file with the provided name exists: \"";
const static char *ERROR_MESSAGE_INVALID_TREE_EMPTY_ROOT = "Invalid tree: This tree has no root (is your input data empty?).\n";
const static char *ERROR_MESSAGE_INVALID_DATUM = "Datum is invalid: \"";

const static int QUANTITY_DEFAULT_ARGUMENTS = 1;

const static char validCharacters[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

const static int EXIT_CODE_SUCCESS = 0;
const static int EXIT_CODE_NO_SUCH_INPUT_FILE = 2;
const static int EXIT_CODE_INVALID_TREE_EMPTY_ROOT = 3;
const static int EXIT_CODE_INVALID_DATUM = 4;

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

bool datumIsValid(const string lastCharInDatum);

int main(int quantityCommandLineArguments, char *commandLineArguments[]) {
    int quantityCommandLineArgumentsWithoutDefaultArgument = quantityCommandLineArguments - QUANTITY_DEFAULT_ARGUMENTS;

    if (noArgumentsPassed(quantityCommandLineArgumentsWithoutDefaultArgument)) {
        try {
            runForKeyboardInput();
        } catch (int &exitCode) {
            return exitCode;
        }
    } else if (oneArgumentPassed(quantityCommandLineArgumentsWithoutDefaultArgument)) {
        try {
            runForFileInput(commandLineArguments);
        } catch (int &exitCode) {
            return exitCode;
        }
    } else {
        cerr << ERROR_MESSAGE_ILLEGAL_QUANTITY_ARGUMENTS << endl;
        return EXIT_CODE_ILLEGAL_QUANTITY_ARGUMENTS;
    }

    return EXIT_CODE_SUCCESS;
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
    ifstream inputFile(inputFileName + IMPLICIT_INPUT_FILE_EXTENSION);

    if (inputFile) {
        string rawInputFileData;
        string rawInputFileLine;

        while (!inputFile.eof()) {
            getline(inputFile, rawInputFileLine);
            rawInputFileData += " " + rawInputFileLine;
        }

        inputFile.close();

        return rawInputFileData;
    } else {
        cerr << ERROR_MESSAGE_NO_SUCH_FILE << inputFileName << "\"\n";
        throw EXIT_CODE_NO_SUCH_INPUT_FILE;
    }
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
        if (datumIsValid(datum)) {
            char lastCharInDatum = datum[datum.length() - 1];

            if (tree->digitIsInTreeFromThisNode(lastCharInDatum, tree->getRoot())) {
                addDatumToTreeNode(tree, datum, lastCharInDatum);
            } else {
                addNewNodeToTree(tree, lastCharInDatum);
                addDatumToTreeNode(tree, datum, lastCharInDatum);
            }
        } else {
            cerr << ERROR_MESSAGE_INVALID_DATUM << datum << "\"\n";
            throw EXIT_CODE_INVALID_DATUM;
        }
    }

    if (tree->getRoot() != nullptr) {
        return tree;
    } else {
        cerr << ERROR_MESSAGE_INVALID_TREE_EMPTY_ROOT;
        throw EXIT_CODE_INVALID_TREE_EMPTY_ROOT;
    }
}

bool datumIsValid(const string datum) {
    for (auto characterInDatum : datum) {
        bool thisCharacterIsValid = false;

        for (auto validCharacter : validCharacters) {
            if (characterInDatum == validCharacter) {
                thisCharacterIsValid = true;
            }
        }

        if (!thisCharacterIsValid) {
            return false;
        }
    }

    return true;
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
