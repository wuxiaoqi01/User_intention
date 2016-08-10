
#ifndef _SHARING_FUNCTION_H_
#define _SHARING_FUNCTION_H_

#define	DCHASH_SIZE	5000000
#define	LEXC_SIZE	256

#define MAXTRL 256 
#define MAXLEN 256

typedef struct TrieNode
{
	int count;
	int weight;
	struct TrieNode *next[MAXTRL];
}TrieNode;

////////////
typedef struct descknode
{
	char * desckey;   //(fdback)(enty para senc)
	char * corrule;   //        (#A)
	int dsval;        //(Õý¸º)  (intentval)
    struct descknode * pnext;
}DESCKNODE, * descklist;

////////////

int GetRealString(char *pbuf);
int removalspecstr(const char *psource, char * ptarget);
int removbrackstr(const char *psource, char * ptarget);
void prepareCryptTable();
unsigned long HashString(const char *lptermName, unsigned long dwHashType);

static void __kmp_test(unsigned char *W, unsigned int wlen, unsigned int *T);
static void __kmp_table(unsigned char *W, unsigned int wlen, unsigned int *T);
unsigned int kmp_search(unsigned char *S, unsigned int slen, unsigned char *W, unsigned int wlen);

void Insert(unsigned char * word, TrieNode *root);
int Find(TrieNode *root, unsigned char *word);
void StopW_instrie(TrieNode *&root, const char * stopwpath);
void impW_instrie(TrieNode *&root, const char * impwpath);
char * Removdisabw(TrieNode *root, char * psegmbuf, char * presegmky);

int min(int a, int b, int c);
int compute_distance(char *strA, int len_a, char *strB, int len_b, int **temp);

int __simimin(int a, int b, int c);
int __simicmp_distancA(char *strA, int pABegin, int pAEnd, char *strB, int pBBegin, int pBEnd, int **temp);
int str2similar(const char * pAcomkey, const char *pBcomkey);

int ins_DeskList(descklist *DL, const char * pdeskey, const char * corrule, int desval);
void freeDeslist(descklist *DL);
void CpDeslist(descklist *DL, descklist dlist);
void writcpdlist(descklist dlist, FILE * fp);
int multfdback2list(descklist *FL, const char * pmfeedbk);
#endif

