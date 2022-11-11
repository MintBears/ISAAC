#pragma once
#include "CEntity.h"

class CAnimator;
class CTexture;

class CAnimation :
    public CEntity
{
public:
    CAnimation(CAnimator* _pAnimator);
    ~CAnimation();

private:
    CAnimator*          m_pAnimator;        
    vector<tAnimFrm>    m_vecFrm;           //애니메이션 정보모음
    CTexture*           m_pAtlas;           //합본 이미지
    int                 m_iCurFrm;          //현제 프레임
    float               m_fAccTime;         //재생 흐른시간
    bool                m_bFinish;          //끝인가
    bool                m_bIsPlay;          //재생여부
public:

    bool IsFinish() { return m_bFinish; }
    void Reset()
    {
        m_iCurFrm = 0;
        m_fAccTime = 0.f;
        m_bFinish = false;
    }

    void SetPlay() { m_bIsPlay = false; }
    void SetStop() { m_bIsPlay = true; }

private:
    void init(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset, int _iMaxFrmCount, float _fDuration);
public:
    void tick();
    void render(HDC _dc);

    CLONE(CAnimation)

    void Save(const wstring& _strRelativePath);
    void Load(const wstring& _strRelativePath);

    friend class CAnimator;

};

