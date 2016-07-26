
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"sharfuct.h"

unsigned long cryptTable[0x500];
/////////////////////////////////////
//function:去除空白字符
//parameter:
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////
int GetRealString(char *pbuf)
{
		int lLen = strlen(pbuf)-1;
		while(lLen>0 && (pbuf[lLen] == (char)0x0d || 
			pbuf[lLen] == (char)0x0a || pbuf[lLen] == ' '
			|| pbuf[lLen] == '\t' )) lLen--;
		if(lLen<0) 
		{
			*pbuf = 0;
			return lLen;
		}
		pbuf[lLen + 1] = 0;
		return lLen+1;
}

/////////////////////////////////////
//function:去除特殊字符串
//parameter:
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////
int removalspecstr(const char *psource, char * ptarget)
{
	int kb = 0, ln;
    char * p, *q, *s, *k;
	
	if(psource == NULL || *psource == 0)
		return kb;
	k = ptarget;
	p = (char *) psource;
	while(* p != 0)
	{
		q = NULL;
		q = strchr(p, '&');
		if(q != NULL)
		{
			s = NULL;
			s = strchr(p, ';');
			if(s!= NULL)
			{
				ln = 0;
			    ln = q - p;
                strncpy(k, p, ln);
				*(k+ln) = 0;
				kb += ln;
				k = k + ln;
				p = s + 1;
			}
			else
			{
				ln = strlen(p);
				strncpy(k, p, ln);
				*(k+ln) = 0;
				kb += ln;
				break;
			}
		}
		else
		{
		    ln = strlen(p);
			strncpy(k, p, ln);
			*(k+ln) = 0;
			break;
		}
	}
	return kb;
}

/////////////////////////////////////
//function:去除()里字符串
//parameter:
//author: wuxiaoqi
//time: 2016-3-23
/////////////////////////////////////
int removbrackstr(const char *psource, char * ptarget)
{
	int kb = 0, ln;
    char * p, *q, *s, *k;
	

	if(psource == NULL || *psource == 0)
		return kb;
	k = ptarget;
	p = (char *) psource;
	while(* p != 0)
	{
		q = NULL;
		q = strchr(p, '(');
		if(q != NULL)
		{
			s = NULL;
			s = strchr(p, ')');
			if(s!= NULL)
			{
				ln = 0;
			    ln = q - p;
                strncpy(k, p, ln);
				*(k+ln) = 0;
				kb += ln;
				k = k + ln;
				p = s + 1;
			}
			else
			{
				ln = strlen(p);
				strncpy(k, p, ln);
				*(k+ln) = 0;
				kb += ln;
				break;
			}
		}
		else
		{
		    ln = strlen(p);
			strncpy(k, p, ln);
			*(k+ln) = 0;
			break;
		}
	}
	return kb;
}
//////////////////////////////////////////////////////////////////////
///function:置换位置解决冲突
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////////////////////////////////
void prepareCryptTable()
{
	unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;
	for( index1 = 0; index1 < 0x100; index1++ )
	{
		for( index2 = index1, i = 0; i < 5; i++, index2 += 0x100)
		{
			unsigned long temp1, temp2;
			seed = (seed * 125 + 3) % (0x2AAAAB);
			temp1 = (seed & 0xFFFF)<<(0x10);
			seed = (seed * 125 + 3) %(0x2AAAAB);
			temp2 = (seed & 0xFFFF);
			cryptTable[index2] = ( temp1 | temp2 );
		}	
	}
}

////////////////////////////////////////////////////////////////
///function:哈希函数
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////////////////////////
unsigned long HashString(const char *lptermName, unsigned long dwHashType)
{
	unsigned char *key  = (unsigned char *)lptermName;
	unsigned long seed1 = 0x7FED7FED;
	unsigned long seed2 = 0xEEEEEEEE;
	int ch;

	while( *key != 0 )
	{
		ch = *key++;
		seed1 = cryptTable[(dwHashType<<8) + ch] ^ (seed1 + seed2);
		seed2 = ch + seed1 + seed2 + (seed2<<5) + 3;
	}
	return seed1;
}
////////////////////////////////
///function: 
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
//////////////////////////////////
#define __malloc(x) malloc(x)
#define __free(x) free(x)
#define __assert(x)
#ifdef DEBUG
static void __kmp_test(unsigned char *W, unsigned int wlen, unsigned int *T)
{
	unsigned int i=0;
	printf("i:\tW[i]\tT[i]\n");
	while(i<wlen)
	{
		printf("%d:\t%c\t%d\n", i, W[i], T[i]);
		i++;
	}
}
#endif
////////////////////////////////
///function: 
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
//////////////////////////////////
static void __kmp_table(unsigned char *W, unsigned int wlen, unsigned int *T)
{
	unsigned int pos=2, cnd=0;
	T[0]=-1;
	T[1]=0;
	while(pos < wlen)
	{
		if (W[pos-1] == W[cnd])
		{
			cnd = cnd+1;
			T[pos] = cnd;
			pos = pos+1;
		}
		else if (cnd > 0)
		{
			cnd = T[cnd];
		}
		else
		{
			T[pos]=0;
			pos=pos+1;
		}

	}
}
////////////////////////////////
///function: 串查找KMP算法
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
//////////////////////////////////
unsigned int kmp_search(unsigned char *S, unsigned int slen, unsigned char *W, unsigned int wlen)
{
	unsigned int m=0, i=0;
	unsigned int *T;

	__assert(S && W);
	T = (unsigned int*)__malloc(wlen * sizeof(unsigned int));
	__assert(T);
	__kmp_table(W, wlen, T);

	#ifdef DEBUG
	__kmp_test(W, wlen, T);
	#endif

	while (m+i < slen)
	{
		if (W[i] == S[m+i])
		{
			if (i == wlen-1) 
			{
				__free(T);
				return m;
			}
			i = i+1;
		} 
		else
		{
			m = m+i-T[i];
			if (T[i] > -1)
				i = T[i];
			else
				i = 0;
		}
	}
	__free(T);
	return slen;
}

///////////////////////////////////////////////////////////
//function: 
//parameter:
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////////////////////
int min(int a, int b, int c)
{
	if(a < b)
	{
		if(a < c)
			return a;
		else
			return c;
	}
	else
	{
		if(b < c)
			return b;
		else
			return c;
	}
}
///////////////////////////////////////////////////////////
//function: 相似比较
//parameter:
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////////////////////
int compute_distance(char *strA, int len_a, char *strB, int len_b, int **temp)
{
	int i, j;
	for(i = 1; i <= len_a; i++)
	{
		temp[i][0] = i;
	}
	
	for(j = 1; j <= len_b; j++)
	{
		temp[0][j] = j;
	}
	temp[0][0] = 0;

	for(i = 1; i <= len_a; i++)
	{
		for(j = 1; j <= len_b; j++) 
		{
			if(strA[i-1] == strB[j-1])
			{
				temp[i][j] = temp[i-1][j-1];
			}
			else
			{
				temp[i][j] = min(temp[i-1][j], temp[i][j-1], temp[i-1][j-1]) + 1;
			}
		}
	}
	return temp[len_a][len_b];
}

///////////////////////////////////
////function:插入一个单词
////parameter: 
////author: wuxiaoqi
////time: 2016-3-23
/////////////////////////////////////////////////////
void Insert(unsigned char * word, int weight, TrieNode *root)
{
     int i;
     TrieNode *cur;
     if(word[0]=='\0')
         return;
     cur=root;
     for(i=0;word[i]!='\0';i++)
     {
         if(cur->next[word[i]]==NULL)
         {
             TrieNode *newNode = (TrieNode *)malloc(sizeof(TrieNode));
             memset(newNode,0,sizeof(TrieNode));
             cur->next[word[i]]=newNode;
         }
         cur=cur->next[word[i]];
     }
	 cur->weight = weight;
     cur->count++;
     return;
}
///////////////////////////////////////////////
////function:查找一个单词是不是在树中
////parameter: 
////author: 
////time: 2016-3-23
///////////////////////////////////////////////////
int Find(TrieNode *root,unsigned char *word)
 {
     int i;
     TrieNode *cur;
     cur=root;
     for(i=0;word[i]!='\0';i++)
     {
         if(cur->next[word[i]]==NULL)
         {
             return 0;
         }
         cur=cur->next[word[i]];
     }

     if(cur->count)
	 {
         return cur->weight;
	 }
     else
         return 0;
}
///////////////////////////////////////////////////////
////function:将整重要词文件插入trie tree
////parameter: 
////author: wuxiaoqi
////time: 2016-3-23
////////////////////////////////////////////
void impW_instrie(TrieNode *&root, const char * impwpath)
{
	FILE * fp;
	int ln, mval;
	char * pbuf, *p, *pmword;

	if(impwpath == NULL || *impwpath == 0)
		return  ;

    fp = NULL;
	fp = fopen(impwpath, "rb");
	if(fp == NULL)
		return ;

	root = (TrieNode *)malloc(sizeof(TrieNode));
    memset(root,0,sizeof(TrieNode));

	pmword = (char *)malloc(1024);
    * pmword = 0;
	pbuf =(char *)malloc(1024);
    *pbuf = 0;

	while(fgets(pbuf, 1024, fp))
	{
		ln = 0;
		ln = GetRealString(pbuf);

		if(ln <= 0 || ln >255)
			continue;

        mval = 0;
        p = NULL;
		p = strchr(pbuf, 0x09);
		if(p != NULL)
		{
			ln = 0;
			ln = p - pbuf;

			* pmword = 0;
			strncpy(pmword, pbuf, ln);
			*(pmword + ln) = 0;

            ++p;
            mval = 0;
			mval = atoi(p);
            Insert((unsigned char * )pmword, mval, root);
		}
        *pbuf = 0;
	}
	free(pmword);
    free(pbuf);
    fclose(fp);
}
///////////////////////////////////////////////////////
////function:将整个停用词文件插入trie tree
////parameter: 
////author: wuxiaoqi
////time: 2016-3-23
////////////////////////////////////////////
void StopW_instrie(TrieNode *&root, const char * stopwpath)
{
	FILE * fp;
	int ln;
	char * pbuf;

	if(stopwpath == NULL || *stopwpath == 0)
		return  ;

    fp = NULL;
	fp = fopen(stopwpath, "rb");
	if(fp == NULL)
		return ;

	root = (TrieNode *)malloc(sizeof(TrieNode));
    memset(root,0,sizeof(TrieNode));

	pbuf =(char *)malloc(1024);
    *pbuf = 0;

	while(fgets(pbuf, 1024, fp))
	{
		ln = 0;
		ln = GetRealString(pbuf);

		if(ln <= 0 || ln >255)
			continue;
		Insert((unsigned char * )pbuf, 1, root);
        *pbuf = 0;
	}
    free(pbuf);
    fclose(fp);
}
///////////////////////////////////////////////////////////
//function: 
//parameter:
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////////////////////
char * Removdisabw(TrieNode *root, char * psegmbuf, char * presegmky)
{
	char *p, *q, *pkeym;
	int ln;
	bool btkf;

	if(psegmbuf == 0 || *psegmbuf == 0)
		 return presegmky;
	pkeym = (char *) malloc(256);
	*pkeym = 0;

	p = psegmbuf;
	while(*p != 0)
	{
		q = NULL;
		q = strchr(p, 0x20);
		if(q != NULL)
		{
			ln = 0;
			ln = q - p;
			*pkeym = 0;
			strncpy(pkeym, p, ln);
			*(pkeym+ln) = 0;

			btkf = false;
			btkf = Find(root, (unsigned char *)pkeym);
            if(btkf == false)
			{
				ln = 0;
				ln = GetRealString(pkeym);
				if(ln > 0 && ln <254)
				{
					strcat(presegmky, pkeym);
					strcat(presegmky, " ");
				}
			}
            p = q + 1;
		}
        else
		{
            btkf = false;
			btkf = Find(root, (unsigned char *)p);
            if(btkf == false)
			{
				ln = 0;
				ln = GetRealString(p);
				if(ln > 0 && ln <254)
					strcat(presegmky, p);
			}
			break;
		}
	}
	free(pkeym);
    return presegmky;
}
////////////////////////////////
///function: 插入链表1
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
//////////////////////////////////
int ins_2desklist(descklist *DL, const char * pdeskey, const char * corrule, int desval)
{
	descklist pn, pr, pk;
	int ln, kbit, pbit;

	if(pdeskey == NULL || *pdeskey == 0)
		return 0;

	pr = NULL;
	pk = *DL;
	while(pk != NULL)
	{
		kbit = -1;
		kbit = strcmp(pdeskey, pk->desckey);
		pbit = -1;
        pbit = strcmp(corrule, pk->corrule); 
		if(pbit == 0 && kbit == 0)
			break;

		pr = pk;
		pk = pk->pnext;
	}
    if(pbit == 0 &&kbit == 0 && pk != NULL)
		return 0;
	else
	{
		pn = NULL;
		pn = (DESCKNODE *)malloc(sizeof(DESCKNODE));
		if(pn != NULL)
		{
			pn->desckey = NULL;
			ln = 0;
			ln = strlen(pdeskey);
			if(ln >=0)
			{
				pn->desckey = (char *)malloc(ln+1);
				strncpy(pn->desckey, pdeskey, ln);
				*(pn->desckey + ln) = 0;
			}

			pn->corrule = NULL;
			ln = 0;
			ln = strlen(corrule);
			if(ln >= 0)
			{
				pn->corrule = (char *)malloc(ln+1);
                strncpy(pn->corrule, corrule, ln);
			    *(pn->corrule + ln) = 0;
			}

			pn->dsval = desval;
            pn->pnext = NULL;

            if(pr == NULL)
			{
				pn->pnext = *DL;
				*DL = pn;
                return 1;
			}
			else
			{
				pn->pnext = pk;
				pr->pnext = pn;
				return 1;
			}
		}
		else
		{
			printf("No memory can be used !!!\n");
			return 0;
		}
	}
	return 0;
}
////////////////////////////////
///function: 插入链表
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
//////////////////////////////////
int ins_DeskList(descklist *DL, const char * pdeskey, const char * corrule, int desval)
{
    descklist pn, pr, pk;
	int ln, kbit;

	if(pdeskey == NULL || *pdeskey == 0)
		return 0;

	pr = NULL;
	pk = *DL;
	while(pk != NULL)
	{
		kbit = -1;
		kbit = strcmp(pdeskey, pk->desckey);
		if(kbit == 0 && pk->dsval == desval)
			break;

		pr = pk;
		pk = pk->pnext;
	}
    if(pk != NULL && kbit == 0 && pk->dsval == desval)
		return 0;
	else
	{
		pn = NULL;
		pn = (DESCKNODE *)malloc(sizeof(DESCKNODE));
		if(pn != NULL)
		{
			pn->desckey = NULL;
			ln = 0;
			ln = strlen(pdeskey);
			if(ln >=0)
			{
				pn->desckey = (char *)malloc(ln+1);
				strncpy(pn->desckey, pdeskey, ln);
				*(pn->desckey + ln) = 0;
			}

			pn->corrule = NULL;
			ln = 0;
			ln = strlen(corrule);
			if(ln >= 0)
			{
				pn->corrule = (char *)malloc(ln+1);
                strncpy(pn->corrule, corrule, ln);
			    *(pn->corrule + ln) = 0;
			}

			pn->dsval = desval;
            pn->pnext = NULL;

            if(pr == NULL)
			{
				pn->pnext = *DL;
				*DL = pn;
                return 1;
			}
			else
			{
				pn->pnext = pk;
				pr->pnext = pn;
				return 1;
			}
		}
		else
		{
			printf("No memory can be used !!!\n");
			return 0;
		}
	}
	return 0;
}
///////////////////////////////////////////////////////////
//function: 实体链表释放
//parameter:
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////////////////////
void freeDeslist(descklist *DL)
{
	descklist pk, pa;
	if(*DL == NULL)
		return ;
    pa = NULL;
	pk = *DL;
	while(pk != NULL)
	{
		pa = pk;
		pk = pk->pnext;

		if(pa->desckey != NULL)
		{
			free(pa->desckey);
			pa->desckey = NULL;
		}
		
		pa->dsval = 0;
		free(pa);
		pa = NULL;
	}
	*DL =NULL;
}
///////////////////////////////////////////////////////////
//function: 
//parameter:
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////////////////////
void writcpdlist(descklist dlist, FILE * fp)
{
	descklist pl;

	if(dlist == NULL)
		return ;
	pl = dlist;
	while(pl != NULL)
	{
		
		fprintf(fp, "<%s\t%s\t%d>", pl->desckey, pl->corrule, pl->dsval);
		pl = pl->pnext;
	}
}
///////////////////////////////////////////////////////////
//function: 拷贝链表
//parameter:
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////////////////////
void CpDeslist(descklist *DL, descklist dlist)
{
	descklist pl;
	if(dlist == NULL)
		return ;
	pl = dlist;
	while(pl != NULL)
	{
		ins_DeskList(DL, pl->desckey, pl->corrule, pl->dsval);
		pl = pl->pnext;
	}
}
///////////////////////////////////////////////////////////
//function: 
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
int multfdback2list(descklist *FL, const char * pmfeedbk)
{
	int mgnum = 0, ln;
	char *p, *q, *s, *fdbkgz, * pzjky;

	if(pmfeedbk == NULL || *pmfeedbk == 0)
		return mgnum;

	pzjky = (char *)malloc(2048);
	fdbkgz = (char *)malloc(2048);

	p = (char *)pmfeedbk;
//printf(" :: === %s \n",pmfeedbk); 
	while(*p != 0)
	{
		q = NULL;
		q = strstr(p, "-:-");
		if(q != NULL)
		{
			ln = 0;
			ln = q - p;
			*pzjky = 0;
			strncpy(pzjky, p, ln);
			*(pzjky + ln) = 0;

			s = NULL;
			s = strstr(pzjky, "-##-");
			if(s != NULL)
			{
				ln = 0;
				ln = s - pzjky;
				*fdbkgz = 0;
				strncpy(fdbkgz, pzjky, ln);
				*(fdbkgz + ln) = 0;
				s += 4;
                mgnum += ins_2desklist(FL, s, fdbkgz, 1);

			}
			else
				mgnum += ins_2desklist(FL, pzjky, "", 1);	
			p = q + 3;
		}
		else
		{
			s = NULL;
			s = strstr(pzjky, "-##-");
			if(s != NULL)
			{
				ln = 0;
				ln = s - p;
				*fdbkgz = 0;
				strncpy(fdbkgz, p, ln);
				*(fdbkgz + ln) = 0;
				s += 4;
        mgnum += ins_2desklist(FL, s, fdbkgz, 1);
			}
			else
					mgnum += ins_2desklist(FL, p, "", 1);
			break;
		}
	}
    if(fdbkgz != NULL)
		free(fdbkgz);
	if(pzjky != NULL)
		free(pzjky);
	return mgnum;
}