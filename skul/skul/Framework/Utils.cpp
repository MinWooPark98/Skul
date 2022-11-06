#include "Utils.h"

random_device Utils::rd;
mt19937 Utils::gen(Utils::rd());

void Utils::SetOrigin(Text& obj, Origins origin)
{
	SetOrigin(obj, origin, obj.getLocalBounds());
}

void Utils::SetOrigin(Sprite& obj, Origins origin)
{
	SetOrigin(obj, origin, obj.getLocalBounds());
}

void Utils::SetOrigin(Shape& obj, Origins origin)
{
	SetOrigin(obj, origin, obj.getLocalBounds());
}

void Utils::SetOrigin(Transformable& obj, Origins origin, FloatRect rect)
{
	Vector2f originPos(rect.width, rect.height);
	originPos.x *= ((int)origin % 3) * 0.5f;
	originPos.y *= ((int)origin / 3) * 0.5f;
	obj.setOrigin(originPos);
}

int Utils::RandomRange(int min, int maxExclude)
{
	return (gen() % (maxExclude - min)) + min;
}

float Utils::RandomRange(float min, float max)
{
	return min + static_cast<float>(rand()) * static_cast<float>(max - min) / RAND_MAX;;
}
float Utils::RandomRange() 
{
	return RandomRange(0.f, 1.f);
 }

Vector2f Utils::RandAreaPoint()
{
	return RandomRange() * RandContact();
}

Vector2f Utils::RandContact()
{
	float radian = RandomRange(0.f, M_PI * 2);
	return Vector2f({ cos(radian),sin(radian) });
}

float Utils::SqrMagnitude(const Vector2f& vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

float Utils::Magnitude(const Vector2f& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float Utils::Dot(const Vector2f& a, const Vector2f& b)
{
	return a.x * b.x + a.y * b.y;
}

Vector2f Utils::GetNormal(const Vector2f& vec)
{
	return Vector2f(-vec.y, vec.x);
}

Vector2f Utils::Normalize(const Vector2f& vec)
{
	float mag = Magnitude(vec);
	if (mag == 0.f)
		return vec;
	return vec / mag;
}
float Utils::Distance(const Vector2f& vec1, const Vector2f& vec2)
{
	return Magnitude(vec1 - vec2);
}

float Utils::Angle(const Vector2f& start, const Vector2f& end)
{

	return Angle(Normalize(end - start));
}

float Utils::Angle(const Vector2f& dir)
{
	return atan2(dir.y, dir.x) * (180.f / M_PI);
}

float Utils::UnitizationFloat(float value)
{
	if (Utils::EqualFloat(value, 0.f))
		return 0.f;
	return value / fabs(value);
}

float Utils::Clamp(float value, float min, float max)
{
	return (value < min) ? min : ((value > max) ? max : value);
}

bool Utils::IsRange(float row, float height, float value)
{
	return value >= row && value <= height;
}

bool Utils::IsRange(const FloatRect rect, const Vector2f value)
{
	return IsRange(rect.left, rect.left + rect.width, value.x) 
		&& IsRange(rect.top, rect.top + rect.height, value.y);
}
