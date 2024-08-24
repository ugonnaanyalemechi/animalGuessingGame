#include <iostream>
#include "GameSetup.h"
#include "GameOperations.h"

using std::cerr;

string convertStringToLowercase(string);
void declareFileOpenFail(string);

string convertStringToLowercase(string text) {
    for (int i = 0; i < text.length(); i++) // looks at each character in string and makes it a lowercase letter
        text[i] = tolower(text[i]);
    return text;
}

void declareFileOpenFail(string fileName) {
    cerr << "\nOops, can't open the specified file; no such file or directory.\n";
    cerr << "The file name used was: " << fileName << "\n";
    exit(0);
}

int main() {
    AnimalNode* rootNode;
    AnimalNode* currentNode;
    AnimalNode* newNode;
    GameSetup gameSetup;
    GameOperations gameOperations;
    GameSave gameSave;
    srand(time(0)); // for computerWinsGame() function

    gameSetup.gameSetupProcess(newNode, rootNode, currentNode);
    gameOperations.processGameOperations(rootNode, currentNode, newNode, gameSave, gameSetup);

    return 0;
}