#pragma once
#include "Scene.h"

class CKey_Manager;
class CStart final
	:public CScene
{
private:
	CStart();
public:
	virtual ~CStart();
public:
	virtual int  Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Render_Scene(HDC hDC) override;
	virtual void Release_Scene() override;
public:
	static CScene* Create();
	static CScene* Create(LPVOID pVoid);
};