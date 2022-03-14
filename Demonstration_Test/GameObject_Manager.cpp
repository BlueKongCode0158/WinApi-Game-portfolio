#include "stdafx.h"
#include "GameObject.h"
#include "GameObject_Manager.h"
#include "Collision_Manager.h"
#include "Tile_Manager.h"
#include "Skil_Manager.h"
#include "Archer.h"
#include "Zombie.h"
#include "Prob.h"
#include "Key_Manager.h"

CGameObject_Manager* CGameObject_Manager::m_pInstance = nullptr;

void CGameObject_Manager::Save_Data_Monster()
{
	HANDLE hFile = CreateFile(
		L"../Data/MonsterData.dat",
		GENERIC_WRITE,
		0, nullptr,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}
	DWORD dwbyte = 0;

	if (!m_listGameObject[GAMEOBJECT::UPDATE_ID::MONSTER].empty())
	{
		for (auto& pMonster : m_listGameObject[GAMEOBJECT::UPDATE_ID::MONSTER])
		{
			TPOINT* tPoint = pMonster->Get_tPoint();
			CGameObject::MONSTER_ID eID = pMonster->Get_MonsterID();
			WriteFile(hFile, tPoint, sizeof(TPOINT), &dwbyte, nullptr);
			WriteFile(hFile, &eID, sizeof(CGameObject::MONSTER_ID), &dwbyte, nullptr);
		}
	}
	CloseHandle(hFile);
}

void CGameObject_Manager::Load_Data_Monster()
{
	HANDLE hFile = CreateFile(L"../Data/MonsterData.dat",
		GENERIC_READ,
		0, nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}
	DWORD dwbyte = 0;

	if (!m_listGameObject[GAMEOBJECT::UPDATE_ID::MONSTER].empty())
	{
		for (auto& pMonster : m_listGameObject[GAMEOBJECT::UPDATE_ID::MONSTER])
		{
			Safe_Delete(pMonster);
		}
		m_listGameObject[GAMEOBJECT::UPDATE_ID::MONSTER].clear();
	}

	while (true)
	{
		TPOINT tPoint{};
		CGameObject::MONSTER_ID eID = CGameObject::MONSTER_ID::NONE;

		ReadFile(hFile, &tPoint, sizeof(TPOINT), &dwbyte, nullptr);
		ReadFile(hFile, &eID, sizeof(CGameObject::MONSTER_ID), &dwbyte, nullptr);

		if (0 == dwbyte)
			break;

		TFPOINT tFPoint{};
		tFPoint.fX = tPoint.fX;
		tFPoint.fY = tPoint.fY;

		CGameObject* pObj = nullptr;

		switch (eID)
		{
		case CGameObject::MONSTER_ID::ARCHER:
			pObj = CArcher::Create();
			pObj->Set_tPoint(tFPoint);
			pObj->Set_MonsterID(eID);
			break;
		case CGameObject::MONSTER_ID::MAGIC:
			break;
		case CGameObject::MONSTER_ID::SLIME:
			break;
		case CGameObject::MONSTER_ID::ZOMBIE:
			pObj = CZombie::Create();
			pObj->Set_tPoint(tFPoint);
			pObj->Set_MonsterID(eID);
			break;
		case CGameObject::MONSTER_ID::NONE:
			CloseHandle(hFile);
			return;
		default:
			CloseHandle(hFile);
			return;
		}
		m_listGameObject[GAMEOBJECT::UPDATE_ID::MONSTER].emplace_back(pObj);
	}
	CloseHandle(hFile);
}

void CGameObject_Manager::Save_Data_Prob()
{
	HANDLE hFile = CreateFile(
		L"../Data/ProbData.dat",
		GENERIC_WRITE,
		0, nullptr,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}
	DWORD dwbyte = 0;

	if (!m_listGameObject[GAMEOBJECT::UPDATE_ID::Prob].empty())
	{
		for (auto& pPRob : m_listGameObject[GAMEOBJECT::UPDATE_ID::Prob])
		{
			TPOINT* tPoint = pPRob->Get_tPoint();
			RECT* tRECT = dynamic_cast<CProb*>(pPRob)->Get_ImageRect();
			CProb::PROBS eID = dynamic_cast<CProb*>(pPRob)->Get_Prob_ID();
			WriteFile(hFile, tPoint, sizeof(TPOINT), &dwbyte, nullptr);
			WriteFile(hFile, tRECT, sizeof(RECT), &dwbyte, nullptr);
			WriteFile(hFile, &eID, sizeof(CProb::PROBS), &dwbyte, nullptr);//이거 잘못하면 터질 듯
		}
	}
	CloseHandle(hFile);

}

void CGameObject_Manager::Load_Data_Prob()
{
	HANDLE hFile = CreateFile
	(
		L"../Data/ProbData.dat",
		GENERIC_READ,
		0, nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}
	DWORD dwbyte = 0;

	if (!m_listGameObject[GAMEOBJECT::UPDATE_ID::Prob].empty())
	{
		for (auto& pProb : m_listGameObject[GAMEOBJECT::UPDATE_ID::Prob])
		{
			Safe_Delete(pProb);
		}
		m_listGameObject[GAMEOBJECT::UPDATE_ID::Prob].clear();
	}

	while (true)
	{
		TPOINT tPoint{};
		RECT tRECT{};
		CProb::PROBS eID{};

		ReadFile(hFile, &tPoint, sizeof(TPOINT), &dwbyte, nullptr);
		ReadFile(hFile, &tRECT, sizeof(RECT), &dwbyte, nullptr);
		ReadFile(hFile, &eID, sizeof(CProb::PROBS), &dwbyte, nullptr);

		if (0 == dwbyte)
			break;

		TFPOINT tFPoint{};
		tFPoint.fX = tPoint.fX;
		tFPoint.fY = tPoint.fY;

		CGameObject* pObj = CProb::Create();
		pObj->Set_tPoint(tFPoint);
		pObj->Set_tSize(tPoint);
		dynamic_cast<CProb*>(pObj)->Set_ImageRect(tRECT);
		dynamic_cast<CProb*>(pObj)->Set_Prob_ID(eID);
		m_listGameObject[GAMEOBJECT::UPDATE_ID::Prob].emplace_back(pObj);
	}
	CloseHandle(hFile);
}

void CGameObject_Manager::Collision_Shield()
{
	//매직 - 몬스터
	list<CSkil*>* plistShield = CSkil_Manager::Get_Instacne()->Get_list(GAMEOBJECT::UPDATE_SKIL::MAGIC);
	list<CGameObject*>* pArmor = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::MONSTER_ARMOR);
	//armor 말고도 보스 스킬도 나눠줘야 할 거 있고.
	if (nullptr == plistShield || nullptr == pArmor)
	{
		return;
	}
	if (!plistShield->empty() && !pArmor->empty())
	{
		CCollision_Manager::Get_Instacne()->Shield_Collision(*plistShield, *pArmor);
	}
}

void CGameObject_Manager::Collision_ShieldHit()
{
	Collision_ShieldHit_Monster();
	Collision_ShieldHit_Boss();
}

void CGameObject_Manager::Collision_TileArrow()
{

	//타일 - 플레이어
	if (!m_listGameObject[GAMEOBJECT::UPDATE_ID::PLAYER].empty())
	{
		CGameObject* pObj = m_listGameObject[GAMEOBJECT::UPDATE_ID::PLAYER].front();
		vector<CTile*>* pVecTile = CTile_Manager::Get_Instance()->Get_Vector();
		// 왜 벡터는 변수로 취할 때 lvalue로 취해야하는가?

		CCollision_Manager::Get_Instacne()->Tile_Collision(*pObj, *pVecTile);
	}
	//아머 - 플레이어
	if (!m_listGameObject[GAMEOBJECT::UPDATE_ID::MONSTER_ARMOR].empty())
	{
		vector<CTile*>* pVecTile = CTile_Manager::Get_Instance()->Get_Vector();
		CCollision_Manager::Get_Instacne()->Tile_Collision(m_listGameObject[GAMEOBJECT::UPDATE_ID::MONSTER_ARMOR], *pVecTile, GAMEOBJECT::UPDATE_ID::MONSTER_ARMOR);
	}
}

void CGameObject_Manager::Collision_Monster()
{
	Collision_Monster_Slash();
	Collision_Boss_Slash();
	//일반 공격 - 몬스터
}

void CGameObject_Manager::Collision_Monster_Slash()
{
	list<CGameObject*>*  pObj = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::MONSTER);
	list<CSkil*>* plistSkil = CSkil_Manager::Get_Instacne()->Get_list(GAMEOBJECT::UPDATE_SKIL::NORMAL);
	if (nullptr == pObj || nullptr == plistSkil)
	{
		return;
	}
	if (!pObj->empty() && !plistSkil->empty())
	{
		CCollision_Manager::Get_Instacne()->Monster_Collision(*plistSkil, *pObj, EMONSTER::ARCHER);
	}

}

void CGameObject_Manager::Collision_Boss_Slash()
{
	list<CSkil*>* plistSkil = CSkil_Manager::Get_Instacne()->Get_list(GAMEOBJECT::UPDATE_SKIL::NORMAL);
	list<CGameObject*>* pBoss = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::BOSS);

	if (nullptr == pBoss || nullptr == plistSkil)
	{
		return;
	}
	if (!pBoss->empty() && !plistSkil->empty())
	{
		CCollision_Manager::Get_Instacne()->Monster_Collision(*plistSkil, *pBoss, EMONSTER::ARCHER);
	}
}

void CGameObject_Manager::Collision_IceSpin()
{
	list<CSkil*>* plistSkil = CSkil_Manager::Get_Instacne()->Get_list(GAMEOBJECT::UPDATE_SKIL::FINAL);
	list<CGameObject*>* plistMonster = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::MONSTER);

	if (nullptr == plistSkil || nullptr == plistMonster)
		return;
	if (!plistSkil->empty() && !plistMonster->empty())
	{
		CCollision_Manager::Get_Instacne()->Shield_Collision(*plistSkil, *plistMonster);
	}
}

void CGameObject_Manager::Collision_IceSpin_Attack()
{
	Collision_IceSpin_Monster();
	Collision_IceSpin_Boss();
	list<CSkil*>* plistSkil = CSkil_Manager::Get_Instacne()->Get_list(GAMEOBJECT::UPDATE_SKIL::FINAL);
	list<CGameObject*>* plistMonster = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::MONSTER);

	if (nullptr == plistSkil || nullptr == plistMonster)
		return;
	if (!plistSkil->empty() && !plistMonster->empty())
	{
		CCollision_Manager::Get_Instacne()->Shield_Collision_Attack(*plistSkil, *plistMonster);
	}
}

void CGameObject_Manager::Collision_ShieldHit_Monster()
{
	list<CSkil*>* plistShield = CSkil_Manager::Get_Instacne()->Get_list(GAMEOBJECT::UPDATE_SKIL::MAGIC);
	list<CGameObject*>* plistMonster = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::MONSTER);

	if (nullptr == plistShield || nullptr == plistMonster)
	{
		return;
	}

	if (!plistShield->empty() && !plistMonster->empty())
	{
		CCollision_Manager::Get_Instacne()->Shield_Collision_Attack(*plistShield, *plistMonster);
	}
}

void CGameObject_Manager::Collision_ShieldHit_Boss()
{
	list<CSkil*>* plistShield = CSkil_Manager::Get_Instacne()->Get_list(GAMEOBJECT::UPDATE_SKIL::MAGIC);
	list<CGameObject*>* plistBoss = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::BOSS);

	if (nullptr == plistShield || nullptr == plistBoss)
	{
		return;
	}

	if (!plistShield->empty() && !plistBoss->empty())
	{
		CCollision_Manager::Get_Instacne()->Shield_Collision_Attack(*plistShield, *plistBoss);
	}

}

void CGameObject_Manager::Collision_IceSpin_Monster()
{
	list<CSkil*>* plistSkil = CSkil_Manager::Get_Instacne()->Get_list(GAMEOBJECT::UPDATE_SKIL::FINAL);
	list<CGameObject*>* plistMonster = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::MONSTER);

	if (nullptr == plistSkil || nullptr == plistMonster)
		return;
	if (!plistSkil->empty() && !plistMonster->empty())
	{
		CCollision_Manager::Get_Instacne()->Shield_Collision_Attack(*plistSkil, *plistMonster);
	}

}

void CGameObject_Manager::Collision_IceSpin_Boss()
{
	list<CSkil*>* plistSkil = CSkil_Manager::Get_Instacne()->Get_list(GAMEOBJECT::UPDATE_SKIL::FINAL);
	list<CGameObject*>* plistMonster = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::BOSS);

	if (nullptr == plistSkil || nullptr == plistMonster)
		return;
	if (!plistSkil->empty() && !plistMonster->empty())
	{
		CCollision_Manager::Get_Instacne()->Shield_Collision_Attack(*plistSkil, *plistMonster);
	}
}

void CGameObject_Manager::Update_GameObject_Manager()
{
	for (int i = 0; i < GAMEOBJECT::UPDATE_ID::UPDATE_END; i++)	//정말 황당한 실수를 하셨군요. 틀린 그림 찾기 스타트..
	{
		for (auto& iter = m_listGameObject[i].begin(); iter != m_listGameObject[i].end(); )
		{
			int iEvent = (*iter)->Update_GameObject();
			if (iEvent == OBJ_DEAD)
			{
				Safe_Delete(*iter);
				iter = m_listGameObject[i].erase(iter);
			}
			else
			{
				iter++;
			}
		}

		for (auto& iter = m_listGameObject[i].begin(); iter != m_listGameObject[i].end(); iter++)
		{
			(*iter)->Late_GamceObject();
		}
		for (auto& pRender : m_listGameObject[i])
		{
			m_listGameObjectSortRender.emplace_back(pRender);
		}
	}
	CSkil_Manager::Get_Instacne()->Update_Skil();

	Collision_Monster();
	Collision_Shield();
	Collision_ShieldHit();

	//Collision_IceSpin();
	Collision_IceSpin_Attack();

	Collision_TileArrow();

	list<CGameObject*>* plistPlayer = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::PLAYER);
	list<CGameObject*>* plistArrow = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::MONSTER_ARMOR);
	if (nullptr == plistArrow || nullptr == plistPlayer)
	{
		return;
	}
	CCollision_Manager::Get_Instacne()->Collision_RectEX(*plistPlayer, *plistArrow);
	
}
void CGameObject_Manager::Render_GameObject_Manager(HDC hDC)
{
	m_listGameObjectSortRender.sort([](auto& pDst, auto& pSrc)
	{
		return (pDst->Get_tPoint()->fY + pDst->Get_tPoint()->iCY) < (pSrc->Get_tPoint()->fY + pSrc->Get_tPoint()->iCY);
	});

	for (auto& iter = m_listGameObjectSortRender.begin(); iter != m_listGameObjectSortRender.end(); iter++)
	{
		(*iter)->Render_GameObject(hDC);
	}
	m_listGameObjectSortRender.clear();

	if (CKey_Manager::Get_EditKey()->Key_Pressing(KEY_3))
	{
		for (int i = 0; i < GAMEOBJECT::UPDATE_ID::UPDATE_END; i++)
		{
			for (auto& iter = m_listGameObject[i].begin(); iter != m_listGameObject[i].end(); iter++)
			{
				(*iter)->Render_GameObject(hDC);
			}
		}
	}
	CSkil_Manager::Get_Instacne()->Render_Skil(hDC);

}
void CGameObject_Manager::Release_GameObject_Manager()
{
	for (int i = 0; i < GAMEOBJECT::UPDATE_ID::UPDATE_END; i++)
	{
		for (auto& iter = m_listGameObject[i].begin(); iter != m_listGameObject[i].end(); iter++)
		{
			Safe_Delete(*iter);
		}
		m_listGameObject[i].clear();
	}
}
void CGameObject_Manager::Collision_Rect_Delete(RECT & rRect)
{
	for (auto& iter = m_listGameObject[GAMEOBJECT::UPDATE_ID::MONSTER].begin(); iter != m_listGameObject[GAMEOBJECT::UPDATE_ID::MONSTER].end();)
	{
		RECT tRECT{};
		if (IntersectRect(&tRECT, &rRect, (*iter)->Get_RECT()))
		{
			Safe_Delete(*iter);
			iter = m_listGameObject[GAMEOBJECT::UPDATE_ID::MONSTER].erase(iter);
		}
		else
		{
			iter++;
		}
	}
}
void CGameObject_Manager::Collision_Rect_Delete_PRob(RECT & rRECT)
{
	for (auto& iter = m_listGameObject[GAMEOBJECT::UPDATE_ID::Prob].begin(); iter != m_listGameObject[GAMEOBJECT::UPDATE_ID::Prob].end();)
	{
		RECT tRECT{};
		if (IntersectRect(&tRECT, &rRECT, (*iter)->Get_RECT()))
		{
			Safe_Delete(*iter);
			iter = m_listGameObject[GAMEOBJECT::UPDATE_ID::Prob].erase(iter);
		}
		else
		{
			iter++;
		}
	}
}
CGameObject_Manager::CGameObject_Manager()
{

}

CGameObject_Manager::~CGameObject_Manager()
{
	Release_GameObject_Manager();
}

