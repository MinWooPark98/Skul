#pragma once
#include "Scene.h"

class Tile;

class MapEditorScene : public Scene
{
protected:
	const Texture* currTex;

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

	void SetTexture(const Texture* tex) { currTex = tex; }
	const Texture* GetTexture() { return currTex; }
};

