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
    vector<tAnimFrm>    m_vecFrm;
    CTexture*           m_pAtlas;
    int                 m_iCurFrm;
    float               m_fAccTime;
    bool                m_bFinish;
public:

    bool IsFinish() { return m_bFinish; }
    void Reset()
    {
        m_iCurFrm = 0;
        m_fAccTime = 0.f;
        m_bFinish = false;
    }

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

