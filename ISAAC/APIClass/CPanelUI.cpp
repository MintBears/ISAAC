#include "pch.h"
#include "CPanelUI.h"

#include "CKeyMgr.h"
#include "CTexture.h"

CPanelUI::CPanelUI()
	: m_bIsMove(false)
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::tick()
{
	if (IsLbtnDown() && m_bIsMove)
	{
		Vec2 vMove = MOUSE_POS - m_vPressPos;

		Vec2 vPos = GetPos();
		vPos += vMove;
		SetPos(vPos);

		m_vPressPos = MOUSE_POS;
	}
	
	CUI::tick();
}

void CPanelUI::render(HDC _dc)
{
	if (nullptr == GetIdleTex())
		return;

	Vec2 vPos = GetPos();

	TransparentBlt(_dc, (float)vPos.x, (float)vPos.y
		, GetIdleTex()->Widht()
		, GetIdleTex()->Height()
		, GetIdleTex()->GetDC()
		, 0, 0
		, GetIdleTex()->Widht()
		, GetIdleTex()->Height()
		, RGB(255, 0, 255));


	render_childUI(_dc);
}

void CPanelUI::MouseLbtnDown()
{
	CUI::MouseLbtnDown();

	m_vPressPos = MOUSE_POS;
}
void CPanelUI::MouseLbtnClicked()
{
	int a = 0;
}
