#include "Ogre.h"
#include "../../Framework/Animator.h"
#include "../../Framework/ResourceMgr.h"
#include "../../Scene/SceneMgr.h"
#include "../TextObj.h"
#include "../Player.h"

Ogre::Ogre()
	:NPC(Types::Ogre)
{
}

Ogre::~Ogre()
{
}

void Ogre::Init()
{
	NPC::Init();
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("OgreIdle"));
	animator->Play("OgreIdle");
	SetHitBox({ 0.f, 0.f, 227.f, 151.f });
}

void Ogre::Activate()
{
	Scene* currScene = SCENE_MGR->GetCurrentScene();
	Player* player = (Player*)currScene->FindGameObj("player");
	player->SetJumpableCount(player->SetJumpableCount() + 1);
}
