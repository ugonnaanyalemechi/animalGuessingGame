#include "GameSetup.h"
#include "main.h"
#include "Debugging.h"
#include <iostream>
#include <fstream>

using namespace std;

fstream inputFile;
Debugging debug1;

void GameSetup::welcomeUser() { // will need to add in parameters
    cout << "Welcome to the Animal Guessing Game!\n" << endl;
    processAnswerForGameDataOptions();
    //loadAnimalGameData(AnimalNode*&, AnimalNode*&, AnimalNode*&);
    //createAndInitializeRootNode(AnimalNode*&, AnimalNode*&);
}

void GameSetup::processAnswerForGameDataOptions() {
    string answer;
    answer = askUserGameDataOptions();
    answer = convertStringToLowercase(answer);
    if (answer == "yes") {
        return;
    }
    else if (answer == "no")
        animalFileName_SAVE = enterInputFileName();
    else {
        askUserToEnterValidAnswer();
        return processAnswerForGameDataOptions();
    }
}

string GameSetup::askUserGameDataOptions() {
    string answer;
    cout << "\nWould you like to use the default game data? If not, you can enter a file to your own." << endl;
    cout << "Enter answer here: "; cin >> answer;
    debug1.show("User's answer");
    return answer;
}

string GameSetup::enterInputFileName() {
    string fileName;
    cout << "\nEnter file name here: "; cin >> fileName;
    return fileName;
}

void GameSetup::openInputFile() {
    inputFile.open(animalFileName_SAVE);
    if (inputFile.fail()) {
        declareFileOpenFail(animalFileName_SAVE);
    }
}

void GameSetup::loadAnimalGameData(AnimalNode*& newNode, AnimalNode*& rootNode, AnimalNode*& currentNode) {
    debug1.show("File name used", animalFileName_SAVE); debug1.pause();
    openInputFile();
    transferInputFileDataToGame(newNode, rootNode, currentNode);
}

void GameSetup::transferInputFileDataToGame(AnimalNode*& newNode, AnimalNode*& rootNode, AnimalNode*& currentNode) {
    string fileLine;
    AnimalNode* lastNodeWithQuestion = nullptr;
    AnimalNode* lastNodeWithOnePtr = nullptr;
    AnimalNode* lastNodeWithBothPtrs = nullptr;
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
        debug1.show("Current line from the input file being processed", fileLine); debug1.pause();

        if (fileLine == "")
            break;

        // check type of file data
        if (fileLine == "G") { // next line in text file has the animal name
            animalGuessDetected = true;
            continue;
        }
        else if (fileLine == "Q") { // next line in text file has a question
            questionDetected = true;
            continue;
        }

        if (checkBranchToFill) {
            // algorithm for finding next point in binary tree to expand
            currentNode = rootNode;
            int counter = 0;
            while (currentNode->yesAns) {
                if (rootNodeYesAnsPathwayComplete && !onRootNodeNoPathway) {
                    currentNode = rootNode->noAns;
                    onRootNodeNoPathway = true;
                }
                if (counter == 2) { // branch to fill was found
                    // process branch to fill
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

                    // check yes-answer node last node with both pointers
                    currentNode = currentNode->yesAns;
                    if (currentNode->question != "") {
                        counter = 0; // eligibility counter is reset because criteria was not met
                    }
                    else if (currentNode->animal != "") {
                        counter++; // eligibility counter was added to because one criteria was met
                        currentNode = lastNodeWithBothPtrs;
                    }

                    // check no-answer node last node with both pointers
                    currentNode = lastNodeWithBothPtrs->noAns;
                    if (currentNode->question != "") {
                        counter = 0;
                        continue;
                    }
                    else if (currentNode->animal != "") {
                        counter++;
                        currentNode = lastNodeWithBothPtrs;
                        continue;
                    }
                }

                // this part of code may be unnecesary
                if ((!currentNode->yesAns) && (!currentNode->noAns)) {
                    currentNode = lastNodeWithBothPtrs->noAns;
                    counter++;
                    continue;
                }
            }
        }

        // creates the root node of the binary tree with a question, creates a node for the yes-answer pathway
        if (questionDetected && !rootNodeEstablished) {
            newNode = new AnimalNode;
            rootNode = newNode;
            rootNode->question = fileLine;
            newNode = new AnimalNode;
            rootNode->yesAns = newNode;
            currentNode = newNode;
            rootNodeEstablished = true;
            questionDetected = false;
            continue;
        }
        // fills current node with question pulled from the file, creates a node for the yes-answer pathway 
        if (questionDetected && onYesAnsPathway) {
            lastNodeWithQuestion = currentNode;
            currentNode->question = fileLine;
            newNode = new AnimalNode;
            currentNode->yesAns = newNode;
            currentNode = newNode;
            questionDetected = false;
            continue;
        }
        // creates a new node for the no-answer pathway, fills that node with a question, creates a new node for the yes-answer pathway, switches to yes-answer pathway via flag
        if (questionDetected && onNoAnsPathway) {
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
            continue;
        }

        // fills current node with animal guess, switches to no-answer pathway via flag
        if (animalGuessDetected && onYesAnsPathway) {
            currentNode->animal = fileLine;
            currentNode = lastNodeWithQuestion;
            onYesAnsPathway = false;
            onNoAnsPathway = true;
            animalGuessDetected = false;
            continue;
        }
        // creates a new node for the no-answer pathway, fills that node with an animal guess
        if (animalGuessDetected && onNoAnsPathway) {
            newNode = new AnimalNode;
            currentNode->noAns = newNode;
            currentNode = newNode;
            currentNode->animal = fileLine;
            checkBranchToFill = true;
            animalGuessDetected = false;
            continue;
        }
    }
}

void GameSetup::createAndInitializeRootNode(AnimalNode*& rootNode, AnimalNode*& currentNode) {
    rootNode = new AnimalNode;
    rootNode->animal = "lizard";
    rootNode->yesAns = nullptr;
    rootNode->noAns = nullptr;
    currentNode = rootNode; // on program start, the game starts out at the rootNode temporarily with asking if animal is a lizard
}