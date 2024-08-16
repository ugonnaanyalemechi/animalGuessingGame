#pragma once
#include "AnimalNode.h"
#include "GameSetup.h"

using std::ostream;

class GameSave 
{
private:
	void checkOutputFileOpens(ostream&, GameSetup);
	void writeGameDataToFile(ostream&, AnimalNode*);
public:
	void saveAnimalGameData(AnimalNode*, GameSetup);
};