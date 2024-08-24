#pragma once
#include "AnimalNode.h"
#include "GameSetup.h"
#include "GameSave.h"
#include <string>

using std::string;

class GameOperations 
{
private:
	bool startGame = true;
	bool gameInProgress = false;
	void initializeGame(AnimalNode*&, AnimalNode*&, AnimalNode*&);
	void promptUserToThinkOfAnimal();
	void processAnswerToComputerQuestion(AnimalNode*&);
	string askUserQuestion(string, AnimalNode*);
	void goToNodeYesAnsInCurrentNodePointsTo(AnimalNode*&);
	void goToNodeNoAnsInCurrentNodePointsTo(AnimalNode*&);
	void processAnswerToComputerAnimalGuess(AnimalNode*&, AnimalNode*&);
	string guessAnimal(AnimalNode*);
	void computerWinsGame();
	void computerLosesGame(AnimalNode*&, AnimalNode*&);
	void storeNewAnimalIntoNewNode(AnimalNode*&);
	void storeNewQuestionIntoCurrentNode(AnimalNode*&, AnimalNode*);
	void processNewAnsForNewNode(AnimalNode*&, AnimalNode*&);
	string askForNewAnswerForNewNode(AnimalNode*);
	void processYesAnsForNewAnimal(AnimalNode*&, AnimalNode*&);
	void storeCurrentNodeAnimalIntoNewNodeNoAns(AnimalNode*&, AnimalNode*);
	void processNoAnsForNewAnimal(AnimalNode*&, AnimalNode*&);
	void storeCurrentNodeAnimalIntoNewNodeYesAns(AnimalNode*&, AnimalNode*);
	void askUserToPlayAgain(AnimalNode*, GameSave, GameSetup);
	void processUserResponseToPlayAgain(AnimalNode*, string, GameSave, GameSetup);
	void endGame(AnimalNode*, GameSave, GameSetup);
public:
	void processGameOperations(AnimalNode*&, AnimalNode*&, AnimalNode*&, GameSave, GameSetup);
};