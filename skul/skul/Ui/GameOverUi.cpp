#include "GameOverUi.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/TextObj.h"
#include "../Framework/Framework.h"
#include "../Scene/SceneMgr.h"

GameOverUi::GameOverUi()
	:text(nullptr), timer(5.f)
{
}

GameOverUi::~GameOverUi()
{
}

void GameOverUi::Init()
{
	SpriteObj::Init();
	auto windowSize = (Vector2f)FRAMEWORK->GetWindowSize();
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/popup_frame.png"));
	SetOrigin(Origins::MC);
	SetPos(windowSize * 0.25f);
	text = new TextObj();
	text->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	text->SetSize(15);
	text->SetPos(windowSize * 0.25f);
}

void GameOverUi::Reset()
{
	SetActive(false);
	timer = 5.f;
}

void GameOverUi::Update(float dt)
{
	timer -= dt;
	if (timer < 0.f)
		SCENE_MGR->ChangeScene(Scenes::Title);
	text->SetText("   메뉴로 돌아갑니다       " + to_string((int)timer));
	text->AsciiToUnicode();
	text->SetOrigin(Origins::MC);
}

void GameOverUi::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	text->Draw(window);
}
