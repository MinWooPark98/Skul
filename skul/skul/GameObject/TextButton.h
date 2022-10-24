#pragma once
#include "TextObj.h"

class TextButton : public TextObj
{
protected:
	bool isMouseOn;
	bool isSelected;

public:
	TextButton();
	virtual ~TextButton();

	virtual void Init() override;
	virtual void Update(float dt) override;

	virtual void MouseOn();
	virtual void MouseOff();

	bool GetSelected() const;

	virtual void Selected();
	virtual void Deselected();
};

