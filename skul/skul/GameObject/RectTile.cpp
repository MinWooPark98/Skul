#include "RectTile.h"

RectTile::RectTile()
{
}

RectTile::~RectTile()
{
}

void RectTile::Init()
{
	tile = new RectangleShape();
	Tile::Init();
}

void RectTile::Release()
{
	if (tile != nullptr)
		delete tile;
}
