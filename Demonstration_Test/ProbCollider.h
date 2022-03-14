#pragma once
#include "Collider.h"

class CProbCollider final
	:public CCollider
{
private:
	CProbCollider();
public:
	virtual ~CProbCollider();
public:
	static CCollider* Create();
public:
	// CCollider��(��) ���� ��ӵ�
	virtual int Ready_Collider() override;
	virtual int Update_Collider() override;
	virtual void Render_Collider(HDC hDC) override;
	virtual void Release_Collider() override;
private:
	void MonsterArmor_Collider();
	void Monster_Collider();
};