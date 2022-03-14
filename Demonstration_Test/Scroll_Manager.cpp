#include "stdafx.h"
#include "Scroll_Manager.h"

CScroll_Manager* CScroll_Manager::m_pProbScroll = nullptr;
CScroll_Manager* CScroll_Manager::m_pInstance = nullptr;
CScroll_Manager::CScroll_Manager()
	:m_iScrollX(0)
	,m_iScrollY(0)
{
}

CScroll_Manager::~CScroll_Manager()
{
}

void CScroll_Manager::Scroll_Lock()
{
	if (0 < m_iScrollX)
	{
		m_iScrollX = 0;
	}
	if (0 < m_iScrollY)
	{
		m_iScrollY = 0;
	}

	if (WINCX - TILECX*TILEX > m_iScrollX)
	{
		m_iScrollX = WINCX - TILECX*TILEX;
	}
	if (WINCY-TILECY*TILEY > m_iScrollY)
	{
		m_iScrollY = WINCY - TILECY*TILEY;
	}
	
	//printf( "%f",m_iScrollY );
}
