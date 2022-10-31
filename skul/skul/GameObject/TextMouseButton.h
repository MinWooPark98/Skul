#pragma once
#include "TextObj.h"
#include <functional>

class TextMouseButton : public TextObj
{
protected:
	bool isMouseOn;
	bool isSelected;

public:
	TextMouseButton();
	virtual ~TextMouseButton();

	virtual void Init() override;
	virtual void Update(float dt) override;

	virtual void MouseOn();
	virtual void MouseOff();

	bool GetSelected() const;

	virtual void Selected();
	function<void()> ShowSelected;
	virtual void Deselected();
	function<void()> StopShowing;
};

