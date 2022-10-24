#pragma once
#include "../GameObject/TextButton.h"
#include <list>

class TextButton;

class SaveLoadButtonUi : public Object
{
public:
protected:
	list<TextButton*> buttons;

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

