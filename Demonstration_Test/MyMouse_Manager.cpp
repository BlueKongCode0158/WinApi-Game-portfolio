#include "stdafx.h"
#include "MyMouse.h"
#include "MyMouse_Manager.h"

CMyMouse_Manager* CMyMouse_Manager::m_pInstance = nullptr;
CMyMouse_Manager::CMyMouse_Manager()
	:m_pMouse(nullptr)
{
}

CMyMouse_Manager::~CMyMouse_Manager()
{
}

void CMyMouse_Manager::Ready_MyMouse_Manager()
{
	m_pMouse = CMyMouse::Create();
}

void CMyMouse_Manager::Update_MyMouse_Manager()
{
	if (nullptr != m_pMouse)
	{
		m_pMouse->Update_MyMouse();
		m_pMouse->Late_MyMouse();
	}
}

void CMyMouse_Manager::Render_MyMouse_Manager(HDC hDC)
{
	if (nullptr != m_pMouse)
	{
		m_pMouse->Render_MyMouse(hDC);
	}
}
