#include "GridRectTile.h"
#include "../Framework/InputMgr.h"
#include "../Scene/MapEditorScene.h"
#include "../Scene/SceneMgr.h"
#include "../Framework/Framework.h"
#include "../Ui/UiMgr.h"
#include "../DataTable/DataTableMGR.h"
#include "../DataTable/FilePathTable.h"
#include "../Framework/ResourceMgr.h"

GridRectTile::GridRectTile()
	:currTex(nullptr)
{
}

GridRectTile::~GridRectTile()
{
}

void GridRectTile::Init()
{
	RectTile::Init();
	tile->setFillColor({ 255, 255, 255, 0 });
}

void GridRectTile::Reset()
{
	RectTile::Reset();
	currTex = nullptr;
	name.clear();
}

void GridRectTile::Update(float dt)
{
	RectTile::Update(dt);
	MapEditorScene* mapEditorScene = ((MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor));
	Vector2f mousePos = mapEditorScene->GetObjMousePos();
	FloatRect tileBound = tile->getGlobalBounds();
	if (mousePos.x < tileBound.left || mousePos.x > tileBound.left + tileBound.width ||
		mousePos.y < tileBound.top || mousePos.y > tileBound.top + tileBound.height ||
		mapEditorScene->GetMode() != MapEditorScene::Modes::Tile ||
		InputMgr::GetMousePos().x >= FRAMEWORK->GetWindowSize().x * 0.9f)
	{
		if (isMouseOn)
		{
			MarkOff();
			isMouseOn = false;
		}
		return;
	}
	isMouseOn = true;
	MarkOn();
	if (InputMgr::GetMouseButton(Mouse::Left))
	{
		name = mapEditorScene->GetObjName();
		if (name.empty())
		{
			SetTexture(nullptr);
			return;
		}
		FilePathTable* filePath = DATATABLE_MGR->Get<FilePathTable>(DataTable::Types::FilePath);
		filePath->SetObjType((FilePathTable::ObjTypes)((int)mapEditorScene->GetMode()));
		SetTexture(RESOURCE_MGR->GetTexture(filePath->Get(name)));
	}
}

void GridRectTile::SetTexture(const Texture* tex)
{
	RectTile::SetTexture(tex);
	currTex = tex;
	if (tex == nullptr)
		tile->setFillColor({ 255, 255, 255, 0 });
	else
		tile->setFillColor({ 255, 255, 255, 255 });
}
