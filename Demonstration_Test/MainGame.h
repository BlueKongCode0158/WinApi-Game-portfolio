#pragma once
class CMainGame
{
public:
	CMainGame();
	virtual ~CMainGame();
public:
	int Ready_MainGame();
	void Update_MainGame();
	void Render_MainGame();
	void Release_MainGame();
private:
	HDC m_hDC;
	DWORD m_FpsTime;
	DWORD m_dwGetick;
	TCHAR m_szFps[32];
};