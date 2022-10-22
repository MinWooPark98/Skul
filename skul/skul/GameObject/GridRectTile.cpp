#include "GridRectTile.h"
#include "../Framework/InputMgr.h"
#include "../Scene/MapEditorScene.h"
#include "../Scene/SceneMgr.h"

GridRectTile::GridRectTile()
{
}

GridRectTile::~GridRectTile()
{
}

void GridRectTile::Update(float dt)
{
	RectTile::Update(dt);
	Vector2f mousePos = ((MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor))->ObjMousePos();
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
	if (isMouseOn && InputMgr::GetMouseButton(Mouse::Left))
		SetTexture(((MapEditorScene*)(SCENE_MGR->GetScene(Scenes::MapEditor)))->GetTexture());
}