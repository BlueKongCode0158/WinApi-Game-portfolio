#include "stdafx.h"
#include "Zombie.h"
#include "Bitmap_Manager.h"
#include "GameObject_Manager.h"
#include "Scroll_Manager.h"
#include "CardEffect.h"
#include "Effect_Manager.h"

#define RECALLTIME 850

CZombie::CZombie()
	:m_NextState(IDLE),
	m_bCardEffect(false),
	m_RecallTime(0),
	m_bAttack(false)
{
	//bool m_bCardEffect;
	//bool m_bAttack;
	//bool m_bCollision;
	//bool m_bHit;
}

CZombie::~CZombie()
{
}

void CZombie::AnimationState()
{
	if (m_CurState != m_NextState)
	{
		switch (m_NextState)
		{
		case IDLE:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 0;
			m_tFrame.iState = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		case HIT:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 1;
			m_tFrame.iState = 3;
			m_tFrame.dwSpeed = 250;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ATTACK_LEFT:
			m_tFrame.iStartFrame = 3;
			m_tFrame.iEndFrame = 4;
			m_tFrame.iState = 0;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ATTACK_RIGHT:
			m_tFrame.iStartFrame = 1;
			m_tFrame.iEndFrame = 2;
			m_tFrame.iState = 0;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		case RUN_LEFT:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 5;
			m_tFrame.iState = 2;
			m_tFrame.dwSpeed = 80;
			m_tFrame.dwTime = GetTickCount();
			break;
		case RUN_RIGHT:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 5;
			m_tFrame.iState = 1;
			m_tFrame.dwSpeed = 80;
			m_tFrame.dwTime = GetTickCount();
			break;
		case DEAD:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 8;
			m_tFrame.iState = 4;
			m_tFrame.dwSpeed = 30;
			m_tFrame.dwTime = GetTickCount();
			break;
		default:
			break;
		}
		m_CurState = m_NextState;
	}
}

int CZombie::Ready_GameObject()
{
	m_eID = CGameObject::MONSTER_ID::ZOMBIE;

	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Monster/GhoulSource.bmp", L"Zombie");
	m_tPoint.iCX = 96;
	m_tPoint.iCY = 96;

	m_tPoint.fX = 600;
	m_tPoint.fY = 500;

	m_tFrame.iStartFrame = 0;
	m_tFrame.iEndFrame = 0;
	m_tFrame.iState = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = GetTickCount();
	//떨어져서 안 보이는건가..

	m_iHp = 300;

	m_RecallTime = GetTickCount();
	m_dwHitTime = GetTickCount();

	m_bAttack = false;

	return READY_OK;
}

int CZombie::Update_GameObject()
{
	CGameObject::Update_Rect();

	if (false == m_bRecog)
	{
		Collision_Player();
	}
	if (false == m_bCardEffect && true == m_bCollision )
	{
		TFPOINT tPoint{};
		tPoint.fX = m_tPoint.fX;
		tPoint.fY = m_tPoint.fY;
		CEffect* pObj = CCardEffect::Create(tPoint);
		dynamic_cast<CCardEffect*>(pObj)->Set_Collision();
		CEffect_Manager::Get_Instance()->Add_EffectObj(pObj, CEffect_Manager::EffectID::CARDEFFECT);

		m_bCardEffect = true;
		m_RecallTime = GetTickCount();
	}
	if (m_RecallTime + RECALLTIME < GetTickCount() && true == m_bCollision && true == m_bRecog)
	{
		if (DEAD == m_CurState && m_tFrame.iStartFrame > m_tFrame.iEndFrame)
		{
			return OBJ_DEAD;
		}
		if (DEAD == m_CurState)
		{
			return OBJ_NOEVENT;
			// 죽는 거 부드럽게 하는 역할.
		}
		if (m_iHp <= 0 && DEAD != m_CurState)
		{
			m_NextState = DEAD;
		}
		//충돌을 여기다가 넣어야할 삘이다.
		CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
		if (nullptr == pObj)
			return OBJ_NOEVENT;
		float fBase = pObj->Get_tPoint()->fX - m_tPoint.fX;
		float fHight = pObj->Get_tPoint()->fY - m_tPoint.fY;
		float fDist = sqrtf(fBase*fBase + fHight*fHight);

		float fAngle = acosf(fBase / fDist);

		if (m_tPoint.fY <= pObj->Get_tPoint()->fY)
			fAngle *= -1.f;

		float fSpeed = 3.f;

		float fRadian = PI / 180.f;

		if (fDist <= 50.f)
		{
			m_bAttack = true;

			if (fAngle <= 90 * fRadian && 0 * fRadian <= fAngle)
			{
				m_NextState = ATTACK_RIGHT;
			}
			else if (fAngle <= 180 * fRadian && 90 * fRadian <= fAngle)
			{
				m_NextState = ATTACK_LEFT;
			}
			else if (0 * fRadian >= fAngle && -90 * fRadian <= fAngle)
			{
				m_NextState = ATTACK_RIGHT;
			}
			else if (-90 * fRadian >= fAngle && -180 * fRadian <= fAngle)
			{
				m_NextState = ATTACK_LEFT;
			}
		}
		else if (fDist > 50.f && false == m_bAttack)
		{
			if (fAngle <= 90 * fRadian && 0 * fRadian <= fAngle)
			{
				m_NextState = RUN_RIGHT;
			}
			else if (fAngle <=180 * fRadian && 90 * fRadian <= fAngle)
			{
				m_NextState = RUN_LEFT;
			}
			else if (0 * fRadian >= fAngle && -90 * fRadian <= fAngle)
			{
				m_NextState = RUN_RIGHT;
			}
			else if (-90 * fRadian >= fAngle && -180 <= fAngle)
			{
				m_NextState = RUN_LEFT;
			}

			m_tPoint.fX += fSpeed*cosf(fAngle);
			m_tPoint.fY -= fSpeed*sinf(fAngle);
		}
		if (true == m_bHit)
		{
			m_NextState = HIT;
		}
		//if (m_dwHitTime + 100 < GetTickCount())
		//{
		//	m_bHit = false;
		//	m_dwHitTime = GetTickCount();	// 필요한 거 맞는데 더 체크.
		//}
	}

	return OBJ_NOEVENT;
}

void CZombie::Late_GamceObject()
{
	if (m_RecallTime + RECALLTIME < GetTickCount())
	{
		if (m_tFrame.iEndFrame >= m_tFrame.iStartFrame)
		{
			if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
			{
				m_tFrame.iStartFrame += 1;
				m_tFrame.dwTime = GetTickCount();
			}
		}
		if (m_tFrame.iStartFrame > m_tFrame.iEndFrame)
		{
			//여기 때문이네.
			if (ATTACK_LEFT == m_CurState)
			{
				m_bAttack = false;
			}
			else if (ATTACK_RIGHT == m_CurState)
			{
				m_bAttack = false;
			}
			else if (DEAD == m_CurState)
			{
				return;
			}
			else if (HIT == m_CurState)		
			{
				m_bAttack = false;
				m_bHit = false;
			}
			else
			{
				m_tFrame.iStartFrame = 0;
			}

		}

		AnimationState();
	}

}

void CZombie::Render_GameObject(HDC hDC)
{
	if (m_RecallTime + RECALLTIME < GetTickCount())
	{
		CGameObject::Update_Rect();
		HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"Zombie");

		int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
		int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();


		//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
		if (true == m_bCardEffect)
		{
			GdiTransparentBlt(hDC,
				m_tRect.left + iScrollX, m_tRect.top + iScrollY,
				m_tPoint.iCX, m_tPoint.iCY,
				hMemDC,
				m_tPoint.iCX * m_tFrame.iStartFrame, m_tPoint.iCY * m_tFrame.iState,
				m_tPoint.iCX, m_tPoint.iCY,
				RGB(255, 0, 255));
		}
		TCHAR szHp[32]{};
		swprintf_s(szHp, L"HP: %d", m_iHp);
		TextOut(hDC, m_tPoint.fX + iScrollX, m_tPoint.fY + iScrollY, szHp, lstrlen(szHp));

	}
}

void CZombie::Release_GameObject()
{
}

CGameObject * CZombie::Create()
{
	CGameObject* pInstance = new CZombie;
	if (0 > pInstance->Ready_GameObject())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

void CZombie::Collision_Player()
{
	CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
	if (nullptr == pObj)
	{
		return;
	}
	float fRadiusSum = ((pObj->Get_tPoint()->iCX)) + (m_tRecognizeSize.iCX >> 1);

	float fBase = pObj->Get_tPoint()->fX - m_tPoint.fX;
	float fHight = pObj->Get_tPoint()->fY - m_tPoint.fY;

	float fDistance = sqrtf(fBase*fBase + fHight*fHight);

	m_bRecog = fDistance <= fRadiusSum;

}
