#pragma once

class CCollider abstract
{
public:
	enum COLLIDER
	{
		PROB, IRON_BAR, CREATE_COLLIDER ,END
	};
public:
	CCollider();
	virtual ~CCollider();
public:
	virtual int Ready_Collider() = 0;
	virtual int Update_Collider() = 0;
	virtual void Render_Collider(HDC hDC) = 0; // 콜라이더 어디 있는지 판별용
	virtual void Release_Collider() = 0;
public:
	void Set_Rect(RECT& rRECT)
	{
		m_tRect.left = rRECT.left;
		m_tRect.top = rRECT.top;
		m_tRect.right = rRECT.right;
		m_tRect.bottom = rRECT.bottom;
	}//그럼 rect만 필요한거 아닌가 점은 필요없지 않아??
	RECT* Get_Rect()
	{
		return &m_tRect;
	}
	CCollider::COLLIDER Get_Collider()
	{
		return m_eColliderName;
	}
public: //보류
	//void Set_tPoint(TPOINT& tPoint)
	//{
	//	m_tPoint.fX = tPoint.fX;
	//	m_tPoint.fY = tPoint.fY;
	//}
	//void Set_Size(TPOINT& tSize)
	//{
	//	m_tPoint.iCX = tSize.iCX;
	//	m_tPoint.iCY = tSize.iCY;
	//}
	//TPOINT* Get_Point()
	//{
	//	return &m_tPoint;
	//}
protected:
	RECT m_tRect;
	//TPOINT m_tPoint;
	COLLIDER m_eColliderName;
};