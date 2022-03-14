#include "stdafx.h"
#include "BossHp_Bar.h"
#include "Bitmap_Manager.h"
#include "GameObject.h"
#include "GameObject_Manager.h"

CBossHp_Bar::CBossHp_Bar()
{
}

CBossHp_Bar::~CBossHp_Bar()
{
}

int CBossHp_Bar::Ready_UI()
{
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/UI/BossHp.bmp", L"BossHp");
	m_tPoint.fX = (WINCX >> 1);
	m_tPoint.fY = 202;
	m_tPoint.iCX = 267;
	m_tPoint.iCY = 21;

	return READY_OK;
}

void CBossHp_Bar::Update_UI()
{
}

void CBossHp_Bar::Late_Update_UI()
{
}

void CBossHp_Bar::Render_UI(HDC hDC)
{
	CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Boss();
	if (nullptr == pObj)
		return;
	if (true == pObj->Get_Collision())
	{
		m_tRECT.left = m_tPoint.fX - (m_tPoint.iCX >> 1);
		m_tRECT.bottom = m_tPoint.fY - (m_tPoint.iCY >> 1);
		m_tRECT.right = m_tPoint.fX + (m_tPoint.iCX >> 1);
		m_tRECT.top = m_tPoint.fY + (m_tPoint.iCY >> 1);

		int iPlayer_HP = pObj->Get_HP();
		int iPlayer_MaxHp = pObj->Get_MaxHp();

		float fPlayerRange = ((iPlayer_HP / iPlayer_MaxHp) + ((iPlayer_HP % iPlayer_MaxHp)) * (0.0005f));

		HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"BossHp");
		m_logFont.lfHeight = -MulDiv(12, GetDeviceCaps(hDC, LOGPIXELSY), 72);
		m_logFont.lfWeight = FW_NORMAL;
		_tcscpy_s(m_logFont.lfFaceName, TEXT("../font/Font/8bitWonder.ttf"));
		m_hFont = CreateFontIndirect(&m_logFont);
		//해당 폰트를 사용한다고 넘겨준다.
		TCHAR szHp[32]{};


		HOldFont = static_cast<HFONT>(SelectObject(hDC, m_hFont));
		swprintf_s(szHp, L"%d / %d", iPlayer_HP, iPlayer_MaxHp);

		int iFontX = m_tRECT.right - 38;
		int iFontY = m_tRECT.top - 20;

		//글자를 겹쳐서 쓰면서 외곽선을 만들어 줄 수 있다.

		int iFontSize = 1;
		float fHpBarRange = m_tPoint.iCX * fPlayerRange;

		GdiTransparentBlt(hDC,
			m_tRECT.left, m_tRECT.bottom,
			fHpBarRange, m_tPoint.iCY,
			hMemDC,
			0, 0, m_tPoint.iCX, m_tPoint.iCY,
			RGB(255, 0, 255));
		SelectObject(hDC, HOldFont);

		SetTextColor(hDC, RGB(0, 0, 0));
		TextOut(hDC, iFontX - iFontSize, iFontY - iFontSize, szHp, lstrlen(szHp));
		TextOut(hDC, iFontX + iFontSize, iFontY + iFontSize, szHp, lstrlen(szHp));
		TextOut(hDC, iFontX - iFontSize, iFontY + iFontSize, szHp, lstrlen(szHp));
		TextOut(hDC, iFontX + iFontSize, iFontY - iFontSize, szHp, lstrlen(szHp));

		SetTextColor(hDC, RGB(255, 255, 255));
		TextOut(hDC, iFontX, iFontY, szHp, lstrlen(szHp));
		DeleteObject(m_hFont);
	}
}

CMyUI * CBossHp_Bar::Create()
{
	CMyUI* pInstance = new CBossHp_Bar;
	if (0 > pInstance->Ready_UI())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}
