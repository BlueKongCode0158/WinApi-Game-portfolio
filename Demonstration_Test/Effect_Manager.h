#pragma once

class CEffect;
class CEffect_Manager final
{
public:
	enum EffectID
	{
		SLASHEFFECT,
		CARDEFFECT,
		EFFECT_END
	};
private:
	static CEffect_Manager* pInstance;
public:
	static CEffect_Manager* Get_Instance()
	{
		if (nullptr == pInstance)
		{
			pInstance = new CEffect_Manager;
		}
		return pInstance;
	}
	static void Release_Instance()
	{
		if (nullptr != pInstance)
		{
			delete pInstance;
			pInstance = nullptr;
		}
	}
public:
	void Add_EffectObj(CEffect* pEffect, EffectID eID)
	{
		m_listEffect[eID].emplace_back(pEffect);
	}
public:
	void Ready_Effect_Manager();
	void Update_Effect_Manager();
	void Render_Effect_Manager(HDC hDC);
	void Release_Effect_Manager();
private:
	list<CEffect*> m_listEffect[EFFECT_END];
};