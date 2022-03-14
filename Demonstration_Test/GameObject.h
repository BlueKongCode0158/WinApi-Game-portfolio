#pragma once

class CGameObject abstract
{
public:
	enum MONSTER_ID{ARCHER,MAGIC,SLIME,ZOMBIE,BOSS,NONE};
public:
	CGameObject();
	virtual ~CGameObject();
public:
	virtual int Ready_GameObject() =0;
	virtual int Update_GameObject() =0;
	virtual void Late_GamceObject() =0;
	virtual void Render_GameObject(HDC hDC) =0;
	virtual void Release_GameObject() =0;
protected:
	void Update_Rect();
public:
	void Set_tPoint(float x, float y)
	{
		m_tPoint.fX = x;
		m_tPoint.fY = y;
	}

	void Set_tPoint(TPOINT& rPoint)
	{
		m_tPoint.fX = rPoint.fX;
		m_tPoint.fY = rPoint.fY;
	}

	void Set_tPoint(TFPOINT& rPoint)
	{
		m_tPoint.fX = rPoint.fX;
		m_tPoint.fY = rPoint.fY;
	}

	void Set_tSize(TPOINT& rSize)
	{
		m_tPoint.iCX = rSize.iCX;
		m_tPoint.iCY = rSize.iCY;
	}

	TPOINT* Get_tPoint()
	{
		return &m_tPoint;
	}
	RECT* Get_RECT()
	{
		return &m_tRect;
	}
	CGameObject::MONSTER_ID Get_MonsterID()
	{
		return m_eID;
	}
	void Set_MonsterID(CGameObject::MONSTER_ID eID)
	{
		m_eID = eID;
	}
public:
	int Get_HP()
	{
		return m_iHp;
	}
	const int Get_MaxHp()
	{
		return m_iMaxHp;
	}
public:
	int Get_Mp()
	{
		return m_iMp;
	}

	const int Get_MaxMp()
	{
		return m_iMaxMp;
	}

	void Set_Mp(int iMp)
	{
		m_iMp += iMp;
	}
public:
	void Set_SubHP(int iSubHp)
	{
		m_iHp -= iSubHp;
	}

	void Set_PlusHp(int iPlusHp)
	{
		m_iHp += iPlusHp;
	}

	int Get_Damage()
	{
		return m_iDamage;
	}
public:
	void Set_Damage(int iDamage)
	{
		m_iDamage = iDamage;
	}
public:
	const bool Get_Wall()
	{
		return m_bWall;
	}
public:
	void Set_Hp(int iHp)
	{
		m_iHp = iHp;
	}
public:
	void Set_Wall() { m_bWall = true; }
	void Set_Wall(bool bWall) { m_bWall = bWall; }
	void Set_Fall() { m_bFall = true; }
	void Set_Fall(bool bFall) { m_bFall = bFall; }
	void Set_Dead() { m_bDead = true; }
public:
	const int Get_Push()
	{
		return m_iPushNum;
	}
	void Sub_Push()
	{
		m_iPushNum -= 1;
	}
public:
	void Set_Collision(bool bCollision)
	{
		m_bCollision = bCollision;
	}
	void Set_Collision()
	{
		m_bCollision = true;
	}
	bool Get_Collision()
	{
		return m_bCollision;
	}
public:
	RECT* Get_CollisionRect()
	{
		return &m_tRect_Collision;
	}
public:
	void Sub_AttackNum(DWORD SubNum)
	{
		m_dwAttackNum -= SubNum;
	}
	DWORD Get_AttackNum()
	{
		return m_dwAttackNum;
	}
protected:
	bool m_bWall;
	bool m_bFall;
	//Wall�� �ε����� �������� ����ž�. ���ǵ带 0���� �ٲ������ �ɷ���.
	//�ε��� ���¿��� Wall�� ���� ���� ������ �̵��Ϸ��� �ϸ� false�� ���ϵ��� �ϸ� �Ƿ���
	//�ѹ� �õ��غ��� ~!
protected:
	RECT m_tRect;
	RECT m_tRect_Recognize;//�켱 ��ġ
	RECT m_tRect_Collision;

	TPOINT m_tPoint;
	int m_iMaxHp;
	int m_iHp;
	int m_iMp;
	int m_iMaxMp;

	int m_iPushNum;

	int m_iDamage;
	FRAME m_tFrame;
protected:
	bool m_bDead;
	MYSIZE m_tRecognizeSize;
	CGameObject::MONSTER_ID m_eID;
protected:
	bool m_bCollision;
protected:
	bool m_bRecog;
protected:
	DWORD m_dwAttackNum;
};