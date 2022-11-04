#include "Arachne.h"
#include "../../Framework/Animator.h"
#include "../../Framework/ResourceMgr.h"
#include "../../Scene/SceneMgr.h"
#include "../TextObj.h"
#include "../Player.h"

Arachne::Arachne()
	:NPC(Types::Arachne), isActive(false), cocoonAnim(nullptr)
{
}

Arachne::~Arachne()
{
}

void Arachne::Init()
{
	NPC::Init();
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("ArachneIdle"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("ArachneReady"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("ArachneAttack"));
	cocoonAnim = new Animator();
	cocoonAnim->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("Cocoon"));
	{
		AnimationEvent ev;
		ev.clipId = "ArachneReady";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip(ev.clipId)->GetFrameCount() - 1;
		ev.onEvent = bind(&Arachne::EvolveSkul, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Cocoon";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip(ev.clipId)->GetFrameCount() - 1;
		ev.onEvent = bind(&Arachne::OnCompleteEvolve, this);
		cocoonAnim->AddEvent(ev);
	}
	animator->Play("ArachneIdle");
	SetHitBox({ 0.f, 0.f, 142.f, 128.f });
	effectLimitCnt = 1;
}

void Arachne::Update(float dt)
{
	NPC::Update(dt);
	cocoonAnim->Update(dt);
	if (isActive)
	{
		if (Utils::Distance(player->GetPos(), evolvingPoint) < 1.f)
		{
			player->SetState(Player::States::Idle);
			player->SetDirection({ 0.f, 0.f });
			player->SetScale({ 1.f, 1.f });
			player->SetForcedAnimUpdate(false);
			animator->Play("ArachneReady");
			isActive = false;
		}
	}
}

void Arachne::Activate()
{
	if (!player->Evolvable())
		return;
	isActive = true;
	cocoonAnim->SetTarget(&player->GetSprite());
	player->SetForcedMode(true);
	player->SetForcedAnimUpdate(true);
	player->SetState(Player::States::Move);
	player->SetDirection(Utils::Normalize(evolvingPoint - player->GetPos()));
}

void Arachne::EvolveSkul()
{
	animator->Play("ArachneAttack");
	cocoonAnim->Play("Cocoon");
}

void Arachne::OnCompleteEvolve()
{
	player->SetForcedMode(false);
	player->EvolveSkul();
	animator->Play("ArachneIdle");
	cocoonAnim->Stop();
}

void Arachne::SetPos(const Vector2f& pos)
{
	NPC::SetPos(pos);
	auto hitBound = GetHitBounds();
	evolvingPoint = { position.x - hitBound.width, position.y };
}
