#pragma once
#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;
using namespace std;

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

		MapData(int type, string name, Vector2f pos, Vector2f size, int origin, int layer) 
			: objType(type), objName(name), xPos(pos.x), yPos(pos.y), width(size.x), height(size.y), origin(origin), layer(layer) {}
	};
	
private:
	list<MapData*> mapData;

public:
	MapEditorDataMgr();
	~MapEditorDataMgr();

	void SaveData();
	void ClearData();
};

