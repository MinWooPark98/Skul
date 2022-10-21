#pragma once
#include "Object.h"
#include "../Framework/Utils.h"

class Tile : public Object
{
protected:
	RectangleShape tile;
	bool isMouseOn;

public:
	Tile();
	virtual ~Tile();

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	bool GetMouseOn() { return isMouseOn; }

	void SetOrigin(Origins origin) { Utils::SetOrigin(tile, origin); }
	void SetSize(const Vector2f& size) { tile.setSize(size); }
	virtual void SetPos(const Vector2f& pos) override;
	
	void DrawTexture(const Texture* tex);
	void EraseTexture();
	
	void MarkOn();
	void MarkOff();
	
	Vector2f GetSize() const { return tile.getSize(); }
	const Texture* GetTexture() const;	// 문제 생길 수 있음 부정확해서 일단 써둠
};

