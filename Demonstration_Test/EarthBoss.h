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
private://보스 스킬 적는 곳
	void Boss_Scatter();
	void Boss_Pillar();
	void Boss_Punch();
	void Boss_Jump(); //이건 할지 안할지 미지수.
private:
	void Update_CollisionRect();
public:
	// CGameObject을(를) 통해 상속됨
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
private://기둥 생성 반복문에 쓰일 것.
	int m_iCratePillar;
	DWORD m_dwSkil_Pillar;
private:
	DWORD m_dwPunch;
	DWORD m_dwPunchTime;
private://점프 패턴에 쓰일 것
	DWORD m_dwJumpTime;
	DWORD m_dwJumpIsTime;
private: //좌표 보관에 쓰일 것. // 이건 갑자기 떨어지는 거에도 쓰이겠다..
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