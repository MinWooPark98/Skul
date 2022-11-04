#include "Werewolf.h"
#include "../Player.h"
#include "../../Scene/SceneMgr.h"
#include "../../Scene/PlayScene.h"
#include "../../Scene/SceneMgr.h"
#include "../Collider.h"

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
	player->MeleeAttack(player->GetAttackDmg() * 2);
}

void Werewolf::Ripper()
{
	player->MeleeAttack(player->GetAttackDmg() * 2);
}
