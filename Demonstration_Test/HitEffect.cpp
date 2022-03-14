#include "stdafx.h"
#include "HitEffect.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"

CHitEffect::CHitEffect()
{
}

CHitEffect::~CHitEffect()
{
}

CEffect * CHitEffect::Create()
{
	CEffect* pInstance = new CHitEffect;
	if (0 > pInstance->Ready_Effect())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

int CHitEffect::Ready_Effect()
{
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Skil/HitSparks_2.bmp", L"HitSparks");

	m_tFrame.iStartFrame = 0;
	m_tFrame.iEndFrame = 7;
	m_tFrame.iState = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	m_tPoint.iCX = 112;
	m_tPoint.iCY = 112;
	return READY_OK;
}

int CHitEffect::Update_Effect()
{
	if (m_tFrame.iStartFrame > m_tFrame.iEndFrame)
	{
		return OBJ_DEAD;
	}
	return OBJ_NOEVENT;
}

void CHitEffect::Late_Update_Effect()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
	{
		m_tFrame.iStartFrame += 1;
	}
}

void CHitEffect::Render_Effect(HDC hDC)
{
	CEffect::Update_RECT();

	HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"HitSparks");

	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();


	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		m_tPoint.iCX, m_tPoint.iCY,
		hMemDC,
		m_tFrame.iStartFrame*m_tPoint.iCX, m_tFrame.iState*m_tPoint.iCY,
		m_tPoint.iCX, m_tPoint.iCY,
		RGB(255, 0, 255));
}

void CHitEffect::Release_Effect()
{
}
