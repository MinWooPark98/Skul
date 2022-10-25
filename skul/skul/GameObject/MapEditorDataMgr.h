#pragma once
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <list>

using namespace sf;
using namespace std;
using json = nlohmann::json;

class MapEditorDataMgr
{
public:
	struct MapData
	{
		int objType;
		string objName;

		float xPos;
		float yPos;

		float width;
		float height;

		int origin; // TL ~ BR
		int layer;
		
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(MapData, objType, objName, xPos, yPos, width, height, origin, layer)

		MapData() {}
		MapData(int type, string name, Vector2f pos, Vector2f size, int origin, int layer) 
			: objType(type), objName(name), xPos(pos.x), yPos(pos.y), width(size.x), height(size.y), origin(origin), layer(layer) {}
	};
	
private:
	vector<list<MapData>> mapData;

public:
	MapEditorDataMgr();
	~MapEditorDataMgr();

	void Init();
	void Release();

	void Reset();

	bool SaveData(const string& filePath);
	bool LoadData(const string& filePath);
	void ClearData();
};

