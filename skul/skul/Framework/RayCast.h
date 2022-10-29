#pragma once
#include <SFML/Graphics.hpp>
#include <list>

class Object;

using namespace sf;
using namespace std;

class RayCast
{
public:
	struct CollidedInfo
	{
		float rayHitDistance;
		Vector2f hittingPoint;
		Object* collidedObj;
	};

private:
	Vector2f startPos;
	Vector2f direction;
	float rayLength;

	bool rayHit;
	int layerMask;
	CollidedInfo* closestObj;
	list<CollidedInfo*> rayCollidedObjs;

public:
	RayCast(const Vector2f& pos = { 0.f, 0.f }, const Vector2f& dir = { 0.f, 0.f }, float len = numeric_limits<float>::max());
	~RayCast();

	void Reset();
	void Update(float dt);

	bool RayHit() const { return rayHit; }
	float RayHitDistance() const;
	const Vector2f& GetHittingPoint() const;
	Object* GetClosestObj() { return closestObj->collidedObj; }

	void SetStartPos(const Vector2f& pos) { startPos = pos; }
	void SetDirection(const Vector2f& dir) { direction = dir; }
	void SetRayLength(float len) { rayLength = len; }
	void SetLayerMask(int layer) { layerMask = layer; }

	float GetRayLength() const { return rayLength; }

	const Vector2f& GetStartPos() const { return startPos; }
};

