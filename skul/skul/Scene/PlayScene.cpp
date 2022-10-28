#include "PlayScene.h"
#include "../GameObject/Player.h"
#include "../GameObject/Skul/DefaultSkul.h"
#include "../Framework/Framework.h"
#include "../GameObject/Collider.h"

PlayScene::PlayScene()
	:Scene(Scenes::Play)
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	for (int i = 0; i < (int)Layer::Count; ++i)
	{
		list<Object*>* objects = new list<Object*>;
		layOut.push_back(objects);
	}

	Player* player = new Player();
	player->Init();
	player->SetName("player");
	layOut[(int)Layer::Player]->push_back(player);
	objList.push_back(player);

	Skul* skul = new DefaultSkul();
	skul->Init();
	player->SetSkul(skul);

	Collider* collider = new Collider();
	collider->Init();
	collider->SetType(Collider::Type::TopSide);
	collider->SetPos({ 0.f, 700.f });
	collider->SetHitBox({ 0.f, 0.f, 1280.f, 64.f });
	layOut[(int)Layer::Collider]->push_back(collider);
	objList.push_back(collider);

	Collider* collider2 = new Collider();
	collider2->Init();
	collider2->SetType(Collider::Type::AllSide);
	collider2->SetPos({ 800.f, 550.f });
	collider2->SetHitBox({ 0.f, 0.f, 100.f, 32.f });
	layOut[(int)Layer::Collider]->push_back(collider2);
	objList.push_back(collider2);

	Collider* collider3 = new Collider();
	collider3->Init();
	collider3->SetType(Collider::Type::TopSide);
	collider3->SetPos({ 340.f, 550.f });
	collider3->SetHitBox({ 0.f, 0.f, 300.f, 32.f });
	layOut[(int)Layer::Collider]->push_back(collider3);
	objList.push_back(collider3);

	for (auto obj : objList)
	{
		obj->SetDevMode(true);
	}
}

void PlayScene::Release()
{
	Scene::Release();
}

void PlayScene::Reset()
{
	Scene::Reset();
}

void PlayScene::Update(float dt)
{
	if (dt > 1.f)
		return;
	Scene::Update(dt);
}

void PlayScene::Draw(RenderWindow& window)
{
	window.setView(worldView);
	for (auto layers : layOut)
	{
		for (auto obj : *layers)
		{
			if (obj->GetActive())
				obj->Draw(window);
		}
	}
	window.setView(uiView);
	//uiMgr->Draw(window);
}

void PlayScene::Enter()
{
	Scene::Enter();

	Vector2i size = FRAMEWORK->GetWindowSize();

	worldView.setSize(size.x * 0.5f, size.y * 0.5f);
	worldView.setCenter(size.x * 0.5f, size.y * 0.75f);

	uiView.setSize(size.x, size.y);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);
}

void PlayScene::Exit()
{
}
