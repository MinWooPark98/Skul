#include "RayCast.h"
#include "../Scene/SceneMgr.h"
#include <iostream>

using namespace std;

RayCast::RayCast(const Vector2f& pos, const Vector2f& dir, float len)
	:startPos(pos), direction(dir), rayLength(len), rayHit(false), layerMask(-1), closestObj(nullptr)
{
}

RayCast::~RayCast()
{
}

void RayCast::Reset()
{
	rayHit = false;
	rayCollidedObjs.clear();
	closestObj = nullptr;
	drawRay[0] = startPos;
	drawRay[1] = startPos + direction * rayLength;
};

void RayCast::Update(float dt)
{
	Reset();
	Scene* currScene = SCENE_MGR->GetCurrentScene();
	auto& layOut = currScene->GetLayout();
	for (int i = 0; i < (int)Scene::Layer::Count; ++i)
	{
		if (layerMask != -1 && i != layerMask)
			continue;
		for (auto& obj : *layOut[i])
		{
			if (!obj->GetActive())
				return;

			auto targetBound = obj->GetHitBounds();

			float targetLeft = targetBound.left;
			float targetRight = targetBound.left + targetBound.width;
			float targetTop = targetBound.top;
			float targetBottom = targetBound.top + targetBound.height;

			// 아래 방향으로 갈 수록 y값 증가하므로 역으로 뒤집어줘야 함
			float angleDir = atan2(-direction.y, direction.x);
			float angleTL = atan2(-(targetTop - startPos.y), targetLeft - startPos.x);
			float angleTR = atan2(-(targetTop - startPos.y), targetRight - startPos.x);
			float angleBL = atan2(-(targetBottom - startPos.y), targetLeft - startPos.x);
			float angleBR = atan2(-(targetBottom - startPos.y), targetRight - startPos.x);

			if (angleDir < 0.f) angleDir += 2 * M_PI;
			if (angleTL < 0.f) angleTL += 2 * M_PI;
			if (angleTR < 0.f) angleTR += 2 * M_PI;
			if (angleBL < 0.f) angleBL += 2 * M_PI;
			if (angleBR < 0.f) angleBR += 2 * M_PI;

			float len = 0.f;

			if (targetLeft > startPos.x && targetBottom < startPos.y)
			{
				if (angleDir > angleTL || angleDir < angleBR)
					continue;

				if (angleDir <= angleBL)
					len = -(targetBottom - startPos.y) / sin(angleDir);
				else
					len = (targetLeft - startPos.x) / cos(angleDir);
			}
			else if (targetRight < startPos.x && targetBottom < startPos.y)
			{
				if (angleDir > angleBL || angleDir < angleTR)
					continue;

				if (angleDir <= angleBR)
					len = (targetRight - startPos.x) / cos(angleDir);
				else
					len = -(targetBottom - startPos.y) / sin(angleDir);
			}
			else if (targetRight < startPos.x && targetTop > startPos.y)
			{
				if (angleDir > angleBR || angleDir < angleTL)
					continue;

				if (angleDir <= angleTR)
					len = -(targetTop - startPos.y) / sin(angleDir);
				else
					len = (targetRight - startPos.x) / cos(angleDir);
			}
			else if (targetLeft > startPos.x && targetTop > startPos.y)
			{
				if (angleDir > angleTR || angleDir < angleBL)
					continue;

				if (angleDir <= angleTL)
					len = (targetLeft - startPos.x) / cos(angleDir);
				else
					len = -(targetTop - startPos.y) / sin(angleDir);
			}
			else if (targetBottom < startPos.y)
			{
				if (angleDir < angleBR || angleDir > angleBL)
					continue;

				len = -(targetBottom - startPos.y) / sin(angleDir);
			}
			else if (targetTop > startPos.y)
			{
				if (angleDir < angleTL || angleDir > angleTR)
					continue;

				len = -(targetTop - startPos.y) / sin(angleDir);
			}
			else if (targetLeft > startPos.x)
			{
				if (angleDir > angleTL && angleDir < angleBL)
					continue;

				len = (targetLeft - startPos.x) / cos(angleDir);
			}
			else if (targetRight < startPos.x)
			{
				if (angleDir < angleTR || angleDir > angleBR)
					continue;

				len = (targetRight - startPos.x) / cos(angleDir);
			}
			if (len > rayLength)
				continue;

			rayHit = true;
			CollidedInfo* info = new CollidedInfo();
			info->rayHitDistance = len;
			info->collidedObj = obj;
			if (len > 0.f)
				info->hittingPoint = { startPos.x + len * cos(angleDir), startPos.y - len * sin(angleDir) };
			else
			{
				float angleDug = angleDir + (angleDir > M_PI ? -M_PI : M_PI);
				info->hittingPoint = startPos;
				// 상대 좌표
				/*if (angleDug < angleTR || angleDug > angleBR)
					info->hittingPoint = Vector2f(-(targetRight - startPos.x), (targetRight - startPos.x) * tan(angleDug));
				else if (angleDug < angleTL)
					info->hittingPoint = Vector2f((targetTop - startPos.y) / tan(angleDug), (targetTop - startPos.y));
				else if (angleDug < angleBL)
					info->hittingPoint = Vector2f(-(targetLeft - startPos.x), (targetLeft - startPos.x) * tan(angleDug));
				else
					info->hittingPoint = Vector2f((targetBottom - startPos.y) / tan(angleDug), (targetBottom - startPos.y));*/
			}
			if (closestObj == nullptr)
				closestObj = info;
			else if (info->rayHitDistance < closestObj->rayHitDistance)
				closestObj = info;
			rayCollidedObjs.push_back(info);
		}
	}
}

float RayCast::RayHitDistance() const
{
	if (!rayHit)
		throw;
	return closestObj->rayHitDistance;
}

const Vector2f& RayCast::GetHittingPoint() const
{
	if (!rayHit)
		throw;
	return closestObj->hittingPoint;
}

void RayCast::SetStartPos(const Vector2f& pos)
{
	startPos = pos;
	SetDrawRay();
}

void RayCast::SetDirection(const Vector2f& dir)
{
	direction = dir;
	SetDrawRay();
}

void RayCast::SetRayLength(float len)
{
	rayLength = len;
	SetDrawRay();
}

void RayCast::SetDrawRay()
{
	drawRay[0] = startPos;
	drawRay[1] = startPos + direction * rayLength;
}
