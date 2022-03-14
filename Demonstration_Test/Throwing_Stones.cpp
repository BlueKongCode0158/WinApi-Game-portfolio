#include "stdafx.h"
#include "Throwing_Stones.h"
#include "GameObject_Manager.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
#include "MyUI.h"
#include "UI_Manager.h"
#include "Font_Damage.h"
#include "Font_Damage_Manager.h"

CThrowing_Stones::CThrowing_Stones()
{
}

CThrowing_Stones::~CThrowing_Stones()
{
}

CGameObject * CThrowing_Stones::Create()
{
	CGameObject* pInstance = new CThrowing_Stones;
	if (0 > pInstance->Ready_GameObject())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

int CThrowing_Stones::Ready_GameObject()
{
	m_tPoint.iCX = 60;
	m_tPoint.iCY = 68;
	m_iDamage = (rand() % 20) + 5;

	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Boss/Boss_Punch.bmp", L"BossPunch");

	m_tFrame.iStartFrame = 0;
	m_tFrame.iEndFrame = 0;
	m_tFrame.iState = 0;

	m_bShotTarget = false;
	m_dwGetick = GetTickCount();
	m_bDead = false;

	return READY_OK;
}

int CThrowing_Stones::Update_GameObject()
{
	if (m_bDead == true)
	{
		return OBJ_DEAD;
	}

	CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
	if (nullptr == pObj)
	{
		return OBJ_DEAD;
	}
	RECT tRECT{};

	if (IntersectRect(&tRECT, &m_tRect, pObj->Get_RECT()))
	{
		pObj->Set_SubHP(m_iDamage);

		CFont_Damage* pFont = CFont_Damage::Create();

		TFPOINT tfPoint{};
		tfPoint.fX = pObj->Get_tPoint()->fX - 10;
		tfPoint.fY = pObj->Get_tPoint()->fY - 10;
		pFont->Set_Point(tfPoint);
		pFont->Set_Damage(m_iDamage);
		pFont->Set_Color(255, 0, 0);
		CFont_Damage_Manager::Get_Instance()->Add_Font_Damage(pFont);


		return OBJ_DEAD;
	}



	if (m_dwGetick + m_dwShotTime < GetTickCount())
	{
		if (false == m_bShotTarget)
		{
			m_bShotTarget = true;

			CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
			if (nullptr == pObj)
			{
				return OBJ_DEAD;
			}
			m_tShotPoint.fX = pObj->Get_tPoint()->fX;
			m_tShotPoint.fY = pObj->Get_tPoint()->fY;

			float fBase = m_tShotPoint.fX - m_tPoint.fX;
			float fHight = m_tShotPoint.fY - m_tPoint.fY;
			float fDist = sqrtf(fBase*fBase + fHight*fHight);

			m_fAngle = acosf(fBase / fDist);

			if (m_tPoint.fY < m_tShotPoint.fY)
				m_fAngle *= -1.f;

			float fRadian = PI / 180.f;

			if (-22.5*fRadian <= m_fAngle && 22.5* fRadian >= m_fAngle)
			{
				m_tFrame.iState = 4;
			}
			else if (22.5*fRadian <= m_fAngle && 67.5*fRadian >= m_fAngle)
			{
				m_tFrame.iState = 5;
			}
			else if (67.5*fRadian <= m_fAngle && 112.5*fRadian >= m_fAngle)
			{
				m_tFrame.iState = 1;
			}
			else if (112.5*fRadian <= m_fAngle && 157.5*fRadian >= m_fAngle)
			{
				m_tFrame.iState = 6;
			}
			else if ((157.5*fRadian <= m_fAngle && 180.f * fRadian >= m_fAngle) || (-180.f*fRadian <= m_fAngle && -157.f*fRadian >= m_fAngle))
			{
				m_tFrame.iState = 3;
			}
			else if (-157.5f*fRadian <= m_fAngle && -112.5*fRadian >= m_fAngle)
			{
				m_tFrame.iState = 6;
			}
			else if (-112.5*fRadian <= m_fAngle && -67.5*fRadian >= m_fAngle)
			{
				m_tFrame.iState = 2;
			}
			else if (-67.5*fRadian <= m_fAngle && -22.5*fRadian >= m_fAngle)
			{
				m_tFrame.iState = 7;
			}

		}

		float fDist = 10;

		m_tPoint.fX += (fDist*cosf(m_fAngle));
		m_tPoint.fY -= (fDist*sinf(m_fAngle));
		return OBJ_NOEVENT;


	}
	return OBJ_NOEVENT;
}

void CThrowing_Stones::Late_GamceObject()
{
}

void CThrowing_Stones::Render_GameObject(HDC hDC)
{
	CGameObject::Update_Rect();

	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

	HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"BossPunch");

	GdiTransparentBlt(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		m_tPoint.iCX, m_tPoint.iCY,
		hMemDC,
		m_tPoint.iCX * m_tFrame.iStartFrame,m_tPoint.iCY*m_tFrame.iState,
		m_tPoint.iCX,m_tPoint.iCY,
		RGB(255,0,255)
		);
}

void CThrowing_Stones::Release_GameObject()
{
}
