#pragma once
#include "../GameObject/TextObj.h"

class TextButtonUi : public TextObj
{
protected:
	bool isMouseOn;

public:
	TextButtonUi();
	virtual ~TextButtonUi();

	virtual void Init() override;
	virtual void Update(float dt) override;

	void EffectOn();
	void EffectOff();
};
