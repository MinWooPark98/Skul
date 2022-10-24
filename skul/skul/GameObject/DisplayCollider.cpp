#include "DisplayCollider.h"
#include "DragRectTile.h"
#include "../Scene/SceneMgr.h"
#include "../Scene/MapEditorScene.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Framework.h"
#include "../Ui/ColliderExampleUi.h"
#include "../Ui/MapEditorUiMgr.h"

DisplayCollider::DisplayCollider()
	:colliderChosen(nullptr)
{
}

DisplayCollider::~DisplayCollider()
{
}

void DisplayCollider::Init()
{
	Object::Init();
	displays.Init();
}

void DisplayCollider::Release()
{
	Object::Release();
	displays.Release();
}

void DisplayCollider::Reset()
{
	Object::Reset();
	displays.Reset();
}

void DisplayCollider::Update(float dt)
{
	MapEditorScene* mapEditorScene = (MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor);
	Vector2f mousePos = mapEditorScene->GetObjMousePos();
	if (colliderChosen == nullptr ||
		mapEditorScene->GetMode() != MapEditorScene::Modes::TileCollider ||
		InputMgr::GetMousePos().x >= FRAMEWORK->GetWindowSize().x * 0.9f)
	{
		return;
	}
	if (InputMgr::GetMouseButtonDown(Mouse::Left))
	{
		DragRectTile* obj = displays.Get();
		obj->SetFillColor({ 255, 255, 255, 0 });
		obj->SetOutlineThickness(5.f);
		switch (colliderChosen->GetType())
		{
		case ColliderExampleUi::ColliderTypes::None:
			delete obj;
			return;
		case ColliderExampleUi::ColliderTypes::TopSide:
			obj->SetOutlineColor({ 255, 0, 0, 255 });
			break;
		case ColliderExampleUi::ColliderTypes::AllSide:
			obj->SetOutlineColor({ 0, 0, 255, 255 });
			break;
		}
		obj->SetPos(mousePos);
	}
	list<DragRectTile*> useList = displays.GetUseList();
	for (auto obj : useList)
	{
		obj->Update(dt);
		if (obj->GetGlobalBounds().contains(mousePos) && InputMgr::GetMouseButtonDown(Mouse::Right))
			displays.Return(obj);
	}
}

void DisplayCollider::Draw(RenderWindow& window)
{
	list<DragRectTile*> useList = displays.GetUseList();
	for (auto obj : useList)
	{
		obj->Draw(window);
	}
}
