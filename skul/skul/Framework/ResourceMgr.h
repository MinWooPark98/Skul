#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

#include "../3rd/Singleton.h"
#include "../3rd/rapidcsv.h"
#include "AnimationClip.h"

using namespace std;
using namespace sf;

enum class ResourceTypes
{
	Texture,
	Font,
	SoundBuffer,
	AnimationClip,
};

class ResourceMgr : public Singleton<ResourceMgr>
{
private:
	map<string, Texture*> texMap;
	map<string, Font*> fontMap;
	map<string, SoundBuffer*> soundMap;
	map<string, AnimationClip*> animationClipMap;

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
	bool LoadAnimationClip(string id);

	Texture* GetTexture(string id);
	Font* GetFont(string id);
	SoundBuffer* GetSoundBuffer(string id);
	AnimationClip* GetAnimationClip(string id);
};

#define RESOURCE_MGR (ResourceMgr::GetInstance())