#include "GameOperations.h"
#include "main.h"
#include "GameSave.h"
#include <iostream>

using namespace std;

void GameOperations::processGameOperations(AnimalNode*& rootNode, AnimalNode*& currentNode, AnimalNode*& newNode, GameSave gameSave, GameSetup gameSetup) {
    while (startGame) {
        if (!gameInProgress)
            initializeGame(newNode, rootNode, currentNode);
        if (currentNode->question != "") // if question string is filled, program will ask a question
            processAnswerToComputerQuestion(currentNode);
        else if (currentNode->animal != "") { // if guess string is filled, program will attempt to guess user's animal
            processAnswerToComputerAnimalGuess(currentNode, newNode);
            askUserToPlayAgain(rootNode, gameSave, gameSetup);
        }
    }
}

void GameOperations::initializeGame(AnimalNode*& newNode, AnimalNode*& rootNode, AnimalNode*& currentNode) {
    promptUserToThinkOfAnimal();
    currentNode = rootNode;
    gameInProgress = true;
}

void GameOperations::promptUserToThinkOfAnimal() {
    int counter = 0;
    cout << "\n\n\nThink of an animal...when you are ready, press the enter key once or twice to proceed.";
    cin.ignore();
    while (cin.get() != '\n') // when an enter key is not inputted
        counter++; // counts the number of key inputs that do not correspond with the enter key
    if (counter != 0) {
        cout << "\nPlease press the enter key to proceed!\n";
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
        cout << "\nPlease type in either yes or no!\n";
        return processAnswerToComputerQuestion(currentNode);
    }
}

string GameOperations::askUserQuestion(string answer, AnimalNode* currentNode) {
    cout << "\n" << currentNode->question << "\n";
    cout << "Enter answer here: "; cin >> answer;
    return answer;
}

void GameOperations::goToNodeYesAnsInCurrentNodePointsTo(AnimalNode*& currentNode) {
    currentNode = currentNode->yesAns;
}

void GameOperations::goToNodeNoAnsInCurrentNodePointsTo(AnimalNode*& currentNode) {
    currentNode = currentNode->noAns;
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
        cout << "\nPlease type in either yes or no!\n";
        return processAnswerToComputerAnimalGuess(currentNode, newNode);
    }
}

string GameOperations::guessAnimal(AnimalNode* currentNode) {
    string answer;
    cout << "\nIs the animal you are thinking of a(an) " << currentNode->animal << "?\n";
    cout << "Enter answer here: "; cin >> answer;
    return answer;
}

void GameOperations::computerWinsGame() {
    string winStatements[] = { "Awesome! ", "Woohoo! ", "Great! ", "Nice! ", "Let's go! " };
    int randomNum = rand() % 5;
    cout << "\n" << winStatements[randomNum] << "I guessed your animal!\n";
}

void GameOperations::computerLosesGame(AnimalNode*& currentNode, AnimalNode*& newNode) {
    storeNewAnimalIntoNewNode(newNode); // new animal is the animal user was thinking
    storeNewQuestionIntoCurrentNode(currentNode, newNode);
    processNewAnsForNewNode(currentNode, newNode); // does not correspond with previous answer
}

void GameOperations::storeNewAnimalIntoNewNode(AnimalNode*& newNode) {
    newNode = new AnimalNode;
    string animal;
    cout << "\nWhat animal did you have in mind?\n";
    cout << "Enter animal here: "; cin.ignore(); getline(cin, animal);
    animal = convertStringToLowercase(animal);
    newNode->animal = animal;
}

void GameOperations::storeNewQuestionIntoCurrentNode(AnimalNode*& currentNode, AnimalNode* newNode) {
    string question;
    cout << "\nWhat is a yes/no question I can use to tell a(an) " << currentNode->animal << " from a(an) " << newNode->animal << "?\n";
    cout << "Enter question here: "; getline(cin, question);
    question[0] = toupper(question[0]); // converts first letter in question to uppercase
    currentNode->question = question;
}

void GameOperations::processNewAnsForNewNode(AnimalNode*& currentNode, AnimalNode*& newNode) {
    string newAnswer = askForNewAnswerForNewNode(newNode); // for the new animal
    newAnswer = convertStringToLowercase(newAnswer);
    if (newAnswer == "yes")
        processYesAnsForNewAnimal(currentNode, newNode);
    else if (newAnswer == "no")
        processNoAnsForNewAnimal(currentNode, newNode);
    else {
        cout << "Please type in either yes or no!\n";
        return processNewAnsForNewNode(currentNode, newNode);
    }
}

string GameOperations::askForNewAnswerForNewNode(AnimalNode* newNode) {
    string newAnswer;
    cout << "\nFor a " << newNode->animal << ", is the answer yes or no?\n";
    cout << "Enter answer here: "; cin >> newAnswer;
    return newAnswer;
}

void GameOperations::processYesAnsForNewAnimal(AnimalNode*& currentNode, AnimalNode*& newNode) {
    currentNode->yesAns = newNode;
    storeCurrentNodeAnimalIntoNewNodeNoAns(newNode, currentNode); // involves creation of new node, not previous new node
    currentNode->animal = ""; // because current node is now a question node
}

void GameOperations::storeCurrentNodeAnimalIntoNewNodeNoAns(AnimalNode*& newNode, AnimalNode* currentNode) {
    newNode = new AnimalNode;
    newNode->animal = currentNode->animal;
    currentNode->noAns = newNode;
}

void GameOperations::processNoAnsForNewAnimal(AnimalNode*& currentNode, AnimalNode*& newNode) {
    currentNode->noAns = newNode;
    storeCurrentNodeAnimalIntoNewNodeYesAns(newNode, currentNode);
    currentNode->animal = "";
}

void GameOperations::storeCurrentNodeAnimalIntoNewNodeYesAns(AnimalNode*& newNode, AnimalNode* currentNode) {
    newNode = new AnimalNode;
    newNode->animal = currentNode->animal;
    currentNode->yesAns = newNode;
}

void GameOperations::askUserToPlayAgain(AnimalNode* rootNode, GameSave gameSave, GameSetup gameSetup) {
    string answer;
    cout << "\nWould you like to play again?\n";
    cout << "Enter answer here: "; cin >> answer;
    answer = convertStringToLowercase(answer);

    processUserResponseToPlayAgain(rootNode, answer, gameSave, gameSetup);
}

void GameOperations::processUserResponseToPlayAgain(AnimalNode* rootNode, string answer, GameSave gameSave, GameSetup gameSetup) {
    if (answer == "no")
        endGame(rootNode, gameSave, gameSetup);
    else if (answer == "yes")
        gameInProgress = false; // user will return back to the start of the game
    else {
        cout << "Please type in either yes or no!\n";
        askUserToPlayAgain(rootNode, gameSave, gameSetup);
    }
}

void GameOperations::endGame(AnimalNode* rootNode, GameSave gameSave, GameSetup gameSetup) {
    startGame = false;
    gameSave.saveAnimalGameData(rootNode, gameSetup);
    cout << "\nPlay again soon!\n";
}