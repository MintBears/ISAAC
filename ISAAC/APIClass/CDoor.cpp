#include "pch.h"
#include "CDoor.h"

CDoor::CDoor(Vec2 _vPos, Vec2 _vScale)
{
	SetPos(_vPos);
	SetScale(_vScale);
}

CDoor::~CDoor()
{
}

void CDoor::tick()
{
}

void CDoor::final_tick()
{
}

void CDoor::render(HDC _dc)
{
}
