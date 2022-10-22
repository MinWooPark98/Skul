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
	Vector2f mousePos = InputMgr::GetMousePos();
	FloatRect tileBound = tile->getGlobalBounds();
	if (mousePos.x < tileBound.left || mousePos.x > tileBound.left + tileBound.width ||
		mousePos.y < tileBound.top || mousePos.y > tileBound.top + tileBound.height)
	{
		if (isMouseOn && !isClicked)
		{
			MarkOff();
			isMouseOn = false;
		}
		return;
	}
	isMouseOn = true;
	if(!isClicked)
		MarkOn();
	if(InputMgr::GetMouseButton(Mouse::Left))
	{
		isClicked = true;
		tile->setOutlineColor({ 255, 0, 0, 255 });
	}
}
