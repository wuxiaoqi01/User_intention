
#ifndef _SCENE_CODE_HASH_H_
#define _SCENE_CODE_HASH_H_
#include"sharfuct.h"

typedef struct Hashinfonode
{
		long nHashA;
		long nHashB;
		int  bExists;
	
		char * primarykey;  
    int rimval;
		char * sencdkey;
		int egnum;
		int endbit;      //
		descklist fdlist;
}HASHINFONODE, * hashinfotabl;
/////////////////////////////////////
/////  �������Ϲ���  ��������hash��ѯ
/////   char * primarykey;  �������Ͼ� 
/////   int rimval;         ��ͼֵ
/////	char * sencdkey;    ��������
/////   int egnum;          ��������
/////	descklist fdlist;   �����б�
/////////////////////////////////////
//    �������� ����hash��ѯ
//    char * primarykey;   ������������ 
//    int rimval;          �����ȼ�
//	  char * sencdkey;
//	  int egnum;
//	  descklist fdlist;    <����  ����  ��ͼֵ>���� 
//
void Init_infhash(hashinfotabl * HashtB);
void free_infhash(hashinfotabl * HashtB);
void writ_infhash(hashinfotabl hashtb, const char * phtbpath);
long GetHashinf(hashinfotabl hash_tb, const char *primkey);
int sethashentpar(hashinfotabl * HashtB, const char *primkey, int rimval, int edbit, const char * psenckey, const char * pkind, int dparnb);
int SetHashinf(hashinfotabl * HashtB, const char *primkey, const char * sencdkey, int rimval, int edbit, const char * potherkey);
void scencorp2hash(hashinfotabl * HashtB, const char * pscecpath);
void entyparbuf2hash(hashinfotabl * HashtB, char * pentparbuf);
void entyparm2hash(hashinfotabl * HashtB, const char * pentppath);
#endif
