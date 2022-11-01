#pragma once
#include "../GameObject/SpriteObj.h"

class TextObj;

class GameOverUi : public SpriteObj
{
protected:
	TextObj* text;

	float timer;

public:
	GameOverUi();
	virtual ~GameOverUi();

	virtual void Init();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};

