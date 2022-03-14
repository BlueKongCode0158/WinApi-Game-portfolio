#pragma once
#include "GameObject.h"

class CEarthBoss final
	:public CGameObject
{
public:
	enum STATE
	{
		BOSS_ATTACK_LEFT,
		BOSS_ATTACK_RIGHT,
		BOSS_ATTACK_BACK,
		BOSS_ATTACK_FRONT,
		BOSS_SCATTER,
		BOSS_JUMP,
		BOSS_JUMPFALL,
		BOSS_IDLE,
		BOSS_HIT,
		BOSS_RUSH,
		BOSS_FAILED
	};
private:
	CEarthBoss();
public:
	virtual ~CEarthBoss();
public:
	static CGameObject* Create();
public:
	void Set_State(CEarthBoss::STATE eID)
	{
		m_eNextState = eID;
	}
private:
	void AnimationState();
private://���� ��ų ���� ��
	void Boss_Scatter();
	void Boss_Pillar();
	void Boss_Punch();
	void Boss_Jump(); //�̰� ���� ������ ������.
private:
	void Update_CollisionRect();
public:
	// CGameObject��(��) ���� ��ӵ�
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_GamceObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
private:
	STATE m_eCurState;
	STATE m_eNextState;
	DWORD m_dwPatternCount;
	bool m_bBossFailed;
private://��� ���� �ݺ����� ���� ��.
	int m_iCratePillar;
	DWORD m_dwSkil_Pillar;
private:
	DWORD m_dwPunch;
	DWORD m_dwPunchTime;
private://���� ���Ͽ� ���� ��
	DWORD m_dwJumpTime;
	DWORD m_dwJumpIsTime;
private: //��ǥ ������ ���� ��. // �̰� ���ڱ� �������� �ſ��� ���̰ڴ�..
	float m_fSaveX;
	float m_fSaveY;
	float m_fPillarfX;
	float m_fPillarfY;
private:
	bool m_bJump;
	bool m_bPillar;
	DWORD m_dwPillarCount;
private:
	RECT m_tShadowRect;
private:
	float m_fJumpPower ;
	float m_fAccel;
	float m_fGravity;
private:
	float m_fOldfY;
};