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
	effectLimitCnt = 2;
}

void Ogre::Activate()
{
	// 아이템 생기면 추가
}
