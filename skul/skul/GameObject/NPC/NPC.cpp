#include "NPC.h"
#include "../../Framework/Animator.h"
#include "../TextObj.h"
#include "../../Framework/ResourceMgr.h"
#include "../../Scene/SceneMgr.h"
#include "../../Framework/InputMgr.h"
#include "../Player.h"

NPC::NPC(Types type)
	:type(type), animator(nullptr), activate(nullptr), effectLimitCnt(0), effectCnt(0), player(nullptr)
{
}

NPC::~NPC()
{
}

void NPC::Init()
{
	SpriteObj::Init();
	animator = new Animator();
	animator->SetTarget(&sprite);
	SetOrigin(Origins::BC);

	activate = new TextObj();
	activate->Init();
	activate->SetActive(false);
	activate->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	activate->SetSize(10.f);
	activate->SetText("F      ��ȭ�ϱ�");
	activate->AsciiToUnicode();
	activate->SetOrigin(Origins::TC);
}

void NPC::Reset()
{
	effectCnt = 0;
}

void NPC::Release()
{
	SpriteObj::Release();
}

void NPC::Update(float dt)
{
	SpriteObj::Update(dt);
	if (animator != nullptr)
		animator->Update(dt);
	Utils::SetOrigin(hitbox, Origins::BC);
	Scene* currScene = SCENE_MGR->GetCurrentScene();
	player = (Player*)currScene->FindGameObj("player");
	if (player->GetHitBounds().intersects(GetHitBounds()))
	{
		activate->SetActive(true);
		if (InputMgr::GetKeyDown(Keyboard::F) && effectCnt < effectLimitCnt)
			Activate();
	}
	else
		activate->SetActive(false);
}

void NPC::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	if(activate->GetActive())
		activate->Draw(window);
}

void NPC::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	activate->SetPos({ pos.x, pos.y + 10.f });
}
