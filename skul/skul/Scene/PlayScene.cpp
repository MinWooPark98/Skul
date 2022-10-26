#include "PlayScene.h"
#include "../GameObject/Player.h"
#include "../GameObject/Skul/DefaultSkul.h"
#include "../Framework/Framework.h"

PlayScene::PlayScene()
	:Scene(Scenes::Play)
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	Skul* skul = new DefaultSkul();
	skul->Init();

	Player* player = new Player();
	player->Init();
	objList.push_back(player);
	player->SetSkul(skul);
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
	Scene::Update(dt);
}

void PlayScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}

void PlayScene::Enter()
{
	Scene::Enter();

	Vector2i size = FRAMEWORK->GetWindowSize();

	worldView.setSize(size.x, size.y);
	worldView.setCenter(size.x * 0.5f, size.y * 0.5f);

	uiView.setSize(size.x, size.y);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);
}

void PlayScene::Exit()
{
}
