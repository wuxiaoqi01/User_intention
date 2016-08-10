
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
/////  场景语料管理  场景语料hash查询
/////   char * primarykey;  场景语料句 
/////   int rimval;         意图值
/////	char * sencdkey;    场景编码
/////   int egnum;          反馈各数
/////	descklist fdlist;   反馈列表
/////////////////////////////////////
//    参数管理 参数hash查询
//    char * primarykey;   参数特征主键 
//    int rimval;          参数等级
//	  char * sencdkey;
//	  int egnum;
//	  descklist fdlist;    <场景  种类  意图值>链表 
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
