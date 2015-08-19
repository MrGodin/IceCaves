
#pragma once

#include "windows.h"

static const int maxPlayersInFile = 25;
static const int maxPlayerNameLength = 15;
static const int maxMapLength = 1024 * 5;

struct relicData
{
	bool relic1 = false;
	bool relic2 = false;
	bool relic3 = false;
	bool relic4 = false;
};
struct levelFileData
{
	int index = 0;
	int prize_count = 0;
	int width = 0;
	int height = 0;
	char string[maxMapLength];
	bool conpleted = 0;
	levelFileData()
	{
		sprintf_s(string, "%s", "\0");
	}
};

struct levelData
{
	char map[4681];
	char textureFilename[MAX_PATH];
	int mapWidth = 0;
	int mapHeight = 0;
	int tileWidth = 0;
	int tileHeight = 0;
	int rows = 0;
	int cols = 0;
	int max = 0;

};
struct playerFileData
{
	int level = 0;
	int tokens = 0;
	int shieldstrength = 0;
	float thrust = 0.0f;
	float traction = 0.0f;
	float speed = 0.0f;
	float accX = 0.0f;
	float accY = 0.0f;
	float initialYVel = 0.0f;
	char name[maxPlayerNameLength];
	float power = 0.0f;
	float bounce_absorb = 0.0f;
	float posX = 0.0f;
	float posY = 0.0f;
	float anti_gravity = 0.0f;
	int   way_point = 0;
	char filename[MAX_PATH];
	levelData Level;
	relicData Relics;
};

struct gameData
{
	int saved_games = 0;
	char games[maxPlayersInFile][maxPlayerNameLength + 1];
	int level = 0;
	bool saved = false;
	bool fullscreen = false;
	bool vsync = true;
};