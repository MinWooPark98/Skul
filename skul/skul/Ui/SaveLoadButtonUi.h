#pragma once
#include "../GameObject/Object.h"
#include <list>

class TextMouseButton;

class SaveLoadButtonUi : public Object
{
public:
protected:
	list<TextMouseButton*> buttons;

public:
	SaveLoadButtonUi();
	virtual ~SaveLoadButtonUi();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetPos(const Vector2f&) override;
};

