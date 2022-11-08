#include "pch.h"
#include "CCameraObj.h"

#include "CEngine.h"

#include "CPlayer.h"
#include "CCollider.h"
#include "CRigidbody.h"

CCameraObj::CCameraObj(Vec2 _vPos, Vec2 _vScale)
{
	SetPos(_vPos);
	SetScale(_vScale);
}

CCameraObj::~CCameraObj()
{
}

void CCameraObj::tick()
{
	CObj::tick();
}

void CCameraObj::final_tick()
{
	CObj::final_tick();
}

void CCameraObj::render(HDC _dc)
{
	HPEN hPen = nullptr;
	hPen = CEngine::GetInst()->GetPen(PEN_TYPE::RED);
	//���� ��� �귯�ø� ���� ������ �͵�� ���۴�.
	HPEN hOriginPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, (HBRUSH)GetStockObject(NULL_BRUSH));
	Vec2 Pos = CCamera::GetInst()->GetRenderPos(GetPos());

	Rectangle(_dc, (int)(Pos.x - GetScale().x / 2.f)
		, (int)(Pos.y - GetScale().y / 2.f)
		, (int)(Pos.x + GetScale().x / 2.f)
		, (int)(Pos.y + GetScale().y / 2.f));
	//�ٽ� ����ġ
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);

	CObj::render(_dc);

}