#include "PlayerUi.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/Player.h"
#include "../GameObject/Skul/Skul.h"
#include "../Scene/SceneMgr.h"

PlayerUi::PlayerUi()
	:player(nullptr)
{
}

PlayerUi::~PlayerUi()
{
}

void PlayerUi::Init()
{
	SpriteObj::Init();
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/player/player_ui_frame.png"));
	symbol.Init();
	skillAIcon.Init();
	skillBFrame.SetTexture(*RESOURCE_MGR->GetTexture("graphics/player/player_skill2_frame.png"));
	skillBFrame.Init();
	skillBFrame.SetOrigin(Origins::MC);
	skillBFrame.SetActive(false);
	skillBIcon.Init();
	skillBIcon.SetActive(false);
	currHpBar.setFillColor({ 255, 0, 255, 255 });
	currHpBar.setSize({ 120.f, 9.f });
	Utils::SetOrigin(currHpBar, Origins::ML);
}

void PlayerUi::Update(float dt)
{
	currHpBar.setSize({ 120.f * player->GetHpRatio(), 9.f });
}

void PlayerUi::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	symbol.Draw(window);
	skillAIcon.Draw(window);
	if (skillBFrame.GetActive())
	{
		skillBFrame.Draw(window);
		skillBIcon.Draw(window);
	}
	window.draw(currHpBar);
}

void PlayerUi::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	FloatRect bound = GetGlobalBounds();
	symbol.SetPos({ pos.x + bound.width * 0.17f, pos.y - bound.height * 0.65f });
	skillAIcon.SetPos({ pos.x + bound.width * 0.42f, pos.y - bound.height * 0.6f });
	skillBFrame.SetPos({ pos.x + bound.width * 0.7f, pos.y - bound.height * 0.6f });
	skillBIcon.SetPos({ pos.x + bound.width * 0.7f, pos.y - bound.height * 0.6f });
	currHpBar.setPosition({ pos.x + bound.width * 0.25f, pos.y - bound.height * 0.25f });
}

void PlayerUi::SetPlayer(const Player* player)
{
	this->player = player;
	ResetUi();
}

void PlayerUi::ResetUi()
{
	const Skul* mainSkul = player->GetMainSkul();
	if (mainSkul != nullptr)
	{
		symbol.SetTexture(*mainSkul->GetSymbol());
		symbol.SetOrigin(Origins::MC);
		skillAIcon.SetTexture(*mainSkul->GetSkillAIcon());
		skillAIcon.SetOrigin(Origins::MC);
		if (mainSkul->GetTier() >= Skul::Tiers::Unique || mainSkul->GetType() == Skul::Types::Default)
		{
			skillBIcon.SetTexture(*mainSkul->GetSkillBIcon());
			skillBIcon.SetOrigin(Origins::MC);
			skillBFrame.SetActive(true);
			skillBIcon.SetActive(true);
		}
		else
		{
			skillBFrame.SetActive(false);
			skillBIcon.SetActive(false);
		}
	}
}
