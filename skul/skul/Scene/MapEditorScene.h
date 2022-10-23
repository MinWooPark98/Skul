#pragma once
#include "Scene.h"

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
		Player,
		Collider,
		Front,
		Count,
	};

protected:
	vector<list<Object*>*> layOut;

	Modes mode;
	string objName;

	bool isPause;
	Vector2f objMousePos;

public:
	MapEditorScene();
	virtual ~MapEditorScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Draw(RenderWindow& window) override;
	virtual void Update(float dt) override;

	virtual void Enter() override;
	virtual void Exit() override;

	const Vector2f& GetObjMousePos() const;

	void SetObjName(const string& name) { objName = name; }
	const string& GetObjName() { return objName; }
	void ClearObjName() { objName.clear(); }

	Modes GetMode() const { return mode; }
	void SetMode(Modes mode) { this->mode = mode; }

	void ChangeMode(int modeNum);
};

