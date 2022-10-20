#pragma once
#include "Object.h"
#include "../Framework/Utils.h"

class Tile : public Object
{
protected:
	RectangleShape tile;
	bool isMouseOn;

public:
	Tile(const Vector2f& size, const Vector2f& pos);
	virtual ~Tile();

	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	bool GetMouseOn() { return isMouseOn; }

	void SetOrigin(Origins origin) { Utils::SetOrigin(tile, origin); }
	void SetSize(const Vector2f& size) { tile.setSize(size); }
	void DrawTexture(const Texture* tex);
	void EraseTexture();
	void MarkOn();
	void MarkOff();
	Vector2f GetSize() const { return tile.getSize(); }
};

