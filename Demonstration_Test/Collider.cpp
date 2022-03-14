#include "stdafx.h"
#include "Collider.h"

CCollider::CCollider()
	:m_eColliderName(CCollider::COLLIDER::END)
{
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CCollider::~CCollider()
{
}

int CCollider::Ready_Collider()
{
	return 0;
}

int CCollider::Update_Collider()
{
	return 0;
}

void CCollider::Render_Collider(HDC hDC)
{
}

void CCollider::Release_Collider()
{
}

