#include "UnderFeetRay.h"

bool UnderFeetRay::RayHit(const FloatRect& targetBound)
{
	if (targetBound.top > startPos.y + rayLength || targetBound.top + targetBound.height < startPos.y)
		return false;
	if (startPos.x > targetBound.left && startPos.x < targetBound.left + targetBound.width)
		return true;
	return false;
}

float UnderFeetRay::RayHitDistance(const FloatRect& targetBound)
{
	// RayHit true가 아니면 throw할까 고민 중
	return targetBound.top - startPos.y;
}
