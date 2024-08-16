#include "GameSave.h"
#include "main.h"
#include "Debugging.h"
#include <fstream>

using namespace std;

ofstream outputFile;
Debugging debug3;

void GameSave::saveAnimalGameData(AnimalNode* rootNode, GameSetup gameSetup) {
    ofstream outputFile(gameSetup.animalFileName_SAVE);
    checkOutputFileOpens(outputFile, gameSetup);
    writeGameDataToFile(outputFile, rootNode);
}

void GameSave::checkOutputFileOpens(ostream& outputFile, GameSetup gameSetup) {
    if (outputFile.fail())
        declareFileOpenFail(gameSetup.animalFileName_SAVE);
}

void GameSave::writeGameDataToFile(ostream& outputFile, AnimalNode* currentNode) { // using pre-order traversal
    if (currentNode->animal != "") { // if an animal guess node
        outputFile << "G" << endl;
        outputFile << currentNode->animal << endl;
        debug3.show("Animal guess saved", currentNode->animal);
        debug3.pause();
    }
    else { // else, it is a question node
        outputFile << "Q" << endl;
        outputFile << currentNode->question << endl;
        debug3.show("Question saved", currentNode->question);
        debug3.pause();
        writeGameDataToFile(outputFile, currentNode->yesAns);
        writeGameDataToFile(outputFile, currentNode->noAns);
    }
}