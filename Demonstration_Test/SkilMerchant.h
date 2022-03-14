#pragma once
#include "GameObject.h"

class CSkilMerchant final
	:public CGameObject
{
private:
	CSkilMerchant();
public:
	virtual ~CSkilMerchant();
public:
	virtual int Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_GamceObject() override;
	virtual void Render_GameObject(HDC hDC) override;
	virtual void Release_GameObject() override;
public:
	static CGameObject* Create();
	static CGameObject* Create(LPVOID pVoid);
};