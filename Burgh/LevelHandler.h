
#include "Map.h"
#include "Player.h"

#include "levelstrings.h"
static TString imageFileNames[1] = { "media\\levelsprite2.png" };
class LevelHandler
{
private:

public:
	LevelHandler(){}

	bool GetLevel(int index, levelData& data)
	{
		switch (index)
		{
		case 1:
		{
			data.mapHeight = iLevel1Height;
			data.mapWidth = iLevel1Width;
			data.tileHeight = 64;
			data.tileWidth = 64;
			data.cols = data.mapWidth / 64;
			data.rows = data.mapHeight / 64;
			sprintf_s(data.textureFilename, "%s", imageFileNames[0].c_str());
			sprintf_s(data.map, "%s", pLevel1String);
		}
		break;
		case 2:
		{
			data.mapHeight = iLevel2Height;
			data.mapWidth = iLevel2Width;
			data.tileHeight = 64;
			data.tileWidth = 64;
			data.cols = data.mapWidth / 64;
			data.rows = data.mapHeight / 64;
			sprintf_s(data.textureFilename, "%s", imageFileNames[0].c_str());
			sprintf_s(data.map, "%s", pLevel2String);
		}
		break;
		case 3:
		{

		}
		break;
		case 4:
		{

		}
		break;
		case 5:
		{

		}
		break;
		case 6:
		{

		}
		break;
		case 7:
		{

		}
		break;
		case 8:
		{

		}
		break;
		case 9:
		{

		}
		break;
		case 10:
		{

		}
		break;

		default:
			return false;
		}
		return true;
	}
};