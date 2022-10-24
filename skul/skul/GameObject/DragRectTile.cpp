#include "DragRectTile.h"
#include "../Framework/InputMgr.h"
#include "../Scene/SceneMgr.h"
#include "../Scene/MapEditorScene.h"

DragRectTile::DragRectTile()
	:isCreated(false)
{
}

DragRectTile::~DragRectTile()
{
}

void DragRectTile::Update(float dt)
{
	RectTile::Update(dt);
	MapEditorScene* mapEditorScene = ((MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor));
	Vector2f mousePos = mapEditorScene->GetObjMousePos();
	if (!isCreated)
	{
		Vector2f pos = { mousePos.x - position.x, mousePos.y - position.y };
		SetSize(pos);
		if (InputMgr::GetMouseButtonUp(Mouse::Left))
			isCreated = true;
	}
}
