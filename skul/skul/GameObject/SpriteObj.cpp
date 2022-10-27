#include "SpriteObj.h"

SpriteObj::SpriteObj()
{
}

SpriteObj::~SpriteObj()
{
}

void SpriteObj::Draw(RenderWindow& window)
{
	Object::Draw(window);
	window.draw(sprite);
}

void SpriteObj::SetTexture(const Texture& tex)
{
	sprite.setTexture(tex, true);
}

void SpriteObj::SetOrigin(Origins origin)
{
	Utils::SetOrigin(sprite, origin);
	Utils::SetOrigin(hitbox, origin);
}

void SpriteObj::SetColor(Color color)
{
	sprite.setColor(color);
}
Vector2f SpriteObj::GetSize() const
{
	FloatRect rect = sprite.getLocalBounds();

	return Vector2f(rect.width, rect.height);
}

void SpriteObj::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	sprite.setPosition(position);
}

void SpriteObj::SetTextureRect(const IntRect& rect)
{
	sprite.setTextureRect(rect);
}
void SpriteObj::SetSize(Vector2f size)
{
	auto localSize = sprite.getLocalBounds();
	sprite.setScale({ size.x / localSize.width, size.y / localSize.height });
}
void SpriteObj::SetScale(Vector2f scale)
{
	sprite.setScale(scale);
}
const IntRect& SpriteObj::GetTextureRect() const
{
	return sprite.getTextureRect();
}

FloatRect SpriteObj::GetGlobalBounds() const
{
	return sprite.getGlobalBounds();
}
FloatRect SpriteObj::GetLocalBounds() const
{
	return sprite.getLocalBounds();
}
