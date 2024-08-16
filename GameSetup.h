#pragma once
#include "AnimalNode.h"
#include <string>

using std::string;

class GameSetup
{
private:
	string animalFileName_SAVE = "../../../myAnimalTreeDB.txt";
	
	void processAnswerForGameDataOptions();
	string askUserGameDataOptions();
	string enterInputFileName();
	void openInputFile();

	void loadAnimalGameData(AnimalNode*&, AnimalNode*&, AnimalNode*&);
	void transferInputFileDataToGame(AnimalNode*&, AnimalNode*&, AnimalNode*&);

	void createAndInitializeRootNode(AnimalNode*&, AnimalNode*&);
public:
	void welcomeUser(); // rename this function to something like gameSetupProcess
};