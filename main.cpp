#include <iostream>
#include "AnimalNode.h"
#include "Debugging.h"
#include "GameSetup.h"
#include "GameOperations.h"
#include "GameSave.h"

using namespace std;

string convertStringToLowercase(string);
void askUserToEnterValidAnswer();
void declareFileOpenFail(string);

string convertStringToLowercase(string text) {
    for (int i = 0; i < text.length(); i++) // looks at each character in string an makes it a lowercase letter
        text[i] = tolower(text[i]);
    return text;
}

void askUserToEnterValidAnswer() {
    cout << "Please type in either yes or no!" << endl;
}

void declareFileOpenFail(string fileName) {
    cerr << "Oops, can't open the specified file; no such file or directory.\n";
    cerr << "The file name used was: " << fileName << endl;
    exit(0);
}

// -- MAIN -- //
int main() {
    AnimalNode* rootNode;
    AnimalNode* currentNode;
    AnimalNode* newNode;
    GameSetup gameSetup;
    GameOperations gameOperations;
    GameSave gameSave;
    srand(time(0)); // for computerWinsGame() function

    gameSetup.welcomeUser(newNode, rootNode, currentNode);
    gameOperations.processGameOperations(rootNode, currentNode, newNode, gameSave, gameSetup);

    return 0;
}