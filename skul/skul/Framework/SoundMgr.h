#pragma once
#include "../3rd/SingleTon.h"
#include <SFML/Audio.hpp>
#include <list>

using namespace sf;
using namespace std;

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

