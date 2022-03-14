#include "stdafx.h"
#include "MyMouse.h"
#include "Bitmap_Manager.h"

CMyMouse::CMyMouse()
{
}

CMyMouse::~CMyMouse()
{
	Release_MyMouse();
}

int CMyMouse::Ready_MyMouse()
{
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/UI/MouseCursor1.bmp", L"MouseCursor");
	m_tPoint.iCX = 64;
	m_tPoint.iCY = 64;
	ShowCursor(FALSE);
	return READY_OK;
}

void CMyMouse::Update_MyMouse()
{
	POINT pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	m_tPoint.fX = static_cast<float>(pt.x);
	m_tPoint.fY = static_cast<float>(pt.y);
}

void CMyMouse::Late_MyMouse()
{
}

void CMyMouse::Render_MyMouse(HDC hDC)
{
	m_tRect.left = m_tPoint.fX - (m_tPoint.iCX >> 1);
	m_tRect.right = m_tPoint.fX + (m_tPoint.iCX >> 1);
	m_tRect.top = m_tPoint.fY - (m_tPoint.iCY >> 1);
	m_tRect.bottom = m_tPoint.fY + (m_tPoint.iCY >> 1);

	HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"MouseCursor");

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tPoint.iCX,
		m_tPoint.iCY,
		hMemDC,
		0, 0,
		m_tPoint.iCX, m_tPoint.iCY,
		RGB(173, 173, 173));
}

void CMyMouse::Release_MyMouse()
{
}

CMyMouse * CMyMouse::Create()
{
	CMyMouse* pInstance = new CMyMouse;
	if (0 > pInstance->Ready_MyMouse())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

CMyMouse * CMyMouse::Create(LPVOID pVoid)
{
	CMyMouse* pInstance = new CMyMouse;
	if (0 > pInstance->Ready_MyMouse())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

