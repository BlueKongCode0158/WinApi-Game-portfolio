#pragma once

class CFont_Damage
{
private:
	CFont_Damage();
public:
	~CFont_Damage();
public:
	static CFont_Damage* Create();
public:
	int Ready_Font_Damage();
	int Update_Font_Damage();
	void Render_Font_Damage(HDC hDC);
	void Release_Font_Damage();
public:
	void Set_Point(TFPOINT& rPoint)
	{
		m_tPoint.fX = rPoint.fX;
		m_tPoint.fY = rPoint.fY;
	}
	void Set_Point(TPOINT& rPoint)
	{
		m_tPoint.fX = rPoint.fX;
		m_tPoint.fY = rPoint.fY;
	}
	void Set_Point(float fX, float fY)
	{
		m_tPoint.fX = fX;
		m_tPoint.fY = fY;
	}
	void Set_Damage(int iDamage)
	{
		m_iDamage = iDamage;
	}
	void Set_Damage(float fDamage)
	{
		//소수점 잘림 주의
		m_iDamage = static_cast<int>(fDamage);
	}
public:
	TPOINT* Get_Point()
	{
		return &m_tPoint;
	}
	void Set_Color(DWORD dwRed, DWORD dwGreen, DWORD dwBlue)
	{
		m_dwRed = dwRed;
		m_dwGreen = dwGreen;
		m_dwBlue = dwBlue;
	}
private:
	TPOINT m_tPoint;
	int m_iDamage;
	TCHAR m_szDamage[32];
	DWORD m_dwDeleteTime;
	LOGFONT m_logFont;
	HFONT m_hFont;
	HFONT HOldFont;
private:
	DWORD m_dwRed;
	DWORD m_dwGreen;
	DWORD m_dwBlue;
};