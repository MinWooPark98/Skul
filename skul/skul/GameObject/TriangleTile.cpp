#include "TriangleTile.h"
#include "../Framework/InputMgr.h"

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

void TriangleTile::Update(float dt)
{
	Tile::Update(dt);
	Vector2f mousePos = InputMgr::GetMousePos();
	FloatRect tileBound = tile->getGlobalBounds();
	if (mousePos.x < tileBound.left || mousePos.x > tileBound.left + tileBound.width ||
		mousePos.y < tileBound.top || mousePos.y > tileBound.top + tileBound.height)
	{
		if (isMouseOn)
		{
			MarkOff();
			isMouseOn = false;
		}
		return;
	}
	isMouseOn = true;
	MarkOn();
}
