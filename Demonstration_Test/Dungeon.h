#pragma once
#include "Scene.h"

class CDungeon
	:public CScene
{
private:
	CDungeon();
public:
	~CDungeon();
public:
	virtual int Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Release_Scene() override;
	virtual void Render_Scene(HDC hDC) override;
public:
	static CScene* Create();
	static CScene* Create(LPVOID pVoid);
};