#include "stdafx.h"
#include "Scene.h"
#include "Scene_Manager.h"
#include "Start.h"
#include "Home.h"
#include "Plaza.h"
#include "Edit.h"
#include "Dungeon.h"
#include "Bitmap_Manager.h"
#include "UI_Manager.h"

CScene_Manager* CScene_Manager::m_pInstance = nullptr;
CScene_Manager::CScene_Manager()
	: m_eCurScene(SCENE_END)
	, m_eNextScene(SCENE_END)
	, m_pScene(nullptr)
{
}

CScene_Manager::~CScene_Manager()
{
	Release_Scene_Manager();
}

void CScene_Manager::Scene_Change(ID eNextID)
{
	m_eNextScene = eNextID;

	if (m_eCurScene != m_eNextScene)
	{
		delete m_pScene;
		m_pScene = nullptr;
		switch (m_eNextScene)
		{
		case CScene_Manager::SCENE_START:
			m_pScene = CStart::Create();
			break;
		case CScene_Manager::SCENE_HOME:
			
			break;
		case CScene_Manager::SCENE_PLAZA:

			break;
		case CScene_Manager::SCENE_DUNGEON:
			m_pScene = CDungeon::Create();
			break;
		case CScene_Manager::SCENE_EDIT:
			m_pScene = CEdit::Create();
			break;
		case CScene_Manager::SCENE_END:

			break;
		default:
			break;
		}
		m_eCurScene = m_eNextScene;
	}
}

void CScene_Manager::Update_Scene_Manager()
{
	m_pScene->Update_Scene();
}

void CScene_Manager::Render_Scene_Manager(HDC hDC)
{
	m_pScene->Render_Scene(hDC);
}

void CScene_Manager::Release_Scene_Manager()
{
	Safe_Delete(m_pScene);
}
