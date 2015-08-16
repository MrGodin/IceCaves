
#include "MapTile.h"
int TGameTile::width;
int TGameTile::height;

TDirection TGameTile::direction;
TGameTile::TGameTile(int x, int y, D3DXCOLOR color)
	:
	color(color),
	x((float)x),
	y((float)y)

{

}
TGameTile::~TGameTile(){};