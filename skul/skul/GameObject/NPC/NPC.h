#pragma once
#include "../SpriteObj.h"

class Animator;
class TextObj;
class Player;

class NPC : public SpriteObj
{
public:
	enum class Types
	{
		None = -1,
		Witch,
		Ogre,
		FoxHuman,
		Arachne,
	};

protected:
	Types type;
	Animator* animator;

	TextObj* activate;

	int effectLimitCnt;
	int effectCnt;

	Player* player;

public:
	NPC(Types type);
	virtual ~NPC();

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetPos(const Vector2f& pos) override;

	virtual void Activate() {}
};

