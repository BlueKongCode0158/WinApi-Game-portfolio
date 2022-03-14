#include "stdafx.h"
#include "Slash.h"
#include "GameObject_Manager.h"
#include "GameObject.h"
#include "Scroll_Manager.h"
#include "Bitmap_Manager.h"

CSlash::CSlash()
{
}

CSlash::~CSlash()
{
}

CSkil * CSlash::Create()
{
	CSkil* pInstacne = new CSlash;
	if (0 > pInstacne->Ready_Skil())
	{
		Safe_Delete(pInstacne);
	}
	return pInstacne;
}

CSkil * CSlash::Create(LPVOID pVoid)
{
	CSkil* pInstacne = new CSlash;
	if (0 > pInstacne->Ready_Skil())
	{
		Safe_Delete(pInstacne);
	}
	return pInstacne;
}

CSkil * CSlash::Create(int iNum)
{
	CSkil* pInstacne = new CSlash;
	pInstacne->Set_ClickNum(iNum);
	if (0 > pInstacne->Ready_Skil())
	{
		Safe_Delete(pInstacne);
	}
	return pInstacne;
}

int CSlash::Ready_Skil()
{
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Skil/Slash_Large.bmp", L"Slash");
	CGameObject* pPlayer = CGameObject_Manager::Get_Instacne()->Get_Player();
	if (nullptr == pPlayer)
	{
		return READY_FAILED;
	}
	int iDistance = 40;	//반지름.
	//플레이어 위치값 가져오는 것 좀 하고..
	POINT pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	int iPlayerX = static_cast<int>(pPlayer->Get_tPoint()->fX);
	int iPlayerY = static_cast<int>(pPlayer->Get_tPoint()->fY);

	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

	pt.x -= iScrollX;
	pt.y -= iScrollY;

	int iBase = pt.x - iPlayerX;							//밑변
	int iHight = pt.y - iPlayerY;							//높이
	float iHypotenuse = sqrt(iBase*iBase + iHight*iHight);	//빗변

	//cos을 구할거니까.. = (빗변/밑변)  -> (밑변/빗변) 유의
	float fAngle = acos(iBase / iHypotenuse);
	if (iPlayerY <= pt.y)
		fAngle *= (-1.f);


	//앵클도 구하고.. 해당 방향까지의 앵글?
	m_tPoint.fX = iPlayerX + (iDistance * cosf(fAngle));
	m_tPoint.fY = iPlayerY - (iDistance * sinf(fAngle));

	m_tPoint.iCX = 64;
	m_tPoint.iCY = 64;

	m_dwGetickCount = GetTickCount();

	m_tFrame.dwSpeed = 0;
	m_tFrame.dwTime = 0;
	m_tFrame.iStartFrame = 0;
	m_tFrame.iEndFrame = 0;
	m_tFrame.iState = 0;


	float fRadian = PI / 180.f;

	m_iAttack = 1;

	if ((-22.5)*fRadian <= fAngle && (22.5 * fRadian >= fAngle))
	{
		if (m_iClickNum == 1)
		{
			m_tFrame.iState = 4;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
		else if (m_iClickNum == 2)
		{
			m_tFrame.iState = 5;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
		else
		{
			m_tFrame.iState = 4;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
	}
	else if (22.5 * fRadian <= fAngle && 67.5 * fRadian >= fAngle)
	{
		if (m_iClickNum == 1)
		{
			m_tFrame.iState = 10;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
		else if (m_iClickNum == 2)
		{
			m_tFrame.iState = 11;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
		else
		{
			m_tFrame.iState = 10;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
	}
	else if ((67.5 * fRadian) <= fAngle && (112.5 * fRadian) >= fAngle)
	{
		if (m_iClickNum == 1)
		{
			m_tFrame.iState = 2;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
		else if (m_iClickNum == 2)
		{
			m_tFrame.iState = 3;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
		else
		{
			m_tFrame.iState = 2;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
	}
	else if (((-67.5)*fRadian <= fAngle && (-22.5)*fRadian >= fAngle))
	{
		if (m_iClickNum == 1)
		{
			m_tFrame.iState = 14;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
		else if (m_iClickNum == 2)
		{
			m_tFrame.iState = 15;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
		else
		{
			m_tFrame.iState = 14;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
	}
	else if (((157.5f * fRadian) <= fAngle && (180.f * fRadian) >= fAngle) || (-180.f * fRadian) <= fAngle && (-157.5*fRadian) >= fAngle)
	{
		if (m_iClickNum == 1)
		{
			m_tFrame.iState = 6;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
		else if (m_iClickNum == 2)
		{
			m_tFrame.iState = 7;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
		else
		{
			m_tFrame.iState = 6;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
	}
	else if ((((112.5 * fRadian) <= fAngle && (157.5 * fRadian) >= fAngle)))
	{
		if (m_iClickNum == 1)
		{
			m_tFrame.iState = 8;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
		else if (m_iClickNum == 2)
		{
			m_tFrame.iState = 9;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
		else
		{
			m_tFrame.iState = 8;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
	}
	else if ((-157.5*fRadian) <= fAngle && (-112.5*fRadian) >= fAngle)
	{
		if (m_iClickNum == 1)
		{
			m_tFrame.iState = 12;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
		else if (m_iClickNum == 2)
		{
			m_tFrame.iState = 13;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
		else
		{
			m_tFrame.iState = 12;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
	}
	else if ((-112.5*fRadian) <= fAngle && ((-67.5*fRadian) >= fAngle))
	{
		if (m_iClickNum == 1)
		{
			m_tFrame.iState = 0;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
		else if (m_iClickNum == 2)
		{
			m_tFrame.iState = 1;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
		else
		{
			m_tFrame.iState = 0;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
		}
	}


	m_iDamage = 20;

	return READY_OK;
}

int CSlash::Update_Skil()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.iStartFrame++;
		if (m_tFrame.iStartFrame > m_tFrame.iEndFrame)
		{
			return OBJ_DEAD;
		}
	}

	//if (m_dwGetickCount + 200 < GetTickCount())
	//{
	//	return OBJ_DEAD;
	//}


	int iSizeX = 82;
	int iSizeY = 82;

	m_tRect.left = m_tPoint.fX - (iSizeX >> 1);
	m_tRect.top = m_tPoint.fY - (iSizeY >> 1);
	m_tRect.right = m_tPoint.fX + (iSizeX >> 1);
	m_tRect.bottom = m_tPoint.fY + (iSizeY >> 1);

	return OBJ_NOEVENT;
}

void CSlash::Render_Skil(HDC hDC)
{
	m_tCollRect.left = m_tPoint.fX - (m_tPoint.iCX >> 1);
	m_tCollRect.top = m_tPoint.fY - (m_tPoint.iCY >> 1);
	m_tCollRect.right = m_tPoint.fX + (m_tPoint.iCX >> 1);
	m_tCollRect.bottom = m_tPoint.fY + (m_tPoint.iCY >> 1);

	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

	int iSizeX = 82;
	int iSizeY = 82;

	m_tRect.left = m_tPoint.fX - (iSizeX >> 1);
	m_tRect.top= m_tPoint.fY - (iSizeY >> 1);
	m_tRect.right = m_tPoint.fX + (iSizeX >> 1);
	m_tRect.bottom = m_tPoint.fY + (iSizeY >> 1);

	m_hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"Slash");

	//Ellipse(hDC, m_tCollRect.left + iScrollX, m_tCollRect.top + iScrollY, m_tCollRect.right + iScrollX, m_tCollRect.bottom + iScrollY);
	GdiTransparentBlt(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, iSizeX, iSizeY, m_hMemDC, m_tFrame.iState *iSizeX, m_tFrame.iStartFrame * iSizeY, iSizeX, iSizeY, RGB(255, 0, 255));
}

void CSlash::Release_Skil()
{
}
