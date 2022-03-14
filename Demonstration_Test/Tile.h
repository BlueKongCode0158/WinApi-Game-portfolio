#pragma once
class CTile
{
public:
	enum AREA { HOME , PLAZA , EARTHDUNGEON };
private:
	CTile();
	CTile(const CTile& rObj) = delete;
	void operator=(const CTile& rhs) = delete;
	// 하는 이유가 컴파일러에서 
	// 임의로 만들어주는 걸 막아주기 위해서
	// 라고 들었는데
public:
	virtual ~CTile();
public:
	int Get_DrawXID() { return m_iDrawXID; }
	int Get_DrawYID() { return m_iDrawYID; }
	int Get_Option() { return m_iOption; }
	CTile::AREA Get_Area() { return m_eArea; }
	TPOINT* Get_POINT() { return &m_tPoint; }
public:
	RECT* Get_Rect() { return &m_tRect; }
public:
	void Set_Area(AREA eArea)
	{
		m_eArea = eArea;
	}
	void Set_Pos(float fX, float fY)
	{
		m_tPoint.fX = fX;
		m_tPoint.fY = fY;
	}
	void Set_Pos(const TPOINT& rPoint)
	{
		m_tPoint.fX = rPoint.fX;
		m_tPoint.fY = rPoint.fY;
		m_tPoint.iCX = rPoint.iCX;
		m_tPoint.iCY = rPoint.iCY;
	}
	void Set_DrawXID(int iDrawX)
	{
		m_iDrawXID = iDrawX;
	}
	void Set_DrawYID(int iDrawY)
	{
		m_iDrawYID = iDrawY;
	}
	void Set_Option(int iOption)
	{
		m_iOption = iOption;
	}
public:
	int Ready_Tile();
	void Update_Tile();
	void Render_Tile(HDC hDC);
	void Release_Tile();
	void Update_Rect();
public:
	static CTile* Create();
private:
	int m_iDrawXID;
	int m_iDrawYID;
	int m_iOption;
	TPOINT m_tPoint;
	RECT   m_tRect;
private:
	AREA m_eArea;
	HDC m_hMemDC;
	// 눌러서 옵션 설정하기? 가능하려나!
};