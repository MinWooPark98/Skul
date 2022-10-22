#include "MapEditorScene.h"
#include "../Framework/Framework.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/Tile.h"
#include "../GameObject/Grid.h"
#include "../Ui/MapEditorUiMgr.h"
#include "../Scene/SceneMgr.h"

MapEditorScene::MapEditorScene()
	:Scene(Scenes::MapEditor), currTex(nullptr), isPause(false)
{
}

MapEditorScene::~MapEditorScene()
{
}

void MapEditorScene::Init()
{
	Grid* grid = new Grid();
	grid->Init();
	objList.push_back(grid);

	for (auto obj : objList)
	{
		obj->Init();
	}

	uiMgr = new MapEditorUiMgr();
	uiMgr->Init();
}

void MapEditorScene::Release()
{
	Scene::Release();
	if (uiMgr != nullptr)
	{
		uiMgr->Release();
		delete uiMgr;
	}
}

void MapEditorScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(uiView);
	uiMgr->Draw(window);
}

void MapEditorScene::Update(float dt)
{
	Scene::Update(dt);
	uiMgr->Update(dt);
	if (InputMgr::GetKeyDown(Keyboard::D))
		worldView.move(10.f, 0.f);
}

void MapEditorScene::Enter()
{
	Scene::Enter();
	FRAMEWORK->GetWindow().setMouseCursorGrabbed(true);

	Vector2i size = FRAMEWORK->GetWindowSize();
	Vector2f centerPos(size.x * 0.5f, size.y * 0.5f);

	worldView.setSize(size.x, size.y);
	worldView.setCenter(centerPos);
	worldView.setViewport(FloatRect(0.f, 0.f, 0.9f, 1.f));

	uiView.setSize(size.x, size.y);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);
}

void MapEditorScene::Exit()
{
}
