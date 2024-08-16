#pragma once
#include "AnimalNode.h"
#include "GameSetup.h"
#include <string>

using std::string;

class GameOperations 
{
private:
	void initializeGame(AnimalNode*&, AnimalNode*&, AnimalNode*&, bool&);
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
				void currentNodeYesAnsPointsToNewNode(AnimalNode*&, AnimalNode*);
				void storeCurrentNodeAnimalIntoNewNodeNoAns(AnimalNode*&, AnimalNode*);
				void removeAnimalInCurrentNode(AnimalNode*&);
			void processNoAnsForNewAnimal(AnimalNode*&, AnimalNode*&);
				void currentNodeNoAnsPointsToNewNode(AnimalNode*&, AnimalNode*);
				void storeCurrentNodeAnimalIntoNewNodeYesAns(AnimalNode*&, AnimalNode*);

	void askUserToPlayAgain(AnimalNode*, bool&, bool&);
		void processUserResponseToPlayAgain(AnimalNode*, string, bool&, bool&);
		void endGame(AnimalNode*, bool&, GameSetup);


public:
	void processGameOperations(AnimalNode*&, AnimalNode*&, AnimalNode*&, bool&, bool&);
};