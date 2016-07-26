
//Scene parameters pairs combination 
#ifndef _SCENE_PARAM_COMB_PAIRS_H_
#define _SCENE_PARAM_COMB_PAIRS_H_

#include"sharfuct.h"

typedef struct  Hashparcombnode
{
	long nHashA;
	long nHashB;
	int  bExists;

	char * parcombk;
	char * psenckey;
	int intenval;
	char * pcombky;
}HASHPRCOMBNODE, * hashpacomb;
///////////////////////////////////////////////
/// ���ܣ� �Ѳ�����ϵļ�ֵ����hash��ѯ
/// char * parcombk; ������϶Լ�
///	char * psenckey; ��������
///	int intenval;    ��ͼ����
/// char * pcombky;  ��������
///////////////////////////////////////////////
void Init_pcmbhash(hashpacomb * HashCB);
void free_pcmbhash(hashpacomb * HashCB);
void writ_pcmbhash(hashpacomb hashcb, const char * pcmbpath);
long GetHashpcmb(hashpacomb hash_cb, const char *parcombkey);
int SetHashpcmb(hashpacomb * HashCB, const char *parcombky, const char * senckey, int intenval, const char * pcombkz);
void parmcombpair2hash(hashpacomb * HashCB, const char * prcombpath);

#endif

