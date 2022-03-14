#include "stdafx.h"
#include "Home.h"
#include "GameObject.h"
#include "GameObject_Manager.h"
#include "MyUI.h"
#include "UI_Manager.h"
#include "Player.h"

CHome::CHome()
{
}

CHome::~CHome()
{
}
void CHome::Update_Scene()
{
}
void CHome::Release_Scene()
{
}

CScene * CHome::Create()
{
	CScene* pInstance = new CHome;
	if (0 > pInstance->Ready_Scene())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

CScene * CHome::Create(LPVOID pVoid)
{
	CScene* pInstance = new CHome;
	if (0 > pInstance->Ready_Scene())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

int CHome::Ready_Scene()
{
	CGameObject* pObj = CPlayer::Create();
	CGameObject_Manager::Get_Instacne()->Add_Game_Object_Manager(pObj, GAMEOBJECT::UPDATE_ID::PLAYER);

	return READY_OK;
}

void CHome::Render_Scene(HDC hDC)
{
}
