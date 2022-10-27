#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class UnderFeetRay
{
private:
	Vector2f startPos;
	float rayLength;

public:
	UnderFeetRay(const Vector2f& pos = {0.f, 0.f}, float len = numeric_limits<float>::max()) :startPos(pos), rayLength(len) {}
	~UnderFeetRay() {}

	bool RayHit(const FloatRect& targetBound);
	float RayHitDistance(const FloatRect& targetBound);

	void SetStartPos(const Vector2f& pos) { startPos = pos; }
	void SetRayLength(float len) { rayLength = len; }

	const Vector2f& GetStartPos() const { return startPos; }
};

