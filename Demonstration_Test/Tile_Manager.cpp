#include "stdafx.h"
#include "Tile_Manager.h"
#include "Tile.h"
#include "Scroll_Manager.h"

CTile_Manager* CTile_Manager::m_pInstance = nullptr;

CTile_Manager::CTile_Manager()
{
}

CTile_Manager::~CTile_Manager()
{
}

void CTile_Manager::Save_Data_Tile_Manager()
{
	HANDLE hFile = CreateFile(
		L"../Data/TileData.dat",
		GENERIC_WRITE,
		0, nullptr,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL
		, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}
	DWORD dwbyte = 0;

	for (auto& pTile : m_vecTile)
	{
		int iDrawIDX = pTile->Get_DrawXID();
		int iDrawIDY = pTile->Get_DrawYID();
		int iOption = pTile->Get_Option();
		CTile::AREA eArea = pTile->Get_Area();
		WriteFile(hFile, pTile->Get_POINT(), sizeof(TPOINT), &dwbyte, nullptr);
		WriteFile(hFile, &iDrawIDX, sizeof(int), &dwbyte, nullptr);
		WriteFile(hFile, &iDrawIDY, sizeof(int), &dwbyte, nullptr);
		WriteFile(hFile, &iOption, sizeof(int), &dwbyte, nullptr);
		WriteFile(hFile, &eArea, sizeof(CTile::AREA), &dwbyte, nullptr);
		// 여기 터질수도 있으니까 킵해놓자.
	}
	CloseHandle(hFile);
	//  다 썼으면 닫아주기
}

void CTile_Manager::Load_Data_Tile_Manager()
{
	HANDLE hFile
		= CreateFile(L"../Data/TileData.dat",
			GENERIC_READ,
			0, nullptr,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}
	DWORD dwbyte = 0;

	if (!m_vecTile.empty())
	{
		for (auto& pTile : m_vecTile)
		{
			Safe_Delete(pTile);
		}
		m_vecTile.clear();
		m_vecTile.shrink_to_fit();
	}
	m_vecTile.reserve(TILEX*TILEY);
	//공간을 예약하겠다.
	
	while (true)
	{
		int iDrawIDX = 0;
		int iDrawIDY = 0;
		int iOption = 0;
		CTile::AREA eArea = CTile::AREA::HOME;

		TPOINT tPoint{};
		//잠시만 장소 안 가져와줬네. 가져와야지.
		ReadFile(hFile, &tPoint, sizeof(TPOINT), &dwbyte, nullptr);
		ReadFile(hFile, &iDrawIDX, sizeof(int), &dwbyte, nullptr);
		ReadFile(hFile, &iDrawIDY, sizeof(int), &dwbyte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwbyte, nullptr);
		ReadFile(hFile, &eArea, sizeof(CTile::AREA), &dwbyte, nullptr);

		if (0 == dwbyte)
			break;

		CTile* pTile = CTile::Create();
		pTile->Set_Pos(tPoint);
		pTile->Set_DrawXID(iDrawIDX);
		pTile->Set_DrawYID(iDrawIDY);
		pTile->Set_Option(iOption);
		pTile->Set_Area(eArea);
		m_vecTile.emplace_back(pTile);
	}
	CloseHandle(hFile);
}

void CTile_Manager::Picking_Tile_Manager(const POINT & rMouse, const int & iDrawXID, const int & iDrawYID, const CTile::AREA eArea ,const int & iOption /*=0*/)
{
	int iIndexX = rMouse.x / TILECX;
	int iIndexY = rMouse.y / TILECY;

	int iIndex = iIndexX + (iIndexY*TILEX);
	//인덱스 구하는 공식
	//타일 식 오류

	//TILEY 타일의 y축 개수.
	//TILEX 타일의 x축 개수
	//TILECX -> 타일의 X축 길이
	//TILECY -> 타일의 Y축 길이.
	if (0 > iIndex || m_vecTile.size() <= iIndex)
		return;

	m_vecTile[iIndex]->Set_DrawXID(iDrawXID);
	m_vecTile[iIndex]->Set_DrawYID(iDrawYID);
	m_vecTile[iIndex]->Set_Option(iOption);
	m_vecTile[iIndex]->Set_Area(eArea);
}

void CTile_Manager::Picking_Tile_Option_Manager(const RECT & rRECT, const int & iOption)
{
	int iStartX = abs(rRECT.left / TILECX);
	int iStartY = abs(rRECT.top / TILECY);
	int iEndX = abs((iStartX + rRECT.right) / TILECX);
	int iEndY = abs((iStartY + rRECT.bottom) / TILECY);

	for (int i = iStartY; i < iEndY; i++)
	{
		for (int j = iStartX; j < iEndX; j++)
		{
			int iIndex = j + (i*TILEX);
			m_vecTile[iIndex]->Set_Option(iOption);
		}
	}
}

void CTile_Manager::Ready_Tile_Manager()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float fX = (j*TILECX) + (TILECX >> 1);	//중점 구하는 식 맞네.
			float fY = (i*TILECY) + (TILECY >> 1);
			CTile* pTile = CTile::Create();
			pTile->Set_Pos(fX, fY);
			m_vecTile.emplace_back(pTile);
		}
	}
}

void CTile_Manager::Render_Tile_Manager(HDC hDC)
{
	
	//나중에 컬링하기.
	// 오늘 할 수 있으면 오늘하기.
	// 절댓값
	// 시간 남으면 식에 대해서 더 탐구해보기
	int iStartCullingX = abs(CScroll_Manager::Get_Instacne()->Get_ScrollX() / TILECX);	// 스크롤 값이 음수 일 수 있으니까 절댓값을 먹여준거구나.
	int iStartCullingY = abs(CScroll_Manager::Get_Instacne()->Get_ScrollY() / TILECY);
	int iEndCullingX = iStartCullingX + WINCX / TILECX;
	int iEndCullingY = iStartCullingY + WINCY / TILECY;

	for (int i = iStartCullingY; i < iEndCullingY + 1; i++)
	{
		for (int j = iStartCullingX; j < iEndCullingX + 1; j++)
		{
			int iIndex = j + (i*TILEX);
			//몇번째 타일인지 말해주는거구나?
			if (0 > iIndex || m_vecTile.size() <= iIndex)
				return;
			m_vecTile[iIndex]->Render_Tile(hDC);
		}
	}
}

void CTile_Manager::Release_Tile_Manager()
{
}
