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
	// 중점 위치를 말한다.
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
		//정렬기능.
		SetTextAlign(hDC, TA_CENTER);

		m_logFont.lfHeight = -MulDiv(24, GetDeviceCaps(hDC, LOGPIXELSY), 72);
		m_logFont.lfWeight = FW_NORMAL;
		_tcscpy_s(m_logFont.lfFaceName, TEXT("../font/Font/Exo2-Bold.ttf"));
		m_hFont = CreateFontIndirect(&m_logFont);
		//해당 폰트를 사용한다고 넘겨준다.

		HOldFont = static_cast<HFONT>(SelectObject(hDC, m_hFont));
		//그 전 폰트를 저장해준다.
		TCHAR* pStr = TEXT("아무 버튼이나 누르시오.");
		//출력 할 글자.

		//글자를 겹쳐서 쓰면서 외곽선을 만들어 줄 수 있다.
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
		//다 쓰고 지워준다.
	}
}
//https://blog.codingcat.kr/39 [참고]
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
