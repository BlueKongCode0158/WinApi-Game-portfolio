#pragma once
#include "Scene.h"

class CHome :
	public CScene
{
private:
	CHome();
public:
	virtual ~CHome();
public:
	virtual int Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Render_Scene(HDC hDC) override;
	virtual void Release_Scene() override;
public:
	static CScene* Create();
	static CScene* Create(LPVOID pVoid);

};