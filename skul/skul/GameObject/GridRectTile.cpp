#include "GridRectTile.h"
#include "../Framework/InputMgr.h"
#include "../Scene/MapEditorScene.h"
#include "../Scene/SceneMgr.h"
#include "../Framework/Framework.h"
#include "../Ui/UiMgr.h"

GridRectTile::GridRectTile()
{
}

GridRectTile::~GridRectTile()
{
}

void GridRectTile::Init()
{
	RectTile::Init();
	tile->setFillColor({ 255, 255, 255, 0 });
}

void GridRectTile::Update(float dt)
{
	RectTile::Update(dt);
	Vector2f mousePos = ((MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor))->ObjMousePos();
	FloatRect tileBound = tile->getGlobalBounds();
	if (mousePos.x < tileBound.left || mousePos.x > tileBound.left + tileBound.width ||
		mousePos.y < tileBound.top || mousePos.y > tileBound.top + tileBound.height ||
		mousePos.x >= FRAMEWORK->GetWindowSize().x * 0.9f)
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
	if (isMouseOn && InputMgr::GetMouseButton(Mouse::Left) && SCENE_MGR->GetScene(Scenes::MapEditor)->GetUiMgr()->FindUiObject("TileExampleUi")->GetActive())
		SetTexture(((MapEditorScene*)(SCENE_MGR->GetScene(Scenes::MapEditor)))->GetTexture());
}

void GridRectTile::SetTexture(const Texture* tex)
{
	RectTile::SetTexture(tex);
	if (tex == nullptr)
		tile->setFillColor({ 255, 255, 255, 0 });
	else
		tile->setFillColor({ 255, 255, 255, 255 });
}
