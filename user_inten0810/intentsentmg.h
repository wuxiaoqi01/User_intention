
#ifndef _INTENTION_SENTENCE_MANAGEMENT_H_
#define _INTENTION_SENTENCE_MANAGEMENT_H_
#define SIMVALD 0.850
typedef struct isenmgnode
{
	char * pintscen; // 意图句实体
	char * pseck;    // 场景编码
	int inteval;     // 意图值
    struct isenmgnode * pnext;
}ITSENCMGNODE, * isenmglist;



///适应一个entity
typedef struct Hashismgnode
{
	long nHashA;
	long nHashB;
	int  bExists;

	char * pwcombkey;           //Word combination
	int gtnum;
	isenmglist islist;

}HASHMANGNODE, *hashtable;


int intenssmglist(isenmglist * ISL, char * pintscen, char * pseck, int inteval);
void freesmlist(isenmglist * ISL);

void Init_mghash(hashtable * HashMg);
void free_mghash(hashtable * HashMg);

void writ_mghash(hashtable hashmg, const char * pnduppath);
long GetHashmg(hashtable hash_mg, const char *pmkey);

////////
int SetHashmg(hashtable * HashMg, char *pmkey, char * pcorscen, char * pscen, int inval);
void Dtinshashmg(hashtable * HashMg, char *pmkey, char * pcorscen, char * pscen, int inval);
int segmtw2warry(char * pymword, char ** PWarry);
void printWarry(char ** PWarry, int gnum);
char * segmWcmbored(char ** PWarry, int gnum, char * prescmbw);
int segmorderWcmb(char * pscensegm, char * pwcmbstr);
char * segmWcmbored(char ** PWarry, int gnum, char * prescmbw);
void wcmb2cormg(hashtable * HashMg, char *pmwcmbs, char * pcorscen, char * pscen, int inval);
void wmcbScenCorp2Hash(hashtable * HashMg, TrieNode *root, char ** PWarry, char * pscorpath);
char * simlquer2scen(isenmglist ilist, char * pustatqk, char *pintscen, char *pscenk, int * Intuval);
char * ustatAquery(hashtable hashmg, TrieNode *root, char ** PWarry, char * pustatqk, char *pintscen, char *pscenk, int * Intuval);
#endif


