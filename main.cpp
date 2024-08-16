﻿#include <iostream>
#include <iomanip>
#include <fstream> 
#include <string> // Used to access getline()
#include "AnimalNode.h"
#include "Debugging.h"
#include "GameSetup.h"

using namespace std;

Debugging debug;

string convertStringToLowercase(string);
void askUserToEnterValidAnswer();
void declareFileOpenFail(string);

// game operations
void initializeGame(AnimalNode*&, AnimalNode*&, AnimalNode*&, bool&);
void processAnswerToComputerQuestion(AnimalNode*&);
void promptUserToThinkOfAnimal();
string askUserQuestion(string, AnimalNode*);
void goToNodeYesAnsInCurrentNodePointsTo(AnimalNode*&);
void goToNodeNoAnsInCurrentNodePointsTo(AnimalNode*&);
string guessAnimal(AnimalNode*);
void processAnswerToComputerAnimalGuess(AnimalNode*&, AnimalNode*&);
void computerWinsGame();
void computerLosesGame(AnimalNode*&, AnimalNode*&);
void storeNewAnimalIntoNewNode(AnimalNode*&);
void storeNewQuestionIntoCurrentNode(AnimalNode*&, AnimalNode*);
void processNewAnsForNewNode(AnimalNode*&, AnimalNode*&);
void processYesAnsForNewAnimal(AnimalNode*&, AnimalNode*&);
void processNoAnsForNewAnimal(AnimalNode*&, AnimalNode*&);
string askForNewAnswerForNewNode(AnimalNode*);
void currentNodeYesAnsPointsToNewNode(AnimalNode*&, AnimalNode*);
void currentNodeNoAnsPointsToNewNode(AnimalNode*&, AnimalNode*);
void storeCurrentNodeAnimalIntoNewNodeNoAns(AnimalNode*&, AnimalNode*);
void storeCurrentNodeAnimalIntoNewNodeYesAns(AnimalNode*&, AnimalNode*);
void removeAnimalInCurrentNode(AnimalNode*&);
void processUserResponseToPlayAgain(AnimalNode*, string, bool&, bool&);
void askUserToPlayAgain(AnimalNode*, bool&, bool&);
void endGame(AnimalNode*, bool&);

// save game data
void checkOutputFileOpens(ostream&);
void writeGameDataToFile(AnimalNode*);
void saveAnimalGameData(AnimalNode*);

string convertStringToLowercase(string text) {
    for (int i = 0; i < text.length(); i++) // looks at each character in string an makes it a lowercase letter
        text[i] = tolower(text[i]);
    return text;
}

void processGameOperations(AnimalNode*& rootNode, AnimalNode*& currentNode, AnimalNode*& newNode, bool& startGame, bool& gameInProgress) {
    while (startGame) {
        if (!gameInProgress)
            initializeGame(newNode, rootNode, currentNode, gameInProgress);
        if (currentNode->question != "") // if question string is filled, program will ask a question
            processAnswerToComputerQuestion(currentNode);
        else if (currentNode->animal != "") { // if guess string is filled, program will attempt to guess user's animal
            processAnswerToComputerAnimalGuess(currentNode, newNode);
            askUserToPlayAgain(rootNode, startGame, gameInProgress);
        }
    }
}
void declareFileOpenFail(string fileName) {
    cerr << "Oops, can't open the specified file; no such file or directory.\n";
    cerr << "The file name used was: " << fileName << endl;
    exit(0);
}
void initializeGame(AnimalNode*& newNode, AnimalNode*& rootNode, AnimalNode*& currentNode, bool& gameInProgress) {
    //loadAnimalGameData(newNode, rootNode, currentNode);
    promptUserToThinkOfAnimal();
    currentNode = rootNode;
    gameInProgress = true;
}
void processAnswerToComputerQuestion(AnimalNode*& currentNode) {
    string answer;
    answer = askUserQuestion(answer, currentNode);
    answer = convertStringToLowercase(answer);
    if (answer == "yes") {
        goToNodeYesAnsInCurrentNodePointsTo(currentNode);
        return; // I think this can be removed
    }
    else if (answer == "no") {
        goToNodeNoAnsInCurrentNodePointsTo(currentNode);
        return; // I think this can be removed
    }
    else {
        askUserToEnterValidAnswer();
        return processAnswerToComputerQuestion(currentNode);
    }
}
void promptUserToThinkOfAnimal() {
    int counter = 0;
    cout << "\nThink of an animal...when you are ready, press the enter key once or twice to proceed.";
    cin.ignore();
    while (cin.get() != '\n') // '\n' = enter key
        counter++; // counts the number of key inputs that do not correspond with the enter key
    if (counter != 0) {
        cout << "Please press the enter key to proceed!" << endl;
        debug.show("Number of non-enter-key keystrokes", counter);
        return promptUserToThinkOfAnimal();
    }
}
string askUserQuestion(string answer, AnimalNode* currentNode) {
    cout << "\n" << currentNode->question << endl;
    cout << "Enter answer here: "; cin >> answer;
    debug.show("User's answer", answer);
    return answer;
}

// both of these functions may need to go because of redundancy
void goToNodeYesAnsInCurrentNodePointsTo(AnimalNode*& currentNode) {
    currentNode = currentNode->yesAns;
    debug.showNodeContents("Current node", currentNode);
}
void goToNodeNoAnsInCurrentNodePointsTo(AnimalNode*& currentNode) {
    currentNode = currentNode->noAns;
    debug.showNodeContents("Current node", currentNode);
}

// may remove later due to redundancy
void askUserToEnterValidAnswer() {
    cout << "Please type in either yes or no!" << endl;
}
string guessAnimal(AnimalNode* currentNode) {
    string answer;
    cout << "\nIs the animal you are thinking of a(an) " << currentNode->animal << "?" << endl;
    cout << "Enter answer here: "; cin >> answer;
    debug.show("User's answer", answer);
    return answer;
}
void processAnswerToComputerAnimalGuess(AnimalNode*& currentNode, AnimalNode*& newNode) {
    string answer;
    answer = guessAnimal(currentNode);
    answer = convertStringToLowercase(answer);
    if (answer == "yes")
        computerWinsGame();
    else if (answer == "no")
        computerLosesGame(currentNode, newNode);
    else {
        askUserToEnterValidAnswer();
        return processAnswerToComputerAnimalGuess(currentNode, newNode);
    }
}
void computerWinsGame() {
    string winStatements[] = { "Awesome! ", "Woohoo! ", "Great! ", "Nice! ", "Let's go! " };
    int randomNum = rand() % 5;

    cout << "\n" << winStatements[randomNum] << "I guessed your animal!" << endl;
}
void computerLosesGame(AnimalNode*& currentNode, AnimalNode*& newNode) {
    storeNewAnimalIntoNewNode(newNode); // new animal is the animal user was thinking
    storeNewQuestionIntoCurrentNode(currentNode, newNode);
    processNewAnsForNewNode(currentNode, newNode); // does not correspond with previous answer
}
void storeNewAnimalIntoNewNode(AnimalNode*& newNode) {
    newNode = new AnimalNode;
    string animal;
    cout << "\nWhat animal did you have in mind?" << endl;
    cout << "Enter animal here: "; cin.ignore(); getline(cin, animal);
    animal = convertStringToLowercase(animal);
    newNode->animal = animal;
    debug.show("Animal user was thinking of", animal);
}
void storeNewQuestionIntoCurrentNode(AnimalNode*& currentNode, AnimalNode* newNode) {
    string question;
    cout << "\nWhat is a yes/no question I can use to tell a(an) " << currentNode->animal << " from a(an) " << newNode->animal << "?" << endl;
    cout << "Enter question here: "; getline(cin, question);
    question[0] = toupper(question[0]); // converts first letter in question to uppercase
    currentNode->question = question;
    debug.show("New question", question);
}
void processNewAnsForNewNode(AnimalNode*& currentNode, AnimalNode*& newNode) {
    string newAnswer = askForNewAnswerForNewNode(newNode); // for the new animal
    newAnswer = convertStringToLowercase(newAnswer);
    if (newAnswer == "yes")
        processYesAnsForNewAnimal(currentNode, newNode);
    else if (newAnswer == "no")
        processNoAnsForNewAnimal(currentNode, newNode);
    else {
        askUserToEnterValidAnswer();
        return processNewAnsForNewNode(currentNode, newNode);
    }
}
void processYesAnsForNewAnimal(AnimalNode*& currentNode, AnimalNode*& newNode) {
    currentNodeYesAnsPointsToNewNode(currentNode, newNode);
    storeCurrentNodeAnimalIntoNewNodeNoAns(newNode, currentNode); // involves creation of new node, not previous new node
    removeAnimalInCurrentNode(currentNode); // because current node is now a question node
}
void processNoAnsForNewAnimal(AnimalNode*& currentNode, AnimalNode*& newNode) {
    currentNodeNoAnsPointsToNewNode(currentNode, newNode);
    storeCurrentNodeAnimalIntoNewNodeYesAns(newNode, currentNode);
    removeAnimalInCurrentNode(currentNode);
}
string askForNewAnswerForNewNode(AnimalNode* newNode) {
    string newAnswer;
    cout << "\nFor a " << newNode->animal << ", is the answer yes or no?" << endl;
    cout << "Enter answer here: "; cin >> newAnswer;
    debug.show("User's answer for " + newNode->animal, newAnswer);
    return newAnswer;
}
void currentNodeYesAnsPointsToNewNode(AnimalNode*& currentNode, AnimalNode* newNode) {
    currentNode->yesAns = newNode;
    debug.showNodeContents("New animal node ('yes' answer)", newNode);
}
void currentNodeNoAnsPointsToNewNode(AnimalNode*& currentNode, AnimalNode* newNode) {
    currentNode->noAns = newNode;
    debug.showNodeContents("New animal node ('no' answer)", newNode);
}
void storeCurrentNodeAnimalIntoNewNodeNoAns(AnimalNode*& newNode, AnimalNode* currentNode) {
    newNode = new AnimalNode;
    newNode->animal = currentNode->animal;
    currentNode->noAns = newNode;
    debug.showNodeContents("New node w/ old animal ('no' answer)", newNode);
}
void storeCurrentNodeAnimalIntoNewNodeYesAns(AnimalNode*& newNode, AnimalNode* currentNode) {
    newNode = new AnimalNode;
    newNode->animal = currentNode->animal;
    currentNode->yesAns = newNode;
    debug.showNodeContents("New node w/ old animal ('yes' answer)", newNode);
}
void removeAnimalInCurrentNode(AnimalNode*& currentNode) {
    currentNode->animal = "";
    debug.showNodeContents("Question (current) node", currentNode);
}
void endGame(AnimalNode* rootNode, bool& startGame) {
    startGame = false;
    saveAnimalGameData(rootNode); // will be used in save game class
    cout << "\nPlay again soon!\n" << endl;
}
void processUserResponseToPlayAgain(AnimalNode* rootNode, string answer, bool& startGame, bool& gameInProgress) {
    if (answer == "no")
        endGame(rootNode, startGame);
    else if (answer == "yes")
        gameInProgress = false; // user will return back to the start of the game
    else {
        askUserToEnterValidAnswer();
        askUserToPlayAgain(rootNode, startGame, gameInProgress);
    }
}
void askUserToPlayAgain(AnimalNode* rootNode, bool& startGame, bool& gameInProgress) {
    string answer;
    cout << "\nWould you like to play again?" << endl;
    cout << "Enter answer here: "; cin >> answer;
    answer = convertStringToLowercase(answer);
    debug.show("User's response", answer);

    processUserResponseToPlayAgain(rootNode, answer, startGame, gameInProgress);
}
void checkOutputFileOpens(ostream& outputFile) {
    if (outputFile.fail())
        declareFileOpenFail(animalFileName_SAVE);
}
void writeGameDataToFile(ostream& outputFile, AnimalNode* currentNode) { // using pre-order traversal
    if (currentNode->animal != "") { // if an animal guess node
        outputFile << "G" << endl;
        outputFile << currentNode->animal << endl;
        debug.show("Animal guess saved", currentNode->animal);
        debug.pause();
    }
    else { // else, it is a question node
        outputFile << "Q" << endl;
        outputFile << currentNode->question << endl;
        debug.show("Question saved", currentNode->question);
        debug.pause();
        writeGameDataToFile(outputFile, currentNode->yesAns);
        writeGameDataToFile(outputFile, currentNode->noAns);
    }
}
void saveAnimalGameData(AnimalNode* rootNode) {
    ofstream outputFile(animalFileName_SAVE);
    checkOutputFileOpens(outputFile);
    writeGameDataToFile(outputFile, rootNode);
}

// -- MAIN -- //
int main() {
    AnimalNode* rootNode;
    AnimalNode* currentNode;
    AnimalNode* newNode;
    bool startGame = true;
    bool gameInProgress = false;
    srand(time(0)); // for computerWinsGame() function

    processGameOperations(rootNode, currentNode, newNode, startGame, gameInProgress);

    return 0;
}