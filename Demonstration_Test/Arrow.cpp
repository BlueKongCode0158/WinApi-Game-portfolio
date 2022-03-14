#include "stdafx.h"
#include "Arrow.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
#include "GameObject_Manager.h"
#include "SoundMgr.h"

CArrow::CArrow()
{
}

CArrow::~CArrow()
{
}

int CArrow::Ready_GameObject()
{
	CSoundMgr::Get_Instance()->PlaySound(L"ArcherArrow.wav", CSoundMgr::CHANNELID::MONSTER);
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Monster/Arrow_1.bmp", L"Arrow");
	m_tPoint.iCX = 32;
	m_tPoint.iCY = 32;

	m_iPushNum = 1;
	m_iDamage = 10;

	CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();

	if (nullptr == pObj)
		return OBJ_NOEVENT;

	float fBase = pObj->Get_tPoint()->fX - m_tPoint.fX ;
	float fHight = pObj->Get_tPoint()->fY - m_tPoint.fY ;
	float fDist = sqrtf(fBase*fBase + fHight*fHight);

	float fAngle = acosf(fBase / fDist);
	float fRadian = PI / 180.f;	//이거 머리에 박아두자..

	if (m_tPoint.fY <= pObj->Get_tPoint()->fY)
	{
		fAngle *= -1.f;
	}

	m_fAngle = fAngle;

	if (-22.5*fRadian <= fAngle && 22.5* fRadian >= fAngle)
	{
		m_tFrame.iStartFrame = 3;
	}
	else if (22.5*fRadian <= fAngle && 67.5*fRadian >= fAngle)
	{
		m_tFrame.iStartFrame = 5;
	}
	else if (67.5*fRadian <= fAngle && 112.5*fRadian >= fAngle)
	{
		m_tFrame.iStartFrame = 0;
	}
	else if (112.5*fRadian <= fAngle && 157.5*fRadian >= fAngle)
	{
		m_tFrame.iStartFrame = 4;
	}
	else if ((157.5*fRadian <= fAngle && 180.f * fRadian >= fAngle) || (-180.f*fRadian <= fAngle && -157.f*fRadian >= fAngle))
	{
		m_tFrame.iStartFrame = 2;
	}
	else if (-157.5f*fRadian <= fAngle && -112.5*fRadian >= fAngle)
	{
		m_tFrame.iStartFrame = 7;
	}
	else if (-112.5*fRadian <= fAngle && -67.5*fRadian >= fAngle)
	{
		m_tFrame.iStartFrame = 1;
	}
	else if (-67.5*fRadian <= fAngle && -22.5*fRadian >= fAngle)
	{
		m_tFrame.iStartFrame = 6;
	}


	m_dwCreateTime = GetTickCount();
	return READY_OK;
}

int CArrow::Update_GameObject()
{
	if (m_bDead == true)
	{
		return OBJ_DEAD;
	}
	if (m_dwCreateTime + 2000 < GetTickCount())
	{
		return OBJ_DEAD;
	}

	m_tPoint.fX += 5*cosf(m_fAngle);
	m_tPoint.fY -= 5 * sinf(m_fAngle);

	return OBJ_NOEVENT;
}

void CArrow::Late_GamceObject()
{
}

void CArrow::Render_GameObject(HDC hDC)
{
	CGameObject::Update_Rect();

	HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"Arrow");
	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();


	Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		m_tPoint.iCX, m_tPoint.iCY, hMemDC,
		m_tFrame.iStartFrame*m_tPoint.iCX, 0 *m_tPoint.iCY,
		m_tPoint.iCX, m_tPoint.iCY,
		RGB(255, 0, 255));
}

void CArrow::Release_GameObject()
{
}

CGameObject * CArrow::Create(TFPOINT & rPoint)
{
	CGameObject* pInstance = new CArrow;
	pInstance->Set_tPoint(rPoint);
	if (0 > pInstance->Ready_GameObject())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

CGameObject * CArrow::Create()
{
	CGameObject* pInstance = new CArrow;
	if (0 > pInstance->Ready_GameObject())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}
