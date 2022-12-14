#include "pch.h"

#include "CEngine.h"

#include "CKeyMgr.h"

int g_arrVK[(UINT)KEY::END]
=
{
	VK_UP,
	VK_DOWN,
	VK_LEFT,
	VK_RIGHT,

	VK_SPACE,

	VK_RETURN,
	VK_ESCAPE,
	VK_LMENU,
	VK_LCONTROL,
	VK_LSHIFT,
	VK_TAB,

	VK_LBUTTON,
	VK_RBUTTON,

	'W',
	'A',
	'S',
	'D',

	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',

	'I',
	'J',
	'K',
	'L',
};

CKeyMgr::CKeyMgr()
	:m_eKey(KEY::END)
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::END; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ (KEY)i, KEY_STATE::NONE });
	}
}

void CKeyMgr::tick()
{

	if (GetFocus())
		//현제 윈도우가 포커스하고있는가
	{
		for (size_t i = 0; i < m_vecKey.size(); i++)
		{
			if (GetAsyncKeyState(g_arrVK[(UINT)m_vecKey[i].key]) & 0x8000)
			{
				//키를 눌렀는데 전에 안눌렀다(처음눌렀을때)
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::TAP;
					m_vecKey[i].bPrev = true;
				}
				//키를눌렀는데 전에 눌러져있었다.(지속적으로 눌렀을때)
				else
				{
					m_vecKey[i].state = KEY_STATE::PRESSED;
				}
				m_eKey = (KEY)i;
			}
			else
			{
				//키를 누르지 않았는데 안눌렀다.(비활성화상태)
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::NONE;
				}
				//키를 누르지 않았는데 눌러져있었다.(방금 땐상태)
				else
				{
					m_vecKey[i].state = KEY_STATE::RELEASED;
					m_vecKey[i].bPrev = false;
				}
			}

		}
	}
	else
	{
		for (size_t i = 0; i < m_vecKey.size(); i++)
		{
			if (KEY_STATE::TAP == m_vecKey[i].state || KEY_STATE::PRESSED == m_vecKey[i].state)
			{
				m_vecKey[i].state = KEY_STATE::RELEASED;
			}
			else if(KEY_STATE::RELEASED == m_vecKey[i].state)
			{
				m_vecKey[i].state = KEY_STATE::NONE;
			}

		}
	}

	POINT ptMousePos = {};
	GetCursorPos(&ptMousePos);

	ScreenToClient(CEngine::GetInst()->GethMainWnd(), &ptMousePos);

	m_vMousePos = ptMousePos;
}
