#include "stdafx.h"
#include "Start.h"
#include "Bitmap_Manager.h"
#include "Key_Manager.h"
#include "MyMouse_Manager.h"
#include "UI_Manager.h"
#include "MyUI.h"
#include "Title.h"
#include "Text.h"
#include "MyButton.h"
#include "SoundMgr.h"
CStart::CStart()
{
}

CStart::~CStart()
{
	Release_Scene();
}

int CStart::Ready_Scene()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"TitleScreen.wav");
	CMyUI* pUIObj = CTitle::Create();
	CUI_Manager::Get_Instance()->Add_UI_Object(pUIObj, UI_OBJECT::START_ID::TITLE);
	pUIObj = CText::Create();
	CUI_Manager::Get_Instance()->Add_UI_Object(pUIObj, UI_OBJECT::START_ID::TEXT);

	pUIObj = CMyButton::Create(L"Start");
	pUIObj->SetPos(WINCX >> 1, 300.f);
	CUI_Manager::Get_Instance()->Add_UI_Object(pUIObj, UI_OBJECT::START_ID::BUTTON);

	pUIObj = CMyButton::Create(L"Edit");
	pUIObj->SetPos(WINCX >> 1, 400.f);
	CUI_Manager::Get_Instance()->Add_UI_Object(pUIObj, UI_OBJECT::START_ID::BUTTON);

	pUIObj = CMyButton::Create(L"Exit");
	pUIObj->SetPos(WINCX>>1, 500.f);
	CUI_Manager::Get_Instance()->Add_UI_Object(pUIObj, UI_OBJECT::START_ID::BUTTON);


	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Background/Background9.bmp", L"Start_Background");
	CMyMouse_Manager::Get_Instance()->Ready_MyMouse_Manager();
	// 마우스는 계속 쓸거기때문에 안 지움.
	return READY_OK;
}

void CStart::Update_Scene()
{

	CKey_Manager::Get_StartKey()->Key_Update();
	CMyMouse_Manager::Get_Instance()->Update_MyMouse_Manager();


	CUI_Manager::Get_Instance()->Update_UI_LOAD_Manager();	//여기서 터진다는 소리구요.


	if (CKey_Manager::Get_StartKey()->Key_Down(KEY_LBUTTON))
	{
		bMyStartID = true;
	}
	else if (CKey_Manager::Get_StartKey()->Key_Down(KEY_ESC))
	{
		bMyStartID = false;
	}

}

void CStart::Render_Scene(HDC hDC)
{
	HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"Start_Background");
	if (nullptr == hMemDC)
	{
		return;
	}

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	CUI_Manager::Get_Instance()->Render_UI_LOAD_Manager(hDC);
	CMyMouse_Manager::Get_Instance()->Render_MyMouse_Manager(hDC);
}

void CStart::Release_Scene()
{
	//CUI_Manager::Get_Instance()->Delete_UI(UI_OBJECT::TEXT);
	//CUI_Manager::Get_Instance()->Delete_UI(UI_OBJECT::TITLE);
	CUI_Manager::Get_Instance()->Release_UI_Manager();
	// 하지만 시작 UI는 계속 쓸 일 없으니 지울거임.
}

CScene * CStart::Create()
{
	CScene* pInstance = new CStart;
	if (0 > pInstance->Ready_Scene())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

CScene * CStart::Create(LPVOID pVoid)
{
	CScene* pInstance = new CStart;
	if (0 > pInstance->Ready_Scene())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}
