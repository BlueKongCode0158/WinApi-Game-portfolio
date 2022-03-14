#pragma once
#include "Collider.h"

class CGameObject;
class CTile;
class CSkil;
class CCollider;
class CCollision_Manager
{
public:
	static CCollision_Manager* Get_Instacne()
	{
		if (nullptr == m_pInstacne)
		{
			m_pInstacne = new CCollision_Manager;
		}
		return m_pInstacne;
	}
	static void Release_Instacne()
	{
		if (m_pInstacne)
		{
			delete m_pInstacne;
			m_pInstacne = nullptr;
		}
	}
	// 시연회 끝나고 Safe_Delete로 지워주기 해보자 히히
	// static으로 처리하면 편하긴한데 모르것네
	// 우선 난 매니저는 이렇게 생성하는게 더 편하더라..
	// 편해지면 나쁜 버릇이긴해요.
	// 충돌판정 엄청 많이 할 것 같은데 이거 화면에 보이는 애들 인덱스 떠다가 그 애들로만 하는게 나을 듯.
	// 아 그치 플레이어 위치 가져와서 그 인덱스 에 있는 애랑만 충돌처리하면 되겠다..!
public:
	void Tile_Collision(CGameObject& pGameObject, vector<CTile*>& pVecTile);
	void Tile_Collision(list<CGameObject*>& pGameObject, vector < CTile*>& pVecTile,GAMEOBJECT::UPDATE_ID eID);
	void Monster_Collision(list<CSkil*>& pGameObject, list<CGameObject*>& plistMonster, EMONSTER eState);	// 이거 어디다가 쓰지. 

	void Shield_Collision(list<CSkil*>& pGameObject, list<CGameObject*>& plistMonsterArmor);
	void Shield_Collision_Attack(list<CSkil*>& pGameObject, list<CGameObject*>& plistMonster);
	void Shield_Collision_AttackBoss(CGameObject& rGameObject, list<CSkil*>& rSkilObject);

	void Collision_RectEx(list<CSkil *>& rlistSkil, list<CGameObject*>& rlistMonster);
	void Collision_RectEX(list<CGameObject*>& rlistPlayer, list<CGameObject*>& rlistMonster);

public:
	bool Collision_Sphere(CSkil * pSkil, CGameObject* pMonster);
	bool Check_Rect(CGameObject* pPlayer, CGameObject* pMonster, float* fX, float* fY);
	bool Check_Rect(CSkil* pSkil, CGameObject* pMonster, float* fX, float* fY);
public:
	void Update_Collider();
	void Render_Collider(HDC hDC);
	void Release_Collider();
	void Collider_Rect_Delete(RECT& rRect);
public:
	void Add_Collider_Object(CCollider* pCollider, CCollider::COLLIDER eID)
	{
		m_listCollider[eID].emplace_back(pCollider);
	}
	void Save_Collider_Data();
	void Load_Collider_Data();
private:
	CCollision_Manager();
	~CCollision_Manager();
private:
	static CCollision_Manager* m_pInstacne;
private:
	list<CCollider*> m_listCollider[CCollider::COLLIDER::END];
};