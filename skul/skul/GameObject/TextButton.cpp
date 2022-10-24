#include "TextButton.h"
#include "../Framework/InputMgr.h"

TextButton::TextButton()
	:isMouseOn(false), isSelected(false)
{
}

TextButton::~TextButton()
{
}

void TextButton::Init()
{
	TextObj::Init();
}

void TextButton::Update(float dt)
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

void TextButton::MouseOn()
{
	text.setOutlineColor({ 255, 255, 255, 255 });
}

void TextButton::MouseOff()
{
	text.setOutlineColor({ 255, 255, 255, 0 });
}

bool TextButton::GetSelected() const
{
	return isSelected;
}

void TextButton::Selected()
{
	if (ShowSelected != nullptr)
		ShowSelected();
	isSelected = true;
}

void TextButton::Deselected()
{
	if (StopShowing != nullptr)
		StopShowing();
	isSelected = false;
}
