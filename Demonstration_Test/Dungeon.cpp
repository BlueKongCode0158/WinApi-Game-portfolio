#include "stdafx.h"
#include "Dungeon.h"
#include "GameObject.h"
#include "GameObject_Manager.h"
#include "UI_Manager.h"
#include "Bitmap_Manager.h"
#include "Player.h"
#include "MyMouse.h"
#include "MyMouse_Manager.h"
#include "Tile_Manager.h"
#include "Tile.h"
#include "Key_Manager.h"
#include "Scene_Manager.h"
#include "Skil_Manager.h"
#include "UI_Manager.h"
#include "Archer.h"
#include "Collision_Manager.h"
#include "Effect_Manager.h"
#include "Font_Damage_Manager.h"
#include "BossBackGround.h"
#include "BossHp_Bar.h"
#include "Hp_Bar.h"
#include "HpBackGround.h"
#include "PlayerImage.h"
#include "Mp_Bar.h"
#include "Zombie.h"
#include "EarthBoss.h"
#include "SoundMgr.h"

CDungeon::CDungeon()
{
}

CDungeon::~CDungeon()
{
	Release_Scene();
}
void CDungeon::Release_Scene()
{
	CUI_Manager::Get_Instance()->Release_UI_Manager();
}

int CDungeon::Ready_Scene()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"Earth.wav");
	CGameObject* pObj = CPlayer::Create();
	CGameObject_Manager::Get_Instacne()->Add_Game_Object_Manager(pObj, GAMEOBJECT::UPDATE_ID::PLAYER);
	pObj = CArcher::Create();
	CGameObject_Manager::Get_Instacne()->Add_Game_Object_Manager(pObj, GAMEOBJECT::UPDATE_ID::MONSTER);

	pObj = CZombie::Create();
	CGameObject_Manager::Get_Instacne()->Add_Game_Object_Manager(pObj, GAMEOBJECT::UPDATE_ID::MONSTER);

	CGameObject_Manager::Get_Instacne()->Load_Data_Monster();
	CGameObject_Manager::Get_Instacne()->Load_Data_Prob();

	pObj = CEarthBoss::Create();
	CGameObject_Manager::Get_Instacne()->Add_Game_Object_Manager(pObj, GAMEOBJECT::UPDATE_ID::BOSS);

	CTile_Manager::Get_Instance()->Ready_Tile_Manager();
	CTile_Manager::Get_Instance()->Load_Data_Tile_Manager();

	CCollision_Manager::Get_Instacne()->Load_Collider_Data();

	CMyUI* pUIObj = CHp_Bar::Create();
	CUI_Manager::Get_Instance()->Add_UI_Object(pUIObj, UI_OBJECT::GAME_ID::HP);

	pUIObj = CHpBackGround::Create();
	CUI_Manager::Get_Instance()->Add_UI_Object(pUIObj, UI_OBJECT::GAME_ID::BACKGROUND);

	pUIObj = CPlayerImage::Create();
	CUI_Manager::Get_Instance()->Add_UI_Object(pUIObj, UI_OBJECT::GAME_ID::PLAYERHEAD);

	pUIObj = CMp_Bar::Create();
	CUI_Manager::Get_Instance()->Add_UI_Object(pUIObj, UI_OBJECT::GAME_ID::MP);
	return READY_OK;
}

void CDungeon::Update_Scene()
{
	
	
	CGameObject_Manager::Get_Instacne()->Update_GameObject_Manager();
	CCollision_Manager::Get_Instacne()->Update_Collider();
	CMyMouse_Manager::Get_Instance()->Update_MyMouse_Manager();

	CEffect_Manager::Get_Instance()->Update_Effect_Manager();
	CFont_Damage_Manager::Get_Instance()->Update_Font_Damage_Manager();
	CUI_Manager::Get_Instance()->Update_UI_Manager();

	if (nullptr == CGameObject_Manager::Get_Instacne()->Get_Player())
	{
		//죽었을 때 조치.
		CKey_Manager::Get_StartKey()->Key_Update();
		if (CKey_Manager::Get_StartKey()->Key_Down(KEY_O))
		{
			CGameObject* pObj = CPlayer::Create();
			CGameObject_Manager::Get_Instacne()->Add_Game_Object_Manager(pObj, GAMEOBJECT::UPDATE_ID::PLAYER);
		}
	}
}

void CDungeon::Render_Scene(HDC hDC)
{
	HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"BackGround");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	CTile_Manager::Get_Instance()->Render_Tile_Manager(hDC);
	CGameObject_Manager::Get_Instacne()->Render_GameObject_Manager(hDC);

	CEffect_Manager::Get_Instance()->Render_Effect_Manager(hDC);
	CFont_Damage_Manager::Get_Instance()->Render_Font_Damage_Manager(hDC);

	CUI_Manager::Get_Instance()->Render_UI_Manager(hDC);
	CMyMouse_Manager::Get_Instance()->Render_MyMouse_Manager(hDC);

}


CScene * CDungeon::Create()
{
	CScene* pInstacne = new CDungeon;
	if (0 > pInstacne->Ready_Scene())
	{
		Safe_Delete(pInstacne);
	}
	return pInstacne;
}

CScene * CDungeon::Create(LPVOID pVoid)
{
	CScene* pInstacne = new CDungeon;
	if (0 > pInstacne->Ready_Scene())
	{
		Safe_Delete(pInstacne);
	}
	return pInstacne;
}
