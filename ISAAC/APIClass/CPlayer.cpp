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
#include "CMap.h"



CPlayer::CPlayer(Vec2 _vPos, Vec2 _vScale)
	: m_fSpeed(600.f)
	, m_fAttackSpeed(1.f)
	, m_CurAttackTime(0.f)
	, m_bIsAttack(false)
	, m_iHp(2)
	, m_fCollisionTime(0.f)
	, m_fInvincibleTime(1.f)
	, m_bisCollision(false)
	, m_pMap(nullptr)

{
	SetPos(_vPos);
	SetScale(_vScale);


	CreateCollider();
	CreateAnimator();
	m_SubAnimator = new CAnimator(this);
	CreatRigidbody();

	//Collider
	//GetCollider()->SetOffsetPos();
	GetCollider()->SetScale(GetScale());

	//Animator
	CTexture* Head = CResMgr::GetInst()->LoadTexture(L"Head", L"texture\\Player\\Head.bmp");
	CTexture* Body = CResMgr::GetInst()->LoadTexture(L"Body", L"texture\\Player\\Body.bmp");

	//MoveLook
	Vec2 vHeadOffset = Vec2(0.f, -5.f);
	GetCAnimator()->CreateAnimation(L"Down", Head, Vec2(0.f, 0.f), Vec2(32.f, 32.f), vHeadOffset, 1, 0.5f);
	GetCAnimator()->FindAnimation(L"Down")->Save(L"animation\\Down.anim");
	GetCAnimator()->CreateAnimation(L"Right", Head, Vec2(64.f, 0.f), Vec2(32.f, 32.f), vHeadOffset, 1, 0.5f);
	GetCAnimator()->FindAnimation(L"Right")->Save(L"animation\\Right.anim");
	GetCAnimator()->CreateAnimation(L"Up", Head, Vec2(128.f, 0.f), Vec2(32.f, 32.f), vHeadOffset, 1, 0.5f);
	GetCAnimator()->FindAnimation(L"Up")->Save(L"animation\\Up.anim");
	GetCAnimator()->CreateAnimation(L"Left", Head, Vec2(192.f, 0.f), Vec2(32.f, 32.f), vHeadOffset, 1, 0.5f);
	GetCAnimator()->FindAnimation(L"Left")->Save(L"animation\\Left.anim");
	//Attack
	GetCAnimator()->CreateAnimation(L"DownAttack", Head, Vec2(0.f, 0.f), Vec2(32.f, 32.f), vHeadOffset, 2, m_fAttackSpeed * 0.5f);
	GetCAnimator()->FindAnimation(L"DownAttack")->Save(L"animation\\DownAttack.anim");
	GetCAnimator()->CreateAnimation(L"RightAttack", Head, Vec2(64.f, 0.f), Vec2(32.f, 32.f), vHeadOffset, 2, m_fAttackSpeed * 0.5f);
	GetCAnimator()->FindAnimation(L"RightAttack")->Save(L"animation\\RightAttack.anim");
	GetCAnimator()->CreateAnimation(L"UpAttack", Head, Vec2(128.f, 0.f), Vec2(32.f, 32.f), vHeadOffset, 2, m_fAttackSpeed * 0.5f);
	GetCAnimator()->FindAnimation(L"UpAttack")->Save(L"animation\\UpAttack.anim");
	GetCAnimator()->CreateAnimation(L"LeftAttack", Head, Vec2(192.f, 0.f), Vec2(32.f, 32.f), vHeadOffset, 2, m_fAttackSpeed * 0.5f);
	GetCAnimator()->FindAnimation(L"LeftAttack")->Save(L"animation\\LeftAttack.anim");
	//MoveBody
	Vec2 vBodyOffset = Vec2(0.f, 10.f);
	m_SubAnimator->CreateAnimation(L"LeftMove", Body, Vec2(0.f, 64.f), Vec2(32.f, 32.f), vBodyOffset, 10, 0.1f);
	m_SubAnimator->FindAnimation(L"LeftMove")->Save(L"animation\\LeftMove.anim");
	m_SubAnimator->CreateAnimation(L"RightMove", Body, Vec2(0.f, 32.f), Vec2(32.f, 32.f), vBodyOffset, 10, 0.1f);
	m_SubAnimator->FindAnimation(L"RightMove")->Save(L"animation\\RightMove.anim");
	m_SubAnimator->CreateAnimation(L"UpMove", Body, Vec2(0.f, 0.f), Vec2(32.f, 32.f), vBodyOffset, 10, 0.1f);
	m_SubAnimator->FindAnimation(L"UpMove")->Save(L"animation\\UpMove.anim");
	m_SubAnimator->CreateAnimation(L"DownMove", Body, Vec2(0.f, 0.f), Vec2(32.f, 32.f), vBodyOffset, 10, 0.1f);
	m_SubAnimator->FindAnimation(L"DownMove")->Save(L"animation\\DownMove.anim");
	//Idle
	m_SubAnimator->CreateAnimation(L"BodyIdle", Body, Vec2(0.f, 0.f), Vec2(32.f, 32.f), vBodyOffset, 1, 0.1f);
	m_SubAnimator->FindAnimation(L"BodyIdle")->Save(L"animation\\BodyIdle.anim");

	//GetCAnimator()->LoadAnimation(L"animation\\HeadMove.anim");


	//Rigidbody
	GetCRigidbody()->SetFriction(400.f);
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

	//???? ????
	if (m_bisCollision)
	{
		m_fCollisionTime += DT;
		if (m_fCollisionTime >= m_fInvincibleTime)
		{
			m_fCollisionTime = 0.f;
		}
	}
	//????
	if (m_iHp == 0)
	{
		//???????? ???????? ?????? ?????????? ?????????? ?????? ???????????? ?????? ????.
		//SetDead();
		SetValid(false);

	}
	
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
	if (_Other->GetOwner()->GetLayerType() == LAYER::BACKGROUND)
	{
		m_pMap = dynamic_cast<CMap*>(_Other->GetOwner());
	}
	if (_Other->GetOwner()->GetLayerType() == LAYER::MONSTER)
	{
		m_bisCollision = true;
	}
}

void CPlayer::OnOverlap(CCollider* _Other)
{
	if (_Other->GetOwner()->GetLayerType() == LAYER::MONSTER)
	{
		if (m_fCollisionTime == 0.f)
		{
			//????????
			m_iHp--;
		}
	}
	else
	{
		m_bisCollision = false;
	}
}

void CPlayer::EndOverlap(CCollider* _Other)
{
	m_bisCollision = false;
}

void CPlayer::Move()
{
	Vec2 vPos = GetPos();

	//?????? : ???? ?????? ???????? ?? tick ???? ?????? ???????? ????????.
	//???? : ???? ?????????? ???????? ???????? ???? ????????????.
	if (IsPressed(KEY::LEFT))
		GetCRigidbody()->AddForce(Vec2(-(m_fSpeed + 200.f), 0.f));
	if (IsPressed(KEY::RIGHR))
		GetCRigidbody()->AddForce(Vec2(m_fSpeed + 200.f, 0.f));
	if (IsPressed(KEY::UP))
		GetCRigidbody()->AddForce(Vec2(0.f, -(m_fSpeed + 200.f)));
	if (IsPressed(KEY::DOWN))
		GetCRigidbody()->AddForce(Vec2(0.f, m_fSpeed + 200.f));


	//???? ????
	if (nullptr != m_pMap)
	{

		Vec2 MapPos = m_pMap->GetPos();
		Vec2 MapScale = m_pMap->GetScale();
		float MapWallPos = (float)m_pMap->GetWallScale();
		//???????????? - ???????? ???????? = ???????? ???? ????		-		?????????? -  ?? ???????? = ?? ????????  => ???? = ?????? ?????? / ???? =  ???? ????????
		//????
		float playerx = GetPos().x - (GetScale().x / 2);
		float mapx = MapPos.x + MapWallPos;
		float rendermapx = CCamera::GetInst()->GetRenderPos(MapPos).x;
		if (playerx < mapx)
		{
			vPos = Vec2(mapx + (GetScale().x / 2), vPos.y);

		}
		//????
		float playery = GetPos().y - (GetScale().y / 2);
		float mapy = MapPos.y + MapWallPos;
		if (playery < mapy)
		{
			//m_pPlayer->GetCRigidbody()->SetVelocity(Vec2(m_pPlayer->GetCRigidbody()->GetVelocity().x, 0.f));
			vPos = Vec2(vPos.x, mapy + (GetScale().y / 2));
		}

		//????
		playerx = GetPos().x + (GetScale().x / 2);
		mapx = MapPos.x + MapScale.x - MapWallPos;
		if (playerx > mapx)
		{
			vPos = Vec2(mapx - (GetScale().x / 2), vPos.y);
		}
		
		//????
		playery = GetPos().y + (GetScale().y / 2);
		mapy = MapPos.y + MapScale.y - MapWallPos;
		if (playery > mapy)
		{
			vPos = Vec2(vPos.x, mapy - (GetScale().y / 2));
		}

	}

	SetPos(vPos);
}

void CPlayer::Ani()
{
	//???????? ????????
	if (IsTap(KEY::LEFT))
		m_SubAnimator->Play(L"LeftMove", true);
	if (IsTap(KEY::RIGHR))
		m_SubAnimator->Play(L"RightMove", true);
	if (IsTap(KEY::UP))
		m_SubAnimator->Play(L"UpMove", true);
	if (IsTap(KEY::DOWN))
		m_SubAnimator->Play(L"DownMove", true);

	//???????? ????????
	if (IsTap(KEY::W))
		GetCAnimator()->Play(L"UpAttack", true);
	else if (IsTap(KEY::A))
		GetCAnimator()->Play(L"LeftAttack", true);
	else if (IsTap(KEY::D))
		GetCAnimator()->Play(L"RightAttack", true);
	else if (IsTap(KEY::S))
		GetCAnimator()->Play(L"DownAttack", true);

	//???????? ??????
	if (IsNone(KEY::LEFT) && IsNone(KEY::DOWN) && IsNone(KEY::UP) && IsNone(KEY::RIGHR))
		m_SubAnimator->Play(L"BodyIdle", true);
	if ((IsNone(KEY::W) && IsNone(KEY::A) && IsNone(KEY::S) && IsNone(KEY::D)))
		GetCAnimator()->Play(L"Down", true);



}

void CPlayer::Attack()
{
	//???????? ????
	if (IsPressed(KEY::W) || IsPressed(KEY::A) || IsPressed(KEY::S) || IsPressed(KEY::D))
	{
		if (m_CurAttackTime == 0.f)
		{
			//CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();
			CMissile* Missile = new CMissile(GetPos(), Vec2(20.f, 20.f));
			Missile->SetSpeed(400.f * m_fAttackSpeed);
			Missile->SetLayerType(LAYER::PLAYER_PROJECTILE);
			switch (CKeyMgr::GetInst()->GetKey())
			{
			case KEY::W:
				Missile->SetDir(90.f);
				break;
			case KEY::A:
				Missile->SetDir(180.f);
				break;
			case KEY::S:
				Missile->SetDir(270.f);
				break;
			case KEY::D:
				Missile->SetDir(0.f);
				break;
			default:
				break;
			}

			Instantiate(Missile, GetPos(), LAYER::PLAYER_PROJECTILE);
		}
		m_bIsAttack = true;
	}

	//???? ????
	if (m_bIsAttack)
	{
		m_CurAttackTime += DT * m_fAttackSpeed;
		if (m_CurAttackTime >= m_fAttackSpeed)
		{
			m_CurAttackTime = 0.f;
			m_bIsAttack = false;
		}
	}
}


