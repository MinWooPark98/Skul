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
	// RayHit true�� �ƴϸ� throw�ұ� ��� ��
	return targetBound.top - startPos.y;
}
