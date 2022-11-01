#include "TitleScene.h"
#include "../GameObject/SpriteObj.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/TextObj.h"
#include "../Framework/Framework.h"
#include "../Framework/InputMgr.h"
#include "../Scene/SceneMgr.h"
#include "../GameObject/TextButtons.h"
#include "../Framework/SoundMgr.h"

TitleScene::TitleScene()
	:Scene(Scenes::Title), buttons(nullptr)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	Vector2f windowSize = (Vector2f)FRAMEWORK->GetWindowSize();

	SpriteObj* background = new SpriteObj();
	background->Init();
	background->SetTexture(*RESOURCE_MGR->GetTexture("graphics/title.png"));
	background->SetSize(windowSize);
	objList.push_back(background);

	buttons = new TextButtons();
	buttons->Init();
	buttons->SetPos({ windowSize.x * 0.5f, windowSize.y * 0.4f });
	buttons->SetDistance(50.f);
	buttons->AddButton("플레이");
	buttons->AddButton("맵 에디터");
	buttons->AddButton("종료하기");
	objList.push_back(buttons);
}

void TitleScene::Reset()
{
	for (auto& obj : objList)
	{
		obj->Reset();
	}
}

void TitleScene::Update(float dt)
{
	Scene::Update(dt);
	if(InputMgr::GetKeyDown(Keyboard::Escape))
		FRAMEWORK->GetWindow().close();

	if (InputMgr::GetKeyDown(Keyboard::Enter))
	{
		switch (buttons->GetVecIdx())
		{
		case 0:
			SCENE_MGR->ChangeScene(Scenes::MonsterScene);
			break;
		case 1:
			SCENE_MGR->ChangeScene(Scenes::MapEditor);
			break;
		case 2:
			FRAMEWORK->GetWindow().close();
			break;
		}
	}
}

void TitleScene::Enter()
{
	Scene::Enter();

	Vector2i size = FRAMEWORK->GetWindowSize();

	worldView.setSize(size.x, size.y);
	worldView.setCenter(size.x * 0.5f, size.y * 0.5f);

	uiView.setSize(size.x, size.y);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);

	SOUND_MGR->Play("sound/MainTitle.wav", true);
}

void TitleScene::Exit()
{
	Scene::Exit();
	Reset();
}
