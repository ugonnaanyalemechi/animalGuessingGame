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
	void findNextBranchToFill(bool&, bool&, bool&, AnimalNode*, AnimalNode*&);
	void checkPointedNodeOfNodeWithBothPtrs(AnimalNode*&, AnimalNode*, int&);
	void setUpRootNode(AnimalNode*&, AnimalNode*&, AnimalNode*&, string, bool&, bool&);
	void setUpQuestionNodeForYesPathway(AnimalNode*&, AnimalNode*&, AnimalNode*&, string, bool&);
	void setUpQuestionNodeForNoPathway(AnimalNode*&, AnimalNode*&, AnimalNode*&, string, bool&, bool&, bool&);
	void setUpAnimalGuessNodeForYesPathway(AnimalNode*&, AnimalNode*, string, bool&, bool&, bool&);
	void setUpAnimalGuessNodeForNoPathway(AnimalNode*&, AnimalNode*&, string, bool&, bool&);
public:
	void gameSetupProcess(AnimalNode*&, AnimalNode*&, AnimalNode*&);
	string gameDataFile = "../../../../defaultGameDataFile.txt";
};