#include "GridRectTile.h"
#include "../Framework/InputMgr.h"

GridRectTile::GridRectTile()
{
}

GridRectTile::~GridRectTile()
{
}

void GridRectTile::Update(float dt)
{
	RectTile::Update(dt);
	if (isMouseOn && InputMgr::GetMouseButton(Mouse::Left))
		SetTextureChosen();
}