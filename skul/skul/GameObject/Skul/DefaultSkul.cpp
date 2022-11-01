#include "DefaultSkul.h"
#include "../../Framework/ResourceMgr.h"
#include "../Player.h"
#include "../../Scene/SceneMgr.h"
#include "../../Scene/PlayScene.h"
#include "../SpriteObj.h"
#include "../Enemy/Enemy.h"

DefaultSkul::DefaultSkul()
	:Skul(Types::Default, Tiers::Normal), head(nullptr), isHeadFlying(false), headSpeed(500.f), isHeadOn(true),
	flyingDuration(0.8f), flyingTimer(0.f), separateTime(2.f), separateTimer(0.f), enemyCollided(false)
{
}

DefaultSkul::~DefaultSkul()
{
}

void DefaultSkul::Init()
{
	type = Types::Default;
	tier = Tiers::Normal;

	SetSymbol(RESOURCE_MGR->GetTexture("graphics/player/default/symbol.png"));
	SetSkillAIcon(RESOURCE_MGR->GetTexture("graphics/player/default/skull_throw.png"));
	SetSkillBIcon(RESOURCE_MGR->GetTexture("graphics/player/default/rebone.png"));

	head = new SpriteObj();
	head->Init();
	head->SetRotation(10.f);
	head->SetGravity(4.f);
	head->SetTexture(*RESOURCE_MGR->GetTexture("graphics/player/default/head.png"));
	head->SetOrigin(Origins::MC);
	head->SetHitBox(head->GetGlobalBounds());
	head->SetHitBoxOrigin(Origins::MC);
	head->SetActive(false);

	Skul::Init();
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulIdle"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulWalk"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulDash"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulJump"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulFall"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulFallRepeat"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulAttackA"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulAttackB"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulJumpAttack"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulSkillA"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulIdle_no_head"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulWalk_no_head"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulDash_no_head"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulJump_no_head"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulFall_no_head"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulFallRepeat_no_head"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulAttackA_no_head"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulAttackB_no_head"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulJumpAttack_no_head"));
	{
		AnimationEvent ev;
		ev.clipId = "DefaultSkulFall";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulFall")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::FallRepeated, this);
		animator->AddEvent(ev);
		AnimationEvent ev2;
		ev2.clipId = "DefaultSkulFall_no_head";
		ev2.frame = ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulFall_no_head")->GetFrameCount() - 1;
		ev2.onEvent = bind(&Skul::FallRepeated, this);
		animator->AddEvent(ev2);
	}
	{
		AnimationEvent ev;
		ev.clipId = "DefaultSkulAttackA";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulAttackA")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAttackA, this);
		animator->AddEvent(ev);
		AnimationEvent ev2;
		ev2.clipId = "DefaultSkulAttackA_no_head";
		ev2.frame = ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulAttackA_no_head")->GetFrameCount() - 1;
		ev2.onEvent = bind(&Skul::OnCompleteAttackA, this);
		animator->AddEvent(ev2);
	}
	{
		AnimationEvent ev;
		ev.clipId = "DefaultSkulAttackB";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulAttackB")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAttackB, this);
		animator->AddEvent(ev);
		AnimationEvent ev2;
		ev2.clipId = "DefaultSkulAttackB_no_head";
		ev2.frame = ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulAttackB_no_head")->GetFrameCount() - 1;
		ev2.onEvent = bind(&Skul::OnCompleteAttackB, this);
		animator->AddEvent(ev2);
	}
	{
		AnimationEvent ev;
		ev.clipId = "DefaultSkulJumpAttack";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulJumpAttack")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAction, this);
		animator->AddEvent(ev);
		AnimationEvent ev2;
		ev2.clipId = "DefaultSkulJumpAttack_no_head";
		ev2.frame = ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulJumpAttack_no_head")->GetFrameCount() - 1;
		ev2.onEvent = bind(&Skul::OnCompleteAction, this);
		animator->AddEvent(ev2);
	}
	{
		AnimationEvent ev;
		ev.clipId = "DefaultSkulSkillA";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulSkillA")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAction, this);
		animator->AddEvent(ev);
	}
}

void DefaultSkul::Update(float dt)
{
	Skul::Update(dt);
	if (isHeadFlying)
	{
		flyingTimer += dt;
		if (flyingTimer >= flyingDuration)
		{
			isHeadFlying = false;
			flyingTimer = 0.f;
			head->SetDirection({ 0.f, 0.f });
			head->SetGravityApply(true);
		}
	}
	else
	{
		headSpeed -= 100.f * dt;
		if (headSpeed < 0.f)
			headSpeed = 0.f;
	}

	if (!isHeadOn)
	{
		head->Update(dt);
		separateTimer += dt;
		Scene* currScene = SCENE_MGR->GetCurrentScene();
		if (separateTimer > separateTime)
			OnCompleteSkillA();

		auto& layOut = currScene->GetLayout();
		if (!enemyCollided)
		{
			for (auto obj : *layOut[(int)Scene::Layer::Enemy])
			{
				if (!obj->GetActive())
					continue;
				if (HeadOnCollision(obj->GetHitBounds()))
				{
					enemyCollided = true;
					((Enemy*)obj)->OnHit(40);
				}
			}
		}
		for (auto obj : *layOut[(int)Scene::Layer::Collider])
		{
			if (HeadOnCollision(obj->GetHitBounds()))
				enemyCollided = true;
		}
		if (head->GetDirection().y > 5.f)
			head->SetDirection({ head->GetDirection().x, 5.f });

		if (headSpeed > 0.f)
			head->Rotate();
		else if (head->GetHitBounds().intersects(player->GetHitBounds()))
			OnCompleteSkillA();
		head->Translate(head->GetDirection() * headSpeed * dt);
	}
}

void DefaultSkul::Draw(RenderWindow& window)
{
	if (!isHeadOn)
		head->Draw(window);
}

void DefaultSkul::SwitchDevMode()
{
	Object::SwitchDevMode();
	head->SwitchDevMode();
}

void DefaultSkul::Idle()
{
	if (isHeadOn)
		animator->Play("DefaultSkulIdle");
	else
		animator->Play("DefaultSkulIdle_no_head");
}

void DefaultSkul::Move()
{
	if (isHeadOn)
		animator->Play("DefaultSkulWalk");
	else
		animator->Play("DefaultSkulWalk_no_head");
}

void DefaultSkul::Dash()
{
	if (isHeadOn)
		animator->Play("DefaultSkulDash");
	else
		animator->Play("DefaultSkulDash_no_head");
}

void DefaultSkul::Jump()
{
	if (isHeadOn)
		animator->Play("DefaultSkulJump");
	else
		animator->Play("DefaultSkulJump_no_head");
}

void DefaultSkul::AttackA()
{
	if (isHeadOn)
		animator->Play("DefaultSkulAttackA");
	else
		animator->Play("DefaultSkulAttackA_no_head");
}

void DefaultSkul::AttackB()
{
	if (isHeadOn)
		animator->Play("DefaultSkulAttackB");
	else
		animator->Play("DefaultSkulAttackB_no_head");
}

void DefaultSkul::JumpAttack()
{
	if (isHeadOn)
		animator->Play("DefaultSkulJumpAttack");
	else
		animator->Play("DefaultSkulJumpAttack_no_head");
}

void DefaultSkul::Fall()
{
	if (isHeadOn)
		animator->Play("DefaultSkulFall");
	else
		animator->Play("DefaultSkulFall_no_head");
}

void DefaultSkul::FallRepeated()
{
	if (isHeadOn)
		animator->Play("DefaultSkulFallRepeat");
	else
		animator->Play("DefaultSkulFallRepeat_no_head");
}

void DefaultSkul::SkillA()
{
	if (isHeadOn)
	{
		isHeadOn = false;
		isHeadFlying = true;
		enemyCollided = false;
		head->SetActive(true);
		head->SetGravityApply(false);
		headSpeed = 500.f;
		head->SetPos({ player->GetPos().x, player->GetPos().y - player->GetHitBounds().height });
		head->SetDirection({ player->GetLastDirX(), 0.f });
		animator->Play("DefaultSkulSkillA");
		return;
	}
	player->SetState(Player::States::Idle);
}

void DefaultSkul::SkillB()
{
	if (!isHeadOn)
	{
		OnCompleteSkillA();
		player->SetPos({ head->GetPos().x, head->GetPos().y - player->GetHitBounds().height });
	}
	else
		player->SetState(Player::States::Idle);
}

void DefaultSkul::SetAnimEvent(Player* player)
{
	AnimationEvent ev;
	ev.clipId = "DefaultSkulAttackA";
	ev.frame = 2;
	ev.onEvent = bind(&Player::MeleeAttack, player);
	animator->AddEvent(ev);
	AnimationEvent ev2;
	ev2.clipId = "DefaultSkulAttackB";
	ev2.frame = 1;
	ev2.onEvent = bind(&Player::MeleeAttack, player);
	animator->AddEvent(ev2);
	AnimationEvent ev3;
	ev3.clipId = "DefaultSkulJumpAttack";
	ev3.frame = 1;
	ev3.onEvent = bind(&Player::MeleeAttack, player);
	animator->AddEvent(ev3);
}

void DefaultSkul::OnCompleteSkillA()
{
	isHeadOn = true;
	isHeadFlying = false;
	flyingTimer = 0.f;
	separateTimer = 0.f;
	head->SetDirection({ 0.f, 0.f });
	head->SetActive(false);
	player->SetState(Player::States::Idle);
	animator->Play("DefaultSkulIdle");
}

bool DefaultSkul::HeadOnCollision(const FloatRect& blockBound)
{
	FloatRect hitBound = head->GetHitBounds();
	if (!hitBound.intersects(blockBound))
		return false;
	isHeadFlying = false;
	head->SetGravityApply(true);
	headSpeed *= 0.5f;
	Vector2f hitCenter(hitBound.left + hitBound.width * 0.5f, hitBound.top + hitBound.height * 0.5f);
	auto& headDir = head->GetDirection();
	if (hitCenter.y - hitBound.height * 0.3f > blockBound.top + blockBound.height && direction.y < 0.f)
	{
		head->Translate({ 0.f, blockBound.top + blockBound.height - hitBound.top });
		head->SetDirection({ headDir.x, 0.f });
		return true;
	}
	else if (hitCenter.y + hitBound.height * 0.3f < blockBound.top && direction.y > 0.f)
	{
		head->Translate({ 0.f, blockBound.top - (hitBound.top + hitBound.height) });
		head->SetDirection({ headDir.x, 0.f });
		return true;
	}

	if (hitCenter.x > blockBound.left + blockBound.width && head->GetDirection().x < 0.f)
	{
		head->Translate({ blockBound.left + blockBound.width - hitBound.left, 0.f });
		head->SetDirection({ -headDir.x, headDir.y });
		return true;
	}
	else if (hitCenter.x < blockBound.left && head->GetDirection().x > 0.f)
	{
		head->Translate({ blockBound.left - (hitBound.left + hitBound.width), 0.f });
		head->SetDirection({ -headDir.x, headDir.y });
		return true;
	}
	return false;
}
