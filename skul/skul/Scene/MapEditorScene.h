#pragma once
#include "Scene.h"

class MapEditorDataMgr;
class SaveLoadUi;
class RectTile;

class MapEditorScene : public Scene
{
public:
	enum class Modes
	{
		None = -1,
		BackGround,		// BC
		BackObject,		// BC
		Enemies,		// BC
		NPC,			// BC
		Player,			// BC
		Reward,			// BC
		Tile,			// TL
		TileCollider,	// TL
		Count,
	};

	enum class Layer
	{
		BackGround,
		BackObject,
		Tile,
		ActivateObject,
		Player,
		Collider,
		Front,
		Count,
	};

protected:
	RectTile* canvas;
	vector<list<Object*>*> layOut;

	Modes mode;
	string objName;

	Vector2f objMousePos;

	MapEditorDataMgr* dataMgr;
	SaveLoadUi* saveLoadUi;

public:
	MapEditorScene();
	virtual ~MapEditorScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void Enter() override;
	virtual void Exit() override;

	const Vector2f& GetObjMousePos() const;

	void SetObjName(const string& name) { objName = name; }
	const string& GetObjName() { return objName; }
	void ClearObjName() { objName.clear(); }

	Modes GetMode() const { return mode; }
	void SetMode(Modes mode) { this->mode = mode; }

	void ChangeMode(int modeNum);
	vector<list<Object*>*>& GetLayout() { return layOut; }

	MapEditorDataMgr* GetDataMgr() { return dataMgr; }
	SaveLoadUi* GetSaveLoadUi() { return saveLoadUi; }
};

