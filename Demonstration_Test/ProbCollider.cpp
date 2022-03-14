#include "stdafx.h"
#include "ProbCollider.h"
#include "Scroll_Manager.h"
#include "GameObject.h"
#include "GameObject_Manager.h"
#include "Key_Manager.h"

CProbCollider::CProbCollider()
{
}

CProbCollider::~CProbCollider()
{
}

CCollider * CProbCollider::Create()
{
	CCollider* pInstance = new CProbCollider;
	if (0 > pInstance->Ready_Collider())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

int CProbCollider::Ready_Collider()
{
	m_eColliderName = CCollider::COLLIDER::PROB;
	return READY_OK;
}

int CProbCollider::Update_Collider()
{
	CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
	list<CGameObject*>* plistArmor = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::MONSTER_ARMOR);

	if (nullptr == pObj)
	{
		return OBJ_NOEVENT;
	}
	RECT* tRECT = pObj->Get_RECT();

	RECT tRect{};
	if (IntersectRect(&tRect, tRECT, &m_tRect))
	{
		if (tRECT->right >= m_tRect.left && tRECT->left <= m_tRect.left)
		{
			pObj->Set_Wall();

			if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_A))
			{
				pObj->Set_Wall(false);
			}

		}
		else if (tRECT->left <= m_tRect.right && tRECT->right >= m_tRect.right)
		{
			pObj->Set_Wall();
			if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_D))
			{
				pObj->Set_Wall(false);
			}
		}
		else if (tRECT->bottom >= m_tRect.top && tRECT->top <= m_tRect.top)
		{
			pObj->Set_Wall();
			if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_W))
			{
				pObj->Set_Wall(false);
			}

		}
		else if (tRECT->top <= m_tRect.bottom && tRECT->bottom >= m_tRect.bottom)
		{
			pObj->Set_Wall();
			if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_S))
			{
				pObj->Set_Wall(false);
			}
		}
	}
	Monster_Collider();
	MonsterArmor_Collider();

	return OBJ_NOEVENT;
}

void CProbCollider::Render_Collider(HDC hDC)
{
	HBRUSH myBrush = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
	HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(hDC, myBrush));
	HPEN myPen = static_cast<HPEN>(CreatePen(PS_SOLID,1,RGB(0,255,0)));
	HPEN oldPen = static_cast<HPEN>(SelectObject(hDC, myPen));

	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	SelectObject(hDC, oldBrush);
	SelectObject(hDC, oldPen);
	DeleteObject(myBrush);
	DeleteObject(myPen);
}

void CProbCollider::Release_Collider()
{
}

void CProbCollider::MonsterArmor_Collider()
{
	list<CGameObject*>* plistArmor = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::MONSTER_ARMOR);

	if (nullptr == plistArmor)
	{
		return;
	}

	for (auto& pArmor : *plistArmor)
	{
		RECT tRect_Armor{};

		if (IntersectRect(&tRect_Armor, &m_tRect, pArmor->Get_RECT()))
		{
			pArmor->Set_Dead();
		}
	}

}

void CProbCollider::Monster_Collider()
{
	list<CGameObject*>* plistMonster = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::MONSTER);
	CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
	if (nullptr == plistMonster || nullptr == pObj)
		return;

	RECT tRect{};
	if (IntersectRect(&tRect, &m_tRect, pObj->Get_RECT()))
	{
		for (auto& pMonster : *plistMonster)
		{
			RECT tRECT{};
			if (IntersectRect(&tRECT, &m_tRect, pMonster->Get_RECT()))
			{
				pMonster->Set_Wall();
			}
		}
	}
}
