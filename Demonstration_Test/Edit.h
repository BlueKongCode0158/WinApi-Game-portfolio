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
	// �ȷ�Ʈ�� �����ֳ� �� �����ֳ��� �Ǻ����ֱ� ���� �������.
	bool m_bSetPalette;
	bool m_bSetOptionPalette;
	bool m_bCreateMonster;
	bool m_bCollisionSetting;
	bool m_bProbSetting;
private:
	// Ÿ�Ͽ� �����ٰž�~!
	CTile::AREA m_eArea;
	int m_iIndexX;
	int m_iIndexY;
private:
	// Ÿ�Ͽ� �����ٰǵ� �̰� �浹ü �����ؼ� �� �� ���Ƽ� ���׾�!
	int m_iOption;
private: //DC �������� �뵵�� �������.
	HDC m_hDC;
private:
	int m_iPushNumV;
	int m_iPushNumB;
	int m_iPushNumTap;
	int m_iPushNumQ;	//�浹ü ��ġ
	int m_iPushNumE;	//���� ��ġ.
private:
	RECT m_tRect;
private:	//���� ���� ����
	CGameObject::MONSTER_ID m_eID;
	TFPOINT m_tfPoint;
private:	//�浹���� ������Ʈ..
	CCollider::COLLIDER m_eCoiiderID;
private://rect��..����..
	RECT m_tProbRect;
	float m_fProbX;
	float m_fProbY;
	RECT m_tCollsionRECT;
private:
	CProb::PROBS m_eProbID;
};