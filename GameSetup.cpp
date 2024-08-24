#include "GameSetup.h"
#include "main.h"
#include <iostream>
#include <fstream>

using namespace std;

fstream inputFile;

void GameSetup::gameSetupProcess(AnimalNode*& newNode, AnimalNode*& rootNode, AnimalNode*& currentNode) {
    cout << "Welcome to the Animal Guessing Game!\n";
    processAnswerForGameDataOptions();
    loadAnimalGameData(newNode, rootNode, currentNode);
}

void GameSetup::processAnswerForGameDataOptions() {
    string answer;
    answer = askUserGameDataOptions();
    answer = convertStringToLowercase(answer);
    if (answer == "yes")
        return;
    else if (answer == "no")
        gameDataFile = enterInputFileName();
    else {
        cout << "\nPlease type in either yes or no!\n";
        return processAnswerForGameDataOptions();
    }
}

string GameSetup::askUserGameDataOptions() {
    string answer;
    cout << "\nWould you like to use the default game data file or use your own file? (Enter 'yes' or 'no')\n";
    cout << "Enter answer here: "; cin >> answer;
    return answer;
}

string GameSetup::enterInputFileName() {
    string fileName;
    cout << "\nEnter file name here: "; cin >> fileName;
    return fileName;
}

void GameSetup::openInputFile() {
    inputFile.open(gameDataFile);
    if (inputFile.fail())
        declareFileOpenFail(gameDataFile);
}

void GameSetup::loadAnimalGameData(AnimalNode*& newNode, AnimalNode*& rootNode, AnimalNode*& currentNode) {
    openInputFile();
    transferInputFileDataToGame(newNode, rootNode, currentNode);
}

void GameSetup::transferInputFileDataToGame(AnimalNode*& newNode, AnimalNode*& rootNode, AnimalNode*& currentNode) {
    string fileLine;
    AnimalNode* lastNodeWithQuestion = nullptr;
    bool animalGuessDetected = false;
    bool questionDetected = false;
    bool onYesAnsPathway = true;
    bool onNoAnsPathway = false;
    bool rootNodeEstablished = false;
    bool checkBranchToFill = false;
    bool rootNodeYesAnsPathwayComplete = false;
    bool onRootNodeNoPathway = false;

    while (inputFile) {
        getline(inputFile, fileLine);
        
        if (fileLine == "")
            break;

        if (fileLine == "G") { // next line in text file has the animal name
            animalGuessDetected = true;
            continue;
        }
        else if (fileLine == "Q") { // next line in text file has a question
            questionDetected = true;
            continue;
        }

        if (checkBranchToFill)
            findNextBranchToFill(rootNodeYesAnsPathwayComplete, onRootNodeNoPathway, checkBranchToFill, rootNode, currentNode);

        if (questionDetected && !rootNodeEstablished) {
            setUpRootNode(newNode, rootNode, currentNode, fileLine, rootNodeEstablished, questionDetected);
            continue;
        }

        if (questionDetected && onYesAnsPathway) {
            setUpQuestionNodeForYesPathway(newNode, currentNode, lastNodeWithQuestion, fileLine, questionDetected);
            continue;
        }

        if (questionDetected && onNoAnsPathway) {
            setUpQuestionNodeForNoPathway(newNode, currentNode, lastNodeWithQuestion, fileLine, questionDetected, onNoAnsPathway, onYesAnsPathway);
            continue;
        }

        if (animalGuessDetected && onYesAnsPathway) {
            setUpAnimalGuessNodeForYesPathway(currentNode, lastNodeWithQuestion, fileLine, onYesAnsPathway, onNoAnsPathway, animalGuessDetected);
            continue;
        }

        if (animalGuessDetected && onNoAnsPathway) {
            setUpAnimalGuessNodeForNoPathway(newNode, currentNode, fileLine, checkBranchToFill, animalGuessDetected);
            continue;
        }
    }
}

void GameSetup::findNextBranchToFill(bool& rootNodeYesAnsPathwayComplete, bool& onRootNodeNoPathway, bool& checkBranchToFill, AnimalNode* rootNode, AnimalNode*& currentNode) {
    currentNode = rootNode;
    AnimalNode* lastNodeWithOnePtr = nullptr;
    AnimalNode* lastNodeWithBothPtrs = nullptr;
    int counter = 0;
    int loopCheck = 0;
    while (currentNode->yesAns) {
        if (rootNodeYesAnsPathwayComplete && !onRootNodeNoPathway) {
            currentNode = rootNode->noAns;
            onRootNodeNoPathway = true;
        }
        if (counter == 2) { // branch to fill was found
            currentNode = lastNodeWithOnePtr;
            checkBranchToFill = false;
            if (rootNode == lastNodeWithOnePtr)
                rootNodeYesAnsPathwayComplete = true;
            break;
        }

        if ((currentNode->yesAns) && (currentNode->noAns == nullptr)) {
            lastNodeWithOnePtr = currentNode;
            currentNode = currentNode->yesAns;
            continue;
        }
        else if (currentNode->yesAns && currentNode->noAns) {
            lastNodeWithBothPtrs = currentNode;

            currentNode = currentNode->yesAns;
            checkPointedNodeOfNodeWithBothPtrs(currentNode, lastNodeWithBothPtrs, counter);

            currentNode = lastNodeWithBothPtrs->noAns;
            checkPointedNodeOfNodeWithBothPtrs(currentNode, lastNodeWithBothPtrs, counter);

            loopCheck++;
            if (loopCheck == 10) {
                counter = 2;
                continue;
            }
        }
    }
}

void GameSetup::checkPointedNodeOfNodeWithBothPtrs(AnimalNode*& currentNode, AnimalNode* lastNodeWithBothPtrs, int& counter) {
    if (currentNode->question != "")
        counter = 0; // eligibility counter is reset to to check through question node
    else if (currentNode->animal != "") {
        counter++; // eligibility counter was added to because animal guess node may indicate complete dead end
        currentNode = lastNodeWithBothPtrs;
    }
}

void GameSetup::setUpRootNode(AnimalNode*& newNode, AnimalNode*& rootNode, AnimalNode*& currentNode, string fileLine, bool& rootNodeEstablished, bool& questionDetected) {
    newNode = new AnimalNode;
    rootNode = newNode;
    rootNode->question = fileLine;
    newNode = new AnimalNode;
    rootNode->yesAns = newNode;
    currentNode = newNode;
    rootNodeEstablished = true;
    questionDetected = false;
}

void GameSetup::setUpQuestionNodeForYesPathway(AnimalNode*& newNode, AnimalNode*& currentNode, AnimalNode*& lastNodeWithQuestion, string fileLine, bool& questionDetected) {
    lastNodeWithQuestion = currentNode;
    currentNode->question = fileLine;
    newNode = new AnimalNode;
    currentNode->yesAns = newNode;
    currentNode = newNode;
    questionDetected = false;
}

void GameSetup::setUpQuestionNodeForNoPathway(AnimalNode*& newNode, AnimalNode*& currentNode, AnimalNode*& lastNodeWithQuestion, string fileLine, bool& questionDetected, bool& onNoAnsPathway, bool& onYesAnsPathway) {
    newNode = new AnimalNode;
    currentNode->noAns = newNode;
    currentNode = newNode;
    currentNode->question = fileLine;
    newNode = new AnimalNode;
    currentNode->yesAns = newNode;
    lastNodeWithQuestion = currentNode;
    currentNode = newNode;
    onNoAnsPathway = false;
    onYesAnsPathway = true;
    questionDetected = false;
}

void GameSetup::setUpAnimalGuessNodeForYesPathway(AnimalNode*& currentNode, AnimalNode* lastNodeWithQuestion, string fileLine, bool& onYesAnsPathway, bool& onNoAnsPathway, bool& animalGuessDetected) {
    currentNode->animal = fileLine;
    currentNode = lastNodeWithQuestion;
    onYesAnsPathway = false;
    onNoAnsPathway = true;
    animalGuessDetected = false;
}

void GameSetup::setUpAnimalGuessNodeForNoPathway(AnimalNode*& newNode, AnimalNode*& currentNode, string fileLine, bool& checkBranchToFill, bool& animalGuessDetected) {
    newNode = new AnimalNode;
    currentNode->noAns = newNode;
    currentNode = newNode;
    currentNode->animal = fileLine;
    checkBranchToFill = true;
    animalGuessDetected = false;
}