#pragma once
#include "Scene.h"

class CPlaza
	:public CScene
{
private:
	CPlaza();
public:
	virtual ~CPlaza();
public:
	virtual int  Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Render_Scene(HDC hDC) override;
	virtual void Release_Scene() override;
};