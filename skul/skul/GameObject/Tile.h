#pragma once
#include "Object.h"
#include "../Framework/Utils.h"
#include <functional>

class Tile : public Object
{
protected:
	Shape* tile;
	bool isMouseOn;

public:
	virtual ~Tile();

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual bool GetMouseOn() { return isMouseOn; }

	virtual void SetOrigin(Origins origin) { Utils::SetOrigin(*tile, origin); }
	virtual void SetPos(const Vector2f& pos) override;
	virtual void SetScale(const Vector2f& scale) { tile->setScale(scale); }
	virtual void SetRotation(float rotation);
	
	virtual void SetFillColor(Color color) { tile->setFillColor(color); }
	virtual void SetOutlineThickness(float t) { tile->setOutlineThickness(t); }
	
	virtual void SetTexture(const Texture* tex);
	const Texture* GetTexture() { return tile->getTexture(); }
	
	virtual void MarkOn();
	virtual void MarkOff();

	void SetMousePos(const Vector2f& mousePos);

	virtual const Texture* GetTexture() const;	// ���� ���� �� ���� ����Ȯ�ؼ� �ϴ� ���
};

