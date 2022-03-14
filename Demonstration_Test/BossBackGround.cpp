#include "stdafx.h"
#include "BossBackGround.h"
#include "Bitmap_Manager.h"
#include "GameObject.h"
#include "GameObject_Manager.h"

CBossBackGround::CBossBackGround()
{
}

CBossBackGround::~CBossBackGround()
{
}

int CBossBackGround::Ready_UI()
{
	m_tPoint.fX = WINCX >> 1;
	m_tPoint.fY = 200;
	m_tPoint.iCX = 339;
	m_tPoint.iCY = 48;

	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/UI/BossHpUI.bmp", L"BossHpUI");
	return READY_OK;
}

void CBossBackGround::Update_UI()
{
}

void CBossBackGround::Late_Update_UI()
{
}

void CBossBackGround::Render_UI(HDC hDC)
{
	CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Boss();
	if (nullptr == pObj)
	{
		return;
	}
	if (true == pObj->Get_Collision())
	{
		m_tRECT.left = m_tPoint.fX - (m_tPoint.iCX >> 1);
		m_tRECT.bottom = m_tPoint.fY - (m_tPoint.iCY >> 1);
		m_tRECT.right = m_tPoint.fX + (m_tPoint.iCX >> 1);
		m_tRECT.top = m_tPoint.fY + (m_tPoint.iCY >> 1);

		HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"BossHpUI");
		GdiTransparentBlt(hDC,
			m_tRECT.left, m_tRECT.bottom,
			m_tPoint.iCX, m_tPoint.iCY,
			hMemDC,
			0, 0, m_tPoint.iCX, m_tPoint.iCY,
			RGB(255, 0, 255));
	}
}

CMyUI * CBossBackGround::Create()
{
	CMyUI* pinstacne = new CBossBackGround;
	if (0 > pinstacne->Ready_UI())
	{
		Safe_Delete(pinstacne);
	}
	return pinstacne;
}
