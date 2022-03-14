#include "stdafx.h"
#include "Key_Manager.h"

CKey_Manager* CKey_Manager::m_pStartKey = nullptr;
CKey_Manager* CKey_Manager::m_pEditKey = nullptr;
CKey_Manager* CKey_Manager::m_pPalyerKey = nullptr;
CKey_Manager::CKey_Manager()
	:m_dwKey(0)
	,m_dwKeyUp(0)
	,m_dwKeyDown(0)
{
}

CKey_Manager::~CKey_Manager()
{
}

void CKey_Manager::Key_Update()
{
	m_dwKey = 0;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_dwKey |= KEY_LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_dwKey |= KEY_RIGHT;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_dwKey |= KEY_UP;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_dwKey |= KEY_DOWN;
	}
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		m_dwKey |= KEY_LBUTTON;
	}
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		m_dwKey |= KEY_RBUTTON;
	}
	if (GetAsyncKeyState('L') & 0x8000)
	{
		m_dwKey |= KEY_L;
	}
	if (GetAsyncKeyState('O') & 0x8000)
	{
		m_dwKey |= KEY_O;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_dwKey |= KEY_SPACE;
	}
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_dwKey |= KEY_W;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_dwKey |= KEY_A;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_dwKey |= KEY_S;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_dwKey |= KEY_D;
	}
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		m_dwKey |= KEY_Q;
	}
	if (GetAsyncKeyState('E') & 0x8000)
	{
		m_dwKey |= KEY_E;
	}
	if (GetAsyncKeyState('R') & 0x8000)
	{
		m_dwKey |= KEY_R;
	}
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
	{
		m_dwKey |= KEY_TAB;
	}
	if (GetAsyncKeyState('F') & 0x8000)
	{
		m_dwKey |= KEY_F;
	}
	if (GetAsyncKeyState('M') & 0x8000)
	{
		m_dwKey |= KEY_M;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		m_dwKey |= KEY_ESC;
	}
	if (GetAsyncKeyState('V') & 0x8000)
	{
		m_dwKey |= KEY_V;
	}
	if (GetAsyncKeyState('C') & 0x8000)
	{
		m_dwKey |= KEY_C;
	}
	if (GetAsyncKeyState('B') & 0x8000)
	{
		m_dwKey |= KEY_B;
	}
	if (GetAsyncKeyState('1') & 0x8000)
	{
		m_dwKey |= KEY_1;
	}
	if (GetAsyncKeyState('2') & 0x8000)
	{
		m_dwKey |= KEY_2;
	}
	if (GetAsyncKeyState('3') & 0x8000)
	{
		m_dwKey |= KEY_3;
	}
}

bool CKey_Manager::Key_Up(DWORD dwkey)
{
	if (m_dwKey & dwkey)
	{
		m_dwKeyUp |= dwkey;
		return false;
	}
	else if (m_dwKeyUp & dwkey)
	{
		m_dwKeyUp ^= dwkey;	//이거 문제였다 ~!
		return true;
	}
	return false;
}

bool CKey_Manager::Key_Down(DWORD dwKey)
{
	if (m_dwKey&dwKey && !(m_dwKeyDown & dwKey))
	{
		m_dwKeyDown |= dwKey;
		return true;
	}
	else if (!(m_dwKey&dwKey) && (m_dwKeyDown & dwKey))
	{
		m_dwKeyDown ^= dwKey;
		return false;
	}
	return false;
}

bool CKey_Manager::Key_Pressing(DWORD dwKey)
{
	if (m_dwKey & dwKey)
	{
		return true;
	}
	return false;
}
