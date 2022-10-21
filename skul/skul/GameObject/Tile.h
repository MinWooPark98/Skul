#pragma once
#include "Object.h"
#include "../Framework/Utils.h"

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

	void SetRotation(float rotation);
	
	virtual void DrawTexture(const Texture* tex);
	virtual void EraseTexture();
	
	virtual void MarkOn();
	virtual void MarkOff();

	virtual const Texture* GetTexture() const;	// ���� ���� �� ���� ����Ȯ�ؼ� �ϴ� ���
};

