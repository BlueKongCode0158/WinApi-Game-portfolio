#pragma once
#define KEY_LEFT	0x00000001
#define KEY_RIGHT	0x00000002
#define KEY_UP		0x00000004
#define KEY_DOWN	0x00000008
#define KEY_LBUTTON	0x00000010
#define KEY_RBUTTON	0x00000020
#define KEY_O		0x00000040		//���̺� ��ư
#define KEY_L		0x00000080		//�ε�   ��ư
#define KEY_SPACE	0x00000100		//����	 ��ư
#define KEY_W		0x00000200
#define KEY_A		0x00000400
#define KEY_S		0x00000800
#define KEY_D		0x00001000
#define KEY_Q		0x00002000
#define KEY_E		0x00004000		//�� ��ư���� ���ٰ� ������ ������ �ɷ�.
#define KEY_R		0x00008000		//�� ��ư���� ���ٰ� ������ ������ �ɷ�.
#define KEY_TAB		0x00010000
#define KEY_F		0x00020000		//��ȭ ��ư.
#define KEY_M		0x00040000		//���� ��ư.
#define KEY_ESC		0x00080000
#define KEY_V		0x00100000		//�ȷ�Ʈ ���� Ű
#define KEY_C		0x00200000		//�浹ó�� �ǰ� �ִ� �� ���� Ű
#define KEY_B		0x00400000		//�ɼ� �ȷ�Ʈ ���� ��~
#define KEY_1		0x00800000
#define KEY_2		0x01000000
#define KEY_3		0x02000000

class CKey_Manager
{
public:
	static CKey_Manager* Get_StartKey()
	{
		if (nullptr == m_pStartKey)
		{
			m_pStartKey = new CKey_Manager;
		}
		return m_pStartKey;
	}
	static CKey_Manager* Get_PlayerKey()
	{
		if (nullptr == m_pPalyerKey)
		{
			m_pPalyerKey = new CKey_Manager;
		}
		return m_pPalyerKey;
	}
	static CKey_Manager* Get_EditKey()
	{
		if (nullptr == m_pEditKey)
		{
			m_pEditKey = new CKey_Manager;
		}
		return m_pEditKey;
	}
	void Release_Instance()
	{
		if (m_pStartKey)
		{
			delete m_pStartKey;
			m_pStartKey = nullptr;
		}
		if (m_pPalyerKey)
		{
			delete m_pPalyerKey;
			m_pPalyerKey = nullptr;
		}
		if (m_pEditKey)
		{
			delete m_pEditKey;
			m_pEditKey = nullptr;
		}
	}
private:
	static CKey_Manager* m_pStartKey;
	static CKey_Manager* m_pEditKey;
	static CKey_Manager* m_pPalyerKey;
private:
	CKey_Manager();
	~CKey_Manager();
public:
	void Key_Update();
	bool Key_Up(DWORD dwkey);
	bool Key_Down(DWORD dwKey);
	bool Key_Pressing(DWORD dwKey);
private:
	DWORD m_dwKey;
	DWORD m_dwKeyDown;
	DWORD m_dwKeyUp;
};