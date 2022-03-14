#include "stdafx.h"
#include "IRon_Collider.h"
#include "Scroll_Manager.h"
#include "GameObject.h"
#include "GameObject_Manager.h"
#include "Player.h"
#include "Prob.h"

CIRon_Collider::CIRon_Collider()
{
}

CIRon_Collider::~CIRon_Collider()
{
}

CCollider * CIRon_Collider::Create()
{
	CCollider* pInstace = new CIRon_Collider;
	if (0 > pInstace->Ready_Collider())
	{
		Safe_Delete(pInstace);
	}
	return pInstace;
}

int CIRon_Collider::Ready_Collider()
{
	m_eColliderName = CCollider::COLLIDER::IRON_BAR;
	m_dwCount = GetTickCount();
	return READY_OK;
}

int CIRon_Collider::Update_Collider()
{
	list<CGameObject*>* plistProb = CGameObject_Manager::Get_Instacne()->Get_List(GAMEOBJECT::UPDATE_ID::Prob);
	CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
	CProb::PROBS eID = CProb::NOMAL;

	if (nullptr == pObj)
	{
		return OBJ_NOEVENT;
	}

	RECT tRECT{};
	if (IntersectRect(&tRECT, pObj->Get_RECT(), &m_tRect))
	{
		if (m_dwCount + 500 < GetTickCount())
		{
			for (auto& rProb : *plistProb)
			{
				RECT tProbRECT{};
				if (IntersectRect(&tProbRECT, rProb->Get_RECT(), &m_tRect))
				{
					eID = dynamic_cast<CProb*>(rProb)->Get_Prob_ID();
					if (eID == CProb::PROBS::IRON)
					{
						rProb->Set_Collision();
					}
				}
			}
			return OBJ_DEAD;
		}
	}
	else
	{
		m_dwCount = GetTickCount();
	}



	return OBJ_NOEVENT;
}

void CIRon_Collider::Render_Collider(HDC hDC)
{
	HBRUSH myBrush = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
	HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(hDC, myBrush));
	HPEN myPen = static_cast<HPEN>(CreatePen(PS_SOLID, 1, RGB(255, 0, 0)));
	HPEN oldPen = static_cast<HPEN>(SelectObject(hDC, myPen));

	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	SelectObject(hDC, oldBrush);
	SelectObject(hDC, oldPen);
	DeleteObject(myBrush);
	DeleteObject(myPen);
}

void CIRon_Collider::Release_Collider()
{
}
