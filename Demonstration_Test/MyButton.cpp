#include "stdafx.h"
#include "MyButton.h"
#include "Key_Manager.h"
#include "Scene_Manager.h"
#include "UI_Manager.h"

CMyButton::CMyButton()
	:m_dwFontSize(0)
{
}

CMyButton::~CMyButton()
{
	m_pKey = nullptr;
}

int CMyButton::Ready_UI()
{
	m_tPoint.iCX = 200;
	m_tPoint.iCY = 80;

	return READY_OK;
}

void CMyButton::Update_UI()
{
}
	//���ٽ� ����� �� ��������

void CMyButton::Late_Update_UI()
{
	if (bMyStartID)
	{
		POINT pt{};

		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		if (PtInRect(&m_tRECT, pt))
		{
			if (CKey_Manager::Get_StartKey()->Key_Down(KEY_LBUTTON))
			{
				if (!lstrcmp(m_pKey, L"Start"))
				{
					CScene_Manager::Get_Instance()->Scene_Change(CScene_Manager::ID::SCENE_DUNGEON);
				}
				else if (!lstrcmp(m_pKey, L"Edit"))
				{
					CScene_Manager::Get_Instance()->Scene_Change(CScene_Manager::ID::SCENE_EDIT);
				}
				else if (!lstrcmp(m_pKey, L"Exit"))
				{
					DestroyWindow(g_hWnd);
				}
			}
			m_dwFontSize = 28;
		}
		else
		{
			m_dwFontSize = 24;
		}
	}


}

void CMyButton::Render_UI(HDC hDC)
{
	if (bMyStartID)
	{
		CMyUI::Update_RECT();
		SetTextAlign(hDC, TA_CENTER);
		//���� Ȯ��
		//Rectangle(hDC, m_tRECT.left, m_tRECT.top, m_tRECT.right, m_tRECT.bottom);
		m_logFont.lfHeight = -MulDiv(m_dwFontSize, GetDeviceCaps(hDC, LOGPIXELSY), 72);
		m_logFont.lfWeight = FW_NORMAL;
		_tcscpy_s(m_logFont.lfFaceName, TEXT("../font/Font/Exo2-Bold.ttf"));
		m_hFont = CreateFontIndirect(&m_logFont);

		HOldFont = static_cast<HFONT>(SelectObject(hDC, m_hFont));
		// ���� �Ǵ°� �ƴ���..��!..
		//�� �� ��Ʈ�� �������ش�.
		//��� �� ����.

		TCHAR* pStr = nullptr;
		if (!lstrcmp(m_pKey, L"Start"))
		{
			pStr = TEXT("���� �ϱ�");
		}
		else if (!lstrcmp(m_pKey, L"Edit"))
		{
			pStr = TEXT("���� �ϱ�");
		}
		else if (!lstrcmp(m_pKey, L"Exit"))
		{
			pStr = TEXT("������");
		}

		//���ڸ� ���ļ� ���鼭 �ܰ����� ����� �� �� �ִ�.
		SetTextColor(hDC, RGB(0, 0, 0));
		TextOut(hDC, m_tPoint.fX - 1, m_tPoint.fY - 1, pStr, lstrlen(pStr));
		TextOut(hDC, m_tPoint.fX + 1, m_tPoint.fY + 1, pStr, lstrlen(pStr));
		TextOut(hDC, m_tPoint.fX - 1, m_tPoint.fY + 1, pStr, lstrlen(pStr));
		TextOut(hDC, m_tPoint.fX + 1, m_tPoint.fY - 1, pStr, lstrlen(pStr));

		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(255, 255, 255));

		TextOut(hDC, m_tPoint.fX, m_tPoint.fY, pStr, lstrlen(pStr));

		SelectObject(hDC, HOldFont);
		DeleteObject(m_hFont);
	}
}

CMyUI * CMyButton::Create(const TCHAR* pVoid)
{
	CMyUI* pInstance = new CMyButton;
	if (0 > pInstance->Ready_UI())
	{
		Safe_Delete(pInstance);
	}
	if (nullptr != pInstance)
	{
		dynamic_cast<CMyButton*>(pInstance)->Set_pKey(pVoid);
	}
	return pInstance;
}
