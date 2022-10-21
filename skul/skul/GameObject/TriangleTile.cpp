#include "TriangleTile.h"

TriangleTile::TriangleTile()
{
}

TriangleTile::~TriangleTile()
{
}

void TriangleTile::Init()
{
	tile = new CircleShape();
	((CircleShape*)tile)->setPointCount(3);
	Tile::Init();
}

void TriangleTile::Release()
{
	if (tile != nullptr)
		delete tile;
}
