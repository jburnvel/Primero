#pragma once
#include <string>

using FString = std::string;
using int32 = int;
//all values initialised to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor
	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	bool CheckGuessValidity(FString) const; // TODO make a more rich return value.

	void Reset();
	FBullCowCount SubmitGuess(FString);

// ^^ Please try and ignore this and focus on the interface above ^^
private:
	//see constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
};