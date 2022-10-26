#include "stdafx.h"
#include "MainGame.h"
#include "Key_Manager.h"
#include "GameObject_Manager.h"
#include "Bitmap_Manager.h"
#include "Scene_Manager.h"
#include "MyMouse_Manager.h"
#include "Tile_Manager.h"
#include "Scroll_Manager.h"
#include "Collision_Manager.h"
#include "Skil_Manager.h"
#include "UI_Manager.h"
#include "Effect_Manager.h"
#include "Font_Damage_Manager.h"
#include "SoundMgr.h"

CMainGame::CMainGame()
	:m_FpsTime(0),
	m_dwGetick(0)
{
}

CMainGame::~CMainGame()
{
	Release_MainGame();
}

int CMainGame::Ready_MainGame()
{
	m_hDC = GetDC(g_hWnd);
	m_dwGetick = GetTickCount();

	AddFontResourceA("../font/Font/8bitWonder.ttf");
	AddFontResourceA("../font/Font/Exo2-Bold.ttf");

	CSoundMgr::Get_Instance()->Initialize();

	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Background/Background1.bmp", L"DubleBuffer");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Map_Tile/HomeTile1.bmp", L"HomeTile");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Map_Tile/EarthTile1.bmp", L"EarthTile");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Map_Tile/PlazaTile1.bmp", L"PlazaTile");

	CScene_Manager::Get_Instance()->Scene_Change(CScene_Manager::SCENE_START);


	return READY_OK;
}

void CMainGame::Update_MainGame()
{
	CScene_Manager::Get_Instance()->Update_Scene_Manager();
	CScroll_Manager::Get_Instacne()->Scroll_Lock();
}

void CMainGame::Render_MainGame()
{
	POINT pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

	float MousefX = pt.x - iScrollX;
	float MousefY = pt.y - iScrollY;
	HDC hDubbleBuffer = CBitmap_Manager::Get_Instance()->FindImage(L"DubleBuffer");
	Rectangle(hDubbleBuffer, 0, 0, WINCX, WINCY);
	CScene_Manager::Get_Instance()->Render_Scene_Manager(hDubbleBuffer);

	TCHAR m_szPointX[32]{};


	SetTextColor(hDubbleBuffer, RGB(173, 173, 173));
	TextOut(hDubbleBuffer, 100, 100, m_szFps, lstrlen(m_szFps));

	swprintf_s(m_szPointX, L"X : %.1f Y: %.1f", MousefX, MousefY);
	TextOut(hDubbleBuffer, WINCX - 100, 100, m_szPointX,lstrlen(m_szPointX));

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hDubbleBuffer, 0, 0, SRCCOPY);
}


void CMainGame::Release_MainGame()
{
	ReleaseDC(g_hWnd, m_hDC);
	RemoveFontResourceA("../font/Font/8bitWonder.ttf");
	RemoveFontResourceA("../font/Font/Exo2-Bold.ttf");
	CSoundMgr::Destroy_Instance();
	CTile_Manager::Get_Instance()->Release_Instance();
	CBitmap_Manager::Get_Instance()->Release_Bitmap();
	CScene_Manager::Get_Instance()->Release_Instance();
	CMyMouse_Manager::Get_Instance()->Release_Instance();
	CScroll_Manager::Get_Instacne()->Release_Instance();
	CScroll_Manager::Get_Instacne()->Release_ProbScroll();
	CKey_Manager::Get_EditKey()->Release_Instance();
	CKey_Manager::Get_PlayerKey()->Release_Instance();
	CKey_Manager::Get_StartKey()->Release_Instance();
	CGameObject_Manager::Get_Instacne()->Release_Instance();
	CSkil_Manager::Get_Instacne()->Release_Instance();
	CCollision_Manager::Get_Instacne()->Release_Instacne();
	CUI_Manager::Get_Instance()->Release_UI_Manager();
	CEffect_Manager::Get_Instance()->Release_Instance();
	CFont_Damage_Manager::Get_Instance()->Release_Damage_Manager();
}
