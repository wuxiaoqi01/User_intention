
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
/// 功能： 把参数组合的键值进行hash查询
/// char * parcombk; 参数组合对键
///	char * psenckey; 场景编码
///	int intenval;    意图编码
/// char * pcombky;  参数种类
///////////////////////////////////////////////
void Init_pcmbhash(hashpacomb * HashCB);
void free_pcmbhash(hashpacomb * HashCB);
void writ_pcmbhash(hashpacomb hashcb, const char * pcmbpath);
long GetHashpcmb(hashpacomb hash_cb, const char *parcombkey);
int SetHashpcmb(hashpacomb * HashCB, const char *parcombky, const char * senckey, int intenval, const char * pcombkz);
void parmcombpair2hash(hashpacomb * HashCB, const char * prcombpath);

#endif

