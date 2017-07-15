#pragma once
#include "FBullCowGame.h"
#include <map>

#define TMap std::map // To make syntax Unreal friendly

FBullCowGame::FBullCowGame(){ Reset(); }//default consturctor


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const{ return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMazTries{ {3,4} ,{4,7} ,{5,10},{6,16},{7,20} };
	return WordLengthToMazTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{	
	const FString HIDEN_WORD = "plane";	// this MUST be an isogram
	MyHiddenWord = HIDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))//if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))// if the guess isn't all lowercase 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;// return error		 
	}	
	else// otherwise
	{
		return EGuessStatus::OK;// return status OK
	}
}

// receives a VALID guess, increments turn, and return count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;	//increment the turn number
	FBullCowCount BullCowCount;//setup a return variable
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	
	//loop through all letters in the hidden word
	for (int32 HWChar = 0; HWChar < WordLength; HWChar++)
	{
		//compare letters against the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++)
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
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;// setup our map
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter])// if the letter is in the map
		{
			return false; // we do NOT have an isogram
		}
		else
		{ 
			LetterSeen[Letter] = true;	//add the letter to the map as seen
		}			
	}
	return true; // for example in cases where  /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{			
		if (!islower(Letter))//if no a lowercase letter
		{
			return false;//return false
		}
	}
	return true;
}
