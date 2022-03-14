#include "stdafx.h"
#include "HpBackGround.h"
#include "Bitmap_Manager.h"

CHpBackGround::CHpBackGround()
{
}

CHpBackGround::~CHpBackGround()
{
}

int CHpBackGround::Ready_UI()
{
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/UI/PlayerHpUI.bmp", L"PlayerHpBackGround");
	m_tPoint.fX = 150;
	m_tPoint.fY = 50;
	m_tPoint.iCX = 246;
	m_tPoint.iCY = 57;

	return READY_OK;
}

void CHpBackGround::Update_UI()
{
}

void CHpBackGround::Late_Update_UI()
{
}

void CHpBackGround::Render_UI(HDC hDC)
{

	m_tRECT.left = m_tPoint.fX - (m_tPoint.iCX >> 1);
	m_tRECT.bottom = m_tPoint.fY - (m_tPoint.iCY >> 1);
	m_tRECT.right = m_tPoint.fX + (m_tPoint.iCX >> 1);
	m_tRECT.top = m_tPoint.fY + (m_tPoint.iCY >> 1);
	
	HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"PlayerHpBackGround");
	GdiTransparentBlt(hDC,
		m_tRECT.left, m_tRECT.bottom,
		m_tPoint.iCX, m_tPoint.iCY,
		hMemDC,
		0, 0, m_tPoint.iCX, m_tPoint.iCY,
		RGB(255, 0, 255));
}

CMyUI * CHpBackGround::Create()
{
	CMyUI* pInstance = new CHpBackGround;
	if (0 > pInstance->Ready_UI())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}
