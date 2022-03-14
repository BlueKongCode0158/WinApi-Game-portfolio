#include "stdafx.h"
#include "Prob.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
#include "GameObject.h"
#include "GameObject_Manager.h"
#include "Key_Manager.h"

CProb::CProb()
{
}

CProb::~CProb()
{
}

int CProb::Ready_GameObject()
{
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Map_Tile/OldTile/SmallProps.bmp", L"SmallProps");
	m_eProbID = CProb::PROBS::NOMAL;
	m_bCollision = false;
	return READY_OK;
}

int CProb::Update_GameObject()
{
	CGameObject::Update_Rect();

	if (true == m_bDead)
	{
		return OBJ_DEAD;
	}
	if (CProb::NOMAL == m_eProbID)
	{

	}
	else if (CProb::PROBS::IRON == m_eProbID && true == m_bCollision)
	{
		CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
		RECT* pRect = pObj->Get_RECT();

		if (nullptr == pObj)
		{
			return OBJ_NOEVENT;
		}

		//bool bWall = pObj->Get_Wall();


		RECT tRECT{};
		if (IntersectRect(&tRECT, &m_tRect, pRect))
		{
			if (pRect->right >= m_tRect.left && pRect->left <= m_tRect.left)
			{
				pObj->Set_Wall();

				if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_A))
				{
					pObj->Set_Wall(false);
				}

			}
			else if (pRect->left <= m_tRect.right && pRect->right >= m_tRect.right)
			{
				pObj->Set_Wall();
				if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_D))
				{
					pObj->Set_Wall(false);
				}
			}
			else if (pRect->bottom >= m_tRect.top && pRect->top <= m_tRect.top)
			{
				pObj->Set_Wall();
				if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_W))
				{
					pObj->Set_Wall(false);
				}

			}
			else if (pRect->top <= m_tRect.bottom && pRect->bottom >= m_tRect.bottom)
			{
				pObj->Set_Wall();
				if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_S))
				{
					pObj->Set_Wall(false);
				}
			}

		}
	}

	return OBJ_NOEVENT;
}

void CProb::Late_GamceObject()
{
}

void CProb::Render_GameObject(HDC hDC)
{
	CGameObject::Update_Rect();
	if (CProb::PROBS::NOMAL == m_eProbID)
	{

		int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
		int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

		HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"SmallProps");

		TCHAR szID[32]{};

		//swprintf_s(szID, L"ID : %d", m_eProbID);
		//TextOut(hDC, m_tPoint.fX + iScrollX, m_tPoint.fY + iScrollY, szID, lstrlen(szID));

		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX, m_tRect.top + iScrollY,
			m_tPoint.iCX, m_tPoint.iCY,
			hMemDC,
			m_tImageRect.left, m_tImageRect.top,
			m_tPoint.iCX, m_tPoint.iCY,
			RGB(255, 0, 255));
	}
	else if (CProb::PROBS::IRON == m_eProbID)
	{
		if (true == m_bCollision || CKey_Manager::Get_EditKey()->Key_Pressing(KEY_3))
		{
			CGameObject::Update_Rect();

			int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
			int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

			HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"SmallProps");

			TCHAR szID[32]{};

			//swprintf_s(szID, L"ID : %d", m_eProbID);
			//TextOut(hDC, m_tPoint.fX + iScrollX, m_tPoint.fY + iScrollY, szID, lstrlen(szID));

			GdiTransparentBlt(hDC,
				m_tRect.left + iScrollX, m_tRect.top + iScrollY,
				m_tPoint.iCX, m_tPoint.iCY,
				hMemDC,
				m_tImageRect.left, m_tImageRect.top,
				m_tPoint.iCX, m_tPoint.iCY,
				RGB(255, 0, 255));
		}
	}
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CProb::Release_GameObject()
{
}

CGameObject * CProb::Create()
{
	CGameObject* pInstacne = new CProb;
	if (0 > pInstacne->Ready_GameObject())
	{
		Safe_Delete(pInstacne);
	}
	return pInstacne;
}
