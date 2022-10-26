#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

using namespace sf;
using namespace std;

enum class LoopTypes
{
	Single,
	Loop,
};

struct AnimationFrame
{
	//string textureId;
	Texture* texture;
	IntRect coord;
	Vector2f origin;
	bool flipX;
	bool flipY;

	AnimationFrame(const vector<string>& row);
};

struct AnimationClip
{ 
	string id;
	LoopTypes loopType;
	int fps;
	vector<AnimationFrame> frames;

	int GetFrameCount() { return frames.size(); }
};

struct AnimationEvent
{
	string clipId;
	int frame;
	function<void()> onEvent;
};
