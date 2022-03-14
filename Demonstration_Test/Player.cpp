#include "stdafx.h"
#include "Player.h"
#include "Bitmap_Manager.h"
#include "Key_Manager.h"
#include "Scroll_Manager.h"
#include "Skil.h"
#include "Skil_Manager.h"
#include "Slash.h"
#include "Dash.h"
#include "EarthShield.h"
#include "IceSpin.h"
#include "SoundMgr.h"

CPlayer::CPlayer()
	:m_CurState(IDLE),
	m_szRobe(nullptr),
	m_iAttackCombo(0),
	m_iSlash(0),
	m_dwWallCount(0),
	m_dwIceSpinCount(0)
{
}

CPlayer::~CPlayer()
{
}

CGameObject * CPlayer::Create()
{
	CGameObject* pInstance = new CPlayer;
	if (0 > pInstance->Ready_GameObject())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

CGameObject * CPlayer::Create(LPVOID pVoid)
{
	CGameObject* pInstance = new CPlayer;
	if (0 > pInstance->Ready_GameObject())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

int CPlayer::Ready_GameObject()
{
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard1_3.bmp", L"Player1");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard2.bmp", L"Player2");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard3.bmp", L"Player3");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard4.bmp", L"Player4");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard5.bmp", L"Player5");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard6.bmp", L"Player6");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard7.bmp", L"Player7");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard8.bmp", L"Player8");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard9.bmp", L"Player9");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard10.bmp", L"Player10");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard11.bmp", L"Player11");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard12.bmp", L"Player12");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard13.bmp", L"Player13");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard14.bmp", L"Player14");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard15.bmp", L"Player15");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard16.bmp", L"Player16");
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Player/NewWizard17.bmp", L"Player17");

	m_iMaxHp = 500;
	m_iHp = m_iMaxHp;

	m_iMaxMp = 100;
	m_iMp = 0;
	m_iDamage = 20;
	//m_tInfo.iHp = 350;
	//m_tInfo.iMp = 100;
	m_fSpeed = 5.f;
	m_tPoint.iCX = 96;
	m_tPoint.iCY = 96;

	m_tPoint.fX = 500.f;
	m_tPoint.fY = 300.f;

	m_tFrame.iStartFrame = 0;
	m_tFrame.iEndFrame = 0;
	m_tFrame.iState = 10;
	m_tFrame.dwSpeed = 5;
	m_tFrame.dwTime = GetTickCount();

	m_dwWallCount = GetTickCount();
	m_dwSlashCount = GetTickCount();
	return READY_OK;
}

void CPlayer::FrameChange()
{
	if (m_CurState != m_NextState)
	{
		switch (m_NextState)
		{
		case CPlayer::IDLE:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 0;
			m_tFrame.iState = 10;
			m_tFrame.dwSpeed = 5;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::IDLE_LEFT:
			m_tFrame.iStartFrame = 3;
			m_tFrame.iEndFrame = 3;
			m_tFrame.iState = 10;
			m_tFrame.dwSpeed = 5;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::IDLE_RIGHT:
			m_tFrame.iStartFrame = 1;
			m_tFrame.iEndFrame = 1;
			m_tFrame.iState = 10;
			m_tFrame.dwSpeed = 5;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::IDLE_BACK:
			m_tFrame.iStartFrame = 2;
			m_tFrame.iEndFrame = 2;
			m_tFrame.iState = 10;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::WALK_LEFT:
			m_tFrame.iStartFrame = 4;
			m_tFrame.iEndFrame = 13;
			m_tFrame.iState = 10;
			m_tFrame.dwSpeed = 40;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::WALK_RIGHT:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 9;
			m_tFrame.iState = 2;
			m_tFrame.dwSpeed = 40;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::WALK_FRONT:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 9;
			m_tFrame.iState = 1;
			m_tFrame.dwSpeed = 40;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::WALK_BACK:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 9;
			m_tFrame.iState = 0;
			m_tFrame.dwSpeed = 40;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::ATTACK_NOMAL_FRONT:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 8;
			m_tFrame.iState = 7;
			m_tFrame.dwSpeed = 40;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::ATTACK_NOMAL_LEFT:
			m_tFrame.iStartFrame = 9;
			m_tFrame.iEndFrame = 17;
			m_tFrame.iState = 11;
			m_tFrame.dwSpeed = 40;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::ATTACK_NOMAL_RIGHT:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 8;
			m_tFrame.iState = 11;
			m_tFrame.dwSpeed = 40;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::ATTACK_NOMAL_BACK:
			m_tFrame.iStartFrame = 0;
			m_tFrame.iEndFrame = 10;
			m_tFrame.iState = 8;
			m_tFrame.dwSpeed = 40;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::DASH_BACK:
			m_tFrame.iState = 6;
			m_tFrame.iStartFrame = 18;
			m_tFrame.iEndFrame = 18;
			m_tFrame.dwSpeed = 40;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::DASH_FRONT:
			m_tFrame.iState = 9;
			m_tFrame.iStartFrame = 17;
			m_tFrame.iEndFrame = 17;
			m_tFrame.dwSpeed = 40;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::DASH_LEFT:
			m_tFrame.iState = 7;
			m_tFrame.iStartFrame = 15;
			m_tFrame.iEndFrame = 15;
			m_tFrame.dwSpeed = 40;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::DASH_RIGHT:
			m_tFrame.iState = 8;
			m_tFrame.iStartFrame = 15;
			m_tFrame.iEndFrame = 15;
			m_tFrame.dwSpeed = 40;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::FALL:
			m_tFrame.iState = 10;
			m_tFrame.iStartFrame = 19;
			m_tFrame.iEndFrame = 19;
			m_tFrame.dwSpeed = 40;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::DIE:
			m_tFrame.iState = 6;
			m_tFrame.iStartFrame = 9;
			m_tFrame.iEndFrame = 15;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		default:
			break;
		}
		m_CurState = m_NextState;

		//ATTACK_NOMAL_FRONT,
		//	ATTACK_NOMAL_LEFT,
		//	ATTACK_NOMAL_RIGHT,
		//	ATTACK_NOMAL_BACK

	}
}

void CPlayer::MoveFrame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iStartFrame;
		m_tFrame.dwTime = GetTickCount();
	}
	if (m_tFrame.iStartFrame >= m_tFrame.iEndFrame)
	{
		if (IDLE_RIGHT == m_CurState)
		{
			m_tFrame.iStartFrame = 1;
		}
		else if (IDLE_BACK == m_CurState)
		{
			m_tFrame.iStartFrame = 2;
		}
		else if (IDLE_LEFT == m_CurState)
		{
			m_tFrame.iStartFrame = 3;
		}
		else if (WALK_LEFT == m_CurState)
		{
			m_tFrame.iStartFrame = 4;
		}
		//else if (ATTACK_NOMAL_LEFT == m_CurState)
		//{
		//	m_tFrame.iStartFrame = 9;
		//}
		else if (ATTACK_NOMAL_BACK == m_CurState  ||
				 ATTACK_NOMAL_LEFT == m_CurState  ||
				 ATTACK_NOMAL_RIGHT == m_CurState ||
				 ATTACK_NOMAL_FRONT == m_CurState     )
		{
			if (m_tFrame.iStartFrame >= m_tFrame.iEndFrame)
			{
				if (ATTACK_NOMAL_BACK == m_CurState)
				{
					m_NextState = IDLE_BACK;
				}
				if (ATTACK_NOMAL_LEFT == m_CurState)
				{
					m_NextState = IDLE_LEFT;
				}
				if (ATTACK_NOMAL_RIGHT == m_CurState)
				{
					m_NextState = IDLE_RIGHT;
				}
				if (ATTACK_NOMAL_FRONT == m_CurState)
				{
					m_NextState = IDLE;
				}
			}
		}
		else if (DASH_BACK == m_CurState)
		{
			m_tFrame.iStartFrame = 18;
		}
		else if(DASH_FRONT == m_CurState)
		{
			m_tFrame.iStartFrame = 17;
		}
		else if (DASH_LEFT == m_CurState)
		{
			m_tFrame.iStartFrame = 15;
		}
		else if (DASH_RIGHT == m_CurState)
		{
			m_tFrame.iStartFrame = 15;
		}
		else if (FALL == m_CurState && m_tInfo.bDash == false)
		{
			CScroll_Manager::Get_Instacne()->Set_ScrollX(-(m_DashOldPoint.fX-m_tPoint.fX));
			CScroll_Manager::Get_Instacne()->Set_ScrollY(-(m_DashOldPoint.fY - m_tPoint.fY));
			m_tPoint.fX = m_DashOldPoint.fX;
			m_tPoint.fY = m_DashOldPoint.fY;

			m_NextState = IDLE;
			m_bFall = false;
			//m_tFrame.iStartFrame = 20;
		}
		else if (DIE == m_CurState)
		{
			return;
		}
		else
		{
			m_tFrame.iStartFrame = 0;
		}
	}
	//여기서 enum 상태 체크하고 enum에 따라서 시작 위치 바꿔주기.
	//그리고 대쉬 같은 건 한번만 재생되고 끝나야되니까 생각포인트 잘 잡아주기.
}

void CPlayer::Move()
{
	if (true == m_bWall)
	{
		m_fSpeed = 0.f;
	}
	else if (true == m_bFall && false == m_tInfo.bDash)
	{
		m_fSpeed = 0.f;
		m_NextState = FALL;
		/*여기서 죽음 처리 or 피가 떨어지는 처리.*/
	}
	else if(false == m_bWall)
	{
		m_fSpeed = 5.f;
	}	// 이거 나중에 대쉬 쓸 때 중첩돼서 오류 날 수 있으니까 잘 새겨두기. 아니면 대쉬에선 가속도 주면 될 것 같기도 하고. 생각 잘하자!
	 

	if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_W))
	{
		m_NextState = WALK_BACK;
		m_NextState = WALK_BACK;
		m_tPoint.fY -= m_fSpeed;
		CScroll_Manager::Get_Instacne()->Set_ScrollY(m_fSpeed);
	}
	if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_S))
	{
		m_NextState = WALK_FRONT;
		m_tPoint.fY += m_fSpeed;
		CScroll_Manager::Get_Instacne()->Set_ScrollY(-m_fSpeed);

	}
	if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_A))
	{
		m_NextState = WALK_LEFT;
		m_tPoint.fX -= m_fSpeed;
		CScroll_Manager::Get_Instacne()->Set_ScrollX(m_fSpeed);
	}

	if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_D))
	{
		m_NextState = WALK_RIGHT;
		m_tPoint.fX += m_fSpeed;
		CScroll_Manager::Get_Instacne()->Set_ScrollX(-m_fSpeed);

	}

	if (CKey_Manager::Get_PlayerKey()->Key_Up(KEY_D))
	{
		m_NextState = IDLE_RIGHT;
	}
	if (CKey_Manager::Get_PlayerKey()->Key_Up(KEY_W))
	{
		m_NextState = IDLE_BACK;
	}
	if (CKey_Manager::Get_PlayerKey()->Key_Up(KEY_S))
	{
		m_NextState = IDLE;
	}
	if (CKey_Manager::Get_PlayerKey()->Key_Up(KEY_A))
	{
		m_NextState = IDLE_LEFT;
	}

	//이미지 상태가 요상한데?
}

void CPlayer::Skil_Slash()
{
	if (CKey_Manager::Get_PlayerKey()->Key_Down(KEY_LBUTTON) /*|| CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_LBUTTON)*/)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CHANNELID::EFFECT);
		if (m_dwSlashCount + 500 < GetTickCount())
		{
			m_iSlash++;
			m_dwSlashCount = GetTickCount();
		}

		m_tInfo.bNomalAtt = true;

		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
		int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

		pt.x -= iScrollX;
		pt.y -= iScrollY;

		float fBase = pt.x - m_tPoint.fX;
		float fHight = pt.y - m_tPoint.fY;
		float fDistance = sqrtf(fBase*fBase + fHight*fHight);

		float fAngle = acosf(fBase / fDistance);

		if (pt.y >= m_tPoint.fY)
			fAngle *= -1.f;

		float fRadian = PI / 180.f;

		if (-45 * fRadian <= fAngle && 45 * fRadian >= fAngle)
		{
			m_NextState = ATTACK_NOMAL_RIGHT;
		}
		else if (45 * fRadian <= fAngle && 135 * fRadian >= fAngle)
		{
			m_NextState = ATTACK_NOMAL_BACK;
		}
		else if ((135 * fRadian <= fAngle && 180 * fRadian >= fAngle) || (-180 * fRadian <= fAngle && -135 * fRadian >= fAngle))
		{
			m_NextState = ATTACK_NOMAL_LEFT;
		}
		else if (-135 * fRadian <= fAngle && -45 * fRadian >= fAngle)
		{
			m_NextState = ATTACK_NOMAL_FRONT;
		}

				//end가 되기 전에 쓰면 라지 슬래쉬가 나가는 구먼..

		if (false == m_bWall)
		{
			m_tPoint.fX += 10 * cos(fAngle);
			m_tPoint.fY -= 10 * sin(fAngle);
		}



		CSkil* pObj = CSlash::Create(m_iSlash); //ready가 여기 들어가서 그렇구먼
		CSkil_Manager::Get_Instacne()->Add_Skil(pObj, GAMEOBJECT::UPDATE_SKIL::NORMAL);
		CSoundMgr::Get_Instance()->PlaySound(L"WindSlashBasic.wav", CSoundMgr::CHANNELID::EFFECT);
	}
	if (CKey_Manager::Get_PlayerKey()->Key_Up(KEY_LBUTTON))
	{
		if (3 <= m_iSlash)
		{
			if (ATTACK_NOMAL_BACK == m_CurState)
			{
				m_NextState = IDLE_BACK;
			}
			if (ATTACK_NOMAL_LEFT == m_CurState)
			{
				m_NextState = IDLE_LEFT;
			}
			if (ATTACK_NOMAL_RIGHT == m_CurState)
			{
				m_NextState = IDLE_RIGHT;
			}
			if (ATTACK_NOMAL_FRONT == m_CurState)
			{
				m_NextState = IDLE;
			}
		}
		m_tInfo.bNomalAtt = false;
	}

	if (3 <= m_iSlash)
	{
		m_iSlash = 0;
	}


}

void CPlayer::Skil_Dash()
{
	if (CKey_Manager::Get_PlayerKey()->Key_Down(KEY_SPACE) && false == m_tInfo.bDash)
	{

		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::DASH);
		CSoundMgr::Get_Instance()->PlaySound(L"WindSnap.wav", CSoundMgr::CHANNELID::DASH);
		int iDashRange = 200;

		//float m_fAngleSpeed = 2.f;
		if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_W))
		{
			m_fAngle = 90.f * (PI / 180.f);

			if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_A))
			{
				m_fAngle = 135 * (PI / 180.f);
				m_NextState = DASH_135;
			}
			else if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_D))
			{
				m_fAngle = 45 * (PI / 180.f);
				m_NextState = DASH_45;
			}
			else
			{
				m_NextState = DASH_BACK;
			}
			//DASH_45,
			//	DASH_135,
			//	DASH_225,
			//	DASH_315,

		}
		else if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_A))
		{
			m_fAngle = 180.f * (PI / 180.f);

			if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_W))
			{
				m_fAngle = 135.f*(PI / 180.f);
				m_NextState = DASH_45;
			}
			else if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_S))
			{
				m_fAngle = 225.f*(PI / 180.f);
				m_NextState = DASH_225;
			}
			else
			{
				m_NextState = DASH_LEFT;
			}
		}
		else if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_S))
		{
			m_fAngle = 270.f * (PI / 180.f);
			if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_A))
			{
				m_fAngle = 225.f*(PI / 180.f);
				m_NextState = DASH_225;
			}
			else if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_D))
			{
				m_fAngle = 315.f*(PI / 180.f);
				m_NextState = DASH_315;
			}
			else
			{
				m_NextState = DASH_FRONT;
			}
		}
		else if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_D))
		{
			m_fAngle = 0.f * (PI / 180.f);

			if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_W))
			{
				m_fAngle = 45.f*(PI / 180.f);
				m_NextState = DASH_45;
			}
			else if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_S))
			{
				m_fAngle = 315.f*(PI / 180.f);
				m_NextState = DASH_315;
			}
			else
			{
				m_NextState = DASH_RIGHT;
			}
		}


		m_DashPoint.fX = m_tPoint.fX + iDashRange * cosf(m_fAngle);
		m_DashPoint.fY = m_tPoint.fY - iDashRange * sinf(m_fAngle);

		m_OldState = m_CurState;
		m_tInfo.bDash = true;
		m_dwDashCount = GetTickCount();

		m_DashOldPoint.fX = m_tPoint.fX;
		m_DashOldPoint.fY = m_tPoint.fY;

	}

	////떨어지기 전 좌표 저장용
	//if (false == m_tInfo.bDash && false == m_bFall)
	//{
	//}

	if (true == m_tInfo.bDash)
	{
		float iSpeed = 0;
		if (false == m_bWall)
		{
			iSpeed = 11.2f;
		}
		//else if (true == m_bFall)
		//{
		//	iSpeed = 0;
		//}
		else if (true == m_bWall)
		{
			iSpeed = 0;
		}

		if (DASH_BACK == m_CurState)
		{

			if (m_tPoint.fY > m_DashPoint.fY)	// 앵클이 ~~ 일 때나..음..두 점사이의 거리 공식..이용하거나.. 스토커? 이용해도 될 것 같구
			{
				m_tPoint.fY -= iSpeed;
				CScroll_Manager::Get_Instacne()->Set_ScrollY(iSpeed);
			}
		}
		else if (DASH_FRONT == m_CurState)
		{
			if (m_tPoint.fY < m_DashPoint.fY)
			{
				m_tPoint.fY += iSpeed;
				CScroll_Manager::Get_Instacne()->Set_ScrollY(-iSpeed);
			}
		}
		else if (DASH_LEFT == m_CurState)
		{
			if (m_tPoint.fX > m_DashPoint.fX)
			{
				m_tPoint.fX -= iSpeed;
				CScroll_Manager::Get_Instacne()->Set_ScrollX(iSpeed);
			}
		}
		else if (DASH_RIGHT == m_CurState)
		{
			if (m_tPoint.fX < m_DashPoint.fX)
			{
				m_tPoint.fX += iSpeed;
				CScroll_Manager::Get_Instacne()->Set_ScrollX(-iSpeed);
				// 삼각함수나 대각선 길이 점 찍어서 날아가는 것도 만들어줘야 할 듯
			}
		}
		else if (DASH_45 == m_CurState)
		{
			if (m_tPoint.fX <m_DashPoint.fX && m_tPoint.fY >m_DashPoint.fY)
			{
				m_tPoint.fX += iSpeed;
				m_tPoint.fY -= iSpeed;
				CScroll_Manager::Get_Instacne()->Set_ScrollX(-iSpeed);
				CScroll_Manager::Get_Instacne()->Set_ScrollY(iSpeed);
			}
		}
		else if (DASH_135 == m_CurState)
		{
			if (m_tPoint.fX > m_DashPoint.fX && m_tPoint.fY > m_DashPoint.fY)
			{
				m_tPoint.fX -= iSpeed;
				m_tPoint.fY -= iSpeed;
				CScroll_Manager::Get_Instacne()->Set_ScrollX(iSpeed);
				CScroll_Manager::Get_Instacne()->Set_ScrollY(iSpeed);
			}
		}
		else if (DASH_225 == m_CurState)
		{
			if (m_tPoint.fX > m_DashPoint.fX && m_tPoint.fY < m_DashPoint.fY)
			{
				m_tPoint.fX -= iSpeed;
				m_tPoint.fY += iSpeed;
				CScroll_Manager::Get_Instacne()->Set_ScrollX(iSpeed);
				CScroll_Manager::Get_Instacne()->Set_ScrollY(-iSpeed);
			}
		}
		else if (DASH_315 == m_CurState)
		{
			if (m_tPoint.fX < m_DashPoint.fX && m_tPoint.fY < m_DashPoint.fY)
			{
				m_tPoint.fX += iSpeed;
				m_tPoint.fY += iSpeed;
				CScroll_Manager::Get_Instacne()->Set_ScrollX(-iSpeed);
				CScroll_Manager::Get_Instacne()->Set_ScrollY(-iSpeed);
			}
		}
		

		if (m_dwDashCount + 300 < GetTickCount() && true == m_tInfo.bDash)
		{
			m_tInfo.bDash = false;
			if (m_bFall == true)
			{
				m_NextState = FALL;
			}
			else if (IDLE_BACK == m_OldState || WALK_BACK == m_OldState)
			{
				m_NextState = IDLE_BACK;
			}
			else if (IDLE_LEFT == m_OldState || WALK_LEFT == m_OldState)
			{
				m_NextState = IDLE_LEFT;
			}
			else if (IDLE_RIGHT == m_OldState || WALK_RIGHT == m_OldState)
			{
				m_NextState = IDLE_RIGHT;
				// 우선 이렇게 해줬는데 대각선으로 날아갈 거 상정해서
				// 삼각함수나 대각선 길이 점 찍어서 날아가는 것도 만들어줘야 할 듯
			}
			else if (IDLE == m_OldState || WALK_FRONT == m_OldState)
			{
				m_NextState = IDLE;
			}
		}
	}
}

void CPlayer::Skil_Shield()
{
   	if (CKey_Manager::Get_PlayerKey()->Key_Down(KEY_RBUTTON) && false == m_tInfo.bMagicAtt && m_iMp >= 20)
	{
		m_iMp -= 20;
		//CSkil* pObj = CEarthShield::Create(30*(PI / 180.f));
		//CSkil_Manager::Get_Instacne()->Add_Skil(pObj, GAMEOBJECT::UPDATE_SKIL::MAGIC);
		for (int i = 0; i <= 180; i = i + 30)
		{
			CSkil* pObj = CEarthShield::Create(i*(PI / 180.f));
			CSkil_Manager::Get_Instacne()->Add_Skil(pObj, GAMEOBJECT::UPDATE_SKIL::MAGIC);
		}
		for (int i = -150; i <= -30; i = i + 30)
		{
			CSkil* pObj = CEarthShield::Create(i*(PI / 180.f));
			CSkil_Manager::Get_Instacne()->Add_Skil(pObj, GAMEOBJECT::UPDATE_SKIL::MAGIC);
		}
		m_tInfo.bMagicAtt = true;
		m_dwShieldCount = GetTickCount();
	}
	if (true == m_tInfo.bMagicAtt && m_dwShieldCount +5000 <GetTickCount())
	{
		m_tInfo.bMagicAtt = false;
	}
	// 이거 스킬 사용 텀 해주려고 넣어준거네요.
}

void CPlayer::Skil_IceSpin()
{
	if (CKey_Manager::Get_PlayerKey()->Key_Down(KEY_Q) && m_iMp >= 20 )
	{
		m_iMp -= 20;
		for (int i = 0; i <= 360; i = i + 90)
		{
			CSkil* pObj = CIceSpin::Create(i * (PI/180.f));
			CSkil_Manager::Get_Instacne()->Add_Skil(pObj, GAMEOBJECT::UPDATE_SKIL::FINAL);
		}
		m_dwIceSpinCount = GetTickCount();
		m_bIceSpinPattern = true;
	}

	if (m_dwIceSpinCount + 200 < GetTickCount() && m_dwIceSpinCount + 210 >GetTickCount())
	{
		m_bIceSpinPattern = true;
	}
	else if (m_dwIceSpinCount + 800 < GetTickCount() && m_dwIceSpinCount + 810 > GetTickCount())
	{
		m_bIceSpinPattern = true;
	}
	else if (m_dwIceSpinCount + 1400 < GetTickCount() && m_dwIceSpinCount + 1410 > GetTickCount())
	{
		m_bIceSpinPattern = true;
	}

	if (m_dwIceSpinCount + 2000 > GetTickCount() && true == m_bIceSpinPattern)
	{
		for (int i = 0; i <= 360; i = i + 90)
		{
			CSkil* pObj = CIceSpin::Create(i * (PI / 180.f));
			CSkil_Manager::Get_Instacne()->Add_Skil(pObj, GAMEOBJECT::UPDATE_SKIL::FINAL);
		}
		m_bIceSpinPattern = false;
	}

	//else if (m_dwIceSpinCount + 150 > GetTickCount() && m_dwIceSpinCount + 100 < GetTickCount())
	//{
	//	for (int i = 0; i <= 360; i = i + 90)
	//	{
	//		CSkil* pObj = CIceSpin::Create(i * (PI / 180.f));
	//		CSkil_Manager::Get_Instacne()->Add_Skil(pObj, GAMEOBJECT::UPDATE_SKIL::FINAL);
	//	}
	//}
}

void CPlayer::ScrollMove()
{
	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();
	if ((WINCX >> 1) < m_tPoint.fX + iScrollX + 10)
	{
		CScroll_Manager::Get_Instacne()->Set_ScrollX(-m_fSpeed);
	}
	if ((WINCX >> 1) > m_tPoint.fX + iScrollX - 10)
	{
		CScroll_Manager::Get_Instacne()->Set_ScrollX(m_fSpeed);
	}
	if ((WINCY >> 1) < m_tPoint.fY + iScrollY + 10)
	{
		CScroll_Manager::Get_Instacne()->Set_ScrollY(-m_fSpeed);
	}
	if ((WINCY >> 1) > m_tPoint.fY + iScrollY - 10)	//중심 걸어주는것.
	{
		CScroll_Manager::Get_Instacne()->Set_ScrollY(m_fSpeed);
	}
}

int CPlayer::Update_GameObject()
{
	if (m_iMaxHp <= m_iHp)
	{
		m_iHp = m_iMaxHp;
	}
	if (m_iMaxMp <= m_iMp)
	{
		m_iMp = m_iMaxMp;
	}


	if (m_CurState == DIE && m_tFrame.iStartFrame > m_tFrame.iEndFrame)
	{
		return OBJ_DEAD;
	}
	
	CKey_Manager::Get_PlayerKey()->Key_Update();
	if (false == m_tInfo.bNomalAtt && false == m_tInfo.bDash)
	{
		Move();
	}
	if (CKey_Manager::Get_PlayerKey()->Key_Down(KEY_E))
	{
		m_iHp -= 100;
	}
	Skil_Slash();	// 보완 할 것.  이건 어차피 계속 반복할게 아니라 End에 닿으면 idle로 바뀌도록 만들어도 될 것 같아.
	Skil_Dash();
	Skil_Shield();
	Skil_IceSpin();
	if (m_iHp <= 0)
	{
		m_NextState = DIE;
	}
	//나중에 플레이어 int 변수로 받고 넘겨주는 형식으로 죽는 판정 낼 수 있을 듯.
	return OBJ_NOEVENT;
}

void CPlayer::Late_GamceObject()
{
	MoveFrame();
	FrameChange();
	ScrollMove();	// 이걸로 지진 조정해줘야돼...
}

void CPlayer::Render_GameObject(HDC hDC)
{
	if (m_iMaxHp <= m_iHp)
	{
		m_iHp = m_iMaxHp;
	}
	if (m_iMaxMp <= m_iMp)
	{
		m_iMp = m_iMaxMp;
	}

	CGameObject::Update_Rect();
	HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"Player1");
	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();
	//Rectangle(hDC, m_tRect.left + iScrollX , m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom+ iScrollY);

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	//HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	//HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	//그림자
	Ellipse(hDC, m_tRect.left + iScrollX  + 20, m_tRect.bottom + iScrollY - 25, m_tRect.right + iScrollX - 20, m_tRect.bottom + iScrollY);
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		m_tPoint.iCX, m_tPoint.iCY,
		hMemDC,
		m_tFrame.iStartFrame*m_tPoint.iCX, m_tFrame.iState*m_tPoint.iCY,
		m_tPoint.iCX, m_tPoint.iCY,
		RGB(255, 0, 255));

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	//MoveToEx(hDC, m_DashPoint.fX + iScrollX, m_DashPoint.fY + iScrollY, nullptr);
	//LineTo(hDC, m_tPoint.fX + iScrollX, m_tPoint.fY + iScrollY);
	//Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CPlayer::Release_GameObject()
{
}

