#include "FBullCowGame.h"

FBullCowGame::FBullCowGame(){ Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries;}
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDEN_WORD = "planet";
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDEN_WORD;

	MyCurrentTry = 1;
	return;
}

bool FBullCowGame::IsGameWon() const { return false; }
bool FBullCowGame::CheckGuessValidity(FString) const { return false; }

// receives a VALID guess, increments turn, and return count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	//increment the turn number
	MyCurrentTry++;
	//setup a return variable
	FBullCowCount BullCowCount;
	int32 HiddenWordLength = MyHiddenWord.length();
	//loop through all letters in the guess
	for (int32 HWChar = 0; HWChar < HiddenWordLength; HWChar++)
	{
		//compare letters against the hidden word
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
		{		
			// if they match then
			if (Guess[GChar] == MyHiddenWord[HWChar])
			{
				if (HWChar == GChar)	{// if they're in the same place
					BullCowCount.Bulls++;//increment bulls
				}
				else {
					BullCowCount.Cows++;//must be a cow
				}
			}
		}
	}
	return BullCowCount;
}
