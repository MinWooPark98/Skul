#pragma once
#include "Object.h"
#include "../Framework/ObjectPool.h"
#include "MapEditorDataMgr.h"

class DragRectTile;
class ColliderExampleUi;

class DisplayCollider : public Object
{
protected:
	ObjectPool<DragRectTile> displays;

	ColliderExampleUi* colliderChosen;

public:
	DisplayCollider();
	virtual ~DisplayCollider();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;

	void SetColliderChosen(Object* chosen) { colliderChosen = (ColliderExampleUi*)chosen; }
	list<DragRectTile*> Get() { return displays.GetUseList(); }

	void Load(const MapEditorDataMgr::MapData& data);
};
