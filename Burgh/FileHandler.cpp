#include "FileHandler.h"


bool FileHandler::LoadGameFile(TString filename)
{
	if ((fopen_s(&gameFilePtr, filename.c_str(), "rb")) == 0)
	{
		if (fread(&currGame, 1, sizeof(currGame), gameFilePtr))
		{
			fclose(gameFilePtr);
			return true;
		}

	}
	return false;
};
bool FileHandler::LoadLevelFile(TString filename)
{
	return false;
};
bool FileHandler::LoadPlayerFile(TString filename, playerFileData& data)
{
	if ((fopen_s(&playerFilePtr, filename.c_str(), "rb")) == 0)
	{
		if (fread(&data, 1, sizeof(data), playerFilePtr))
		{
			fclose(playerFilePtr);
			return true;
		}

	}
	return false;
};
bool FileHandler::WriteGameFile(TString filename)
{
	if ((fopen_s(&gameFilePtr, filename.c_str(), "wb")) == 0)
	{
		if (fwrite(&currGame, 1, sizeof(gameData), gameFilePtr))
		{
			fclose(gameFilePtr);
			return true;
		}

	}
	return false;
	return false;
};
bool FileHandler::WritePlayerFile(TString filename, const playerFileData data)
{
	if ((fopen_s(&playerFilePtr, filename.c_str(), "wb")) == 0)
	{
		if (fwrite(&data, 1, sizeof(data), playerFilePtr))
		{
			fclose(playerFilePtr);
			return true;
		}

	}
	return false;
};