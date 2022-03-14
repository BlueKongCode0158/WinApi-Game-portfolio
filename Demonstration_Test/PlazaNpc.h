#pragma once
#include "GameObject.h"

class CPlazaNpc final
	:public CGameObject
{
private:
	CPlazaNpc();
public:
	virtual ~CPlazaNpc();
public:
	// CGameObject을(를) 통해 상속됨
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_GamceObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
public:
	static CGameObject* Create();
	static CGameObject* Create(LPVOID pVoid);
};