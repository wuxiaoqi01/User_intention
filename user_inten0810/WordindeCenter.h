
///Word indexing Center 
#ifndef _WORD_INDEXING_CENTER_H_
#define _WORD_INDEXING_CENTER_H_
////
typedef struct wimorpnode
{
	char * pword;
	int weight;
	long wbsit;
	struct wimorpnode * pnext;
}WIMORPNODE, * wmoplist;

typedef struct corpusmgnode
{
	char * psenck;   // 意图句实
	int inteval;     // 意图值
	int sclen;       // 句子长度
	int endsit;      //  
    char * pfdbak;   //小胖可是很厉害的哦，给您播放#A，希望您喜欢
	char * pkind;           //#A-Y
    struct corpusmgnode * pnext;
}CORPMGNODE, *  corpmglist;

///适应一个word
typedef struct Hashindexnode
{
	long nHashA;
	long nHashB;
	int  bExists;

	char * pwordkey;           //Wordkey
	int wdlen;
	int weight;
	int gtnum;
    corpmglist cmglist;

}HASHINDNODE, *hashindex;

//////////////////////////////////////////////////////
//////////
int Inswmoplist(wmoplist * WL, char * pword, int weight, long wbsit);
void freewmoplist(wmoplist * WL);
void printmoplist(wmoplist wplist);
int Inscorplist(corpmglist * CL, char * psenck, int sclen, int intval, int edsit, char * pfdback, char * pkind);
void cpcorplist(corpmglist * CL, corpmglist cylist);
corpmglist listeamsearch(corpmglist crlist, char * psenck, int intval, char * pkind);
void freecrplist(corpmglist * CL);
void writindwlist(corpmglist clist, FILE * fp);
void printindwlist(corpmglist clist);
void Init_indexhash(hashindex * HashX);
void free_indexhash(hashindex * HashX);
void writ_indexhash(hashindex hashxc, const char * pnduppath);
long GetHashindex(hashindex hash_xc, const char *pmkey);
int SetHashindex(hashindex * HashX, char *pwkey, int weight, char * pscenk, int inval, int sclen, int edsit, char * pfdback, char * pkind);
void winfo_2hash(TrieNode * sroot, TrieNode * mroot, hashindex * HashX, char * corpdpath);
int lexweightsort(hashindex windtable,TrieNode * sroot, TrieNode * mroot, char * puserquery, wmoplist * WL);
void intersectionlist(corpmglist clista, corpmglist clistb, corpmglist * iCL); 
void MwordAnd(hashindex windtable, wmoplist wlist, int gnum, corpmglist *MwL);
/////////////////////////
void mWindxsearch(hashindex windtable, TrieNode * sroot, TrieNode * mroot, char * puquerys, corpmglist *WrL);

#endif