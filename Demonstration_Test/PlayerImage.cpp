#include "stdafx.h"
#include "PlayerImage.h"
#include "Bitmap_Manager.h"

CPlayerImage::CPlayerImage()
{
}

CPlayerImage::~CPlayerImage()
{
}

int CPlayerImage::Ready_UI()
{
	m_tPoint.fX = 55.f;
	m_tPoint.fY = 12.f;
	m_tPoint.iCX = 39;
	m_tPoint.iCY = 42;

	m_tFrame.iStartFrame = 0;
	m_tFrame.iEndFrame = 16;
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/UI/PlayerState.bmp", L"PlayerHead");
	return READY_OK;
}

void CPlayerImage::Update_UI()
{
}

void CPlayerImage::Late_Update_UI()
{
}

void CPlayerImage::Render_UI(HDC hDC)
{
	m_tRECT.left = m_tPoint.fX - (m_tPoint.iCX >> 1);
	m_tRECT.bottom = m_tPoint.fY - (m_tPoint.iCY >> 1);
	m_tRECT.right = m_tPoint.fX + (m_tPoint.iCX >> 1);
	m_tRECT.top = m_tPoint.fY + (m_tPoint.iCY >> 1);

	HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"PlayerHead");

	//Rectangle(hDC, m_tRECT.left, m_tRECT.top, m_tRECT.right, m_tRECT.bottom);
	GdiTransparentBlt(hDC,
		m_tRECT.left, m_tRECT.top,
		m_tPoint.iCX, m_tPoint.iCY,
		hMemDC,
		m_tFrame.iStartFrame*m_tPoint.iCX, 0,
		m_tPoint.iCX, m_tPoint.iCY,
		RGB(255, 0, 255));
}

CMyUI * CPlayerImage::Create()
{
	CMyUI* pInstance = new CPlayerImage;
	if (0 > pInstance->Ready_UI())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}
