#include "stdafx.h"
#include "MyUI.h"

CMyUI::CMyUI()
{
}

CMyUI::~CMyUI()
{
}

void CMyUI::Update_RECT()
{
	m_tRECT.left = m_tPoint.fX - (m_tPoint.iCX >> 1);
	m_tRECT.right = m_tPoint.fX + (m_tPoint.iCX >> 1);
	m_tRECT.top = m_tPoint.fY - (m_tPoint.iCY >> 1);
	m_tRECT.bottom = m_tPoint.fY + (m_tPoint.iCY >> 1);
}
