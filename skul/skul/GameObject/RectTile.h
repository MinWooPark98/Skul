#pragma once
#include "Tile.h"

class RectTile : public Tile
{
public:
	RectTile();
	virtual ~RectTile();

	virtual void Init() override;
	virtual void Release() override;

	void SetSize(const Vector2f& size) { ((RectangleShape*)tile)->setSize(size); }
	const Vector2f& GetSize() const { return ((RectangleShape*)tile)->getSize(); }	// 문제 생길 수 있음
};

