#pragma once
#include "SpriteObj.h"

class Animator;
class TextObj;

class Gate : public SpriteObj
{
public:
	enum class Types
	{
		None = -1,
		Monster,
		NPC,
		Boss,
	};
protected:
	Types type;
	Animator* animator;

	TextObj* activate;

public:
	Gate();
	virtual ~Gate();
	
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetPos(const Vector2f& pos) override;
	virtual void SetType(Types type) { this->type = type; }

	virtual void Activate();
};

