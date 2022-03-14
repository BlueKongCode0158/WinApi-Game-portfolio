#include "stdafx.h"
#include "Font_Damage.h"
#include "Scroll_Manager.h"
#define FONT_TIME 500

CFont_Damage::CFont_Damage()
{
}

CFont_Damage::~CFont_Damage()
{
}

CFont_Damage * CFont_Damage::Create()
{
	CFont_Damage* pInstance = new CFont_Damage();
	if (0 > pInstance->Ready_Font_Damage())
	{
		Safe_Delete(pInstance);
	}
	return pInstance;
}

int CFont_Damage::Ready_Font_Damage()
{

	m_dwDeleteTime = GetTickCount();
	return READY_OK;
}

int CFont_Damage::Update_Font_Damage()
{
	if (m_dwDeleteTime + FONT_TIME < GetTickCount())
	{
		return OBJ_DEAD;
	}

	m_tPoint.fY -= 0.5f;
	return OBJ_NOEVENT;
}

void CFont_Damage::Render_Font_Damage(HDC hDC)
{
	SetTextAlign(hDC, TA_CENTER);

	m_logFont.lfHeight = -MulDiv(10, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	m_logFont.lfWeight = FW_NORMAL;
	_tcscpy_s(m_logFont.lfFaceName, TEXT("../font/Font/8bitWonder.ttf"));
	m_hFont = CreateFontIndirect(&m_logFont);
	//�ش� ��Ʈ�� ����Ѵٰ� �Ѱ��ش�.

	HOldFont = static_cast<HFONT>(SelectObject(hDC, m_hFont));
	//�� �� ��Ʈ�� �������ش�.
	swprintf_s(m_szDamage, L"%d", m_iDamage);
	//��� �� ����.


	int iScrollX = CScroll_Manager::Get_Instacne()->Get_ScrollX();
	int iScrollY = CScroll_Manager::Get_Instacne()->Get_ScrollY();

	//���ڸ� ���ļ� ���鼭 �ܰ����� ����� �� �� �ִ�.
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, m_tPoint.fX - 1 + iScrollX, m_tPoint.fY - 1 + iScrollY, m_szDamage, lstrlen(m_szDamage));
	TextOut(hDC, m_tPoint.fX + 1 + iScrollX, m_tPoint.fY + 1 + iScrollY, m_szDamage, lstrlen(m_szDamage));
	TextOut(hDC, m_tPoint.fX - 1 + iScrollX, m_tPoint.fY + 1 + iScrollY, m_szDamage, lstrlen(m_szDamage));
	TextOut(hDC, m_tPoint.fX + 1 + iScrollX, m_tPoint.fY - 1 +iScrollY, m_szDamage, lstrlen(m_szDamage));

	

	SetTextColor(hDC, RGB(m_dwRed, m_dwGreen, m_dwBlue));
	TextOut(hDC, m_tPoint.fX + iScrollX, m_tPoint.fY + iScrollY, m_szDamage, lstrlen(m_szDamage));

	SelectObject(hDC, HOldFont);
	DeleteObject(m_hFont);
	//�� ���� �����ش�.
}

void CFont_Damage::Release_Font_Damage()
{
}
