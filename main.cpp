#include <iostream>
#include <vector>
#include <sstream>


using namespace std;

static int DEFAULT_ARGUMENT = 1;

int main(int quantityCommandLineArguments, char *commandLineArguments[]) {
    int quantityCommandLineArgumentsWithoutDefaultArgument = quantityCommandLineArguments - DEFAULT_ARGUMENT;

    if (quantityCommandLineArgumentsWithoutDefaultArgument == 0) {
        string rawKeyboardData;
        vector<int> keyboardData;
        istringstream streamedRawKeyboardData;
        string keyboardDatum;

        getline(cin, rawKeyboardData);
        streamedRawKeyboardData = istringstream(rawKeyboardData);

        while (getline(streamedRawKeyboardData, keyboardDatum, ' ')) {
            try {
                cout << stoi(keyboardDatum) << "\n";
                keyboardData.push_back(stoi(keyboardDatum));
            } catch (invalid_argument &e) { //TODO: Name and implementation
                cout << "Cannot convert string \"" + keyboardDatum + "\" to integer! Ignoring and continuing." << "\n";
            }
        }
    } else if (quantityCommandLineArgumentsWithoutDefaultArgument == 1) {
        cout << commandLineArguments[1];
    } else {
        //TODO
    }

    return 0;
}