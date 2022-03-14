#include "stdafx.h"
#include "Effect.h"

CEffect::CEffect()
{
}

CEffect::~CEffect()
{
}

void CEffect::Update_RECT()
{
	m_tRect.left = m_tPoint.fX - (m_tPoint.iCX >> 1);
	m_tRect.top = m_tPoint.fY - (m_tPoint.iCY >> 1);
	m_tRect.right = m_tPoint.fX + (m_tPoint.iCX >> 1);
	m_tRect.bottom = m_tPoint.fY + (m_tPoint.iCY >> 1);
}
