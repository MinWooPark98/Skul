#pragma once
#include "../3rd/Singleton.h"
#include <SFML/Audio.hpp>
#include <list>

using namespace std;
using namespace sf;

class SoundMgr : public Singleton<SoundMgr>
{
private:
	list<Sound*> playing;
	list<Sound*> waiting;
	float volume;

public:
	SoundMgr();
	~SoundMgr();

	const int TotalChannels;

	void Init();
	void Release();

	void Play(string id, bool loop = false);
	void StopAll();

	void Update();
};

#define SOUND_MGR (SoundMgr::GetInstance())
