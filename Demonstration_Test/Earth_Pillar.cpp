#include "stdafx.h"
#include "Earth_Pillar.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
#include "GameObject_Manager.h"
#include "Font_Damage.h"
#include "Font_Damage_Manager.h"

CEarth_Pillar::CEarth_Pillar()
	:m_fDist(0.f)
{
}

CEarth_Pillar::~CEarth_Pillar()
{
}

int CEarth_Pillar::Ready_GameObject()
{
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Boss/EarthBossPillar.bmp", L"Pillar");
	m_tFrame.iStartFrame = 0;
	m_tFrame.iEndFrame = 2;
	m_tFrame.iState = 0;
	m_tFrame.dwSpeed = 400;
	m_tFrame.dwTime = GetTickCount();
	m_dwAttackNum = 1;

	float fCenterX = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::BOSS)->front()->Get_tPoint()->fX;
	float fCenterY = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::BOSS)->front()->Get_tPoint()->fY;

	m_iDamage = (rand() % 10) + 5 ;

	m_tPoint.fX = fCenterX + (m_fDist * cos(m_fAngle));
	m_tPoint.fY = fCenterY - (m_fDist * sin(m_fAngle));
	m_tPoint.iCX = 32;
	m_tPoint.iCY = 128;

	return READY_OK;
}

int CEarth_Pillar::Update_GameObject()
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
	if (IntersectRect(&tRECT, &m_tCollisionRect, pObj->Get_RECT()) && 0 < m_dwAttackNum)
	{
		pObj->Set_SubHP(m_iDamage);
		m_dwAttackNum -= 1;

		CFont_Damage* pFont = CFont_Damage::Create();

		TFPOINT tfPoint{};
		tfPoint.fX = pObj->Get_tPoint()->fX - 10;
		tfPoint.fY = pObj->Get_tPoint()->fY - 10;
		pFont->Set_Point(tfPoint);
		pFont->Set_Damage(m_iDamage);
		pFont->Set_Color(255, 0, 0);
		CFont_Damage_Manager::Get_Instance()->Add_Font_Damage(pFont);


		return OBJ_NOEVENT;
	}


	if ((m_tFrame.iStartFrame >= m_tFrame.iEndFrame) && m_tFrame.dwTime + 1000 < GetTickCount())
	{
		return OBJ_DEAD;
	}
	// µ¥¹ÌÁö´Â ¿©±â¼­ Áà¾ßÇÏ³ª °í¹ÎµÅ..
	return 0;
}

void CEarth_Pillar::Late_GamceObject()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
	{
		m_tFrame.iStartFrame += 1;
		if (m_tFrame.iStartFrame < 2)
		{
			m_tFrame.dwTime = GetTickCount();
		}
	}

	if (m_tFrame.iStartFrame > m_tFrame.iEndFrame)
	{
		m_tFrame.iStartFrame = 2;
	}
}

void CEarth_Pillar::Render_GameObject(HDC hDC)
{
	CGameObject::Update_Rect();
	int iSizeY = 0;
	if (0 == m_tFrame.iStartFrame)
	{
		iSizeY = 32;
	}
	else if (1 == m_tFrame.iStartFrame)
	{
		iSizeY = 64;
	}
	else if (2 == m_tFrame.iStartFrame)
	{
		iSizeY = 96;
	}
	m_tCollisionRect.left = m_tPoint.fX - (m_tPoint.iCX >> 1);
	m_tCollisionRect.right = m_tPoint.fX + (m_tPoint.iCX >> 1);
	m_tCollisionRect.top = m_tRect.bottom - iSizeY;
	m_tCollisionRect.bottom = m_tRect.bottom;

	

	HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"Pillar");

	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		m_tPoint.iCX, m_tPoint.iCY,
		hMemDC,
		m_tFrame.iStartFrame * m_tPoint.iCX, m_tFrame.iState * m_tPoint.iCY,
		m_tPoint.iCX, m_tPoint.iCY,
		RGB(255, 0, 255));

	//Rectangle(hDC, m_tCollisionRect.left + iScrollX, m_tCollisionRect.top + iScrollY, m_tCollisionRect.right + iScrollX, m_tCollisionRect.bottom + iScrollY);
}

void CEarth_Pillar::Release_GameObject()
{
}

CGameObject * CEarth_Pillar::Create(float fAngle , float fDist)
{
	CGameObject* pInstance = new CEarth_Pillar();
	dynamic_cast<CEarth_Pillar*>(pInstance)->Set_Angle(fAngle);
	dynamic_cast<CEarth_Pillar*>(pInstance)->Set_fDist(fDist);
	if (0 > pInstance->Ready_GameObject())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}
