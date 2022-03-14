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
	// �ÿ�ȸ ������ Safe_Delete�� �����ֱ� �غ��� ����
	// static���� ó���ϸ� ���ϱ��ѵ� �𸣰ͳ�
	// �켱 �� �Ŵ����� �̷��� �����ϴ°� �� ���ϴ���..
	// �������� ���� �����̱��ؿ�.
	// �浹���� ��û ���� �� �� ������ �̰� ȭ�鿡 ���̴� �ֵ� �ε��� ���ٰ� �� �ֵ�θ� �ϴ°� ���� ��.
	// �� ��ġ �÷��̾� ��ġ �����ͼ� �� �ε��� �� �ִ� �ֶ��� �浹ó���ϸ� �ǰڴ�..!
public:
	void Tile_Collision(CGameObject& pGameObject, vector<CTile*>& pVecTile);
	void Tile_Collision(list<CGameObject*>& pGameObject, vector < CTile*>& pVecTile,GAMEOBJECT::UPDATE_ID eID);
	void Monster_Collision(list<CSkil*>& pGameObject, list<CGameObject*>& plistMonster, EMONSTER eState);	// �̰� ���ٰ� ����. 

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