#include "MapEditorScene.h"
#include "../Framework/Framework.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/RectTile.h"
#include "../GameObject/Grid.h"
#include "../Ui/MapEditorUiMgr.h"
#include "../Scene/SceneMgr.h"
#include "../GameObject/DisplayObj.h"
#include "../GameObject/ExampleOnCursor.h"
#include "../GameObject/DisplayCollider.h"
#include "../GameObject/MapEditorDataMgr.h"
#include "../Ui/SaveLoadUi.h"
#include "../Framework/SoundMgr.h"

MapEditorScene::MapEditorScene()
	:Scene(Scenes::MapEditor), mode(Modes::None), dataMgr(nullptr), saveLoadUi(nullptr), canvas(nullptr)
{
}

MapEditorScene::~MapEditorScene()
{
}

void MapEditorScene::Init()
{
	for (int i = 0; i < (int)Layer::Count; ++i)
	{
		list<Object*>* objects = new list<Object*>;
		layOut.push_back(objects);
	}

	Vector2f windowSize = (Vector2f)FRAMEWORK->GetWindowSize();
	canvas = new RectTile;
	canvas->SetName("background");
	canvas->Init();
	canvas->SetSize({ windowSize.x * 2.f - 2.f, windowSize.y * 2.f - 2.f });
	canvas->SetFillColor({ 255, 255, 255, 255 });
	objList.push_back(canvas);

	Grid* grid = new Grid();
	grid->SetName("grid");
	grid->Init();
	layOut[(int)Layer::Tile]->push_back(grid);
	objList.push_back(grid);

	DisplayObj* displayObj = new DisplayObj();
	displayObj->SetName("displayObj");
	displayObj->Init();
	objList.push_back(displayObj);

	ExampleOnCursor* exampleOnCursor = new ExampleOnCursor();
	exampleOnCursor->SetName("exampleOnCursor");
	exampleOnCursor->Init();
	layOut[(int)Layer::Front]->push_back(exampleOnCursor);
	objList.push_back(exampleOnCursor);

	DisplayCollider* displayCollider = new DisplayCollider();
	displayCollider->SetName("displayCollider");
	displayCollider->Init();
	objList.push_back(displayCollider);

	dataMgr = new MapEditorDataMgr();
	dataMgr->Init();

	saveLoadUi = new SaveLoadUi();
	saveLoadUi->Init();

	uiMgr = new MapEditorUiMgr();
	uiMgr->Init();

	displayCollider->SetColliderChosen(uiMgr->FindUiObj("TileColliderExampleUi"));
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

void MapEditorScene::Reset()
{
	for (int i = 0; i < (int)Layer::Count; ++i)
	{
		if (i == (int)Layer::Tile || i == (int)Layer::Front)
			continue;
		layOut[i]->clear();
	}
	for (auto& obj : objList)
	{
		obj->Reset();
	}
	uiMgr->Reset();
	mode = Modes::None;
	objName.clear();
}

void MapEditorScene::Update(float dt)
{
	if (isPause)
	{
		saveLoadUi->Update(dt);
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::F5))
		Reset();

	if (InputMgr::GetKeyDown(Keyboard::W))
		worldView.move(0.f, -75.f);
	if (InputMgr::GetKeyDown(Keyboard::S))
		worldView.move(0.f, 75.f);
	if (InputMgr::GetKeyDown(Keyboard::A))
		worldView.move(-75.f, 0.f);
	if (InputMgr::GetKeyDown(Keyboard::D))
		worldView.move(75.f, 0.f);
	worldView.setSize(worldView.getSize() * (1.f - 0.05f * InputMgr::GetMouseWheelMoved()));

	Scene::Update(dt);
	uiMgr->Update(dt);
}

void MapEditorScene::Draw(RenderWindow& window)
{
	window.setView(worldView);
	canvas->Draw(window);
	for (auto layers : layOut)
	{
		for (auto obj : *layers)
		{
			if (obj->GetActive())
				obj->Draw(window);
		}
	}
	window.setView(uiView);
	uiMgr->Draw(window);

	if (isPause)
		saveLoadUi->Draw(window);
}

void MapEditorScene::Enter()
{
	Scene::Enter();
	FRAMEWORK->GetWindow().setMouseCursorGrabbed(true);

	Vector2i size = FRAMEWORK->GetWindowSize();

	worldView.setSize(size.x, size.y);
	worldView.setCenter(size.x * 0.4f, size.y * 0.4f);
	worldView.setViewport(FloatRect(0.f, 0.f, 0.9f, 1.f));

	uiView.setSize(size.x, size.y);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);

	SOUND_MGR->Play("sound/MapEditorScene.wav", true);
}

void MapEditorScene::Exit()
{
	Reset();
}

void MapEditorScene::ChangeMode(int modeNum)
{
	((MapEditorUiMgr*)uiMgr)->ResetButton();
	SetMode((Modes)modeNum);
}
