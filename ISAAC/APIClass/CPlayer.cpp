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
	, m_fAttackSpeed(1.f)

{
	CreateCollider();
	CreateAnimator();
	m_SubAnimator = new CAnimator(this);
	CreatRigidbody();

	GetCollider()->SetOffsetPos(Vec2(0.f, 5.f));
	GetCollider()->SetScale(Vec2(30.f, 33.f));


	CTexture* Head = CResMgr::GetInst()->LoadTexture(L"Head", L"texture\\Head.bmp");
	CTexture* Body = CResMgr::GetInst()->LoadTexture(L"Body", L"texture\\Body.bmp");

	//MoveLook
	GetCAnimator()->CreateAnimation(L"Down", Head, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 1, 0.5f);
	GetCAnimator()->FindAnimation(L"Down")->Save(L"animation\\Down.anim");
	GetCAnimator()->CreateAnimation(L"Right", Head, Vec2(64.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 1, 0.5f);
	GetCAnimator()->FindAnimation(L"Right")->Save(L"animation\\Right.anim");
	GetCAnimator()->CreateAnimation(L"Up", Head, Vec2(128.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 1, 0.5f);
	GetCAnimator()->FindAnimation(L"Up")->Save(L"animation\\Up.anim");
	GetCAnimator()->CreateAnimation(L"Left", Head, Vec2(192.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 1, 0.5f);
	GetCAnimator()->FindAnimation(L"Left")->Save(L"animation\\Left.anim");
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
	//Attack
	GetCAnimator()->CreateAnimation(L"DownAttack", Head, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 2, m_fAttackSpeed * 0.3f);
	GetCAnimator()->FindAnimation(L"DownAttack")->Save(L"animation\\DownAttack.anim");
	GetCAnimator()->CreateAnimation(L"RightAttack", Head, Vec2(64.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 2, m_fAttackSpeed * 0.3f);
	GetCAnimator()->FindAnimation(L"RightAttack")->Save(L"animation\\RightAttack.anim");
	GetCAnimator()->CreateAnimation(L"UpAttack", Head, Vec2(128.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 2, m_fAttackSpeed * 0.3f);
	GetCAnimator()->FindAnimation(L"UpAttack")->Save(L"animation\\UpAttack.anim");
	GetCAnimator()->CreateAnimation(L"LeftAttack", Head, Vec2(192.f, 0.f), Vec2(32.f, 32.f), Vec2(0.f, 0.f), 2, m_fAttackSpeed * 0.3f);
	GetCAnimator()->FindAnimation(L"LeftAttack")->Save(L"animation\\LeftAttack.anim");
	//Idle
	m_SubAnimator->CreateAnimation(L"BodyIdle", Body, Vec2(0.f, 0.f), Vec2(32.f, 32.f), vBodyOffset, 1, 0.1f);
	m_SubAnimator->FindAnimation(L"BodyIdle")->Save(L"animation\\BodyIdle.anim");





	//GetCAnimator()->LoadAnimation(L"animation\\HeadMove.anim");

	GetCRigidbody()->SetFriction(100.f);
	GetCRigidbody()->IsGround(true);
	GetCRigidbody()->SetVelocityLimit(200.0f);

	GetCAnimator()->Play(L"Down", true);
	m_SubAnimator->Play(L"BodyIdle", true);

}

CPlayer::~CPlayer()
{
	DEL(m_SubAnimator);
}

void CPlayer::tick()
{
	Move();

	Attack();

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
		GetCRigidbody()->AddForce(Vec2(-(m_fSpeed + 200.f), 0.f));
	if (IsPressed(KEY::RIGHR))
		GetCRigidbody()->AddForce(Vec2(m_fSpeed + 200.f, 0.f));
	if (IsPressed(KEY::UP))
		GetCRigidbody()->AddForce(Vec2(0.f, -(m_fSpeed + 200.f)));
	if (IsPressed(KEY::DOWN))
		GetCRigidbody()->AddForce(Vec2(0.f, m_fSpeed + 200.f));
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

	//캐릭터가 공격할때
	if (IsTap(KEY::W))
		GetCAnimator()->Play(L"UpAttack", true);
	else if (IsTap(KEY::A))
		GetCAnimator()->Play(L"LeftAttack", true);
	else if (IsTap(KEY::D))
		GetCAnimator()->Play(L"RightAttack", true);
	else if (IsTap(KEY::S))
		GetCAnimator()->Play(L"DownAttack", true);

	//캐릭터가 멈출때
	if (IsNone(KEY::LEFT) && IsNone(KEY::DOWN) && IsNone(KEY::UP) && IsNone(KEY::RIGHR))
		m_SubAnimator->Play(L"BodyIdle", true);
	if ((IsNone(KEY::W) && IsNone(KEY::A) && IsNone(KEY::S) && IsNone(KEY::D)))
		GetCAnimator()->Play(L"Down", true);



}

void CPlayer::Attack()
{
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
			Instantiate(Missile, GetPos(), LAYER::PLAYER_PROJECTILE);
		}
	}
}


