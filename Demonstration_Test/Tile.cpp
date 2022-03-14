#include "stdafx.h"
#include "Tile.h"
#include "Scroll_Manager.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
#include "Key_Manager.h"
CTile::CTile()
	:m_iDrawXID(0),
	m_iDrawYID(0),
	m_iOption(0),
	m_eArea(PLAZA)
{
}

CTile::~CTile()
{
	Release_Tile();
}

int CTile::Ready_Tile()
{
	m_tPoint.iCX = TILECX;
	m_tPoint.iCY = TILECY;
	return READY_OK;
}

void CTile::Update_Tile()
{
}

void CTile::Render_Tile(HDC hDC)
{
	Update_Rect();
	//L"HomeTile");
	//, L"EarthTile");
	//, L"PlazaTile");
	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();
	if (HOME == m_eArea)
	{
		m_hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"HomeTile");
	}
	else if (PLAZA == m_eArea)
	{
		m_hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"PlazaTile");
	}
	else if (EARTHDUNGEON == m_eArea)
	{
		m_hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"EarthTile");
	}

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		m_tPoint.iCX, m_tPoint.iCY,
		m_hMemDC,
		m_iDrawXID*m_tPoint.iCX, m_iDrawYID*m_tPoint.iCY,
		m_tPoint.iCX, m_tPoint.iCY,
		RGB(255, 0, 255));

	TCHAR szTileOption[16];
	swprintf_s(szTileOption, L"%d", m_iOption);
	if (CKey_Manager::Get_EditKey()->Key_Pressing(KEY_C))
	{
		int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
		int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();
		SetTextColor(hDC, RGB(255, 0, 0));
		TextOut(hDC, m_tPoint.fX + iScrollX, m_tPoint.fY + iScrollY, szTileOption, lstrlen(szTileOption));
	}

}
	//HDC hMemDC=CBitmap_Manager::Get_Instance()->FindImage()

void CTile::Release_Tile()
{
}

void CTile::Update_Rect()
{
	m_tRect.left = m_tPoint.fX - (m_tPoint.iCX >> 1);
	m_tRect.top = m_tPoint.fY - (m_tPoint.iCY >> 1);
	m_tRect.right = m_tPoint.fX + (m_tPoint.iCX >> 1);
	m_tRect.bottom = m_tPoint.fY + (m_tPoint.iCY >> 1);
}

CTile * CTile::Create()
{
	CTile* pInstance = new CTile;
	if (0 > pInstance->Ready_Tile())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}
