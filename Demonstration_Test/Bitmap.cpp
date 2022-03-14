#include "stdafx.h"
#include "Bitmap.h"

CBitmap::CBitmap()
{
}

CBitmap::~CBitmap()
{
	Release_Bitmap();
}

void CBitmap::Insert_Bitmap(const TCHAR * pFilePath)
{
	HDC hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC); //동일한 화면이 필요.

	ReleaseDC(g_hWnd, hDC);
	m_hBitmap = static_cast<HBITMAP>(LoadImage(NULL, pFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
	m_hOldBitmap = static_cast<HBITMAP>(SelectObject(m_hMemDC, m_hBitmap));
}

void CBitmap::Release_Bitmap()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
