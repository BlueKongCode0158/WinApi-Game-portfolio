#pragma once
#include "GameObject.h"

class CKey_Manager;
class CPlayer final
	:public CGameObject
{
private:
	enum STATE 
	{ 
		IDLE, 
		IDLE_LEFT, 
		IDLE_RIGHT, 
		IDLE_BACK, 
		WALK_LEFT, 
		WALK_RIGHT,
		WALK_BACK,
		WALK_FRONT,
		ATTACK_NOMAL_FRONT,
		ATTACK_NOMAL_LEFT,
		ATTACK_NOMAL_RIGHT,
		ATTACK_NOMAL_BACK,
		DASH_FRONT,
		DASH_BACK,
		DASH_LEFT,
		DASH_RIGHT,
		DASH_45,
		DASH_135,
		DASH_225,
		DASH_315,
		FALL,
		DIE
	};
private:
	CPlayer();
public:
	~CPlayer();
public:
	static CGameObject* Create();
	static CGameObject* Create(LPVOID pVoid);
public:
	// CGameObject��(��) ���� ��ӵ�
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_GamceObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
public:
	void FrameChange();
	void MoveFrame();
	void Move();
	void Skil_Slash();
	void Skil_Dash();
	void Skil_Shield();
	void Skil_IceSpin();
public:
	OBJINFO* Get_Info()
	{
		return &m_tInfo;
	}
private:
	void ScrollMove();
private:
	float m_fSpeed;
	float m_fAngle;
private:
	OBJINFO m_tInfo;
	TCHAR* m_szRobe;
	STATE m_CurState;
	STATE m_NextState;
	STATE m_OldState;
	//FRAME m_tFrame;
private:
	int m_iAttackCombo;	//���Ϳ� �󸶳� �浹�߳Ŀ� ���� �޺��� ���ž�.
	int m_iSlash;		//�������� �󸶳� ���Ŀ� ���� ��ų ����� �ٲ�Ű�
	bool m_bIceSpinPattern;
private:
	DWORD m_dwWallCount;
	DWORD m_dwSlashCount;
	DWORD m_dwDashCount;
	DWORD m_dwShieldCount;
	DWORD m_dwIceSpinCount;
private:
	TFPOINT m_DashPoint;
	TFPOINT m_DashOldPoint;
};