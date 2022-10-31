#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CEventMge.h"
#include "CPathMgr.h"
#include "CResMgr.h"

#include "CLevel.h"

#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidbody.h"

#include "CMissile.h"



#include "CPlayer_Body.h"



CPlayer::CPlayer()
	: m_fSpeed(200.f)

{
	CreateCollider();
	CreateAnimator();
	m_SubAnimator = new CAnimator(this);
	CreatRigidbody();

	GetCollider()->SetOffsetPos(Vec2(0.f, 5.f));
	GetCollider()->SetScale(Vec2(30.f, 33.f));


	CTexture* Head = CResMgr::GetInst()->LoadTexture(L"Head", L"texture\\Head.bmp");
	CTexture* Body = CResMgr::GetInst()->LoadTexture(L"Body", L"texture\\Body.bmp");

	//Idle
	GetCAnimator()->CreateAnimation(L"Down", Head, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 1, 0.5f);
	GetCAnimator()->FindAnimation(L"Down")->Save(L"animation\\Down.anim");
	GetCAnimator()->CreateAnimation(L"Right", Head, Vec2(64.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 1, 0.5f);
	GetCAnimator()->FindAnimation(L"Right")->Save(L"animation\\Right.anim");
	GetCAnimator()->CreateAnimation(L"Up", Head, Vec2(128.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 1, 0.5f);
	GetCAnimator()->FindAnimation(L"Up")->Save(L"animation\\Up.anim");
	GetCAnimator()->CreateAnimation(L"Left", Head, Vec2(192.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 1, 0.5f);
	GetCAnimator()->FindAnimation(L"Left")->Save(L"animation\\Left.anim");

	//Attack
	GetCAnimator()->CreateAnimation(L"DownAttack", Head, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 2, 0.5f);
	GetCAnimator()->FindAnimation(L"DownAttack")->Save(L"animation\\DownAttack.anim");
	GetCAnimator()->CreateAnimation(L"RightAttack", Head, Vec2(64.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 2, 0.5f);
	GetCAnimator()->FindAnimation(L"RightAttack")->Save(L"animation\\RightAttack.anim");
	GetCAnimator()->CreateAnimation(L"UpAttack", Head, Vec2(128.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 2, 0.5f);
	GetCAnimator()->FindAnimation(L"UpAttack")->Save(L"animation\\UpAttack.anim");
	GetCAnimator()->CreateAnimation(L"LeftAttack", Head, Vec2(192.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 2, 0.5f);
	GetCAnimator()->FindAnimation(L"LeftAttack")->Save(L"animation\\LeftAttack.anim");


	//MoveBody
	Vec2 vBodyOffset = Vec2(0.f, 15.f);
	m_SubAnimator->CreateAnimation(L"LeftMove", Body, Vec2(0.f, 64.f), Vec2(32.f, 32.f), vBodyOffset, 10, 0.1f);
	m_SubAnimator->FindAnimation(L"LeftMove")->Save(L"animation\\LeftMove.anim");
	m_SubAnimator->CreateAnimation(L"RightMove", Body, Vec2(0.f, 32.f), Vec2(32.f, 32.f), vBodyOffset, 10, 0.1f);
	m_SubAnimator->FindAnimation(L"RightMove")->Save(L"animation\\RightMove.anim");
	m_SubAnimator->CreateAnimation(L"UpMove", Body, Vec2(0.f, 0.f), Vec2(32.f, 32.f), vBodyOffset, 10, 0.1f);
	m_SubAnimator->FindAnimation(L"UpMove")->Save(L"animation\\UpMove.anim");
	m_SubAnimator->CreateAnimation(L"DownMove", Body, Vec2(0.f, 0.f), Vec2(32.f, 32.f), vBodyOffset, 10, 0.1f);
	m_SubAnimator->FindAnimation(L"DownMove")->Save(L"animation\\DownMove.anim");

	m_SubAnimator->CreateAnimation(L"LeftIdle", Body, Vec2(0.f, 64.f), Vec2(32.f, 32.f), vBodyOffset, 1, 0.1f);
	m_SubAnimator->FindAnimation(L"LeftIdle")->Save(L"animation\\LeftIdle.anim");
	m_SubAnimator->CreateAnimation(L"RightIdle", Body, Vec2(0.f, 32.f), Vec2(32.f, 32.f), vBodyOffset, 1, 0.1f);
	m_SubAnimator->FindAnimation(L"RightIdle")->Save(L"animation\\RightIdle.anim");
	m_SubAnimator->CreateAnimation(L"UpIdle", Body, Vec2(0.f, 0.f), Vec2(32.f, 32.f), vBodyOffset, 1, 0.1f);
	m_SubAnimator->FindAnimation(L"UpIdle")->Save(L"animation\\UpIdle.anim");
	m_SubAnimator->CreateAnimation(L"DownIdle", Body, Vec2(0.f, 0.f), Vec2(32.f, 32.f), vBodyOffset, 1, 0.1f);
	m_SubAnimator->FindAnimation(L"DownIdle")->Save(L"animation\\DownIdle.anim");
	
	//GetCAnimator()->LoadAnimation(L"animation\\HeadMove.anim");

	GetCRigidbody()->SetFriction(100.f);
	GetCRigidbody()->IsGround(true);
	GetCRigidbody()->SetVelocityLimit(200.0f);

	GetCAnimator()->Play(L"Down", true);
	m_SubAnimator->Play(L"DownIdle", true);

}

CPlayer::~CPlayer()
{
	DEL(m_SubAnimator);
}

void CPlayer::tick()
{
	Move();

	if (IsTap(KEY::LSHIFT))
	{
		//CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();

		for (int i = 0; i < 3; i++)
		{
			CMissile* Missile = new CMissile;
			//Missile->SetPos(GetPos());
			Missile->SetScale(Vec2(20.F, 20.f));
			Missile->SetSpeed(400.f);
			Missile->SetDir(45.f + (45.f * (float)i));
			//바로 레벨에 추가한다.
			//CurLevel->AddObject(Missile, LAYER::PLAYER_PROJECTILE);
			//여기다가 보내면 tick에서 호출한 오브젝트는 바로 처리안하고 Event에 들어가서 처리한다.
			//_evn.eType : 이벤트 타입 설정하고, _evn.wParam : 이벤트 정보 저장하고, AddEvent(_evn) : 이벤트메니저에 넣는다.
			//tEvent _evn = {};
			//_evn.eType = EVENT_TYPE::CREATE_OBJECT;
			//_evn.wParam = (DWORD_PTR)Missile;
			//_evn.lParam = (DWORD_PTR)LAYER::PLAYER_PROJECTILE;
			//CEventMge::GetInst()->AddEvent(_evn);
			//이것들을 함수화
			Instantiate(Missile, GetPos(), LAYER::PLAYER_PROJECTILE);
		}
	}

	Ani();

	CObj::tick();
}

void CPlayer::final_tick()
{
	if (nullptr != m_SubAnimator)
	{
		m_SubAnimator->final_tick();
	}
	CObj::final_tick();
}

void CPlayer::render(HDC _dc)
{
	if (nullptr != m_SubAnimator)
	{
		m_SubAnimator->render(_dc);
	}
	CObj::render(_dc);
}

void CPlayer::BeginOverlap(CCollider* _Other)
{

}

void CPlayer::OnOverlap(CCollider* _Other)
{
}

void CPlayer::EndOverlap(CCollider* _Other)
{
}

void CPlayer::Move()
{
	Vec2 vPos = GetPos();

	//문제점 : 현재 각각의 키상태를 매 tick 마다 확인을 해야되는 상황이다.
	//해결 : 이걸 종합적으로 관리해줄 메니저를 따로 만들어야된다.
	if (IsPressed(KEY::LEFT))
	{
		GetCRigidbody()->AddForce(Vec2(-(m_fSpeed + 200.f), 0.f));
		//vPos.x -= m_fSpeed * DT;
	}

	if (IsPressed(KEY::RIGHR))
	{
		GetCRigidbody()->AddForce(Vec2(m_fSpeed + 200.f, 0.f));
		//vPos.x += m_fSpeed * DT;
	}

	if (IsPressed(KEY::UP))
	{
		GetCRigidbody()->AddForce(Vec2(0.f, -200.f));
		//vPos.y -= m_fSpeed * DT;
	}

	if (IsPressed(KEY::DOWN))
	{
		GetCRigidbody()->AddForce(Vec2(0.f, 200.f));
		//vPos.y += m_fSpeed * DT;
	}
	SetPos(vPos);
}

void CPlayer::Ani()
{
	//캐릭터가 움직일때
	if (IsTap(KEY::LEFT))
		m_SubAnimator->Play(L"LeftMove", true);
	if (IsTap(KEY::RIGHR))
		m_SubAnimator->Play(L"RightMove", true);
	if (IsTap(KEY::UP))
		m_SubAnimator->Play(L"UpMove", true);
	if (IsTap(KEY::DOWN))
		m_SubAnimator->Play(L"DownMove", true);
	//캐릭터가 멈출때
	if (IsRelease(KEY::LEFT))
		m_SubAnimator->Play(L"LeftMove", true);
	if (IsRelease(KEY::RIGHR))
		m_SubAnimator->Play(L"RightIdle", true);
	if (IsRelease(KEY::UP))
		m_SubAnimator->Play(L"UpIdle", true);
	if (IsRelease(KEY::DOWN))
		m_SubAnimator->Play(L"DownIdle", true);

	//캐릭터가 공격할때
	if (IsTap(KEY::W))
		GetCAnimator()->Play(L"UpAttack", true);
	if (IsTap(KEY::A))
		GetCAnimator()->Play(L"LeftAttack", true);
	if (IsTap(KEY::D))
		GetCAnimator()->Play(L"RightAttack", true);
	if (IsTap(KEY::S))
		GetCAnimator()->Play(L"DownAttack", true);
}
