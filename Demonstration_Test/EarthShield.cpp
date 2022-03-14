#include "stdafx.h"
#include "EarthShield.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
#include "GameObject.h"
#include "Player.h"
#include "GameObject_Manager.h"

CEarthShield::CEarthShield()
{
}

CEarthShield::~CEarthShield()
{
}

CSkil * CEarthShield::Create()
{
	return nullptr;
}

CSkil * CEarthShield::Create(LPVOID pVoid)
{
	return nullptr;
}

CSkil * CEarthShield::Create(TFPOINT & rPoint)
{
	CSkil* pInstance = new CEarthShield;
	dynamic_cast<CEarthShield*>(pInstance)->Set_Point(rPoint);
	if (0 > pInstance->Ready_Skil())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

CSkil * CEarthShield::Create(float fAngle)
{
	CSkil* pInstance = new CEarthShield;
	pInstance->Set_Angle(fAngle);
	if (0 > pInstance->Ready_Skil())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

int CEarthShield::Ready_Skil()
{
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Skil/Shield_2.bmp", L"Shield");
	m_tPoint.iCX = 50;
	m_tPoint.iCY = 50;

	m_iDamage = 10;
	m_bAttack = false;

	m_dwAttackTime = GetTickCount();
	m_dwShildTime = GetTickCount();
	m_tFrame.iEndFrame = 0;
	return READY_OK;
}

int CEarthShield::Update_Skil()
{
	if (m_dwShildTime + 4000 < GetTickCount())
	{
		return OBJ_DEAD;
	}

	CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
	if (nullptr == pObj)
	{
		return OBJ_NOEVENT;
	}

	if (m_dwAttackTime + 1500 < GetTickCount())
	{
		m_bAttack = false;
		m_dwAttackTime = GetTickCount();
	}

	float fDist = 70;
	float fPlayerX = pObj->Get_tPoint()->fX;
	float fPlayerY = pObj->Get_tPoint()->fY;
	

	float fRadius = PI / 180.f;

	//좌표 구하는 공식
	//좌표 저정해주는 부분

	m_tPoint.fX = fPlayerX + fDist * cosf(m_fAngle);
	m_tPoint.fY = fPlayerY - fDist * sinf(m_fAngle);


	if (GetTickCount() < m_dwShildTime + 2000)
	{
		m_fAngle += 3 * fRadius;	//이게 계속 각도를 높여주는 부분이고.
	}
	if (m_dwShildTime + 2000 < GetTickCount() && GetTickCount() < m_dwShildTime + 3000)
	{
		m_fAngle += 1.5 * fRadius;
	}
	
	float fBase =  m_tPoint.fX - pObj->Get_tPoint()->fX ;
	float fHight = m_tPoint.fY - pObj->Get_tPoint()->fY ;
	float fDistance = sqrtf( fBase * fBase + fHight * fHight );

	float fAngle = acosf(fBase / fDistance);
	// ( 밑변 / 빗변 )

	if (pObj->Get_tPoint()->fY <= m_tPoint.fY)	//어디가 도착점인지 생각을 잘못해서 그렇게 나온거였네 :3..
	{
		fAngle *= -1.f;
	}


	// 해당 좌표에 따른 스프라이트 변화
	if (-15.f*fRadius <= fAngle && 15.f*fRadius >= fAngle)
	{
		m_tFrame.iStartFrame = 10;
	}
	else if (15.f*fRadius <= fAngle && 45.f*fRadius >= fAngle)
	{
		m_tFrame.iStartFrame = 7;
	}
	else if (45.f*fRadius <= fAngle && 75.f*fRadius >= fAngle)
	{
		m_tFrame.iStartFrame = 5;
	}
	else if (75.f*fRadius <= fAngle && 105.f*fRadius >= fAngle)
	{
		m_tFrame.iStartFrame = 0;
	}
	else if (105.f*fRadius <= fAngle&&135.f*fRadius >= fAngle)
	{
		m_tFrame.iStartFrame = 4;
	}
	else if (135.f*fRadius <= fAngle && 165.f*fRadius >= fAngle)
	{
		m_tFrame.iStartFrame = 6;
	}
	else if ((165.f*fRadius <= fAngle && 180.f*fRadius >= fAngle) || (-180.f*fRadius <= fAngle && -165.f*fRadius >= fAngle))
	{
		m_tFrame.iStartFrame =11;
	}
	else if (-165.f*fRadius <= fAngle && -135.f*fRadius >= fAngle)
	{
		m_tFrame.iStartFrame = 8;
	}
	else if (-135.f*fRadius <= fAngle && -105.f*fRadius >= fAngle)
	{
		m_tFrame.iStartFrame = 2;
	}
	else if (-105.f*fRadius <= fAngle && -75.f*fRadius >= fAngle)
	{
		m_tFrame.iStartFrame = 1;
	}
	else if (-75.f*fRadius <= fAngle && -45.f*fRadius >= fAngle)
	{
		m_tFrame.iStartFrame = 3;
	}
	else if (-45.f*fRadius <= fAngle && -15.f*fRadius >= fAngle)
	{
		m_tFrame.iStartFrame = 9;
	}
	return OBJ_NOEVENT;
}

void CEarthShield::Render_Skil(HDC hDC)
{
	m_tCollRect.left = m_tPoint.fX - (m_tPoint.iCX >> 1);
	m_tCollRect.top = m_tPoint.fY - (m_tPoint.iCY >> 1);
	m_tCollRect.right = m_tPoint.fX + (m_tPoint.iCX >> 1);
	m_tCollRect.bottom = m_tPoint.fY + (m_tPoint.iCY >> 1);
	//이거 함수로 빼두면 더 편할 듯

	int iImageSizeX = 40;
	int iImageSizeY = 46;

	m_tRect.left = m_tPoint.fX - (iImageSizeX >> 1);
	m_tRect.top = m_tPoint.fY - (iImageSizeY >> 1);
	m_tRect.right = m_tPoint.fX + (iImageSizeX >> 1);
	m_tRect.bottom = m_tPoint.fY + (iImageSizeY >> 1);

	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

	m_hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"Shield");
	//Ellipse(hDC, m_tCollRect.left + iScrollX, m_tCollRect.top + iScrollY, m_tCollRect.right + iScrollX, m_tCollRect.bottom + iScrollY);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		iImageSizeX, iImageSizeY,
		m_hMemDC,
		iImageSizeX*m_tFrame.iStartFrame, 0, iImageSizeX, iImageSizeY, RGB(255, 0, 255));
}

void CEarthShield::Release_Skil()
{
}
