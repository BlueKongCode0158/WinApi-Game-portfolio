#pragma once

class CSkil abstract
{
public:
	CSkil();
	virtual ~CSkil();
public:
	virtual int Ready_Skil() = 0;
	virtual int Update_Skil() = 0;
	virtual void Render_Skil(HDC hDC) = 0;
	virtual void Release_Skil() = 0;
public:
	RECT* Get_CollRect() { return &m_tCollRect; }
	RECT* Get_RECT() { return &m_tRect; }
	TPOINT* Get_Point() { return &m_tPoint; }
	FRAME* Get_Frame() { return &m_tFrame; }
public:
	void Set_Frame(int iState, int iStart)
	{
		m_tFrame.iState = iState;
		m_tFrame.iStartFrame = iStart;
	}
	void Set_ClickNum(int iNum)
	{
		m_iClickNum = iNum;
	}
	int Get_Damage()
	{
		return m_iDamage;
	}
	int Get_AttackNum()
	{
		return m_iAttack;
	}
	void Set_AttackNum()
	{
		m_iAttack -= 1;
	}
	void Set_Angle(float fAngle)
	{
		m_fAngle = fAngle;
	}
public:
	void Set_Attack()
	{
		m_bAttack = true;
	}
	const bool Get_Attack()
	{
		return m_bAttack;
	}
protected:
	RECT m_tRect;
	RECT m_tCollRect;
	TPOINT m_tPoint;
	DWORD m_dwGetickCount;
	DWORD m_dwAttackTime;
	bool m_bAttack;
	HDC m_hMemDC;
protected:
	FRAME m_tFrame;
	int m_iClickNum;
	int m_iDamage;
	int m_iAttack;
	float m_fAngle;
};