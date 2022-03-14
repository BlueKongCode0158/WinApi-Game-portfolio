#include "stdafx.h"
#include "SlashEffect.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
#include "GameObject_Manager.h"
#include "Player.h"

CSlashEffect::CSlashEffect()
{
}

CSlashEffect::~CSlashEffect()
{
	Release_Effect();
}

int CSlashEffect::Ready_Effect()
{
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Skil/SlashHitSpark_1.bmp", L"SlashEffect");
	m_tPoint.iCX = 96;
	m_tPoint.iCY = 96;

	m_tFrame.iStartFrame = 0;
	m_tFrame.iEndFrame = 3;
	m_tFrame.iState = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	return READY_OK;
}

int CSlashEffect::Update_Effect()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.iStartFrame += 1;
		if (m_tFrame.iEndFrame >= 4 && m_tFrame.iState >= 4)
		{
			m_tFrame.iStartFrame = 0;
			m_tFrame.iState += 1;
		}
	}

	if (m_tFrame.iStartFrame > m_tFrame.iEndFrame)
	{
		CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
		if (nullptr == pObj)
		{
			return OBJ_DEAD;
		}
		pObj->Set_Mp(5);
		return OBJ_DEAD;
	}
	return OBJ_NOEVENT;
}

void CSlashEffect::Late_Update_Effect()
{
}

void CSlashEffect::Render_Effect(HDC hDC)
{
	//m_tRect.left = m_tPoint.fX - (m_tPoint.iCX >> 1);
	//m_tRect.top = m_tPoint.fY - (m_tPoint.iCY >> 1);
	//m_tRect.right = m_tPoint.fX + (m_tPoint.iCX >> 1);
	//m_tRect.bottom = m_tPoint.fY + (m_tPoint.iCY >> 1);
	CEffect::Update_RECT();

	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();
	m_hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"SlashEffect");
	GdiTransparentBlt(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY , m_tPoint.iCX, m_tPoint.iCY,
		m_hMemDC,
		m_tFrame.iStartFrame*m_tPoint.iCX, m_tFrame.iState*m_tPoint.iCY, m_tPoint.iCX, m_tPoint.iCY, RGB(255, 0, 255));
}

void CSlashEffect::Release_Effect()
{
}

CEffect * CSlashEffect::Create(TPOINT * tPoint)
{
	CEffect* pInstance = new CSlashEffect;
	dynamic_cast<CSlashEffect*>(pInstance)->Set_tPoint(*tPoint);
	if (0 > pInstance->Ready_Effect())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}
