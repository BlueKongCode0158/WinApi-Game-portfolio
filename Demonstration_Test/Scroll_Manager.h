#pragma once

//스크롤은 전부 먹여줄거니까.. 어 그냥 static으로 해줄까.
//통일성 지켜주자.
class CScroll_Manager final
{
public:
	static CScroll_Manager* Get_ProbScroll()
	{
		if (nullptr == m_pProbScroll)
		{
			m_pProbScroll = new CScroll_Manager;
		}
		return m_pProbScroll;
	}
	static void Release_ProbScroll()
	{
		if (m_pProbScroll)
		{
			delete m_pProbScroll;
			m_pProbScroll = nullptr;
		}
	}
	static CScroll_Manager* Get_Instacne()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CScroll_Manager;
		}
		return m_pInstance;
	}
	static void Release_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	CScroll_Manager();
	~CScroll_Manager();
public:
	int Get_ScrollX() { return m_iScrollX; }
	int Get_ScrollY() { return m_iScrollY; }
	void Set_ScrollX(int iX) { m_iScrollX += iX; }
	void Set_ScrollY(int iY) { m_iScrollY += iY; }
public:
	void Scroll_Lock();
private:
	static CScroll_Manager* m_pInstance;
	static CScroll_Manager* m_pProbScroll;
private:
	int m_iScrollX;
	int m_iScrollY;
};