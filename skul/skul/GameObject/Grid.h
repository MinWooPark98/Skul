#pragma once
#include "../GameObject/Object.h"

class GridRectTile;

class Grid : public Object
{
protected:
	vector<vector<GridRectTile*>*> map;
	// 추후 GridTex에 있는 currTex, position 데이터 순회해가면서 저장할 예정

public:
	Grid();
	virtual ~Grid();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

