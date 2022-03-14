#include "stdafx.h"
#include "Create_Collider.h"
#include "Scroll_Manager.h"
#include "GameObject.h"
#include "Player.h"
#include "GameObject_Manager.h"
#include "Prob.h"

CCreate_Collider::CCreate_Collider()
{
}

CCreate_Collider::~CCreate_Collider()
{
}

CCollider * CCreate_Collider::Create()
{
	CCollider* pInstance = new CCreate_Collider;
	if (0 > pInstance->Ready_Collider())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

int CCreate_Collider::Ready_Collider()
{
	m_iEnemyNum = 0;
	m_iBossNum = 0;
	m_eColliderName = CCollider::COLLIDER::CREATE_COLLIDER;
	return READY_OK;
}

int CCreate_Collider::Update_Collider()
{
	m_iEnemyNum = 0;

	//보관하는 인수 넣어줘야 되나 ㅎㅎ...
	//여기 안에서 플레이어와 충돌시 몬스터 obj의 소환을 true 만들어주는 거 넣어주자.
	CGameObject* pPlayer = CGameObject_Manager::Get_Instacne()->Get_Player();
	list<CGameObject*>* rlistMonster = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::MONSTER);
	list<CGameObject*>* rlistBoss = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::BOSS);

	if (nullptr == pPlayer)
	{
		return OBJ_NOEVENT;
	}

	if (nullptr == rlistMonster)	//이거 아니다제..
	{
		//철장도 여기서 없애줄것 -> 프랍일려나~
		//이 녀석과 닿아 있는 철장 삭제.
		return OBJ_DEAD;
	}

	if (nullptr == rlistBoss)
	{
		return OBJ_DEAD;
	}

	RECT tRECT{};
	if (IntersectRect(&tRECT, &m_tRect, pPlayer->Get_RECT()))
	{
		for (auto& pMonster : *rlistMonster)
		{
			RECT tMonsterRect{};
			if (IntersectRect(&tMonsterRect, &m_tRect, pMonster->Get_RECT()))
			{
				pMonster->Set_Collision();
				m_iEnemyNum += 1;
			}
		}
	}
	else
	{
		for (auto& pMonster : *rlistMonster)
		{
			RECT tMonsterRect{};
			if (IntersectRect(&tMonsterRect, &m_tRect, pMonster->Get_RECT()))
			{
				pMonster->Set_Collision(false);
			}
		}
	}

	if (IntersectRect(&tRECT, &m_tRect, pPlayer->Get_RECT()))
	{
		for (auto& pMonster : *rlistBoss)
		{
			RECT tMonsterRect{};
			if (IntersectRect(&tMonsterRect, &m_tRect, pMonster->Get_RECT()))
			{
				pMonster->Set_Collision();
				m_iBossNum = 1;

				if (pMonster->Get_HP() <= 0)
				{
					m_iBossNum = 0;
				}
			}
		}
	}
	else
	{
		for (auto& pMonster : *rlistBoss)
		{
			RECT tMonsterRect{};
			if (IntersectRect(&tMonsterRect, &m_tRect, pMonster->Get_RECT()))
			{
				pMonster->Set_Collision(false);
			}
		}
	}

	//else
	//{
	//	for (auto& pMonster : *rlistBoss)
	//	{
	//		RECT tMonsterRect{};
	//		if (IntersectRect(&tMonsterRect, &m_tRect, pMonster->Get_RECT()))
	//		{
	//			pMonster->Set_Collision(false);
	//		}
	//	}
	//}

	if (0 == m_iEnemyNum && 0 == m_iBossNum)
	{
		list<CGameObject*>* plistProb = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::Prob);
		CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();

		if (nullptr == plistProb || nullptr == pObj)
		{
			return OBJ_NOEVENT;
		}

		RECT tPlayerRECT{};

		if (IntersectRect(&tPlayerRECT, &m_tRect, pObj->Get_RECT()))
		{
			RECT tRECT{};
			for (auto& pProb : *plistProb)
			{
				if (IntersectRect(&tRECT, &m_tRect, pProb->Get_RECT()) && (dynamic_cast<CProb*>(pProb)->Get_Prob_ID() == CProb::PROBS::IRON))
				{
					pProb->Set_Dead();
				}
			}
		}
	}

	return OBJ_NOEVENT;
}

void CCreate_Collider::Render_Collider(HDC hDC)
{
	HBRUSH myBrush = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
	HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(hDC, myBrush));
	HPEN myPen = static_cast<HPEN>(CreatePen(PS_SOLID, 1, RGB(0, 0, 255)));
	HPEN oldPen = static_cast<HPEN>(SelectObject(hDC, myPen));

	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	SelectObject(hDC, oldBrush);
	SelectObject(hDC, oldPen);
	DeleteObject(myBrush);
	DeleteObject(myPen);

}

void CCreate_Collider::Release_Collider()
{
}
