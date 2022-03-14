#pragma once
#include "Tile.h"
class CTile_Manager final
{
private:
	CTile_Manager();
	CTile_Manager(const CTile_Manager& rObj) = delete;
	void operator=(const CTile_Manager& rhs) = delete;
	~CTile_Manager();
public:
	static CTile_Manager* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CTile_Manager;
		}
		return m_pInstance;
	}
	static void Release_Instance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
private:
	static CTile_Manager* m_pInstance;
public:
	void Save_Data_Tile_Manager();
	void Load_Data_Tile_Manager();
	void Picking_Tile_Manager(const POINT& rMouse, const int& iDrawXID, const int& iDrawYID,CTile::AREA eArea ,const int& iOption = 0);
	void Picking_Tile_Option_Manager(const RECT & rRECT, const int&iOption);
public:
	void Ready_Tile_Manager();
	void Render_Tile_Manager(HDC hDC);
	void Release_Tile_Manager();
public:
	vector<CTile*>* Get_Vector() { return &m_vecTile; }
private:
	vector<CTile*> m_vecTile;
};
// ; 하나로 오류가 날 수 있다.