#include "stdafx.h"
#include "Collision_Manager.h"
#include "Scroll_Manager.h"
#include "GameObject.h"
#include "Player.h"
#include "Tile.h"
#include "Key_Manager.h"
#include "Skil.h"
#include "Archer.h"
#include "SlashEffect.h"
#include "Skil_Manager.h"
#include "Effect.h"
#include "Effect_Manager.h"
#include "SlashEffect.h"
#include "Font_Damage.h"
#include "Font_Damage_Manager.h"
#include "Zombie.h"
#include "EarthBoss.h"
#include "HitEffect.h"
#include "Collider.h"
#include "ProbCollider.h"
#include "Create_Collider.h"
#include "IRon_Collider.h"

CCollision_Manager* CCollision_Manager::m_pInstacne = nullptr;

void CCollision_Manager::Tile_Collision(CGameObject& pGameObject, vector<CTile*>& pVecTile)
{
	int iIndexX = (pGameObject.Get_tPoint()->fX) / TILECX;
	int iIndexY = (pGameObject.Get_tPoint()->fY) / TILECY;

	int iIndexID = iIndexX + (iIndexY*TILEX);

	if (0 > iIndexID || pVecTile.size() <= iIndexID)
		return;

	int iOption = pVecTile[iIndexID]->Get_Option();
	// 옵션 값이..enum으로 판별해볼까

	RECT rect{};

	if (IntersectRect(&rect, pGameObject.Get_RECT(), pVecTile[iIndexID]->Get_Rect()))
	{
		if (NORMAL == iOption)
		{
			//pGameObject.Set_Wall(false);
			pGameObject.Set_Fall(false);

		}
		else if (WALL == iOption)
		{

			RECT* TileRECT = pVecTile[iIndexID]->Get_Rect();
			TPOINT* PlayerPoint = pGameObject.Get_tPoint();	// 이가 결국 중심점이랑 하는 거잖아. 그러니까 안되는거지.

			POINT PlayePT{};
			PlayePT.x = static_cast<int>(PlayerPoint->fX);
			PlayePT.y = static_cast<int>(PlayerPoint->fY);

			TileRECT = pVecTile[iIndexID]->Get_Rect();

			pGameObject.Set_Wall();

			int iDistanceX_1 = abs(abs(PlayePT.x) - abs(TileRECT->left));
			int iDistanceY_1 = abs(abs(PlayePT.y) - abs(TileRECT->top));
			int iDistance_LT = sqrt(iDistanceX_1*iDistanceX_1 + iDistanceY_1 * iDistanceY_1 );	//좌측 상단

			int iDistanceX_2 = abs(abs(PlayePT.x) - abs(TileRECT->right));
			int iDistanceY_2 = abs(abs(PlayePT.y) - abs(TileRECT->top));
			int iDistance_RT = sqrt(iDistanceX_2 * iDistanceX_2 + iDistanceY_2 * iDistanceY_2 );	//우측 상단

			int iDistanceX_3 = abs(abs(PlayePT.x) - abs(TileRECT->left));
			int iDistanceY_3 = abs(abs(PlayePT.y)- abs(TileRECT->bottom));
			int iDistance_LB = sqrt(iDistanceX_3 * iDistanceX_3 + iDistanceY_3 * iDistanceY_3);	//좌측 하단

			int iDistanceX_4 = abs(abs(PlayePT.x) - abs(TileRECT->right));
			int iDistanceY_4 = abs(abs(PlayePT.y) - abs(TileRECT->bottom));
			int iDistance_RB = sqrt(iDistanceX_4 * iDistanceX_4 + iDistanceY_4 * iDistanceY_4);	//우측 하단


			if (PtInRect(TileRECT, PlayePT))
			{
				if ((iDistance_RT < iDistance_LT && iDistance_RB < iDistance_LB) && PlayePT.x >= TileRECT->left)	//플레이어의 왼쪽 x 좌표가 타일의 오른쪽 x 좌표보다 작아진다면
				{
					//이거 rect 보다 점으로 판별하는게 더 쉬울 것 같아. 일어나서 점으로 판별시도해보기.
					//현재 플레이어 x좌표 변수에 지정해주고 그 x값이 변화가 없는 동안 아래쪽키들 되도록? 만들어줄까?
					if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_D))
					{
						pGameObject.Set_Wall(false);	//d만 누르면 무조건 아 지금 d 가 무조건 참으로 나와서 아래쪽으로 못 내려가는거 아니야?
						// 합리적 의심..
						// 일어나서 조건 더 추가하고
						// 생각해서 타일 충돌 마무리 하자.
					}
					if ((iDistance_LB < iDistance_LT && iDistance_RB < iDistance_RT) && (PlayePT.y <= TileRECT->bottom)/* || (PlayePT.y <= TileRECT->bottom)*/)
					{
						if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_S) )
						{
							pGameObject.Set_Wall(false);
						}
					}
					else if (iDistance_LT < iDistance_LB && iDistance_RT < iDistance_RB)
					{
						if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_W))
						{
							pGameObject.Set_Wall(false);
						}
					}
				}
				else if (iDistance_LT<iDistance_RT && iDistance_LB<iDistance_RB)
				{
					if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_A))
					{
						pGameObject.Set_Wall(false);
					}

					if (iDistance_LB < iDistance_LT && iDistance_RB < iDistance_RT)
					{
						if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_S))
						{
							pGameObject.Set_Wall(false);
						}
					}
					else if (iDistance_LT < iDistance_LB && iDistance_RT < iDistance_RB)
					{
						if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_W))
						{
							pGameObject.Set_Wall(false);
						}
					}

				}
				if (iDistance_LB < iDistance_LT && iDistance_RB < iDistance_RT)
				{
					if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_S))
					{
						pGameObject.Set_Wall(false);
					}
				}
				else if (iDistance_LT < iDistance_LB && iDistance_RT < iDistance_RB)
				{
					if (CKey_Manager::Get_PlayerKey()->Key_Pressing(KEY_W))
					{
						pGameObject.Set_Wall(false);
					}
				}
			}

		}
		else if (FALL == iOption)
		{
			pGameObject.Set_Fall();
		}
		else if (CREATEWALL == iOption)
		{

		}
	}

}

void CCollision_Manager::Tile_Collision(list<CGameObject*>& pGameObject, vector<CTile*>& pVecTile, GAMEOBJECT::UPDATE_ID eID)
{
	if (GAMEOBJECT::UPDATE_ID::MONSTER_ARMOR == eID)
	{
		for (list<CGameObject*>::iterator iter = pGameObject.begin(); iter != pGameObject.end(); iter++)
		{
			int iIndexX = (*iter)->Get_tPoint()->fX / TILECX;
			int iIndexY = (*iter)->Get_tPoint()->fY / TILECY;

			int iIndexID = iIndexX + (iIndexY*TILEX);

			if (0 > iIndexID || pVecTile.size() <= iIndexID)
				return;

			int iOption = pVecTile[iIndexID]->Get_Option();
			// 옵션 값이..enum으로 판별해볼까

			RECT rect{};

			if (IntersectRect(&rect, (*iter)->Get_RECT(), pVecTile[iIndexID]->Get_Rect()))
			{
				if (NORMAL == iOption)
				{
					(*iter)->Set_Wall(false);
					(*iter)->Set_Fall(false);

				}
				else if (WALL == iOption)
				{

					(*iter)->Set_Dead();


				}
				else if (FALL == iOption)
				{
					//(*iter)->Set_Dead();
				}
				else if (CREATEWALL == iOption)
				{

				}
			}
		}
	}
}

void CCollision_Manager::Monster_Collision(list<CSkil*>& rSkil, list<CGameObject*>& rlistMonster, EMONSTER eState)	// 이건 좋지 못한 것 같아..
{
	if (&rSkil == nullptr && &rlistMonster == nullptr)
		return;
	if (EMONSTER::ARCHER == eState)
	{
		for (auto& pMonster : rlistMonster)
		{
			for (auto& pSkil : rSkil)
			{
				if (Collision_Sphere(pSkil, pMonster))
				{
					if (pMonster->Get_HP() > 0 && pSkil->Get_AttackNum() > 0)
					{
						if (CGameObject::MONSTER_ID::ARCHER == pMonster->Get_MonsterID())
						{
							dynamic_cast<CArcher*>(pMonster)->Set_Hit();
						}
						else if (CGameObject::MONSTER_ID::ZOMBIE == pMonster->Get_MonsterID())
						{
							dynamic_cast<CZombie*>(pMonster)->Set_Hit();
						}
						else if (CGameObject::MONSTER_ID::BOSS == pMonster->Get_MonsterID())
						{
							dynamic_cast<CEarthBoss*>(pMonster)->Set_State(CEarthBoss::STATE::BOSS_HIT);
						}
						int iPlayerDamage = pSkil->Get_Damage();
						int iRand = rand() % iPlayerDamage;
						iPlayerDamage += iRand;

						pMonster->Set_SubHP(iPlayerDamage);
						pSkil->Set_AttackNum();

						TPOINT tPoint{};
						tPoint.fX = pMonster->Get_RECT()->left + (rand() % pMonster->Get_tPoint()->iCX);
						tPoint.fY = pMonster->Get_RECT()->top + (rand() % pMonster->Get_tPoint()->iCY);

						CEffect* pSkilEffect = CSlashEffect::Create(pMonster->Get_tPoint());
						pSkilEffect->Set_tPoint(tPoint);
						CEffect_Manager::Get_Instance()->Add_EffectObj(pSkilEffect, CEffect_Manager::EffectID::SLASHEFFECT);

						CFont_Damage* pFont = CFont_Damage::Create();

						TFPOINT tfPoint{};
						tfPoint.fX = pMonster->Get_tPoint()->fX - 10;
						tfPoint.fY = pMonster->Get_tPoint()->fY - 10;
						pFont->Set_Point(tfPoint);
						pFont->Set_Damage(iPlayerDamage);
						pFont->Set_Color(255, 255, 255);
						CFont_Damage_Manager::Get_Instance()->Add_Font_Damage(pFont);

						if (pMonster->Get_HP() < 0)
						{
							pMonster->Set_Hp(0);
						}
					}
				}
			}
		}
	}
}

void CCollision_Manager::Shield_Collision_Attack(list<CSkil*>& pGameObject, list<CGameObject*>& plistMonster)
{
	for (auto& pSkil : pGameObject)
	{
		for (auto& pMonster : plistMonster)
		{
			if (Collision_Sphere(pSkil, pMonster) && false == pSkil->Get_Attack())
			{
				if (pMonster->Get_HP() > 0)
				{
					if (CGameObject::MONSTER_ID::ARCHER == pMonster->Get_MonsterID())
					{
						dynamic_cast<CArcher*>(pMonster)->Set_STATE(CArcher::STATE::HIT);
					}
					else if (CGameObject::MONSTER_ID::ZOMBIE == pMonster->Get_MonsterID())
					{
						dynamic_cast<CZombie*>(pMonster)->Set_State(CZombie::STATE::HIT);
					}
					else if (CGameObject::MONSTER_ID::BOSS == pMonster->Get_MonsterID())
					{
						dynamic_cast<CEarthBoss*>(pMonster)->Set_State(CEarthBoss::STATE::BOSS_HIT);
					}


					CFont_Damage* pFont = CFont_Damage::Create();

					int iPlayerDamage = pSkil->Get_Damage();
					int iRand = rand() % iPlayerDamage;
					iPlayerDamage += iRand;

					pSkil->Set_Attack();
					pMonster->Set_SubHP(iPlayerDamage);



					TPOINT tPoint{};
					tPoint.fX = pMonster->Get_RECT()->left + (rand() % pMonster->Get_tPoint()->iCX);
					tPoint.fY = pMonster->Get_RECT()->top + (rand() % pMonster->Get_tPoint()->iCY);


					CEffect* pEffect = CHitEffect::Create();
					pEffect->Set_tPoint(tPoint);
					CEffect_Manager::Get_Instance()->Add_EffectObj(pEffect, CEffect_Manager::EffectID::SLASHEFFECT);

					TFPOINT tfPoint{};
					tfPoint.fX = pMonster->Get_tPoint()->fX - 10;
					tfPoint.fY = pMonster->Get_tPoint()->fY - 10;
					pFont->Set_Point(tfPoint);
					pFont->Set_Damage(iPlayerDamage);
					pFont->Set_Color(255, 255, 255);
					CFont_Damage_Manager::Get_Instance()->Add_Font_Damage(pFont);

					if (pMonster->Get_HP() < 0)
					{
						pMonster->Set_Hp(0);
					}
				}
			}
		}
	}
}

void CCollision_Manager::Shield_Collision_AttackBoss(CGameObject & rGameObject, list<CSkil*>& rSkilObject)
{
}

void CCollision_Manager::Shield_Collision(list<CSkil*>& pGameObject, list<CGameObject*>& plistMonsterArmor)
{
	for (auto& pSkil : pGameObject)
	{
		for (auto& pMonsterArmor : plistMonsterArmor)
		{
			if (Collision_Sphere(pSkil, pMonsterArmor))
			{
				pMonsterArmor->Set_Dead();
			}
		}
	}
}

bool CCollision_Manager::Collision_Sphere(CSkil * pSkil, CGameObject * pMonster)
{
	float fRadiusSum = ((pSkil->Get_Point()->iCX >> 1)) + ((pMonster->Get_tPoint()->iCX >> 1));

	float fBase = pMonster->Get_tPoint()->fX - pSkil->Get_Point()->fX;
	float fHight = pMonster->Get_tPoint()->fY - pSkil->Get_Point()->fY;

	float fDistance = sqrtf(fBase*fBase + fHight*fHight);

	return fDistance <= fRadiusSum;
}

bool CCollision_Manager::Check_Rect(CGameObject * pPlayer, CGameObject * pMonster, float* fX, float* fY)
{
	float fDistX = fabs(pPlayer->Get_tPoint()->fX - pMonster->Get_tPoint()->fX);
	float fRadiusSumX = (pPlayer->Get_tPoint()->iCX >> 1) + (pMonster->Get_tPoint()->iCX >> 1);

	float fDistY = fabs(pPlayer->Get_tPoint()->fY - pMonster->Get_tPoint()->fY);
	float fRadiusSumY = (pPlayer->Get_tPoint()->iCY >> 1) + (pMonster->Get_tPoint()->iCY >> 1);

	if (fDistX <= fRadiusSumX && fDistY <= fRadiusSumY)
	{
		*fX = fRadiusSumX - fDistX + 5;
		*fY = fRadiusSumY - fDistY + 5;
		return true;
	}
	return false;
}

bool CCollision_Manager::Check_Rect(CSkil * pSkil, CGameObject * pMonster, float* fX, float* fY)
{
	float fDistX = fabs(pSkil->Get_Point()->fX - pMonster->Get_tPoint()->fX);
	float fRadiusSumX = (pSkil->Get_Point()->iCX >> 1) + (pMonster->Get_tPoint()->iCX >> 1);

	float fDistY = fabs(pSkil->Get_Point()->fY - pMonster->Get_tPoint()->fY);
	float fRadiusSumY = (pSkil->Get_Point()->iCY >> 1) + (pMonster->Get_tPoint()->iCY >> 1);

	if (fDistX <= fRadiusSumX && fDistY <= fRadiusSumY)
	{
		*fX = fRadiusSumX - fDistX + 5;
		*fY = fRadiusSumY - fDistY + 5;
		return true;
	}
	return false;
}

void CCollision_Manager::Update_Collider()
{
	for (int i = 0; i < CCollider::COLLIDER::END; i++)
	{
		for (auto& iter = m_listCollider[i].begin(); iter != m_listCollider[i].end();)
		{
			int iEvent = (*iter)->Update_Collider();
			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete(*iter);
				iter = m_listCollider[i].erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
}

void CCollision_Manager::Render_Collider(HDC hDC)
{
	for (int i = 0; i < CCollider::COLLIDER::END; i++)
	{
		for (auto& iter = m_listCollider[i].begin(); iter != m_listCollider[i].end(); iter++)
		{
			(*iter)->Render_Collider(hDC);
		}
	}
}

void CCollision_Manager::Release_Collider()
{
	for (int i = 0; i < CCollider::COLLIDER::END; i++)
	{
		for (auto& pCollider : m_listCollider[i])
		{
			Safe_Delete(pCollider);
		}
		m_listCollider[i].clear();
	}
}

void CCollision_Manager::Collider_Rect_Delete(RECT & rRect)
{
	for (int i = 0; i < CCollider::COLLIDER::END; i++)
	{
		RECT tRect{};
		for (auto& iter = m_listCollider[i].begin(); iter != m_listCollider[i].end();)
		{
			RECT* ColliderRect = (*iter)->Get_Rect();
			if (IntersectRect(&tRect, &rRect, ColliderRect))
			{
				Safe_Delete(*iter);
				iter = m_listCollider[i].erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
}

void CCollision_Manager::Collision_RectEx(list<CSkil *>& rlistSkil, list<CGameObject*>& rlistMonster)
{
	float fX = 0.f;
	float fY = 0.f;

	for (auto& pDst : rlistSkil)
	{
		for (auto& pSrc : rlistMonster)
		{
			if (Check_Rect(pDst, pSrc, &fX, &fY))
			{
				float fSrcX = pSrc->Get_tPoint()->fX;
				float fSrcY = pSrc->Get_tPoint()->fY;

				if (fX > fY)
				{
					if (fSrcY <= pDst->Get_Point()->fY)
					{
						fY *= -1.f;
					}
					pSrc->Set_tPoint(fSrcX, fSrcY + fY);
				}
				else
				{
					if (fSrcX <= pDst->Get_Point()->fX)
					{
						fX *= -1.f;
					}
					pSrc->Set_tPoint(fSrcX + fX, fSrcY);
				}
			}
		}
	}
}

void CCollision_Manager::Collision_RectEX(list<CGameObject*>& rlistPlayer, list<CGameObject*>& rlistMonster)
{
	float fX = 0.f;
	float fY = 0.f;

	for (auto& pDst : rlistMonster)
	{
		for (auto& pSrc : rlistPlayer)
		{
			if (Check_Rect(pSrc, pDst, &fX, &fY) && pDst->Get_Push() >= 1)
			{
				float fSrcX = pSrc->Get_tPoint()->fX;
				float fSrcY = pSrc->Get_tPoint()->fY;

				if (fX > fY && false == pSrc->Get_Wall())
				{
					if (fSrcY <= pDst->Get_tPoint()->fY)
					{
						fY *= -1.f;
					}
					pSrc->Set_tPoint(fSrcX, fSrcY + fY);
				}
				else if(fY > fX && false == pSrc->Get_Wall())
				{
					if (fSrcX <= pDst->Get_tPoint()->fX)
					{
						fX *= -1.f;
					}
					pSrc->Set_tPoint(fSrcX + fX, fSrcY);
				}
				pDst->Sub_Push();
				pDst->Set_Dead();

				int iMonsterDamage = pDst->Get_Damage();
				int iRand = rand() & pDst->Get_Damage();
				iMonsterDamage += iRand;
				pSrc->Set_SubHP(iMonsterDamage);

				CFont_Damage* pFont = CFont_Damage::Create();
				TFPOINT tfPoint{};
				tfPoint.fX = pSrc->Get_tPoint()->fX - 10;
				tfPoint.fY = pSrc->Get_tPoint()->fY - 10;
				pFont->Set_Point(tfPoint);
				pFont->Set_Damage(iMonsterDamage);
				pFont->Set_Color(255, 0, 0);
				CFont_Damage_Manager::Get_Instance()->Add_Font_Damage(pFont);
			}
		}
	}
}

void CCollision_Manager::Save_Collider_Data()
{
	HANDLE hFile = CreateFile(
		L"../Data/ColliderData.dat",
		GENERIC_WRITE,
		0, nullptr,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}
	DWORD dwbyte = 0;

	for (int i = 0; i < CCollider::COLLIDER::END; i++)
	{
		if (!m_listCollider[i].empty())
		{
			for (auto& pCollider : m_listCollider[i])
			{
				RECT* tRECT = pCollider->Get_Rect();
				CCollider::COLLIDER eCollider = pCollider->Get_Collider();
				WriteFile(hFile, tRECT, sizeof(RECT), &dwbyte, nullptr);
				WriteFile(hFile, &eCollider, sizeof(CCollider::COLLIDER), &dwbyte, nullptr);
			}
		}
	}
	CloseHandle(hFile);
}

void CCollision_Manager::Load_Collider_Data()
{
	HANDLE hFile = CreateFile(
		L"../Data/ColliderData.dat",
		GENERIC_READ,
		0, nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}
	DWORD dwbyte = 0;

	for (int i = 0; i < CCollider::COLLIDER::END; i++)
	{
		if (!m_listCollider[i].empty())
		{
			for (auto& pCollider : m_listCollider[i])
			{
				Safe_Delete(pCollider);
			}
			m_listCollider[i].clear();
		}
	}

	while (true)
	{
		RECT tRECT{};
		CCollider::COLLIDER eID;

		ReadFile(hFile, &tRECT, sizeof(RECT), &dwbyte, nullptr);
		ReadFile(hFile, &eID, sizeof(CCollider::COLLIDER), &dwbyte, nullptr);

		if (0 == dwbyte)
			break;

		CCollider* pCollider = nullptr;

		switch (eID)
		{
		case CCollider::COLLIDER::PROB:
			pCollider = CProbCollider::Create();
			pCollider->Set_Rect(tRECT);
			Add_Collider_Object(pCollider, eID);
			break;
		case CCollider::COLLIDER::IRON_BAR:
			pCollider = CIRon_Collider::Create();
			pCollider->Set_Rect(tRECT);
			Add_Collider_Object(pCollider, CCollider::COLLIDER::IRON_BAR);
			break;
		case CCollider::COLLIDER::CREATE_COLLIDER:
			pCollider = CCreate_Collider::Create();
			pCollider->Set_Rect(tRECT);
			Add_Collider_Object(pCollider, CCollider::COLLIDER::CREATE_COLLIDER);
			break;
		default:
			CloseHandle(hFile);
			return;
		}
	}
	CloseHandle(hFile);
}

CCollision_Manager::CCollision_Manager()
{
}

CCollision_Manager::~CCollision_Manager()
{
	Release_Collider();
}
