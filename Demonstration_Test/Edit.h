#pragma once
#include "Scene.h"
#include "Tile.h"
#include "GameObject.h"
#include "Collider.h"
#include "Prob.h"

class CKey_Manager;
class CEdit
	:public CScene
{
private:
	CEdit();
public:
	~CEdit();
public:
	virtual int Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Render_Scene(HDC hDC) override;
	virtual void Release_Scene() override;
public:
	static CScene* Create();
	static CScene* Create(LPVOID pVoid);
private:
	void Tile_Palette(HDC hDC);
	void Tile_Option_Palette(HDC hDC);
	void Monster_Palette(HDC hDC);
	void Collision_Palette(HDC hDC);
	void Prob_Palette(HDC hDC);
private:
	void Tile_Option_Setting();
	void ScrollMove();
	void ViewKey();
	void OptionKey();
private:
	void Collider_Update();
	void Prob_Update();
	void SaveButton_Update();
	void Monster_Update();
private:
	void Prob_Object();
	void Collision_Object();
private:
	float m_fScrollSpeed;
private:
	// 팔레트가 켜져있나 안 켜져있나를 판별해주기 위해 만들어줌.
	bool m_bSetPalette;
	bool m_bSetOptionPalette;
	bool m_bCreateMonster;
	bool m_bCollisionSetting;
	bool m_bProbSetting;
private:
	// 타일에 셋해줄거야~!
	CTile::AREA m_eArea;
	int m_iIndexX;
	int m_iIndexY;
private:
	// 타일에 셋해줄건데 이건 충돌체 관련해서 쓸 것 같아서 빼뒀어!
	int m_iOption;
private: //DC 저장해줄 용도로 만들어줌.
	HDC m_hDC;
private:
	int m_iPushNumV;
	int m_iPushNumB;
	int m_iPushNumTap;
	int m_iPushNumQ;	//충돌체 설치
	int m_iPushNumE;	//프랍 설치.
private:
	RECT m_tRect;
private:	//몬스터 관련 변수
	CGameObject::MONSTER_ID m_eID;
	TFPOINT m_tfPoint;
private:	//충돌관련 오브젝트..
	CCollider::COLLIDER m_eCoiiderID;
private://rect를..보자..
	RECT m_tProbRect;
	float m_fProbX;
	float m_fProbY;
	RECT m_tCollsionRECT;
private:
	CProb::PROBS m_eProbID;
};