#include "stdafx.h"
#include "Mp_Bar.h"
#include "Bitmap_Manager.h"
#include "GameObject_Manager.h"
#include "Player.h"

CMp_Bar::CMp_Bar()
{
}

CMp_Bar::~CMp_Bar()
{
}

int CMp_Bar::Ready_UI()
{
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/UI/Mp_Bar.bmp", L"Mp");
	m_tPoint.fX = 156.f;
	m_tPoint.fY = 67.f;
	m_tPoint.iCX = 144;
	m_tPoint.iCY = 12;
	return READY_OK;
}

void CMp_Bar::Update_UI()
{
}

void CMp_Bar::Late_Update_UI()
{
}

void CMp_Bar::Render_UI(HDC hDC)
{
	m_tRECT.left = m_tPoint.fX - (m_tPoint.iCX >> 1);
	m_tRECT.bottom = m_tPoint.fY - (m_tPoint.iCY >> 1);
	m_tRECT.right = m_tPoint.fX + (m_tPoint.iCX >> 1);
	m_tRECT.top = m_tPoint.fY + (m_tPoint.iCY >> 1);

	CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
	if (nullptr == pObj)
		return;
	int iPlayer_Mp = pObj->Get_Mp();
	int iPlayer_MaxMp = pObj->Get_MaxMp();

	float fPlayerRange = ((iPlayer_Mp / iPlayer_MaxMp) + ((iPlayer_Mp % iPlayer_MaxMp)) * (0.01f));


	HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"Mp");

	//player 값을.. 가져..와?..
	GdiTransparentBlt(hDC,
		m_tRECT.left, m_tRECT.bottom,
		m_tPoint.iCX * fPlayerRange, m_tPoint.iCY,
		hMemDC,
		0, 0, m_tPoint.iCX, m_tPoint.iCY,
		RGB(255, 0, 255));

}

CMyUI * CMp_Bar::Create()
{
	CMyUI* pInstance = new CMp_Bar;
	if (0 > pInstance->Ready_UI())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}
