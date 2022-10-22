#include "MapEditorScene.h"
#include "../Framework/Framework.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/RectTile.h"
#include "../GameObject/Grid.h"
#include "../Ui/MapEditorUiMgr.h"
#include "../Scene/SceneMgr.h"

MapEditorScene::MapEditorScene()
	:Scene(Scenes::MapEditor), currTex(nullptr), isPause(false), mode(Modes::None)
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
		layOut.insert({ (Layer)i, objects });
	}

	Vector2f windowSize = (Vector2f)FRAMEWORK->GetWindowSize();
	RectTile* background = new RectTile;
	background->Init();
	background->SetSize({ windowSize.x * 2.f, windowSize.y * 2.f });
	background->SetFillColor({ 255, 255, 255, 255 });
	layOut[Layer::Canvas]->push_back(background);
	objList.push_back(background);

	Grid* grid = new Grid();
	grid->Init();
	layOut[Layer::Canvas]->push_back(grid);
	objList.push_back(grid);

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
	window.setView(worldView);
	for (auto& pair : layOut)
	{
		for (auto obj : *pair.second)
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

const Vector2f& MapEditorScene::ObjMousePos() const
{
	Vector2f mousePos = InputMgr::GetMousePos();
	return Vector2f(mousePos.x * (1.f / 0.9f) + (worldView.getCenter().x - FRAMEWORK->GetWindowSize().x * 0.5f), mousePos.y + worldView.getCenter().y - FRAMEWORK->GetWindowSize().y * 0.5f);
}

void MapEditorScene::ChangeMode(int modeNum)
{
	((MapEditorUiMgr*)uiMgr)->ResetButton();
	SetMode((Modes)mode);
}
