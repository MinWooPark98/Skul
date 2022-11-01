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
		Gate,			// BC
		Tile,			// TL
		TileCollider,	// TL
		Count,
	};

protected:
	RectTile* canvas;

	Modes mode;
	string objName;

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

	void SetObjName(const string& name) { objName = name; }
	const string& GetObjName() { return objName; }
	void ClearObjName() { objName.clear(); }

	Modes GetMode() const { return mode; }
	void SetMode(Modes mode) { this->mode = mode; }

	void ChangeMode(int modeNum);

	MapEditorDataMgr* GetDataMgr() { return dataMgr; }
	SaveLoadUi* GetSaveLoadUi() { return saveLoadUi; }
};

