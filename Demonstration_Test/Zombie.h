#pragma once
#include "GameObject.h"

class CZombie final
	:public CGameObject
{
public:
	enum STATE
	{
		IDLE,
		HIT,
		ATTACK_LEFT,
		ATTACK_RIGHT,
		RUN_LEFT,
		RUN_RIGHT,
		DEAD
	};
public:
	void Set_State(CZombie::STATE eID)
	{
		m_NextState = HIT;
	}
private:
	CZombie();
public:
	virtual ~CZombie();
public:
	void AnimationState();
public:
	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_GamceObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
public:
	void Set_Hit() { m_bHit = true; }
private:
	void Collision_Player();
public:
	static CGameObject* Create();
private:
	STATE m_CurState;
	STATE m_NextState;
private:
	DWORD m_RecallTime;
	DWORD m_dwHitTime;
private:
	bool m_bCardEffect;
	bool m_bAttack;
	bool m_bHit;
};