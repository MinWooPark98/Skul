#include "Werewolf.h"
#include "../Player.h"
#include "../../Scene/SceneMgr.h"
#include "../../Scene/PlayScene.h"
#include "../../Scene/SceneMgr.h"
#include "../Collider.h"
#include "../../Framework/SoundMgr.h"

Werewolf::Werewolf()
	:Skul(OffensiveTypes::Speed, Types::Werewolf, Tiers::None)
{
}

Werewolf::~Werewolf()
{
}

void Werewolf::Init()
{
	Skul::Init();
	skillSet.push_back(Skills::Predation);
	skillSet.push_back(Skills::Ripper);
}

void Werewolf::AttackA()
{
	SOUND_MGR->Play("sound/Atk_Sword_Small.wav");
}

void Werewolf::AttackB()
{
	SOUND_MGR->Play("sound/Atk_Sword_Small.wav");
}

void Werewolf::JumpAttack()
{
	SOUND_MGR->Play("sound/Atk_Sword_Small.wav");
}

void Werewolf::Predation()
{
	auto playerDirX = Utils::UnitizationFloat(player->GetLastDirX());
	player->Translate({ player->GetGlobalBounds().width * playerDirX, 0.f });
	Scene* currScene = SCENE_MGR->GetCurrentScene();
	auto& layOut = currScene->GetLayout();
	for (auto obj : *layOut[(int)Scene::Layer::Collider])
	{
		if (((Collider*)obj)->GetType() != Collider::Types::AllSide)
			continue;
		if (player->GetHitBounds().intersects(obj->GetHitBounds()))
		{
			if (playerDirX > 0.f)
				player->SetPos({ obj->GetHitBounds().left - player->GetHitBounds().width * 0.5f, player->GetPos().y });
			else
				player->SetPos({ obj->GetHitBounds().left + obj->GetHitBounds().width + player->GetHitBounds().width * 0.5f, player->GetPos().y });
			break;
		}
	}
	SOUND_MGR->Play("sound/Atk_Sword_Large.wav");
	player->MeleeAttack(player->GetAttackDmg() * 2);
}

void Werewolf::Ripper()
{
	SOUND_MGR->Play("sound/Atk_Sword_Large.wav");
	player->MeleeAttack(player->GetAttackDmg() * 2);
}
