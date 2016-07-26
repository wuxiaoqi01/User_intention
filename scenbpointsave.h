//scene breakpoint preservation 
#ifndef _SCENE_BREAKPOINT_PRESERVA_H_
#define _SCENE_BREAKPOINT_PRESERVA_H_
#include"hashinfoadm.h"

typedef struct sbkpointnode
{                           //ͷ�巨
		char * psenckey;        //����
		int itentval;           //��ͼ
		int endbit;             //��������״̬
    int paranum;            //���в�������
    long *lparsity;         //
		struct sbkpointnode * pnext;
}SBKPOINTNODE, * bpoinlist;

typedef struct Hashscbkpsavnode
{
		long nHashA;
		long nHashB;
		int  bExists;

		char * robotid;          //������ID
		int spnum;               //
    bpoinlist bplist;        //�����ϵ�
}HASHSCKSNODE, * hashsptable;
//////////////////////////////////////////////////
///  ���ݻ�����id���г����ϵ���Ϣ���棬���ջ�����id���з���
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
