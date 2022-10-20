#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include "../3rd/SingleTon.h"
#include "../3rd/rapidcsv.h"

using namespace sf;
using namespace std;

enum class ResourceTypes
{
	Texture,
	Font,
	SoundBuffer,
};

class ResourceMgr : public Singleton<ResourceMgr>
{
private:
	map<string, Texture*> texMap;
	map<string, Font*> fontMap;
	map<string, SoundBuffer*> soundMap;
public:
	ResourceMgr();
	~ResourceMgr();

	static string FilePath;

	void ReleaseAll();

	bool LoadAll();
	bool Load(ResourceTypes type, string id);
	bool LoadTexture(string id);
	bool LoadFont(string id);
	bool LoadSoundBuffer(string id);

	Texture* GetTexture(string id) const;
	Font* GetFont(string id) const;
	SoundBuffer* GetSoundBuffer(string id) const;
};

#define RESOURCE_MGR (ResourceMgr::GetInstance())
