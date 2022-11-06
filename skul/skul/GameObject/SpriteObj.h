#pragma once
#include "Object.h"
#include "../Framework/Utils.h"

class SpriteObj :public Object
{
protected:
	Sprite sprite;

public:
	SpriteObj();
	virtual ~SpriteObj();

	virtual void Draw(RenderWindow& window) override;

	void SetTexture(const Texture& tex);
	void SetOrigin(Origins origin);
	void SetColor(Color color);
	Vector2f GetSize()const;

	Sprite& GetSprite() { return sprite; }
	virtual void SetPos(const Vector2f& pos) override;
	void SetTextureRect(const IntRect& rect);
	const IntRect& GetTextureRect()const;
	void SetSize(Vector2f size);
	void SetScale(Vector2f scale);
	void SetHitBoxOrigin(Origins origin) { Utils::SetOrigin(hitbox, origin); }
	void SetHitBoxOrigin(const Vector2f& origin) { hitbox.setOrigin(origin); }
	void Rotate() { sprite.rotate(rotation); }

	FloatRect GetGlobalBounds() const;
	FloatRect GetLocalBounds() const;
};

