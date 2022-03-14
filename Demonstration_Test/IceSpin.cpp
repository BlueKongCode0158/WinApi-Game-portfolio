#include "stdafx.h"
#include "IceSpin.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
#include "GameObject_Manager.h"
#include "GameObject.h"
#include "Player.h"

#define SKILTIME_ICE 4000

CIceSpin::CIceSpin()
	:m_fDistance(0.f)
{
}

CIceSpin::~CIceSpin()
{
}

int CIceSpin::Ready_Skil()
{
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Skil/IceSpin_2.bmp", L"IceSpin");
	m_tFrame.iStartFrame = 0;
	m_tFrame.iEndFrame = 7;
	m_tFrame.iState = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	m_tPoint.iCX = 96;
	m_tPoint.iCY = 96;

	m_fDistance = 50.f;
	m_iDamage = 20;

	CGameObject* pPlayer = CGameObject_Manager::Get_Instacne()->Get_Player();
	if (nullptr == pPlayer)
	{
		return READY_FAILED;
	}
	m_bAttack = false;
	m_dwAttackTime = GetTickCount();

	m_tPoint.fX = pPlayer->Get_tPoint()->fX + m_fDistance*cosf(m_fAngle);
	m_tPoint.fY = pPlayer->Get_tPoint()->fY - m_fDistance*sinf(m_fAngle);

	m_dwCreateTime = GetTickCount();

	return READY_OK;
}

int CIceSpin::Update_Skil()
{
	// 여기서 좌표값 건드려줘야 된다 이말이야..
	CGameObject* pPlayer = CGameObject_Manager::Get_Instacne()->Get_Player();
	if (nullptr == pPlayer)
	{
		return OBJ_DEAD;
	}

	if (m_dwAttackTime + 1500 < GetTickCount())
	{
		m_bAttack = false;
		m_dwAttackTime = GetTickCount();
	}

	m_tPoint.fX = pPlayer->Get_tPoint()->fX + m_fDistance*cosf(m_fAngle);
	m_tPoint.fY = pPlayer->Get_tPoint()->fY - m_fDistance*sinf(m_fAngle);


	float fRadius = PI / 180.f;
	m_fAngle += fRadius * 4.f;

	if (m_dwCreateTime + SKILTIME_ICE < GetTickCount()) //GetTickCount 가 더 커지는 순간에 죽는다는거고 그러면..
	{
		return OBJ_DEAD;
	}
	else if (m_dwCreateTime + 1500 > GetTickCount())
	{
		m_fDistance += 2.f;
	}
	else if (m_dwCreateTime + 1500 < GetTickCount() && m_dwCreateTime + 3500 > GetTickCount())
	{
		m_fDistance -= 1.f;
	}



	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		if (m_tFrame.iEndFrame >= m_tFrame.iStartFrame)
		{
			m_tFrame.iStartFrame += 1;
			m_tFrame.dwTime = GetTickCount();
		}
	}

	if (m_tFrame.iStartFrame > m_tFrame.iEndFrame)
	{
		m_tFrame.iStartFrame = 0;
	}

	return OBJ_NOEVENT;
}

void CIceSpin::Render_Skil(HDC hDC)
{
	m_tRect.left = m_tPoint.fX - (m_tPoint.iCX >> 1);
	m_tRect.top = m_tPoint.fY - (m_tPoint.iCY >> 1);
	m_tRect.right = m_tPoint.fX + (m_tPoint.iCX >> 1);
	m_tRect.bottom = m_tPoint.fY + (m_tPoint.iCY >> 1);

	m_hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"IceSpin");

	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

	//Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		m_tPoint.iCX, m_tPoint.iCY, m_hMemDC,
		m_tFrame.iStartFrame*m_tPoint.iCX, 0,
		m_tPoint.iCX, m_tPoint.iCY,
		RGB(255, 0, 255));
}

void CIceSpin::Release_Skil()
{
}

CSkil * CIceSpin::Create(float fAngle)
{
	CSkil* pInstance = new CIceSpin;
	pInstance->Set_Angle(fAngle);
	if (0 > pInstance->Ready_Skil())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}
