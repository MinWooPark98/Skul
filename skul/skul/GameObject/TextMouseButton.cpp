#include "TextMouseButton.h"
#include "../Framework/InputMgr.h"

TextMouseButton::TextMouseButton()
	:isMouseOn(false), isSelected(false)
{
}

TextMouseButton::~TextMouseButton()
{
}

void TextMouseButton::Init()
{
	TextObj::Init();
}

void TextMouseButton::Update(float dt)
{
	Vector2f mousePos = InputMgr::GetMousePos();
	FloatRect textBound = text.getGlobalBounds();

	if (mousePos.x < textBound.left || mousePos.x > textBound.left + textBound.width ||
		mousePos.y < textBound.top || mousePos.y > textBound.top + textBound.height)
	{
		if (isMouseOn)
		{
			MouseOff();
			isMouseOn = false;
		}
		return;
	}
	isMouseOn = true;
	MouseOn();
	if (InputMgr::GetMouseButtonDown(Mouse::Left))
		Selected();
}

void TextMouseButton::MouseOn()
{
	text.setOutlineColor({ 255, 255, 255, 255 });
}

void TextMouseButton::MouseOff()
{
	text.setOutlineColor({ 255, 255, 255, 0 });
}

bool TextMouseButton::GetSelected() const
{
	return isSelected;
}

void TextMouseButton::Selected()
{
	if (ShowSelected != nullptr)
		ShowSelected();
	isSelected = true;
}

void TextMouseButton::Deselected()
{
	if (StopShowing != nullptr)
		StopShowing();
	isSelected = false;
}
