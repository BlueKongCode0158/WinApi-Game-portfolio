#include "stdafx.h"
#include "Hp_Bar.h"
#include "Bitmap_Manager.h"
#include "Player.h"
#include "GameObject_Manager.h"

CHp_Bar::CHp_Bar()
	:m_iHp(0),
	m_iMaxHp(0)

{
}

CHp_Bar::~CHp_Bar()
{
}

int CHp_Bar::Ready_UI()
{
	CBitmap_Manager::Get_Instance()->Insert_Bitmap(L"../Image/UI/HpBar.bmp", L"HP");
	m_tPoint.fX = 175.f;
	m_tPoint.fY = 43.f;
	m_tPoint.iCX = 183;
	m_tPoint.iCY = 24;
	return READY_OK;
}

void CHp_Bar::Update_UI()
{
}

void CHp_Bar::Late_Update_UI()
{
}

void CHp_Bar::Render_UI(HDC hDC)
{
	m_tRECT.left = m_tPoint.fX - (m_tPoint.iCX >> 1);
	m_tRECT.bottom = m_tPoint.fY - (m_tPoint.iCY >> 1);
	m_tRECT.right = m_tPoint.fX + (m_tPoint.iCX >> 1);
	m_tRECT.top = m_tPoint.fY + (m_tPoint.iCY >> 1);

	CGameObject* pObj = CGameObject_Manager::Get_Instacne()->Get_Player();
	if (nullptr == pObj)
		return;
	int iPlayer_HP = pObj->Get_HP();
	int iPlayer_MaxHp = pObj->Get_MaxHp();

	float fPlayerRange = ((iPlayer_HP/iPlayer_MaxHp)+ ((iPlayer_HP % iPlayer_MaxHp)) * (0.002f));

	HDC hMemDC = CBitmap_Manager::Get_Instance()->FindImage(L"HP");
	m_logFont.lfHeight = -MulDiv(12, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	m_logFont.lfWeight = FW_NORMAL;
	_tcscpy_s(m_logFont.lfFaceName, TEXT("../font/Font/8bitWonder.ttf"));
	m_hFont = CreateFontIndirect(&m_logFont);
	//해당 폰트를 사용한다고 넘겨준다.

	HOldFont = static_cast<HFONT>(SelectObject(hDC, m_hFont));
	swprintf_s(m_szHp, L"%d / %d", iPlayer_HP, iPlayer_MaxHp);

	int iFontX = 235;
	int iFontY = 15;

	//글자를 겹쳐서 쓰면서 외곽선을 만들어 줄 수 있다.

	int iFontSize = 1;
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, iFontX - iFontSize, iFontY - iFontSize, m_szHp, lstrlen(m_szHp));
	TextOut(hDC, iFontX + iFontSize, iFontY + iFontSize, m_szHp, lstrlen(m_szHp));
	TextOut(hDC, iFontX - iFontSize, iFontY + iFontSize, m_szHp, lstrlen(m_szHp));
	TextOut(hDC, iFontX + iFontSize, iFontY - iFontSize, m_szHp, lstrlen(m_szHp));

	//149 149
	//151 151
	//149 151
	//151 149
	SetTextColor(hDC, RGB(255,255,255));

	TextOut(hDC, iFontX, iFontY, m_szHp, lstrlen(m_szHp));

	float fHpBarRange = m_tPoint.iCX * fPlayerRange;

	GdiTransparentBlt(hDC,
		m_tRECT.left, m_tRECT.bottom,
		fHpBarRange, m_tPoint.iCY,
		hMemDC,
		0, 0, m_tPoint.iCX, m_tPoint.iCY,
		RGB(255, 0, 255));
	SelectObject(hDC, HOldFont);
	DeleteObject(m_hFont);

}

CMyUI * CHp_Bar::Create()
{
	CMyUI* pInstance = new CHp_Bar;
	if (0 > pInstance->Ready_UI())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

CMyUI * CHp_Bar::Create(int iHp)
{
	CMyUI* pInstance = new CHp_Bar;
	if (0 > pInstance->Ready_UI())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}
