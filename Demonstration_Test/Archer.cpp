#include "stdafx.h"
#include "Archer.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
#include "Player.h"
#include "GameObject_Manager.h"
#include "Collision_Manager.h"
#include "Effect.h"
#include "Effect_Manager.h"
#include "CardEffect.h"
#include "GameObject.h"
#include "Arrow.h"
#include "GameObject.h"
#include "SoundMgr.h"

#define RECALLTIME 850


CArcher::CArcher()
	:m_NextSTate(IDLE),
	m_iArrowNum(0),
	m_bCardEffect(false)
{
}

CArcher::~CArcher()
{
}

CGameObject * CArcher::Create()
{
	CGameObject* pInstance = new CArcher;
	if (0 > pInstance->Ready_GameObject())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

int CArcher::Ready_GameObject()
{
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Monster/Archer_1.bmp", L"Archer");
	
	m_eID = CGameObject::MONSTER_ID::ARCHER;

	m_iHp = 200;
	m_iMp = 0;
	m_iDamage = 10;

	m_tPoint.iCX = 96;
	m_tPoint.iCY = 96;

	m_tPoint.fX = 700.f;
	m_tPoint.fY = 450.f;

	m_bHit = false;
	m_dwHitTime = GetTickCount();

	m_tRecognizeSize.iCX = 500;
	m_tRecognizeSize.iCY = 500;

	m_tRect_Recognize.left   = m_tPoint.fX - (m_tRecognizeSize.iCX >> 1);
	m_tRect_Recognize.top    = m_tPoint.fY - (m_tRecognizeSize.iCY >> 1);
	m_tRect_Recognize.right  = m_tPoint.fX + (m_tRecognizeSize.iCX >> 1);
	m_tRect_Recognize.bottom = m_tPoint.fY + (m_tRecognizeSize.iCY >> 1);

	m_RecallTime = GetTickCount();
	m_iArrowNum = 1;
	return READY_OK;
}

int CArcher::Update_GameObject()
{
	CGameObject::Update_Rect();

	Collision_Player();
	if (true == m_bCollision && false == m_bCardEffect)
	{
		TFPOINT tPoint{};
		tPoint.fX = m_tPoint.fX;
		tPoint.fY = m_tPoint.fY;
		CEffect* pObj = CCardEffect::Create(tPoint);
		dynamic_cast<CCardEffect*>(pObj)->Set_Collision();
		CEffect_Manager::Get_Instance()->Add_EffectObj(pObj, CEffect_Manager::EffectID::CARDEFFECT);

		m_bCardEffect = true;
		//CEffect* pObj = CCardEffect::Create(tPoint);
		//CEffect_Manager::Get_Instance()->Add_EffectObj(pObj, CEffect_Manager::EffectID::CARDEFFECT);
	}
	if(true == m_bCollision && true == m_bCardEffect && true == m_bRecog)
	{
		if (m_RecallTime + RECALLTIME < GetTickCount())
		{
			//�浹�� ����ٰ� �־���� ���̴�.
			if (DEAD == m_CurState && m_tFrame.iStartFrame > m_tFrame.iEndFrame)
			{
				return OBJ_DEAD;
			}

			//ȭ�� �߻�
			Create_Arrow();

			m_bHit;
			if (m_dwHitTime + 50 < GetTickCount())
			{
				m_bHit = false;
				m_dwHitTime = GetTickCount();	// �ʿ��� �� �´µ� �� üũ.
			}
		}
	}
	else if (false == m_bCardEffect)
	{
		m_RecallTime = GetTickCount();
	}
	return OBJ_NOEVENT;
}

void CArcher::Late_GamceObject()
{
	if (m_RecallTime + RECALLTIME < GetTickCount())
	{
		if (true == m_bCollision && true == m_bCardEffect)
		{
			ShotAniamation();
			if (m_iHp <= 0 && m_CurState != DEAD)
			{
				m_NextSTate = DEAD;
			}
			if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
			{
				m_tFrame.iStartFrame += 1;
				m_tFrame.dwTime = GetTickCount();
				if (m_iArrowNum == 0)
				{
					m_iArrowNum = 1;
				}
			}
		}
		else
		{
			m_NextSTate = IDLE;
		}

		//���ǹ��� �� �ɾ��ָ� �λ��� ��������..
		Animation_State();

		if (m_tFrame.iStartFrame > m_tFrame.iEndFrame)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"ArcherAttackWindup.wav", CSoundMgr::CHANNELID::MONSTER);
			if (ATTACK_FRONT == m_CurState || ATTACK_315 == m_CurState || ATTACK_225 == m_CurState)
			{
				m_tFrame.iStartFrame = 4;
			}
			else if (DEAD == m_CurState)
			{
				return;
			}
			else if (HIT == m_CurState || true == m_bHit)		//�� ���� ��ü�� �� �ɸ���? �Ƴ� ��� ���� �Ÿ��ٴ°Ÿ�.. else���� �ɸ��� �� ���� �ʱ�.
			{
				m_NextSTate = ATTACK_FRONT; // ������.
				//ShotAniamation();		// �׷� ���⼭ �ٽ� ��Ʈ�� �ɸ��ٴ� �ǵ�
				//Animation_State();
			}
			else
			{
				m_tFrame.iStartFrame = 0;
			}

		}
	}

	//m_tFrame.iStartFrame;
	//m_iHp;
}

void CArcher::Render_GameObject(HDC hDC)
{
	if (m_RecallTime + RECALLTIME < GetTickCount())
	{

		CGameObject::Update_Rect();

		int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
		int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

		HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"Archer");


		//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
		//Ellipse(hDC, m_tRect_Recognize.left + iScrollX, m_tRect_Recognize.top + iScrollY, m_tRect_Recognize.right + iScrollX, m_tRect_Recognize.bottom + iScrollY);
		GdiTransparentBlt(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tPoint.iCX, m_tPoint.iCY,
			hMemDC, m_tFrame.iStartFrame*m_tPoint.iCX, m_tFrame.iState*m_tPoint.iCY, m_tPoint.iCX, m_tPoint.iCY, RGB(255, 0, 255));

		TCHAR szHp[32]{};
		swprintf_s(szHp, L"HP: %d", m_iHp);
		TextOut(hDC, m_tPoint.fX + iScrollX, m_tPoint.fY + iScrollY, szHp, lstrlen(szHp));

		CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();

		if (nullptr == pObj)
		{
			return;
		}
		HPEN hSelectPen;
		HPEN hOldPen;

		//�÷��̾ ������ ���� �� !
		hSelectPen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
		hOldPen = static_cast<HPEN>(SelectObject(hDC, hSelectPen));
		float fPlayerX = pObj->Get_tPoint()->fX;
		float fPlayerY = pObj->Get_tPoint()->fY;
		if (true == m_bCollision)
		{
			MoveToEx(hDC, m_tPoint.fX + iScrollX, m_tPoint.fY + iScrollY, nullptr);
			LineTo(hDC, fPlayerX + iScrollX, fPlayerY + iScrollY);
		}
		SelectObject(hDC, hOldPen);
		DeleteObject(hSelectPen);
	}
}

void CArcher::Release_GameObject()
{
}

void CArcher::Animation_State()
{
	if (m_CurState != m_NextSTate)
	{
		switch (m_NextSTate)
		{
		case IDLE:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 0;
			m_tFrame.iState = 0;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ATTACK_LEFT:
			m_tFrame.iState = 6;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 3;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ATTACK_RIGHT:
			m_tFrame.iState = 5;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 3;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ATTACK_FRONT:
			m_tFrame.iState = 5;
			m_tFrame.iStartFrame = 4;
			m_tFrame.iEndFrame = 7;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ATTACK_BACK:
			m_tFrame.iState = 8;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 3;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ATTACK_45:
			m_tFrame.iState = 4;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 3;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ATTACK_135:
			m_tFrame.iState = 7;
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 3;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ATTACK_225:
			m_tFrame.iState = 4;
			m_tFrame.iStartFrame = 4;
			m_tFrame.iEndFrame = 7;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ATTACK_315:
			m_tFrame.iState = 6;
			m_tFrame.iStartFrame = 4;
			m_tFrame.iEndFrame = 7;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		case HIT:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 1;
			m_tFrame.iState = 2;
			m_tFrame.dwSpeed = 250;
			m_tFrame.dwTime = GetTickCount();
			break;
		case RUN:

			break;
		case DEAD:
			m_tFrame.iStartFrame = 2;
			m_tFrame.iEndFrame = 8;
			m_tFrame.iState = 2;
			m_tFrame.dwSpeed = 30;
			m_tFrame.dwTime = GetTickCount();
			break;
		default:
			break;
		}
		m_CurState = m_NextSTate;
	}
}

void CArcher::ShotAniamation()
{
	if (m_CurState == CArcher::STATE::DEAD)
		return;


	CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
	if (nullptr == pObj)
		return;
	TPOINT* tPlayerPoint = pObj->Get_tPoint();

	float fBase = tPlayerPoint->fX - m_tPoint.fX;
	float fHight = tPlayerPoint->fY - m_tPoint.fY;
	float fDistane = sqrtf(fBase*fBase + fHight*fHight);

	float fAngle = acosf(fBase / fDistane);

	if (tPlayerPoint->fY >= m_tPoint.fY)
		fAngle *= -1.f;

	float fRadian = PI / 180.f;

	if (fAngle != m_fAngle && m_NextSTate != DEAD)
	{
		if (-22.5*fRadian <= fAngle && 22.5* fRadian >= fAngle)
		{
			m_NextSTate = ATTACK_RIGHT;
		}
		else if (22.5*fRadian <= fAngle && 67.5*fRadian >= fAngle)
		{
			m_NextSTate = ATTACK_45;

		}
		else if (67.5*fRadian <= fAngle && 112.5*fRadian >= fAngle)
		{
			m_NextSTate = ATTACK_BACK;

		}
		else if (112.5*fRadian <= fAngle && 157.5*fRadian >= fAngle)
		{
			m_NextSTate = ATTACK_135;

		}
		else if ((157.5*fRadian <= fAngle && 180.f * fRadian >= fAngle) || (-180.f*fRadian <= fAngle && -157.f*fRadian >= fAngle))
		{
			m_NextSTate = ATTACK_LEFT;
		}
		else if (-157.5f*fRadian <= fAngle && -112.5*fRadian >= fAngle)
		{
			m_NextSTate = ATTACK_225;
		}
		else if (-112.5*fRadian <= fAngle && -67.5*fRadian >= fAngle)
		{
			m_NextSTate = ATTACK_FRONT;
		}
		else if (-67.5*fRadian <= fAngle && -22.5*fRadian >= fAngle)
		{
			m_NextSTate = ATTACK_315;
		}

		m_fAngle = fAngle;
	}
	else if (true == m_bHit && m_NextSTate != DEAD)
	{
		m_NextSTate = HIT;
	}
	//else if(HIT == m_CurState &&)
}

void CArcher::Create_Arrow()
{
	//�� �ѹ� ����.
	if ((ATTACK_LEFT == m_CurState || ATTACK_RIGHT == m_CurState || ATTACK_BACK == m_CurState || ATTACK_45 == m_CurState || ATTACK_135 == m_CurState)
		&& 3 == m_tFrame.iStartFrame && 1 == m_iArrowNum)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"ArcherAttackRelease", CSoundMgr::CHANNELID::MONSTER);
		TFPOINT tPoint{};
		tPoint.fX = m_tPoint.fX + 50*cosf(m_fAngle);
		tPoint.fY = m_tPoint.fY - 50*sinf(m_fAngle);
		CGameObject* pArrow = CArrow::Create(tPoint);
		CGameObject_Manager::Get_Instacne()->Add_Game_Object_Manager(pArrow, GAMEOBJECT::UPDATE_ID::MONSTER_ARMOR);

		m_iArrowNum -= 1;
		//�̰� ��ǥ �����༭ �־���� ��.
	}
	else if ((ATTACK_FRONT == m_CurState || ATTACK_225 == m_CurState || ATTACK_315 == m_CurState) && 6 == m_tFrame.iStartFrame && 1 == m_iArrowNum)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"ArcherAttackRelease", CSoundMgr::CHANNELID::MONSTER);
		TFPOINT tPoint{};
		tPoint.fX = m_tPoint.fX + 50 * cosf(m_fAngle);
		tPoint.fY = m_tPoint.fY - 50 * sinf(m_fAngle);
		CGameObject* pArrow = CArrow::Create(tPoint);
		CGameObject_Manager::Get_Instacne()->Add_Game_Object_Manager(pArrow, GAMEOBJECT::UPDATE_ID::MONSTER_ARMOR);
		m_iArrowNum -= 1;
	}

}

void CArcher::Collision_Player()
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
