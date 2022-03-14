#pragma once
#include "GameObject.h"

class CProb final
	:public CGameObject
{
public:
	enum PROBS
	{
		NOMAL,IRON
	};
private:
	CProb();
public:
	virtual ~CProb();
public:
	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_GamceObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
public:
	static CGameObject* Create();
public:
	void Set_Prob_ID(CProb::PROBS eID)
	{
		m_eProbID = eID;
	}
	CProb::PROBS Get_Prob_ID()
	{
		return m_eProbID;
	}
public:
	RECT* Get_ImageRect()
	{
		return &m_tImageRect;
	}
	void Set_ImageRect(RECT& rRECT)
	{
		m_tImageRect.left = rRECT.left;
		m_tImageRect.top = rRECT.top;
		m_tImageRect.right = rRECT.right;
		m_tImageRect.bottom = rRECT.bottom;
	}
private:
	RECT m_tImageRect;
	CProb::PROBS m_eProbID;
};