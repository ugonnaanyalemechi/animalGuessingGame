#include "GameOperations.h"
#include "main.h"
#include "Debugging.h"
#include <iostream>

using namespace std;

Debugging debug2;

void GameOperations::processGameOperations(AnimalNode*& rootNode, AnimalNode*& currentNode, AnimalNode*& newNode, bool& startGame, bool& gameInProgress) {
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

void GameOperations::initializeGame(AnimalNode*& newNode, AnimalNode*& rootNode, AnimalNode*& currentNode, bool& gameInProgress) {
    //loadAnimalGameData(newNode, rootNode, currentNode);
    promptUserToThinkOfAnimal();
    currentNode = rootNode;
    gameInProgress = true;
}

void GameOperations::promptUserToThinkOfAnimal() {
    int counter = 0;
    cout << "\nThink of an animal...when you are ready, press the enter key once or twice to proceed.";
    cin.ignore();
    while (cin.get() != '\n') // '\n' = enter key
        counter++; // counts the number of key inputs that do not correspond with the enter key
    if (counter != 0) {
        cout << "Please press the enter key to proceed!" << endl;
        debug2.show("Number of non-enter-key keystrokes", counter);
        return promptUserToThinkOfAnimal();
    }
}

void GameOperations::processAnswerToComputerQuestion(AnimalNode*& currentNode) {
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

string GameOperations::askUserQuestion(string answer, AnimalNode* currentNode) {
    cout << "\n" << currentNode->question << endl;
    cout << "Enter answer here: "; cin >> answer;
    debug2.show("User's answer", answer);
    return answer;
}

void GameOperations::goToNodeYesAnsInCurrentNodePointsTo(AnimalNode*& currentNode) {
    currentNode = currentNode->yesAns;
    debug2.showNodeContents("Current node", currentNode);
}

void GameOperations::goToNodeNoAnsInCurrentNodePointsTo(AnimalNode*& currentNode) {
    currentNode = currentNode->noAns;
    debug2.showNodeContents("Current node", currentNode);
}

void GameOperations::processAnswerToComputerAnimalGuess(AnimalNode*& currentNode, AnimalNode*& newNode) {
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

string GameOperations::guessAnimal(AnimalNode* currentNode) {
    string answer;
    cout << "\nIs the animal you are thinking of a(an) " << currentNode->animal << "?" << endl;
    cout << "Enter answer here: "; cin >> answer;
    debug2.show("User's answer", answer);
    return answer;
}

void GameOperations::computerWinsGame() {
    string winStatements[] = { "Awesome! ", "Woohoo! ", "Great! ", "Nice! ", "Let's go! " };
    int randomNum = rand() % 5;

    cout << "\n" << winStatements[randomNum] << "I guessed your animal!" << endl;
}

void GameOperations::computerLosesGame(AnimalNode*& currentNode, AnimalNode*& newNode) {
    storeNewAnimalIntoNewNode(newNode); // new animal is the animal user was thinking
    storeNewQuestionIntoCurrentNode(currentNode, newNode);
    processNewAnsForNewNode(currentNode, newNode); // does not correspond with previous answer
}

void GameOperations::storeNewAnimalIntoNewNode(AnimalNode*& newNode) {
    newNode = new AnimalNode;
    string animal;
    cout << "\nWhat animal did you have in mind?" << endl;
    cout << "Enter animal here: "; cin.ignore(); getline(cin, animal);
    animal = convertStringToLowercase(animal);
    newNode->animal = animal;
    debug2.show("Animal user was thinking of", animal);
}

void GameOperations::storeNewQuestionIntoCurrentNode(AnimalNode*& currentNode, AnimalNode* newNode) {
    string question;
    cout << "\nWhat is a yes/no question I can use to tell a(an) " << currentNode->animal << " from a(an) " << newNode->animal << "?" << endl;
    cout << "Enter question here: "; getline(cin, question);
    question[0] = toupper(question[0]); // converts first letter in question to uppercase
    currentNode->question = question;
    debug2.show("New question", question);
}

void GameOperations::processNewAnsForNewNode(AnimalNode*& currentNode, AnimalNode*& newNode) {
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

string GameOperations::askForNewAnswerForNewNode(AnimalNode* newNode) {
    string newAnswer;
    cout << "\nFor a " << newNode->animal << ", is the answer yes or no?" << endl;
    cout << "Enter answer here: "; cin >> newAnswer;
    debug2.show("User's answer for " + newNode->animal, newAnswer);
    return newAnswer;
}

void GameOperations::processYesAnsForNewAnimal(AnimalNode*& currentNode, AnimalNode*& newNode) {
    currentNodeYesAnsPointsToNewNode(currentNode, newNode);
    storeCurrentNodeAnimalIntoNewNodeNoAns(newNode, currentNode); // involves creation of new node, not previous new node
    removeAnimalInCurrentNode(currentNode); // because current node is now a question node
}

void GameOperations::currentNodeYesAnsPointsToNewNode(AnimalNode*& currentNode, AnimalNode* newNode) {
    currentNode->yesAns = newNode;
    debug2.showNodeContents("New animal node ('yes' answer)", newNode);
}

void GameOperations::storeCurrentNodeAnimalIntoNewNodeNoAns(AnimalNode*& newNode, AnimalNode* currentNode) {
    newNode = new AnimalNode;
    newNode->animal = currentNode->animal;
    currentNode->noAns = newNode;
    debug2.showNodeContents("New node w/ old animal ('no' answer)", newNode);
}

void GameOperations::removeAnimalInCurrentNode(AnimalNode*& currentNode) {
    currentNode->animal = "";
    debug2.showNodeContents("Question (current) node", currentNode);
}

void GameOperations::processNoAnsForNewAnimal(AnimalNode*& currentNode, AnimalNode*& newNode) {
    currentNodeNoAnsPointsToNewNode(currentNode, newNode);
    storeCurrentNodeAnimalIntoNewNodeYesAns(newNode, currentNode);
    removeAnimalInCurrentNode(currentNode);
}

void GameOperations::currentNodeNoAnsPointsToNewNode(AnimalNode*& currentNode, AnimalNode* newNode) {
    currentNode->noAns = newNode;
    debug2.showNodeContents("New animal node ('no' answer)", newNode);
}

void GameOperations::storeCurrentNodeAnimalIntoNewNodeYesAns(AnimalNode*& newNode, AnimalNode* currentNode) {
    newNode = new AnimalNode;
    newNode->animal = currentNode->animal;
    currentNode->yesAns = newNode;
    debug2.showNodeContents("New node w/ old animal ('yes' answer)", newNode);
}

void GameOperations::askUserToPlayAgain(AnimalNode* rootNode, bool& startGame, bool& gameInProgress) {
    string answer;
    cout << "\nWould you like to play again?" << endl;
    cout << "Enter answer here: "; cin >> answer;
    answer = convertStringToLowercase(answer);
    debug2.show("User's response", answer);

    processUserResponseToPlayAgain(rootNode, answer, startGame, gameInProgress);
}

void GameOperations::processUserResponseToPlayAgain(AnimalNode* rootNode, string answer, bool& startGame, bool& gameInProgress) {
    if (answer == "no")
        endGame(rootNode, startGame);
    else if (answer == "yes")
        gameInProgress = false; // user will return back to the start of the game
    else {
        askUserToEnterValidAnswer();
        askUserToPlayAgain(rootNode, startGame, gameInProgress);
    }
}

void endGame(AnimalNode* rootNode, bool& startGame) {
    startGame = false;
    saveAnimalGameData(rootNode); // will be used in save game class
    cout << "\nPlay again soon!\n" << endl;
}