#pragma once
#include "Utils.h"
#include "MyString.h"


class FileHandler
{
private:
	FILE* playerFilePtr = NULL;
	FILE* gameFilePtr = NULL;
	FILE* levelFilePtr = NULL;
	levelFileData currLevel;
	playerFileData currPlayer;
	gameData currGame;
public:
	FileHandler()
	{
		for (int c = 0; c < maxPlayersInFile; c++)
			sprintf_s(currGame.games[c], "%s", "\0");
	}
	bool LoadGameFile(TString filename);
	bool LoadLevelFile(TString filename);
	bool LoadPlayerFile(TString filename, playerFileData& data);
	bool WriteGameFile(TString filename);
	bool WritePlayerFile(TString filename, const playerFileData data);

	gameData* GameData(){ return &currGame; }

};