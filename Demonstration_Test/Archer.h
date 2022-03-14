#pragma once
#include "GameObject.h"

class CEffect;
class CArcher final
	:public CGameObject
{
public:
	enum STATE 
	{
		IDLE,
		ATTACK_LEFT,
		ATTACK_RIGHT,
		ATTACK_FRONT,
		ATTACK_BACK,
		ATTACK_45,
		ATTACK_135,
		ATTACK_225,
		ATTACK_315,
		HIT,
		RUN,
		DEAD 
	};

private:
	CArcher();
public:
	virtual ~CArcher();
public:
	static CGameObject* Create();
public:
	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_GamceObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
private:
	void Animation_State();
	void ShotAniamation();
public:
	void Set_STATE(STATE eID) { m_NextSTate = eID; }
	void Set_Hit() { m_bHit = true; }
public:
	void Create_Arrow();
private:
	STATE m_CurState;
	STATE m_NextSTate;
	float m_fAngle;
private:
	bool m_bHit;
	DWORD m_dwHitTime;

	DWORD m_RecallTime;
	int m_iRecallSpeed;

	int m_iArrowNum;

private: //충돌 관련 함수 및 변수
	void Collision_Player();
	bool m_bCardEffect;
};