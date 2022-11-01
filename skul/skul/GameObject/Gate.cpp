#include "Gate.h"
#include "../Framework/Animator.h"
#include "TextObj.h"
#include "../Framework/ResourceMgr.h"
#include "../Scene/SceneMgr.h"
#include "../Framework/InputMgr.h"
#include "../Scene/SceneMgr.h"

Gate::Gate()
	:type(Types::None), animator(nullptr), activate(nullptr)
{
}

Gate::~Gate()
{
}

void Gate::Init()
{
	SpriteObj::Init();
	animator = new Animator();
	animator->SetTarget(&sprite);
	SetOrigin(Origins::BC);

	string clip;
	switch (type)
	{
	case Gate::Types::Monster:
		clip = "MonsterGateIdle";
		SetHitBox({ 0.f, 0.f, 176.f, 128.f });
		break;
	case Gate::Types::NPC:
		clip = "NpcGateIdle";
		SetHitBox({ 0.f, 0.f, 215.f, 159.f });
		break;
	case Gate::Types::Boss:
		clip = "BossGateIdle";
		SetHitBox({ 0.f, 0.f, 221.f, 158.f });
		break;
	default:
		break;
	}
	SetHitBoxOrigin(Origins::BC);
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip(clip));
	animator->Play(clip);

	activate = new TextObj();
	activate->Init();
	activate->SetActive(false);
	activate->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	activate->SetSize(10.f);
	activate->SetText("F      들어가기");
	activate->AsciiToUnicode();
	activate->SetOrigin(Origins::TC);
}

void Gate::Release()
{
}

void Gate::Update(float dt)
{
	SpriteObj::Update(dt);
	if (animator != nullptr)
		animator->Update(dt);
	Utils::SetOrigin(hitbox, Origins::BC);
	Scene* currScene = SCENE_MGR->GetCurrentScene();
	Object* player = currScene->FindGameObj("player");
	if (player->GetHitBounds().intersects(GetHitBounds()))
	{
		activate->SetActive(true);
		if (InputMgr::GetKeyDown(Keyboard::F))
			Activate();
	}
	else
		activate->SetActive(false);
}

void Gate::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	if (activate->GetActive())
		activate->Draw(window);
}

void Gate::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	activate->SetPos({ pos.x, pos.y + 10.f });
}

void Gate::Activate()
{
	switch (type)
	{
	case Gate::Types::Monster:
		SCENE_MGR->ChangeScene(Scenes::MonsterScene);
		break;
	case Gate::Types::NPC:
		SCENE_MGR->ChangeScene(Scenes::NpcScene);
		break;
	case Gate::Types::Boss:
		// 보스 맵 없음
		SCENE_MGR->ChangeScene(Scenes::Title);
		break;
	default:
		break;
	}
}
