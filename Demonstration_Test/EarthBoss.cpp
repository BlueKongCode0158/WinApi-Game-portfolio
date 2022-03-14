#include "stdafx.h"
#include "EarthBoss.h"
#include "Bitmap_Manager.h"
#include "GameObject_Manager.h"
#include "Scroll_Manager.h"
#include "Earth_Pillar.h"
#include "Throwing_Stones.h"
#include "Key_Manager.h"
#include "Player.h"
#include "Font_Damage.h"
#include "Font_Damage_Manager.h"
#include "UI_Manager.h"
#include "MyUI.h"
#include "BossBackGround.h"
#include "BossHp_Bar.h"

CEarthBoss::CEarthBoss()
	:m_iCratePillar(0),
	m_dwPunchTime(0),
	m_bPillar(false),
	m_dwPillarCount(0)
{
}

CEarthBoss::~CEarthBoss()
{
}

CGameObject * CEarthBoss::Create()
{
	CGameObject* pInstace = new CEarthBoss;
	if (0 > pInstace->Ready_GameObject())
	{
		Safe_Delete(pInstace);
	}
	return pInstace;
}

void CEarthBoss::AnimationState()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case STATE::BOSS_ATTACK_BACK:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 3;
			m_tFrame.iState = 3;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::BOSS_ATTACK_FRONT:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 3;
			m_tFrame.iState = 1;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::BOSS_ATTACK_LEFT:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 3;
			m_tFrame.iState = 8;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::BOSS_ATTACK_RIGHT:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 3;
			m_tFrame.iState = 2;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::BOSS_JUMPFALL:
			m_tFrame.iStartFrame = 2;
			m_tFrame.iEndFrame = 2;
			m_tFrame.iState = 7;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::BOSS_HIT:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 4;
			m_tFrame.iState = 6;
			m_tFrame.dwSpeed = 250;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::BOSS_IDLE:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 0;
			m_tFrame.iState = 0;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::BOSS_JUMP:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 1;
			m_tFrame.iState = 7;
			m_tFrame.dwSpeed = 700;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::BOSS_RUSH:
			break;
		case STATE::BOSS_SCATTER:
			m_tFrame.iStartFrame = 2;
			m_tFrame.iEndFrame = 7;
			m_tFrame.iState = 0;
			m_tFrame.dwSpeed = 250;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::BOSS_FAILED:
			m_tFrame.iStartFrame = 8;
			m_tFrame.iEndFrame = 9;
			m_tFrame.iState = 0;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		default:
			break;
		}
		m_eCurState = m_eNextState;
	}
}

void CEarthBoss::Boss_Scatter()
{

}

void CEarthBoss::Boss_Pillar()
{
	//이거 텀 줘야겠다..
	if (m_dwSkil_Pillar + 50 < GetTickCount() && true == m_bPillar)
	{
		if (m_iCratePillar > 500)
		{
			m_iCratePillar = 0;
			CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
			if (nullptr == pObj)
			{
				return;
			}
			m_fPillarfX = pObj->Get_tPoint()->fX;
			m_fPillarfY = pObj->Get_tPoint()->fY;
		}


		m_iCratePillar += 40;
		m_eNextState = CEarthBoss::STATE::BOSS_SCATTER;

		float fBase = m_fPillarfX - m_tPoint.fX;
		float fHight = m_fPillarfY - m_tPoint.fY;
		float fDist = sqrtf(fBase*fBase + fHight*fHight);

		float fDistAngle = acosf(fBase / fDist) * (180.f / PI);

		if (m_tPoint.fY < m_fPillarfY)
		{
			fDistAngle *= -1.f;
		}


		for (int i = fDistAngle; i <= 360; i+=80 )
		{
			float fAngle = i * (PI / 180.f);
			CGameObject* pObj = CEarth_Pillar::Create(fAngle, m_iCratePillar);
			CGameObject_Manager::Get_Instacne()->Add_Game_Object_Manager(pObj, GAMEOBJECT::UPDATE_ID::BOSSSKIL);
		}
		m_dwSkil_Pillar = GetTickCount();
	}
}

void CEarthBoss::Boss_Punch()
{
	if (m_dwPunch + 3000 < GetTickCount())
	{
		if (m_dwPunchTime < 1500)
		{
			m_dwPunchTime = 500;
		}

		m_eNextState = CEarthBoss::STATE::BOSS_SCATTER;
		int iDist = 50;
		float fX = 0;
		float fY = 0;
		for (int i = 120; i <= 360; i += 120)
		{
			fX = m_tPoint.fX + 80 * cosf(i*(PI / 180.f));
			fY = m_tPoint.fY - 80 * sinf(i*(PI / 180.f));
			CGameObject* pObj = CThrowing_Stones::Create();
			pObj->Set_tPoint(fX,fY);
			dynamic_cast<CThrowing_Stones*>(pObj)->Set_ShotTime(m_dwPunchTime);
			CGameObject_Manager::Get_Instacne()->Add_Game_Object_Manager(pObj, GAMEOBJECT::UPDATE_ID::BOSSSKIL);

			m_dwPunchTime += 1000;
		}
		//원인이 뭘까..
		m_dwPunch = GetTickCount();
	}
}

void CEarthBoss::Boss_Jump()
{
	if ((m_dwJumpTime + 3000 < GetTickCount()) && false == m_bJump)
	{
		m_bJump = true;
		m_dwJumpIsTime = GetTickCount();
	}
	if (true == m_bJump)
	{
		m_eNextState = CEarthBoss::STATE::BOSS_JUMP;
		m_fAccel += 0.20f;
		m_tPoint.fY -= m_fJumpPower * m_fAccel - m_fGravity * m_fAccel * m_fAccel * 0.5f;

		if (m_fOldfY < m_tPoint.fY)
		{
			m_eNextState = CEarthBoss::STATE::BOSS_JUMPFALL;
		}

		m_fOldfY = m_tPoint.fY;
		m_tPoint.fX = m_fSaveX;
		RECT tRECT{};

		if (IntersectRect(&tRECT,&m_tShadowRect,&m_tRect) && m_dwJumpIsTime + 300 < GetTickCount())
		{
			m_bJump = false;
			m_fAccel = 0.f;
			m_tPoint.fY = m_fSaveY - 50;
			m_dwJumpTime = GetTickCount();
			m_eNextState = CEarthBoss::STATE::BOSS_IDLE;

			CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
			if (nullptr == pObj)
			{
				return;
			}
			if (true == dynamic_cast<CPlayer*>(pObj)->Get_Info()->bDash)
			{
				return;
			}
			else
			{
				pObj->Set_SubHP(40);
				
				CFont_Damage* pFont = CFont_Damage::Create();
				TFPOINT tfPoint{};
				tfPoint.fX = pObj->Get_tPoint()->fX - 10;
				tfPoint.fY = pObj->Get_tPoint()->fY - 10;
				pFont->Set_Point(tfPoint);
				pFont->Set_Damage(40);
				pFont->Set_Color(255, 0, 0);
				CFont_Damage_Manager::Get_Instance()->Add_Font_Damage(pFont);
			}
		}
	}


}

void CEarthBoss::Update_CollisionRect()
{
	if (false == m_bJump)
	{
		m_fSaveX = m_tPoint.fX;
		m_fSaveY = m_tPoint.fY + 50;
	}
	else
	{
		CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
		if (nullptr == pObj)
		{
			return;
		}

		float fBase = pObj->Get_tPoint()->fX - m_fSaveX;
		float fHight = pObj->Get_tPoint()->fY - m_fSaveY;
		float fDist = sqrtf(fBase*fBase + fHight*fHight);

		float fAngle = acosf(fBase / fDist);
		float fSpeed = 2.f;

		if (m_fSaveY < pObj->Get_tPoint()->fY)
		{
			fAngle *= -1.f;
		}

		m_fSaveX += (fSpeed * cosf(fAngle));
		m_fSaveY -= (fSpeed * sinf(fAngle));

	}

	m_tShadowRect.left = m_fSaveX - 30 ;
	m_tShadowRect.top = m_fSaveY - 24;
	m_tShadowRect.right = m_fSaveX + 30 ;
	m_tShadowRect.bottom = m_fSaveY + 24;
}

int CEarthBoss::Ready_GameObject()
{
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Boss/EarthBoss_1.bmp", L"EarthBoss");
	m_eID = CGameObject::MONSTER_ID::BOSS;

	m_bJump = false;
	m_iMaxHp = 2000;
	m_iHp = m_iMaxHp;

	m_tFrame.iStartFrame = 0;
	m_tFrame.iEndFrame = 0;
	m_tFrame.iState = 0;
	m_tFrame.dwSpeed = 500;
	m_tFrame.dwTime = GetTickCount();

	m_tPoint.fX = 730.f;
	m_tPoint.fY = 2670.f;

	m_dwSkil_Pillar = GetTickCount();
	m_dwPatternCount = GetTickCount();
	m_dwPunch = GetTickCount();
	m_dwJumpTime = GetTickCount();

	m_tPoint.iCX = 110;
	m_tPoint.iCY = 128;

	m_fJumpPower = 15.5;
	m_fAccel = 0.f;
	m_fGravity = 4.5f;

	m_bBossFailed = false;
	m_bJump = false;

	CMyUI* pUi = CBossHp_Bar::Create();
	CUI_Manager::Get_Instance()->Add_UI_Object(pUi, UI_OBJECT::GAME_ID::BOSSHP);
	pUi = CBossBackGround::Create();
	CUI_Manager::Get_Instance()->Add_UI_Object(pUi, UI_OBJECT::GAME_ID::BOSSBACKGROUND);
	return READY_OK;
}

int CEarthBoss::Update_GameObject()
{
	if (m_bCollision == true)
	{
		Update_CollisionRect();

		if (CKey_Manager::Get_PlayerKey()->Key_Down(KEY_ESC))
		{
			if (false == m_bJump)
				m_bJump = true;
			else
				m_bJump = false;
		}


		if (m_iHp <= 0 && m_tFrame.iStartFrame > m_tFrame.iEndFrame)
		{
			m_iHp = 0;
			return OBJ_NOEVENT;
		}
		if (m_iHp <= 0)
		{
			m_eNextState = BOSS_FAILED;
			m_bBossFailed = true;		//우선 만들어줌.
			return OBJ_NOEVENT;
		}

		if (false == m_bBossFailed)
		{
			if (m_dwPatternCount + 2000 < GetTickCount() && m_dwPatternCount + 4000 > GetTickCount() && false == m_bJump)
			{
				Boss_Punch();
			}
			else if (m_dwPatternCount + 4000 < GetTickCount() && m_dwPatternCount + 5000 > GetTickCount() && false == m_bJump)
			{

				m_dwPillarCount = GetTickCount();
			}
			else if (m_dwPatternCount + 5000 < GetTickCount() && m_dwPatternCount + 8000 > GetTickCount() && false == m_bJump)
			{
				if (false == m_bPillar && m_dwPillarCount + 500 < GetTickCount())
				{
					m_bPillar = true;
					m_dwPillarCount = GetTickCount();
					m_dwSkil_Pillar = 0;
				}
				else if (true == m_bPillar && m_dwPillarCount + 500 < GetTickCount())
				{
					m_bPillar = false;
					m_dwPillarCount = GetTickCount();
				}
				Boss_Pillar();
			}
			else if (m_dwPatternCount + 8000 < GetTickCount() && m_dwPatternCount + 10000 > GetTickCount() && false == m_bJump)
			{

			}
			else if (m_dwPatternCount + 10000 < GetTickCount() && m_dwPatternCount + 12000 > GetTickCount())
			{
				Boss_Jump();
			}
			else if (m_dwPatternCount + 12500 < GetTickCount())
			{
				m_dwPatternCount = GetTickCount();
				m_dwPunchTime = 0;
				m_iCratePillar = 0;
				m_dwPunch = GetTickCount();
			}

			//if (m_iHp >= 1500)
			//{
			//	if (m_dwPatternCount + 2000 < GetTickCount() && m_dwPatternCount + 4000 > GetTickCount() && false == m_bJump)
			//	{
			//		Boss_Punch();
			//	}
			//	else if (m_dwPatternCount + 4000 < GetTickCount() && m_dwPatternCount + 5000 > GetTickCount() && false == m_bJump)
			//	{

			//		m_dwPillarCount = GetTickCount();
			//	}
			//	else if (m_dwPatternCount + 5000 < GetTickCount() && m_dwPatternCount + 8000 > GetTickCount() && false == m_bJump)
			//	{
			//		if (false == m_bPillar && m_dwPillarCount + 500 < GetTickCount())
			//		{
			//			m_bPillar = true;
			//			m_dwPillarCount = GetTickCount();
			//			m_dwSkil_Pillar = 0;
			//		}
			//		else if(true == m_bPillar && m_dwPillarCount + 500 < GetTickCount())
			//		{
			//			m_bPillar = false;
			//			m_dwPillarCount = GetTickCount();
			//		}
			//		Boss_Pillar();
			//	}
			//	else if (m_dwPatternCount + 8000 < GetTickCount() && m_dwPatternCount + 10000 > GetTickCount() && false == m_bJump)
			//	{

			//	}
			//	else if (m_dwPatternCount + 10000 < GetTickCount() && m_dwPatternCount + 12000 > GetTickCount())
			//	{
			//		Boss_Jump();
			//	}
			//	else if (m_dwPatternCount + 12500 < GetTickCount())
			//	{
			//		m_dwPatternCount = GetTickCount();
			//		m_dwPunchTime = 0;
			//		m_iCratePillar = 0;
			//		m_dwPunch = GetTickCount();
			//	}
			//	//그림자 렉트랑 이미지 렉트가 닿아 있었을 때는 몬스터를 따라가고
			//	//안 닿아 있으면 플레이어 근처로 따라가도록
			//	//그리고 따라갈 경우 해당 그림자가 추락 지점 ㅇㅇ
			//	//Boss_Pillar();
			//	//보스 패턴 넣는 곳
			//	//보스 패턴 전체적으로 조절해줄 겟틱 변수 하나 더 만들기.
			//}
			//else if (m_iHp <= 1500 && m_iHp >= 800)
			//{
			//	//보스 패턴 넣는 곳
			//}
			//else if (m_iHp <= 800 && m_iHp >= 0)
			//{
			//	//보스 패턴 넣는 곳
			//}
		}
	}
	// 애니메이션 활동 변경
	// 및 보스 패턴.
	// 이 이뤄지고 충돌도 이뤄짐.
	// 왜 ? 여기서 충돌 되는거고 충돌과 관련된 애니메이션이 여기서 나오니까.
	return OBJ_NOEVENT;
}

void CEarthBoss::Late_GamceObject()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.iStartFrame += 1;
		m_tFrame.dwTime = GetTickCount();
	}


	if (m_tFrame.iStartFrame > m_tFrame.iEndFrame)
	{
		if (STATE::BOSS_SCATTER == m_eCurState)
		{
			m_tFrame.iStartFrame = 2;
		}
		else if (STATE::BOSS_JUMPFALL == m_eCurState)
		{
			m_tFrame.iStartFrame = 2;
		}
		else if (STATE::BOSS_HIT == m_eCurState)
		{
			m_eNextState = STATE::BOSS_IDLE;
		}
		else if (STATE::BOSS_FAILED == m_eCurState)
		{
			m_tFrame.iStartFrame = 9;
			//m_tFrame.iEndFrame = 9;
			return;
		}
		else
		{
			m_tFrame.iStartFrame = 0;
		}
	}
	AnimationState();
	//애니메이션 스테이트 변경점.
}

void CEarthBoss::Render_GameObject(HDC hDC)
{
	Update_CollisionRect();
	//렌더 하는 부분
	CGameObject::Update_Rect();


	HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"EarthBoss");

	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	Ellipse(hDC, m_tShadowRect.left + iScrollX, m_tShadowRect.top + iScrollY, m_tShadowRect.right + iScrollX, m_tShadowRect.bottom + iScrollY);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		m_tPoint.iCX, m_tPoint.iCY,
		hMemDC,
		m_tFrame.iStartFrame*m_tPoint.iCX, m_tFrame.iState*m_tPoint.iCY,
		m_tPoint.iCX, m_tPoint.iCY,
		RGB(255, 0, 255));
}

void CEarthBoss::Release_GameObject()
{
}
