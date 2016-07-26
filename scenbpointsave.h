//scene breakpoint preservation 
#ifndef _SCENE_BREAKPOINT_PRESERVA_H_
#define _SCENE_BREAKPOINT_PRESERVA_H_
#include"hashinfoadm.h"

typedef struct sbkpointnode
{                           //头插法
		char * psenckey;        //场景
		int itentval;           //意图
		int endbit;             //场景结束状态
    int paranum;            //已有参数个数
    long *lparsity;         //
		struct sbkpointnode * pnext;
}SBKPOINTNODE, * bpoinlist;

typedef struct Hashscbkpsavnode
{
		long nHashA;
		long nHashB;
		int  bExists;

		char * robotid;          //机器人ID
		int spnum;               //
    bpoinlist bplist;        //场景断点
}HASHSCKSNODE, * hashsptable;
//////////////////////////////////////////////////
///  根据机器人id进行场景断点信息保存，按照机器人id进行反馈
///
//////////////////////////////////////////
int mparms2sitary(long * parsitym, long *yparsit, int gum);
int ins_bplist(bpoinlist *BL, const char * senckey, int inttval, int endstat, long *yparsit, int gum);
void freeBPList(bpoinlist *BL);

//////////////////////////////////////
void Init_sckhash(hashsptable * HashSP);
void free_sckhash(hashsptable * HashSP);
void writ_sckhash(hashsptable hashtb, const char * phtbpath);
long GetHashsck(hashsptable hash_tb, const char *primkey);
int SetHashsck(hashsptable * HashtB, const char *probtid, const char * senckey, int intenval, int endbit, long *yparsit, int gum);

//////////////////////////////////////

#endif
