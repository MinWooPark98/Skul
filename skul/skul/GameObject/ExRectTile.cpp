#include "exRectTile.h"
#include "../Framework/InputMgr.h"

ExRectTile::ExRectTile()
{
}

ExRectTile::~ExRectTile()
{
}

void ExRectTile::Update(float dt)
{
	RectTile::Update(dt);
	if(isMouseOn && InputMgr::GetMouseButton(Mouse::Left))
	{
		if (ClickOn == nullptr)
			return;
		ClickOn(tile->getTexture());
	}
}
