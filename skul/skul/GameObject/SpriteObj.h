#pragma once
#include "Object.h"

class SpriteObj : public Object
{
protected:
	Sprite sprite;
public:
	SpriteObj();
	virtual ~SpriteObj();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetTexture(Texture& tex);
};

