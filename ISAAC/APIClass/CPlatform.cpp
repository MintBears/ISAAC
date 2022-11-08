#include "pch.h"
#include "CPlatform.h"

#include "CPlayer.h"
#include "CCollider.h"
#include "CRigidbody.h"

CPlatform::CPlatform(Vec2 _vPos, Vec2 _vScale)
{
	SetPos(_vPos);
	SetScale(_vScale);

	CreateCollider();
	GetCollider()->SetScale(GetScale());
}

CPlatform::~CPlatform()
{
}

void CPlatform::tick()
{

	CObj::tick();
}

void CPlatform::final_tick()
{
	CObj::final_tick();
}

void CPlatform::render(HDC _dc)
{
	
	//Vec2 Pos = CCamera::GetInst()->GetRenderPos(GetPos());
	//Vec2 Size = GetScale();
	//Rectangle(_dc
	//	, Pos.x
	//	, Pos.y
	//	, (int)GetScale().x
	//	, (int)GetScale().y);
	//int a = GetScale().x;
	
	CObj::render(_dc);
	
}

void CPlatform::BeginOverlap(CCollider* _Other)
{
	
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_Other->GetOwner());
	if (nullptr == pPlayer)
		return;
	
	
}

void CPlatform::OnOverlap(CCollider* _Other)
{

}

void CPlatform::EndOverlap(CCollider* _Other)
{
	if (_Other->GetOwner()->GetLayerType() == LAYER::PLAYER)
	{
		m_pPlayer = dynamic_cast<CPlayer*>(_Other->GetOwner());
	}
}
