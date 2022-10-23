#pragma once
#include "Scene.h"

class Tile;

class MapEditorScene : public Scene
{
public:
	enum class Modes
	{
		None = -1,
		BackGround,
		BackObject,
		Enemies,
		NPC,
		Player,
		Reward,
		Tile,
		TileCollider,
		Count,
	};

	enum class Layer
	{
		Canvas,
		BackGround,
		BackObject,
		ActivateObject,
		Tile,
		Collider,
		Player,
		Count,
	};

protected:
	map<Layer, list<Object*>*> layOut;

	Modes mode;
	string objName;

	bool isPause;

public:
	MapEditorScene();
	virtual ~MapEditorScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Draw(RenderWindow& window) override;
	virtual void Update(float dt) override;

	virtual void Enter() override;
	virtual void Exit() override;

	const Vector2f& ObjMousePos() const;

	void SetObjName(const string& name) { objName = name; }
	const string& GetObjName() { return objName; }
	void ClearObjName() { objName.clear(); }

	Modes GetMode() const { return mode; }
	void SetMode(Modes mode) { this->mode = mode; }

	void ChangeMode(int modeNum);
};

