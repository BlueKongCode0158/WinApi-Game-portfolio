#include "stdafx.h"
#include "GameObject.h"

CGameObject::CGameObject()
	:m_bWall(false),
	m_bDead(false),
	m_iPushNum(0),
	m_bCollision(false),
	m_bRecog(false)
{
}

CGameObject::~CGameObject()
{
}

void CGameObject::Update_Rect()
{
	m_tRect.left = m_tPoint.fX - (m_tPoint.iCX >> 1);
	m_tRect.right = m_tPoint.fX + (m_tPoint.iCX >> 1);
	m_tRect.top = m_tPoint.fY - (m_tPoint.iCY >> 1);
	m_tRect.bottom = m_tPoint.fY + (m_tPoint.iCY >> 1);
}
