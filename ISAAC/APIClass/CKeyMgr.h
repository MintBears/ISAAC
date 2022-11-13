#pragma once


enum class KEY
	//Ű�� ����
{
	UP,
	DOWN,
	LEFT,
	RIGHR,

	SPACE,
	ENTER,
	ESC,
	LALT,
	LCTRL,
	LSHIFT,
	TAB,

	LBTN,
	RBTN,

	W,
	A,
	S,
	D,

	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,

	I,
	J,
	K,
	L,


	END,		//Ű ������ ���� ���� ǥ��
};

enum class KEY_STATE
	//Ű�� ���� ����
{
	TAP,		//��������
	PRESSED,	//������ִµ���
	RELEASED,	//��������
	NONE,		//�ƹ��͵� �ƴѼ���
};

struct tKeyInfo
	//Ű������ ���� ����ü
{
	KEY			key;
	KEY_STATE	state;
	bool		bPrev;
};



class CKeyMgr
{
	SINGLE(CKeyMgr)

private:

	vector<tKeyInfo>	m_vecKey;
	Vec2				m_vMousePos;

	KEY					m_eKey;

public:
	void init();
	void tick();

public:
	KEY_STATE GetKeyState(KEY _key) { return m_vecKey[(UINT)_key].state; }
	KEY GetKey() { return m_eKey; }
	Vec2 GetMousePos() { return m_vMousePos; }
};

