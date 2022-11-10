#pragma once

class CTexture;

struct tCamEffect
{
	CAMERA_EFFECT	m_eCurEffect;
	float			m_fAccTime;
	float			m_fMaxTime;
};
class CCamera
{
	SINGLE(CCamera);

private:

	Vec2			m_vPos;
	Vec2			m_vScale;

	Vec2			m_vCamRoomLT;	//LeftTop
	Vec2			m_vCamRoomRB;	//RightBottom

	Vec2			m_Look;			//타겟
	Vec2			m_Diff;			//

	CTexture*		m_pBlindTex;

	list<tCamEffect>	m_listCamEffect;
	float			m_fRatio;

	//카메라 쉐이크
	Vec2			m_vOffset;		//흔들릴때 위치 값
	float			m_fAccTime;		//쉐이크 진행시간
	float			m_fMaxTime;		//쉐이크 최대시간
	float			m_fRange;		//흔들림 범위
	float			m_fShakeSpeed;	//흔들림 시간
	float			m_fShakeDir;	//쉐이크 진행방향
	bool			m_bCamShake;


public:

	void SetPos(Vec2 _v) { m_vPos = _v; }
	Vec2 GetPos() { return m_vPos; }

	void SetScale(Vec2 _v) { m_vScale = _v; }
	Vec2 GetScale() { return m_vPos; }

	void SetCamRoomPos(Vec2 _vLeftTop, Vec2 _vRightBottom) 
	{
		m_vCamRoomLT = _vLeftTop;
		m_vCamRoomRB = _vRightBottom;
	}


	void SetLook(Vec2 _Look) { m_Look = _Look; }
	Vec2 GetLoot() { return m_Look; }
	Vec2 GetRenderPos(Vec2 _RealPos) { return _RealPos - m_Diff; }
	Vec2 GetRealPos(Vec2 _RealPos) { return _RealPos + m_Diff; }


public:
	void tick();
	void render(HDC _dc);

public:
	void FadeOut(float _fTerm);
	void FadeIn(float _fTerm);
	void CameraShake(float _fRange, float _fSpeed, float _fTerm);

private:
	void CameraEffect();
	void CameraShake();


};
 
