#pragma once

typedef struct MYPOINT
{
	MYPOINT()
	{
		ZeroMemory(this, sizeof(POINT));
	}
	float fX;
	float fY;
	int iCX;
	int iCY;
}TPOINT;

typedef struct INFO
{
	INFO()
	{
		ZeroMemory(this, sizeof(INFO));
	}

	//GetickCount()�� �ʱ�ȭ ���ش�. -> �ð� �������� �ϱ�.
	bool bDash;
	bool bNomalAtt;
	bool bMagicAtt;
	bool bFinalAtt;
	bool bDeonSkil1;
	bool bDeonSkil2;

	//�Ӽ�
	//int iProperty; // �̰� ��ų�� ����.
}OBJINFO;

typedef struct SKIL
{
	
};

typedef struct TFrame
{
	int iStartFrame;
	int iEndFrame;
	int iState;
	DWORD dwSpeed;	//���ǵ�
	DWORD dwTime;	//�ð�
}FRAME;

typedef struct TFPOINT
{
	TFPOINT()
	{
		ZeroMemory(this, sizeof(TFPOINT));
	}
	float fX;
	float fY;
}VECTOR2;

typedef struct TSIZE
{
	TSIZE()
	{
		ZeroMemory(this, sizeof(TSIZE));
	}
	int iCX;
	int iCY;
}MYSIZE;