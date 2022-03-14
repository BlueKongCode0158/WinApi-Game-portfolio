#include "stdafx.h"
#include "Title.h"
#include "Bitmap_Manager.h"

CTitle::CTitle()
{
}

CTitle::~CTitle()
{
}

int CTitle::Ready_UI()
{

	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Logo/TitleLogo4.bmp", L"Logo");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Black.bmp", L"BackGround");
	m_tPoint.iCX = WINCX;
	m_tPoint.iCY = WINCY;

	m_tPoint.fX = WINCX >> 1;
	m_tPoint.fY = (WINCY >> 1)/* Àû´ç -170*/;

	return READY_OK;
}

void CTitle::Update_UI()
{
	if (true == bMyStartID)
	{
		int iY = (WINCY >> 1) - 170;
		m_tPoint.fY -= 20.f;

		if (m_tPoint.fY <= iY)
		{
			m_tPoint.fY = iY;
		}
	}
	else if (false == bMyStartID)
	{
		int iY = WINCY >> 1;
		m_tPoint.fY += 20.f;

		if (m_tPoint.fY >= iY)
		{
			m_tPoint.fY = iY;
		}
	}
}

void CTitle::Late_Update_UI()
{
} 

void CTitle::Render_UI(HDC hDC)
{
	CMyUI::Update_RECT();
	HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"Logo");
	if (true == bMyStartID)
	{
		BLENDFUNCTION _AlphaBlend;
		_AlphaBlend.AlphaFormat = 0;
		_AlphaBlend.BlendFlags = 0;
		_AlphaBlend.SourceConstantAlpha = 170;
		_AlphaBlend.BlendOp = 0;
		HDC hBackDC = CBitmap_Manager::Get_Instance()->FindImage(L"BackGround");
		GdiAlphaBlend(hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, WINCX, WINCY, _AlphaBlend);
	}
	GdiTransparentBlt(hDC,
		m_tRECT.left, m_tRECT.top,
		m_tPoint.iCX,
		m_tPoint.iCY,
		hMemDC,
		0, 0,
		m_tPoint.iCX, m_tPoint.iCY,
		RGB(255, 0, 255));
}

CMyUI * CTitle::Create()
{
	CMyUI* pInstacne = new CTitle;
	if (0 > pInstacne->Ready_UI())
	{
		Safe_Delete(pInstacne);
	}
	return pInstacne;
}

CMyUI * CTitle::Create(LPVOID pVoid)
{
	CMyUI* pInstacne = new CTitle;
	if (0 > pInstacne->Ready_UI())
	{
		Safe_Delete(pInstacne);
	}
	return pInstacne;
}
