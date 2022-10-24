#pragma once
#include "Object.h"
#include "../Framework/ObjectPool.h"
#include <list>

class SpriteObj;

class DisplayObj : public Object
{
protected:
	vector<list<SpriteObj*>*> objSeperated;

	ObjectPool<SpriteObj> displays;

public:
	DisplayObj();
	virtual ~DisplayObj();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;

	vector<list<SpriteObj*>*>& Get() { return objSeperated; }
};
