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

	//GetickCount()로 초기화 해준다. -> 시간 나오도록 하기.
	bool bDash;
	bool bNomalAtt;
	bool bMagicAtt;
	bool bFinalAtt;
	bool bDeonSkil1;
	bool bDeonSkil2;

	//속성
	//int iProperty; // 이건 스킬로 빼자.
}OBJINFO;

typedef struct SKIL
{
	
};

typedef struct TFrame
{
	int iStartFrame;
	int iEndFrame;
	int iState;
	DWORD dwSpeed;	//스피드
	DWORD dwTime;	//시간
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