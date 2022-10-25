#include "PlayScene.h"

PlayScene::PlayScene()
	:Scene(Scenes::Play)
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
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
}

void PlayScene::Exit()
{
}
