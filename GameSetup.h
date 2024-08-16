#pragma once
#include "AnimalNode.h"
#include <string>

using std::string;

class GameSetup
{
private:
	void processAnswerForGameDataOptions();
	string askUserGameDataOptions();
	string enterInputFileName();
	void openInputFile();

	void loadAnimalGameData(AnimalNode*&, AnimalNode*&, AnimalNode*&);
	void transferInputFileDataToGame(AnimalNode*&, AnimalNode*&, AnimalNode*&);
public:
	void gameSetupProcess(AnimalNode*&, AnimalNode*&, AnimalNode*&);
	string gameDataFile = "../../../defaultGameDataFile.txt";
};