#include "stdafx.h"
#include "CardEffect.h"
#include "Bitmap_Manager.h"
#include "Scroll_Manager.h"
#include "GameObject_Manager.h"
#include "GameObject.h"

CCardEffect::CCardEffect()
	:m_bCollision(false)
{
}

CCardEffect::~CCardEffect()
{
}

int CCardEffect::Ready_Effect()
{
	// 몬스터 좌표 받아와서 생성할거고
	// 이게 파괴되는 순간? 쯤에 몬스터 생성..음..
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/Card/MonsterCard_2.bmp", L"CardEffect");
	m_tPoint.iCX = 96;
	m_tPoint.iCY = 192;
	m_tFrame.iState = 0;
	m_tFrame.iEndFrame = 29;
	m_tFrame.iStartFrame = 0;
	m_tFrame.dwSpeed = 30;

	m_tRecognizeSize.iCX = 500;
	m_tRecognizeSize.iCY = 500;

	m_tRect_Recognize.left = m_tPoint.fX - (m_tRecognizeSize.iCX >> 1);
	m_tRect_Recognize.top = m_tPoint.fY - (m_tRecognizeSize.iCY >> 1);
	m_tRect_Recognize.right = m_tPoint.fX + (m_tRecognizeSize.iCX >> 1);
	m_tRect_Recognize.bottom = m_tPoint.fY + (m_tRecognizeSize.iCY >> 1);
	m_tFrame.dwTime = GetTickCount();

	//m_tFrame.dwTime = GetTickCount();
	return READY_OK;
}

int CCardEffect::Update_Effect()
{
	if (false == m_bCollision)
	{
		//Collision_Player();
	}
	else
	{
		if (m_tFrame.iStartFrame > m_tFrame.iEndFrame)
		{
			return OBJ_DEAD;
		}

		if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
		{
			m_tFrame.iStartFrame += 1;
			m_tFrame.dwTime = GetTickCount();
		}
	}
	return OBJ_NOEVENT;
}

void CCardEffect::Late_Update_Effect()
{
}

void CCardEffect::Render_Effect(HDC hDC)
{
	
	CEffect::Update_RECT();

	HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"CardEffect");

	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();


	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		m_tPoint.iCX, m_tPoint.iCY,
		hMemDC,
		m_tFrame.iStartFrame*m_tPoint.iCX, m_tFrame.iState * m_tPoint.iCY,
		m_tPoint.iCX, m_tPoint.iCY,
		RGB(255, 0, 255));

}

void CCardEffect::Release_Effect()
{
}

void CCardEffect::Collision_Player()
{
	//원인 여기있구나 ㅋㅋ...^^
	CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
	if (nullptr == pObj)
	{
		return;
	}
	float fRadiusSum = ((pObj->Get_tPoint()->iCX)) + (m_tRecognizeSize.iCX >> 1);

	float fBase = pObj->Get_tPoint()->fX - m_tPoint.fX;
	float fHight = pObj->Get_tPoint()->fY - m_tPoint.fY;

	float fDistance = sqrtf(fBase*fBase + fHight*fHight);

	m_bCollision = fDistance <= fRadiusSum;

}

CEffect * CCardEffect::Create(TFPOINT & rPoint)
{
	CEffect* pInstance = new CCardEffect;
	pInstance->Set_tPoint(rPoint);
	if (0 > pInstance->Ready_Effect())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}
