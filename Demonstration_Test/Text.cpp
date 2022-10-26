#include "stdafx.h"
#include "Text.h"

const int iMaxColor = 255;
const int iMinColor = 100;

CText::CText()
	:m_hFont(NULL),
	m_Font_Color(iMinColor),
	m_bColorBlack(false),
	m_bColorWhite(true)
{
	ZeroMemory(&m_logFont, sizeof(m_logFont));
}

CText::~CText()
{
}

int CText::Ready_UI()
{
	m_tPoint.fX = (WINCX >> 1);
	// ���� ��ġ�� ���Ѵ�.
	m_tPoint.fY = WINCY - 100;

	return READY_OK;
}

void CText::Update_UI()
{
	if (bMyStartID == false)
	{
		if (m_bColorWhite == true && (m_Font_Color >= iMinColor) && (m_Font_Color <= iMaxColor))
		{
			m_Font_Color++;
			if (m_Font_Color >= iMaxColor)
			{
				m_Font_Color = iMaxColor;
				m_bColorWhite = false;
				m_bColorBlack = true;
			}
		}
		else if (m_bColorBlack == true && (m_Font_Color >= iMinColor) && (m_Font_Color <= iMaxColor))
		{
			m_Font_Color--;
			if (m_Font_Color <= iMinColor)
			{
				m_Font_Color = iMinColor;
				m_bColorWhite = true;
				m_bColorBlack = false;
			}
		}
	}
}

void CText::Late_Update_UI()
{
}

void CText::Render_UI(HDC hDC)
{
	if (bMyStartID == false)
	{
		//���ı��.
		SetTextAlign(hDC, TA_CENTER);

		m_logFont.lfHeight = -MulDiv(24, GetDeviceCaps(hDC, LOGPIXELSY), 72);
		m_logFont.lfWeight = FW_NORMAL;
		_tcscpy_s(m_logFont.lfFaceName, TEXT("../font/Font/Exo2-Bold.ttf"));
		m_hFont = CreateFontIndirect(&m_logFont);
		//�ش� ��Ʈ�� ����Ѵٰ� �Ѱ��ش�.

		HOldFont = static_cast<HFONT>(SelectObject(hDC, m_hFont));
		//�� �� ��Ʈ�� �������ش�.
		TCHAR* pStr = TEXT("�ƹ� ��ư�̳� �����ÿ�.");
		//��� �� ����.

		//���ڸ� ���ļ� ���鼭 �ܰ����� ����� �� �� �ִ�.
		SetTextColor(hDC, RGB(0, 0, 0));
		TextOut(hDC, m_tPoint.fX - 1, m_tPoint.fY - 1, pStr, lstrlen(pStr));
		TextOut(hDC, m_tPoint.fX + 1, m_tPoint.fY + 1, pStr, lstrlen(pStr));
		TextOut(hDC, m_tPoint.fX - 1, m_tPoint.fY + 1, pStr, lstrlen(pStr));
		TextOut(hDC, m_tPoint.fX + 1, m_tPoint.fY - 1, pStr, lstrlen(pStr));

		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(m_Font_Color, m_Font_Color, m_Font_Color));
		TextOut(hDC, m_tPoint.fX, m_tPoint.fY, pStr, lstrlen(pStr));

		SelectObject(hDC, HOldFont);
		DeleteObject(m_hFont);
		//�� ���� �����ش�.
	}
}
//https://blog.codingcat.kr/39 [����]
CMyUI * CText::Create()
{
	CMyUI* pInstacne = new CText;
	if (0 > pInstacne->Ready_UI())
	{
		Safe_Delete(pInstacne);
	}
	return pInstacne;
}

CMyUI * CText::Create(LPVOID pVoid)
{
	CMyUI* pInstacne = new CText;
	if (0 > pInstacne->Ready_UI())
	{
		Safe_Delete(pInstacne);
	}
	return pInstacne;
}
