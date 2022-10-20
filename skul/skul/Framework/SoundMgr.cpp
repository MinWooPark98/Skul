#include "SoundMgr.h"
#include "ResourceMgr.h"

SoundMgr::SoundMgr()
	: TotalChannels(64), volume(100.f)
{
}

SoundMgr::~SoundMgr()
{
	Release();
}

void SoundMgr::Init()
{
	Release();

	for (int i = 0; i < TotalChannels; ++i)
	{
		waiting.push_back(new Sound());
	}
}

void SoundMgr::Release()
{
	for (auto sound : waiting)
	{
		delete sound;
	}
	waiting.clear();

	for (auto sound : playing)
	{
		delete sound;
	}
	playing.clear();
}

void SoundMgr::Play(string id, bool loop)
{
	if (waiting.empty())
	{
		return;
	}

	Sound* sound = waiting.front();
	waiting.pop_front();

	SoundBuffer* sBuffer = RESOURCE_MGR->GetSoundBuffer(id);
	sound->setBuffer(*sBuffer);
	sound->setLoop(loop);
	sound->setVolume(volume);
	sound->play();
	playing.push_back(sound);
}

void SoundMgr::StopAll()
{
	for (auto sound : playing)
	{
		sound->stop();
	}
}

void SoundMgr::Update()
{
	auto it = playing.begin();
	while (it != playing.end())
	{
		if ((*it)->getStatus() == SoundSource::Stopped)
		{
			(*it)->resetBuffer();
			waiting.push_back(*it);
			it = playing.erase(it);
		}
		else
		{
			++it;
		}
	}
}
