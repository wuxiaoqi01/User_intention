//Autonomous intention 
#ifndef _AUTONOMOUS_INTENTION_H_
#define _AUTONOMOUS_INTENTION_H_
#include"WordindeCenter.h"
#include"paralocafdback.h"
//////////////////////////////////////
//////
//////
//////
//////////////////////////////////////
#define	 PARM_SITRMAX	16

typedef struct paranryknode
{
	char * parmpaty;   //述求句按参数种类退换
	char * parmback;   //参数组合对
    char * psencek;    //场景编码
	char * parkcmb;    //参数种类组描述 #A-Y;#B-Y 
	int intenval;      //意图id
    struct paranryknode * pnext;
}PARANRYKNODE, * parmaylist;

///////////////
int segparareplace(hashinfotabl cptable, const char * purequisegmt, long * parmsitay);
int ins_PCmbList(parmaylist *DL, const char * parmpaty, const char * parcmbkey, const char * psenckey, const char * parkdcmb, int intenval);
void freePMblist(parmaylist *DL);
void prinpmlist(parmaylist mlist);

char * FULL_SUB_MATCH(hashinfotabl schash, char * kuquery, char * psenck, int *Ituval, char * presfdback);
int Analyparfdbkind(hashinfotabl cptable, hashpacomb cmbtable, char * puquerys, long * parmsitay, int gnum, parmaylist * KL);
char * fdbackparaminst(hashinfotabl cptable, char * kypfdback, char * psenc, int itenval, long * parmsit, int gnum, char * pfeedback);
int Dfbackusintent(hashsptable hspt, char * probotid, hashinfotabl schash, hashindex windtable, hashtable mwhash, TrieNode *root, TrieNode * mroot, char ** PWarry, parmaylist ptlist, char * psenck, int *Ituval, char * presfdback);
char * uqeryWordsimi(hashinfotabl schash, hashinfotabl cptable, hashpacomb cmbtable, char * kuquery, char * psenck, int *Ituval, char * presfdback);
void robotpointmg(hashsptable * HMP, char * probotid, char * psenck, int itenval, int endbit, long *yparsit, int gum);
char * usercontextanys(hashsptable * HMP, hashinfotabl cptable, hashpacomb cmbtable, hashploctable clohash, char * probotid, long * parmsit, int gnum, char * psenck, int *Ituval, char * presfdback);
char *Userinteninparmg(hashsptable * HMP, hashinfotabl schash, hashindex windtable, hashtable mwhash, TrieNode *root, TrieNode * mroot, char ** PWarry, hashinfotabl cptable, hashpacomb cmbtable,
                                     hashploctable clohash, char * probotid, char * kuquery, char * psenck, int *Ituval, char * presfdback);
char * UintenanayBrpsav(hashsptable * HMP, hashinfotabl schash, hashtable mwhash, TrieNode *root, char ** PWarry, hashinfotabl cptable, hashpacomb cmbtable,
                                     hashploctable clohash, char * probotid, char * kuquery, char * psenck, int *Ituval, char * presfdback);
#endif
