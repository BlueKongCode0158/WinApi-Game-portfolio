#include "stdafx.h"
#include "Edit.h"
#include "Bitmap_Manager.h"
#include "MyMouse_Manager.h"
#include "Key_Manager.h"
#include "Scroll_Manager.h"
#include "Tile_Manager.h"
#include "GameObject_Manager.h"
#include "GameObject.h"
#include "Archer.h"
#include "Zombie.h"
#include "Collision_Manager.h"
#include "Collider.h"
#include "ProbCollider.h"
#include "Prob.h"
#include "IRon_Collider.h"
#include "Create_Collider.h"

CEdit::CEdit()
	:m_fScrollSpeed(0.f),
	m_bSetPalette(false),
	m_eArea(CTile::AREA::HOME),
	m_iIndexX(0),
	m_iIndexY(0),
	m_iPushNumV(0),
	m_iPushNumB(0),
	m_iOption(0),
	m_bSetOptionPalette(false),
	m_bCreateMonster(false),
	m_bCollisionSetting(false),
	m_bProbSetting(false)
{
}

CEdit::~CEdit()
{
}
CScene * CEdit::Create()
{
	CScene* pInstance = new CEdit;
	if (0 > pInstance->Ready_Scene())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

CScene * CEdit::Create(LPVOID pVoid)
{
	CScene* pInstance = new CEdit;
	if (0 > pInstance->Ready_Scene())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

void CEdit::ScrollMove()
{
	if (CKey_Manager::Get_EditKey()->Key_Pressing(KEY_W))
	{
		CScroll_Manager::Get_Instacne()->Set_ScrollY(m_fScrollSpeed);
		//끌어내려져야하므로 +
	}
	if (CKey_Manager::Get_EditKey()->Key_Pressing(KEY_A))
	{
		CScroll_Manager::Get_Instacne()->Set_ScrollX(m_fScrollSpeed);
		//스크롤은 오른쪽으로 와야하므로 +
	}
	if (CKey_Manager::Get_EditKey()->Key_Pressing(KEY_S))
	{
		CScroll_Manager::Get_Instacne()->Set_ScrollY(-m_fScrollSpeed);
		//플레이어가 아래로 가면 스크롤은 증가
	}
	if (CKey_Manager::Get_EditKey()->Key_Pressing(KEY_D))
	{
		CScroll_Manager::Get_Instacne()->Set_ScrollX(-m_fScrollSpeed);
	}

}

void CEdit::ViewKey()
{
	if (CKey_Manager::Get_EditKey()->Key_Down(KEY_V))
	{
		if (0 <= m_iPushNumV)
		{
			m_bSetPalette = true;
			m_iPushNumV += 1;
		}
		if (1 < m_iPushNumV)
		{
			m_bSetPalette = false;
			m_iPushNumV = 0;
		}
		m_bSetOptionPalette = false;
		m_bCollisionSetting = false;
		m_bCreateMonster = false;
		m_bProbSetting = false;
	}

	if (CKey_Manager::Get_EditKey()->Key_Down(KEY_B))
	{
		if (0 <= m_iPushNumB)
		{
			m_bSetOptionPalette = true;
			m_iPushNumB += 1;
		}
		if (1 < m_iPushNumB)
		{
			m_bSetOptionPalette = false;
			m_iPushNumB = 0 ;
		}
		m_bProbSetting = false;
		m_bCollisionSetting = false;
		m_bCreateMonster = false;
		m_bSetPalette = false;
	}

	if (CKey_Manager::Get_EditKey()->Key_Down(KEY_TAB))
	{
		if (0 <= m_iPushNumTap)
		{
			m_bCreateMonster = true;
			m_iPushNumTap += 1;
		}
		if (1 < m_iPushNumTap)
		{
			m_bCreateMonster = false;
			m_iPushNumTap = 0;
		}
		m_bSetOptionPalette = false;
		m_bCollisionSetting = false;
		m_bProbSetting = false;
		m_bSetPalette = false;
	}

	if (CKey_Manager::Get_EditKey()->Key_Down(KEY_Q))
	{
		if (0 <= m_iPushNumQ)
		{
			m_bCollisionSetting = true;
			m_iPushNumQ += 1;
		}
		if (1 < m_iPushNumQ)
		{
			m_bCollisionSetting = false;
			m_iPushNumQ = 0;
		}
		m_bProbSetting = false;
		m_bCreateMonster = false;
		m_bSetOptionPalette = false;
		m_bSetPalette = false;
	}
	if (CKey_Manager::Get_EditKey()->Key_Down(KEY_E))
	{
		if (0 <= m_iPushNumE)
		{
			m_bProbSetting = true;
			m_iPushNumE += 1;
		}
		if (1 < m_iPushNumE)
		{
			m_bProbSetting = false;
			m_iPushNumE = 0;
		}
		m_bCollisionSetting = false;
		m_bCreateMonster = false;
		m_bSetOptionPalette = false;
		m_bSetPalette = false;
	}
}

void CEdit::OptionKey()
{
}

void CEdit::Collider_Update()
{
	if (true == m_bCollisionSetting && false == m_bProbSetting && false == m_bSetOptionPalette && false == m_bSetPalette)
	{
		RECT tRECT{};

		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= CScroll_Manager::Get_Instacne()->Get_ScrollX();
		pt.y -= CScroll_Manager::Get_Instacne()->Get_ScrollY();


		if (CKey_Manager::Get_EditKey()->Key_Down(KEY_LBUTTON))
		{
			m_tCollsionRECT.left = pt.x;
			m_tCollsionRECT.top = pt.y;
		}
		if (CKey_Manager::Get_EditKey()->Key_Pressing(KEY_LBUTTON))
		{
			m_tCollsionRECT.right = pt.x;
			m_tCollsionRECT.bottom = pt.y;
		}
		if (CKey_Manager::Get_EditKey()->Key_Up(KEY_LBUTTON))
		{
			m_tCollsionRECT.right = pt.x;
			m_tCollsionRECT.bottom = pt.y;
			if (CCollider::COLLIDER::PROB == m_eCoiiderID)
			{
				CCollider* pCollider = CProbCollider::Create();
				pCollider->Set_Rect(m_tCollsionRECT);
				CCollision_Manager::Get_Instacne()->Add_Collider_Object(pCollider, CCollider::COLLIDER::CREATE_COLLIDER);
			}
			else if (CCollider::COLLIDER::IRON_BAR == m_eCoiiderID)
			{
				CCollider* pCollider = CIRon_Collider::Create();
				pCollider->Set_Rect(m_tCollsionRECT);
				CCollision_Manager::Get_Instacne()->Add_Collider_Object(pCollider, CCollider::COLLIDER::CREATE_COLLIDER);
			}
			else if (CCollider::COLLIDER::CREATE_COLLIDER == m_eCoiiderID)
			{
				CCollider* pCollider = CCreate_Collider::Create();
				pCollider->Set_Rect(m_tCollsionRECT);
				CCollision_Manager::Get_Instacne()->Add_Collider_Object(pCollider, CCollider::COLLIDER::CREATE_COLLIDER);
			}
		}
		if (CKey_Manager::Get_EditKey()->Key_Down(KEY_RBUTTON))
		{
			int iDistance = 30;

			tRECT.left = pt.x - iDistance;
			tRECT.top = pt.y - iDistance;
			tRECT.right = pt.x + iDistance;
			tRECT.bottom = pt.y + iDistance;


			CCollision_Manager::Get_Instacne()->Collider_Rect_Delete(tRECT);
		}
	}
}

void CEdit::Prob_Update()
{
	if (true == m_bProbSetting && false == m_bCollisionSetting && false == m_bCreateMonster && false == m_bSetOptionPalette && false == m_bSetPalette)
	{
		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= CScroll_Manager::Get_Instacne()->Get_ScrollX();
		pt.y -= CScroll_Manager::Get_Instacne()->Get_ScrollY();

		if (CKey_Manager::Get_EditKey()->Key_Down(KEY_1))
		{
			m_eProbID = CProb::PROBS::NOMAL;
		}
		if (CKey_Manager::Get_EditKey()->Key_Down(KEY_2))
		{
			m_eProbID = CProb::PROBS::IRON;
		}

		if (CKey_Manager::Get_EditKey()->Key_Down(KEY_RBUTTON))
		{
			m_fProbX = pt.x;
			m_fProbY = pt.y;
		}
		if (CKey_Manager::Get_EditKey()->Key_Up(KEY_RBUTTON))
		{
			TPOINT tPoint{};
			tPoint.fX = m_fProbX;
			tPoint.fY = m_fProbY;
			tPoint.iCX = abs(m_tProbRect.right - m_tProbRect.left);
			tPoint.iCY = abs(m_tProbRect.bottom - m_tProbRect.top);
			CGameObject* pObj = CProb::Create();
			pObj->Set_tPoint(tPoint);
			pObj->Set_tSize(tPoint);
			dynamic_cast<CProb*>(pObj)->Set_Prob_ID(m_eProbID);
			dynamic_cast<CProb*>(pObj)->Set_ImageRect(m_tProbRect);
			CGameObject_Manager::Get_Instacne()->Add_Game_Object_Manager(pObj, GAMEOBJECT::UPDATE_ID::Prob);
		}

		if (CKey_Manager::Get_EditKey()->Key_Down(KEY_ESC))
		{
			RECT tRECT{};

			int iDistance = 30;

			tRECT.left = pt.x - iDistance;
			tRECT.top = pt.y - iDistance;
			tRECT.right = pt.x + iDistance;
			tRECT.bottom = pt.y + iDistance;

			CGameObject_Manager::Get_Instacne()->Collision_Rect_Delete_PRob(tRECT);
		}
	
	}
}

void CEdit::SaveButton_Update()
{
	if (CKey_Manager::Get_EditKey()->Key_Down(KEY_O))
	{
		CGameObject_Manager::Get_Instacne()->Save_Data_Monster();
		CGameObject_Manager::Get_Instacne()->Save_Data_Prob();
		CCollision_Manager::Get_Instacne()->Save_Collider_Data();
		CTile_Manager::Get_Instance()->Save_Data_Tile_Manager();
	}
	if (CKey_Manager::Get_EditKey()->Key_Down(KEY_L))
	{
		CGameObject_Manager::Get_Instacne()->Load_Data_Monster();
		CGameObject_Manager::Get_Instacne()->Load_Data_Prob();
		CCollision_Manager::Get_Instacne()->Load_Collider_Data();
		CTile_Manager::Get_Instance()->Load_Data_Tile_Manager();
	}

}

void CEdit::Monster_Update()
{
	if (m_bCreateMonster == true && false == m_bCollisionSetting && false == m_bProbSetting && false == m_bSetOptionPalette && false == m_bSetPalette)
	{
		if (CKey_Manager::Get_EditKey()->Key_Down(KEY_LBUTTON))
		{
			POINT pt{};
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd, &pt);
			pt.x -= CScroll_Manager::Get_Instacne()->Get_ScrollX();	// 값은 계속 증가하겠네.
			pt.y -= CScroll_Manager::Get_Instacne()->Get_ScrollY();

			TFPOINT tfPoint{};
			tfPoint.fX = pt.x;
			tfPoint.fY = pt.y;
			// 해당 좌표에 넣어줄 것이므로,
			if (CGameObject::MONSTER_ID::ARCHER == m_eID)
			{
				CGameObject* pObj = CArcher::Create();
				pObj->Set_tPoint(tfPoint);
				CGameObject_Manager::Get_Instacne()->Add_Game_Object_Manager(pObj, GAMEOBJECT::UPDATE_ID::MONSTER);
			}
			else if (CGameObject::MONSTER_ID::MAGIC == m_eID)
			{
			}
			else if (CGameObject::MONSTER_ID::SLIME == m_eID)
			{

			}
			else if (CGameObject::MONSTER_ID::ZOMBIE == m_eID)
			{
				CGameObject* pObj = CZombie::Create();
				pObj->Set_tPoint(tfPoint);
				CGameObject_Manager::Get_Instacne()->Add_Game_Object_Manager(pObj, GAMEOBJECT::UPDATE_ID::MONSTER);
			}
			else
			{

			}
		}
		if (CKey_Manager::Get_EditKey()->Key_Up(KEY_RBUTTON))
		{
			RECT tRECT{};

			POINT pt{};
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd, &pt);

			pt.x -= CScroll_Manager::Get_Instacne()->Get_ScrollX();
			pt.y -= CScroll_Manager::Get_Instacne()->Get_ScrollY();

			int iDistance = 30;

			tRECT.left = pt.x - iDistance;
			tRECT.top = pt.y - iDistance;
			tRECT.right = pt.x + iDistance;
			tRECT.bottom = pt.y + iDistance;

			CGameObject_Manager::Get_Instacne()->Collision_Rect_Delete(tRECT);
			//몬스터만 지워지는 역할을 한다.
		}
	}
}

void CEdit::Prob_Object()
{
}

void CEdit::Collision_Object()
{
}

int CEdit::Ready_Scene()
{
	CTile_Manager::Get_Instance()->Ready_Tile_Manager();
	m_fScrollSpeed = 5.f;
	m_eProbID = CProb::PROBS::NOMAL;
	CTile_Manager::Get_Instance()->Load_Data_Tile_Manager();
	CCollision_Manager::Get_Instacne()->Load_Collider_Data();
	CGameObject_Manager::Get_Instacne()->Load_Data_Monster();
	CGameObject_Manager::Get_Instacne()->Load_Data_Prob();
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Num.bmp", L"OptionNum");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Monster_Pallete.bmp", L"MonsterP");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/ColliderSelect.bmp", L"Collider");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Map_Tile/OldTile/SmallProps.bmp", L"Prob");
	return READY_OK;
}


void CEdit::Tile_Palette(HDC hDC)
{
	if (true == m_bSetPalette)
	{
		if (CKey_Manager::Get_EditKey()->Key_Down(KEY_DOWN))
		{
			if (CTile::AREA::HOME == m_eArea)
			{
				m_eArea = CTile::AREA::PLAZA;
			}
			else if (CTile::AREA::PLAZA == m_eArea)
			{
				m_eArea = CTile::AREA::EARTHDUNGEON;
			}
			else if (CTile::AREA::EARTHDUNGEON == m_eArea)
			{
				m_eArea = CTile::AREA::HOME;
			}
		}
		int iImageSizeX = 0;
		int iImageSizeY = 0;

		//L"HomeTile");
		//, L"EarthTile");
		//, L"PlazaTile");
		if (CTile::AREA::HOME == m_eArea)
		{
			m_hDC = CBitmap_Manager::Get_Instance()->FindImage(L"HomeTile");
			iImageSizeX = 320;
			iImageSizeY = 320;
		}
		else if (CTile::AREA::PLAZA == m_eArea)
		{
			m_hDC = CBitmap_Manager::Get_Instance()->FindImage(L"PlazaTile");
			iImageSizeX = 384;
			iImageSizeY = 320;
		}
		else if (CTile::AREA::EARTHDUNGEON == m_eArea)
		{
			m_hDC = CBitmap_Manager::Get_Instance()->FindImage(L"EarthTile");
			iImageSizeX = 768;
			iImageSizeY = 384;
		}
		Rectangle(hDC, 0, 0, iImageSizeX, iImageSizeY);

		GdiTransparentBlt(hDC,
			0, 0,
			iImageSizeX, iImageSizeY,
			m_hDC,
			0, 0,
			iImageSizeX, iImageSizeY,
			RGB(255, 0, 255)
		);

		for (int i = 0; i <= (iImageSizeY / TILECY); i++)	//계속 조건식에서 넋 놓는다. 정신줄 잡기! // 아닌가 여기가 문제인가?..
		{
			MoveToEx(hDC, 0, i*TILECY, NULL);
			LineTo(hDC, iImageSizeX, i*TILECY);
		}

		//가로줄을 그림.
		for (int i = 0; i <= (iImageSizeX / TILECX); i++)	//여기서 문제가 있는건데 말이지.	// 줄무늬 고쳤다 희희
		{

			MoveToEx(hDC, i*TILECX, 0, NULL);
			LineTo(hDC, i*TILECX, iImageSizeY);
		}

		POINT pt{};
		RECT Palette_Rect{};
		Palette_Rect.left = 0;
		Palette_Rect.top = 0;
		Palette_Rect.right = iImageSizeX;
		Palette_Rect.bottom = iImageSizeY;

		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		int iIndexX = pt.x / TILECX;
		int iIndexY = pt.y / TILECY;

		if (PtInRect(&Palette_Rect, pt))
		{
			if (CKey_Manager::Get_EditKey()->Key_Down(KEY_LBUTTON))	
			{
				m_iIndexX = iIndexX;
				m_iIndexY = iIndexY;
			}
		}
		//이거 마우스 인자 받는 걸로 함수 만들어도 될 정도로 많이 쓰는디

	}
}
void CEdit::Tile_Option_Palette(HDC hDC)
{
	if (true == m_bSetOptionPalette)
	{
		RECT tRect{};

		tRect.left = 0;
		tRect.top = 0;
		tRect.right = (TILECX * 4);
		tRect.bottom = TILECY;

		//Rectangle(hDC, tRect.left, tRect.top, tRect.right, tRect.bottom);
		HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"OptionNum");


		BitBlt(hDC, 0, 0, 128, 32, hMemDC, 0, 0, SRCCOPY);

		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		int iIndexX = pt.x / TILECX;
		int iIndexY = pt.y / TILECY;

		if (PtInRect(&tRect, pt)) //이거 그냥 렉트 충돌로 하는게 낫지 않나
		{
			if (CKey_Manager::Get_EditKey()->Key_Down(KEY_LBUTTON))
			{
				if (0 == iIndexX)
				{
					m_iOption = 0;
				}
				else if (1 == iIndexX)
				{
					m_iOption = 1;
				}
				else if (2 == iIndexX)
				{
					m_iOption = 2;
				}
				else if (3 == iIndexX)
				{
					m_iOption = 3;
				}

			}
		}

	}
}
void CEdit::Monster_Palette(HDC hDC)
{
	if (m_bCreateMonster == true )
	{

		HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"MonsterP");

		RECT tRect{};

		tRect.left = 0;
		tRect.top = 0;
		tRect.right = (96 * 4);
		tRect.bottom = 96;

		BitBlt(hDC, 0, 0, 384, 96, hMemDC, 0, 0, SRCCOPY);

		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		int iIndexX = pt.x / 96;
		int iIndexY = pt.y / 96;

		if (PtInRect(&tRect, pt))
		{
			if (CKey_Manager::Get_EditKey()->Key_Down(KEY_RBUTTON))
			{
				if (0 == iIndexX)
				{
					m_eID = CGameObject::MONSTER_ID::ARCHER;
				}
				else if (1 == iIndexX)
				{
					m_eID = CGameObject::MONSTER_ID::MAGIC;
				}
				else if (2 == iIndexX)
				{
					m_eID = CGameObject::MONSTER_ID::SLIME;
				}
				else if (3 == iIndexX)
				{
					m_eID =CGameObject::MONSTER_ID::ZOMBIE;
				}
			}
		}

	}
}
void CEdit::Collision_Palette(HDC hDC)
{
	if (true == m_bCollisionSetting && false == m_bProbSetting && false == m_bSetOptionPalette && false == m_bSetPalette && false == m_bCreateMonster)
	{
		RECT tRECT{};

		tRECT.right = 32 * 5;
		tRECT.bottom = 32;
		HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"Collider");

		//Rectangle(hDC, tRECT.left, tRECT.top, tRECT.right, tRECT.bottom);
		BitBlt(hDC, 0, 0, 160, 32, hMemDC,0, 0, SRCCOPY);

		//rect로 바꾸는게 더 정신건강에 좋을 것 같기도 하다..

		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		int iIndexX =abs( pt.x / 32 );
		int iindexY = abs(pt.y / 32);
		
		if (PtInRect(&tRECT, pt))
		{
			if (0 == iIndexX && 0 == iindexY)
			{
				m_eCoiiderID = CCollider::COLLIDER::PROB;
			}
			else if (1 == iIndexX && 0 == iindexY)
			{
				m_eCoiiderID = CCollider::COLLIDER::IRON_BAR;
			}
			else if (2 == iIndexX && 0 == iindexY)
			{
				m_eCoiiderID = CCollider::COLLIDER::CREATE_COLLIDER;
			}
		}

	}
}
void CEdit::Prob_Palette(HDC hDC)
{
	if (true == m_bProbSetting && false == m_bCollisionSetting && false == m_bCreateMonster && false == m_bSetOptionPalette && false == m_bSetPalette)
	{
		RECT tRECT{};

		//스크롤 기능
		float fSpeed = 5.f;
		if (CKey_Manager::Get_EditKey()->Key_Pressing(KEY_DOWN))
		{
			CScroll_Manager::Get_ProbScroll()->Set_ScrollY(-fSpeed);
		}
		if (CKey_Manager::Get_EditKey()->Key_Pressing(KEY_UP))
		{
			CScroll_Manager::Get_ProbScroll()->Set_ScrollY(fSpeed);
		}
		if (CKey_Manager::Get_EditKey()->Key_Pressing(KEY_LEFT))
		{
			CScroll_Manager::Get_ProbScroll()->Set_ScrollX(fSpeed);
		}
		if (CKey_Manager::Get_EditKey()->Key_Pressing(KEY_RIGHT))
		{
			CScroll_Manager::Get_ProbScroll()->Set_ScrollX(-fSpeed);
		}


		int iScrollX = CScroll_Manager::Get_ProbScroll()->Get_ScrollX();
		int iScrollY = CScroll_Manager::Get_ProbScroll()->Get_ScrollY();


		HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"Prob");

		Rectangle(hDC, 0, 0, 512, WINCY);
		BitBlt
		(hDC,
			0, 0, 512, WINCY,
			hMemDC,
			-iScrollX, -iScrollY, SRCCOPY);

		//포인트 좌표값 저장 //이거 함수로 만들어두면 편할 것 같긴하다..
		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		pt.x -= iScrollX;
		pt.y -= iScrollY;

		if (CKey_Manager::Get_EditKey()->Key_Down(KEY_LBUTTON))
		{
			m_tProbRect.left = pt.x;
			m_tProbRect.top = pt.y;
		}
		if (CKey_Manager::Get_EditKey()->Key_Pressing(KEY_LBUTTON))
		{
			m_tProbRect.right = pt.x;
			m_tProbRect.bottom = pt.y;
		}
		if (CKey_Manager::Get_EditKey()->Key_Up(KEY_LBUTTON))
		{
			m_tProbRect.right = pt.x;
			m_tProbRect.bottom = pt.y;
		}
		//GdiTransparentBlt
		//(hDC,
		//	0 , 0 , 512, WINCY,
		//	hMemDC,
		//	-iScrollX,-iScrollY,
		//	512 - iScrollX, WINCY - iScrollY, RGB(255, 0, 255));
		//GdiTransparentBlt
		//(hDC, 0 + iScrollX, 0 + iScrollY, 512 + iScrollX, WINCY + iScrollY,
		//	hMemDC,
		//	0/*iScrollX*/, 0/*iScrollX*/,
		//	512/*512 + iScrollX*/, WINCY/*WINCY + iScrollY*/, RGB(255,0,255));
		//이걸로 늘리기 가능하네..

		HBRUSH myBrush = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
		HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(hDC, myBrush));
		HPEN myPen = static_cast<HPEN>(CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
		HPEN oldPen = static_cast<HPEN>(SelectObject(hDC, myPen));

		Rectangle(hDC, m_tProbRect.left + iScrollX, m_tProbRect.top + iScrollY, m_tProbRect.right + iScrollX, m_tProbRect.bottom + iScrollY);

		SelectObject(hDC, oldBrush);
		SelectObject(hDC, oldPen);
		DeleteObject(myBrush);
		DeleteObject(myPen);
	}
}
void CEdit::Tile_Option_Setting()
{
	POINT pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

	pt.x -= iScrollX;
	pt.y -= iScrollY;
	if (CKey_Manager::Get_EditKey()->Key_Down(KEY_RBUTTON))
	{
		m_tRect.left = pt.x;
		m_tRect.top = pt.y;
	}
	if (CKey_Manager::Get_EditKey()->Key_Pressing(KEY_RBUTTON))
	{
		m_tRect.right = pt.x;
		m_tRect.bottom = pt.y;
	}
	if (CKey_Manager::Get_EditKey()->Key_Up(KEY_RBUTTON))
	{
		m_tRect.right = pt.x;
		m_tRect.bottom = pt.y;
		CTile_Manager::Get_Instance()->Picking_Tile_Option_Manager(m_tRect, m_iOption);

		ZeroMemory(&m_tRect, sizeof(RECT));
	}

	//CTile_Manager::Get_Instance()->Picking_Tile_Option_Manager(m_tRect, m_iOption);	//주의, 이미 스크롤값이 먹여져있다는 걸 명심.
	//예측 - > 계속 초기화 되면서 값을 기억 못하고 있음.
	//예측이 정답이었읍니다.

}
// 여기서 안에서 충돌처리 다 해줘야 오류 안 나겠다. [ 잊을까봐 적어놓음 ]
//  아닐수도 있는데 우선 불안하니까 써줄까!
//  디버깅 연습 베스트

void CEdit::Update_Scene()
{
	CKey_Manager::Get_EditKey()->Key_Update();

	ViewKey();
	ScrollMove();

	//정신놔서 들어가는 인자도 까먹니 빡대가리야.
	// 조건자때문에 오류나는 거 였음.
	if (false == m_bSetPalette && false ==m_bSetOptionPalette && false ==m_bCreateMonster && false == m_bCollisionSetting && false == m_bProbSetting)
	{
		if (CKey_Manager::Get_EditKey()->Key_Down(KEY_LBUTTON) || CKey_Manager::Get_EditKey()->Key_Pressing(KEY_LBUTTON))
		{
			POINT pt{};
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd, &pt);
			pt.x -= CScroll_Manager::Get_Instacne()->Get_ScrollX();
			pt.y -= CScroll_Manager::Get_Instacne()->Get_ScrollY();
			// 해당 좌표에 넣어줄 것이므로,
			CTile_Manager::Get_Instance()->Picking_Tile_Manager(pt, m_iIndexX, m_iIndexY, m_eArea);
		}
	}
	Monster_Update();
	Collider_Update();
	Prob_Update();
	CMyMouse_Manager::Get_Instance()->Update_MyMouse_Manager();

	SaveButton_Update();
	if (false == m_bSetPalette && false == m_bSetOptionPalette && false == m_bCreateMonster && false == m_bCollisionSetting && false == m_bProbSetting)
	{
		Tile_Option_Setting();
	}
}
void CEdit::Release_Scene()
{
}


void CEdit::Render_Scene(HDC hDC)
{

	CTile_Manager::Get_Instance()->Render_Tile_Manager(hDC);
	CCollision_Manager::Get_Instacne()->Render_Collider(hDC);
	CGameObject_Manager::Get_Instacne()->Render_GameObject_Manager(hDC);
	//순서 중요

	//HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"BackGround");
	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

	if (CKey_Manager::Get_EditKey()->Key_Pressing(KEY_C))
	{
		for (int i = 0; i <= TILEX; i++)	//계속 조건식에서 넋 놓는다. 정신줄 잡기!
		{
			MoveToEx(hDC, 0 + iScrollX, i*TILECY + iScrollY, NULL);
			LineTo(hDC, TILEX*TILECX + iScrollX, i*TILECY + iScrollY);
		}
		//가로줄을 그림.
		for (int i = 0; i <= TILEY; i++)
		{

			MoveToEx(hDC, i*TILECX + iScrollX, 0 + iScrollY, NULL);
			LineTo(hDC, i*TILECX + iScrollX, TILEY*TILECY + iScrollY);
		}
	}
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	Tile_Palette(hDC);
	Tile_Option_Palette(hDC);
	Monster_Palette(hDC);
	Collision_Palette(hDC);
	Prob_Palette(hDC);
	if (true == m_bCollisionSetting)
	{
		CCollision_Manager::Get_Instacne()->Render_Collider(hDC);
	}
	//크기에 딱 맞게 생성되네.
	//새로줄을 그림.
	//직선이 그어지면서 OK
	CMyMouse_Manager::Get_Instance()->Render_MyMouse_Manager(hDC);
}
