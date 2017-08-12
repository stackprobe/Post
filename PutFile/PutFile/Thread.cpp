#include "all.h"

typedef struct Info_st
{
	void (*UserFunc)(void *);
	void *UserInfo;
}
Info_t;

/*
	�ő�X���b�h�� 2028 (���_�l)
*/
#define THREAD_MAX 3000

static Info_t Infos[THREAD_MAX];
static int InfoIndex;

static uint __stdcall Perform(void *info)
{
	((Info_t *)info)->UserFunc(((Info_t *)info)->UserInfo);
	return 0;
}

/*
	�g�p��
		critical();
		{
			int h = runThread(UserFunc, UserInfo);
			waitForever(h);
			handleClose(h);
		}
		uncritical();
*/
int runThread(void (*userFunc)(void *), void *userInfo)
{
	errorCase(!userFunc);

	Info_t *info = Infos + InfoIndex; // THREAD_MAX ��O�� Perform() �� info �̎Q�Ƃ͏I����Ă���ƌ��Ȃ��B

	info->UserFunc = userFunc;
	info->UserInfo = userInfo;

	InfoIndex = (InfoIndex + 1) % THREAD_MAX;

	int h = (int)_beginthreadex(0, 0, Perform, info, 0, 0);
	errorCase(!h); // ? ���s
	return h;
}

void initCritical(critical_t *i)
{
	InitializeCriticalSection(&i->Csec);
}
void uninitCritical(critical_t *i)
{
	DeleteCriticalSection(&i->Csec);
}
void enterCritical(critical_t *i)
{
	EnterCriticalSection(&i->Csec);
}
void leaveCritical(critical_t *i)
{
	LeaveCriticalSection(&i->Csec);
}

static int CritCommonInited;
static critical_t CritCommon;
thread_tls static int CritCommonLockCount;

void critical(void)
{
	if(!CritCommonInited)
	{
		initCritical(&CritCommon);
		CritCommonInited = 1;
	}
	if(!CritCommonLockCount)
	{
		enterCritical(&CritCommon);
	}
	CritCommonLockCount++;
}
void uncritical(void)
{
	errorCase(!CritCommonInited);
	errorCase(!CritCommonLockCount);

	CritCommonLockCount--;
	if(!CritCommonLockCount)
	{
		leaveCritical(&CritCommon);
	}
}
