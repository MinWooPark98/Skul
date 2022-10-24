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

MapEditorScene::MapEditorScene()
	:Scene(Scenes::MapEditor), isPause(false), mode(Modes::None)
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

	uiMgr = new MapEditorUiMgr();
	uiMgr->Init();

	Vector2f windowSize = (Vector2f)FRAMEWORK->GetWindowSize();
	RectTile* background = new RectTile;
	background->SetName("background");
	background->Init();
	background->SetSize({ windowSize.x * 2.f, windowSize.y * 2.f });
	background->SetFillColor({ 255, 255, 255, 255 });
	layOut[(int)Layer::Canvas]->push_back(background);
	objList.push_back(background);

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
	displayCollider->SetColliderChosen(uiMgr->FindUiObj("TileColliderExampleUi"));
	layOut[(int)Layer::Collider]->push_back(displayCollider);
	objList.push_back(displayCollider);
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
	window.setView(worldView);
	for (auto layers : layOut)
	{
		for (auto obj : *layers)
		{
			if(obj->GetActive())
				obj->Draw(window);
		}
	}
	window.setView(uiView);
	uiMgr->Draw(window);
}

void MapEditorScene::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::W))
		worldView.move(0.f, -75.f);
	if (InputMgr::GetKeyDown(Keyboard::S))
		worldView.move(0.f, 75.f);
	if (InputMgr::GetKeyDown(Keyboard::A))
		worldView.move(-75.f, 0.f);
	if (InputMgr::GetKeyDown(Keyboard::D))
		worldView.move(75.f, 0.f);
	worldView.setSize(worldView.getSize() * (1.f - 0.05f * InputMgr::GetMouseWheelMoved()));

	Vector2f mousePos = InputMgr::GetMousePos();
	Vector2f windowSize = (Vector2f)FRAMEWORK->GetWindowSize();
	objMousePos = ScreenToWorld((Vector2i)mousePos);

	Scene::Update(dt);
	uiMgr->Update(dt);
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
}

void MapEditorScene::Exit()
{
}

const Vector2f& MapEditorScene::GetObjMousePos() const
{
	return objMousePos;
}

void MapEditorScene::ChangeMode(int modeNum)
{
	((MapEditorUiMgr*)uiMgr)->ResetButton();
	SetMode((Modes)modeNum);
}
