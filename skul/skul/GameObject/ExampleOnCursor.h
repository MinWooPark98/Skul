#pragma once
#include "SpriteObj.h"

class ExampleOnCursor : public SpriteObj
{
protected:
	string recentName;

public:
	ExampleOnCursor();
	~ExampleOnCursor();

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};
