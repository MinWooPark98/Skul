#include "TextObj.h"
#include "../Framework/Utils.h"

TextObj::TextObj()
{
}

TextObj::~TextObj()
{
}

void TextObj::Init()
{
	Object::Init();
}

void TextObj::Update(float dt)
{
	Object::Update(dt);
}

void TextObj::Draw(RenderWindow& window)
{
	window.draw(text);
}

void TextObj::SetPos(Vector2f position)
{
	Object::SetPos(position);
	text.setPosition(position);
}

void TextObj::SetFont(Font& font)
{
	text.setFont(font);
}

void TextObj::SetText(string str)
{
	text.setString(str);
}
void TextObj::SetOrigin(Origins origin)
{
	Utils::SetOrigin(text, origin);
}
const string TextObj::GetText() const
{
	return text.getString();
}
