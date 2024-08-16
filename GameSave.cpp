#include "GameSave.h"
#include "main.h"
#include "Debugging.h"
#include <fstream>

using namespace std;

Debugging debug3;

void GameSave::saveAnimalGameData(AnimalNode* rootNode, GameSetup gameSetup) {
    ofstream outputFile(gameSetup.gameDataFile);
    checkOutputFileOpens(outputFile, gameSetup);
    writeGameDataToFile(outputFile, rootNode);
}

void GameSave::checkOutputFileOpens(ostream& outputFile, GameSetup gameSetup) {
    if (outputFile.fail())
        declareFileOpenFail(gameSetup.gameDataFile);
}

void GameSave::writeGameDataToFile(ostream& outputFile, AnimalNode* currentNode) { // using pre-order traversal
    if (currentNode->animal != "") { // if an animal guess node
        outputFile << "G\n";
        outputFile << currentNode->animal << "\n";
        debug3.show("Animal guess saved", currentNode->animal);
        debug3.pause();
    }
    else { // else, it is a question node
        outputFile << "Q\n";
        outputFile << currentNode->question << "\n";
        debug3.show("Question saved", currentNode->question);
        debug3.pause();
        writeGameDataToFile(outputFile, currentNode->yesAns);
        writeGameDataToFile(outputFile, currentNode->noAns);
    }
}