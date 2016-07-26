
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"sharfuct.h"
#include"segment.h"
#include"intentsentmg.h"
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////////////////////////
int intenssmglist(isenmglist * ISL, char * pintscen, char * pseck, int inteval)
{
	isenmglist pn, pk, pr;
	int kbit, ln;

    if(pintscen== NULL || *pintscen == 0)
		return 0;

	pr = NULL;
	pk = *ISL;
	while(pk != NULL)
	{
		kbit = -1;
		kbit = strcmp(pintscen, pk->pintscen);
		if(kbit <= 0)
		{
             break;
		}
		pr = pk;
        pk = pk->pnext;
	}
    if(pk!= NULL && kbit == 0)
	{
		return 0;
	}
	pn = NULL;
	pn = (ITSENCMGNODE *)malloc(sizeof(ITSENCMGNODE));
	if(pn != NULL)
	{
		ln = 0;
		ln = strlen(pintscen);
		pn->pintscen = NULL;
		pn->pintscen = (char *)malloc(ln+1);
		strncpy(pn->pintscen, pintscen, ln);
		*(pn->pintscen + ln) = 0;

		if(pseck != NULL && *pseck != 0)
		{
			ln = 0;
			ln = strlen(pseck);
			pn->pseck = NULL;
			pn->pseck = (char *)malloc(ln+1);
			strncpy(pn->pseck, pseck, ln);
			*(pn->pseck + ln) = 0;
		}
        pn->inteval = inteval;
		pn->pnext = NULL;
//printf("22 ===>	%s	%s	%d\n", pintscen, pseck, inteval);
		if(pr == NULL)
		{
			pn->pnext = *ISL;
			*ISL = pn;
		     return 1;
		}
		else
		{
			pn->pnext = pk;
			pr->pnext = pn;
			return  1;
		}
	}
	else
	{
		printf("");
		return 0;
	}
	return 0;
}
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////////////////////////
void freesmlist(isenmglist * ISL)
{
	isenmglist pk, pa;
	if(*ISL == NULL)
		return ;
    pa = NULL;
	pk = *ISL;
	while(pk != NULL)
	{
		pa = pk;
		pk = pk->pnext;

		if(pa->pintscen != NULL)
		{
			free(pa->pintscen);
			pa->pintscen = NULL;
		}
		
        if(pa->pseck != NULL)
		{
			free(pa->pseck);
			pa->pseck = NULL;
		}
		pa->inteval = 0;

		free(pa);
		pa = NULL;
	}
	*ISL =NULL;

}
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////////////////////////
void Init_mghash(hashtable * HashMg)
{
	long i;
	prepareCryptTable();
	* HashMg = (HASHMANGNODE*)malloc(sizeof(HASHMANGNODE) * DCHASH_SIZE);
	if(* HashMg ==NULL)
		return ;
	
	for(i = 0; i<DCHASH_SIZE; i++)
	{
		((*HashMg)+i)->bExists = 0;
		((*HashMg)+i)->nHashA = -1;
		((*HashMg)+i)->nHashB = -1;
        
		((*HashMg)+i)->pwcombkey = NULL;
        ((*HashMg)+i)->gtnum = 0;
		((*HashMg)+i)->islist = NULL;
	}
}
////////////////////////////////////////////////////////////////
///function:哈希函数
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////////////////////////
void free_mghash(hashtable * HashMg)
{
	long i;

	if(* HashMg == NULL)
	{
		HashMg = NULL;
		return ;
	}
	for(i = 0; i<DCHASH_SIZE; i++)
	{
		if(	((*HashMg)+i)->bExists != 0)
		{
			((*HashMg)+i)->bExists = 0;
			((*HashMg)+i)->nHashA = -1;
			((*HashMg)+i)->nHashB = -1;

			if(((*HashMg)+i)->pwcombkey != NULL)
			{
				free(((*HashMg)+i)->pwcombkey);
				((*HashMg)+i)->pwcombkey = NULL;
			}
		
			((*HashMg)+i)->gtnum = 0;
			if(((*HashMg)+i)->islist != NULL)
			{
				freesmlist(&(((*HashMg)+i)->islist));
				((*HashMg)+i)->islist = NULL;
			}
		}
	}
	free(*HashMg);
	*HashMg = NULL;
}
////////////////////////////////////////////////////////////////
///function:哈希函数
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////////////////////////
void writ_mghash(hashtable hashmg, const char * pnduppath)
{
	FILE * fw;
    long i;
    isenmglist pd;

	if(pnduppath == NULL || * pnduppath== 0)
		return ;
    fw = fopen(pnduppath, "wb");
	if(fw == NULL)
		return ;
	if(hashmg == NULL)
		return ;
	for(i = 0; i<DCHASH_SIZE; i++)
	{
		if((hashmg+i)->bExists != 0)
		{
			fprintf(fw, "%s--:--", (hashmg+i)->pwcombkey);
			pd = NULL;
			pd = (hashmg+i)->islist;
			while(pd != NULL)
			{
				fprintf(fw, "%s####",pd->pintscen);
				fprintf(fw, "%s####",pd->pseck);
				fprintf(fw, "%d####\t",pd->inteval);
				pd = pd->pnext;
			}
			fprintf(fw, "\n");
		}
	}
	fclose(fw);
}
////////////////////////////////////////////////////////////////
///function:哈希函数
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////////////////////////
long GetHashmg(hashtable hash_mg, const char *pmkey)
{
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString(pmkey, HASH_OFFSET);
	unsigned long nHashA = HashString(pmkey, HASH_A);
	unsigned long nHashB = HashString(pmkey, HASH_B);
	unsigned long nHashStart = nHash % DCHASH_SIZE, nHashPos = nHashStart;
	
	while((hash_mg +nHashPos)->bExists)
	{
		if((hash_mg +nHashPos)->nHashA == (long) nHashA && (hash_mg +nHashPos)->nHashB == (long) nHashB)
			return nHashPos;
		else
			nHashPos = (nHashPos + 1)%DCHASH_SIZE;
		if(nHashPos == nHashStart)
			break;
	}
	return -1;
}
////////////////////////////////////////////////////////////////
///function:主键数据插入哈希函数
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////////////////////////
int SetHashmg(hashtable * HashMg, char *pmkey, char * pcorscen, char * pscen, int inval)
{
	int ln;
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString(pmkey, HASH_OFFSET);
	unsigned long nHashA = HashString(pmkey, HASH_A);
	unsigned long nHashB = HashString(pmkey, HASH_B);
	unsigned long nHashStart = nHash%DCHASH_SIZE, nHashPos = nHashStart;
	while(((*HashMg)+nHashPos)->bExists)
	{
		nHashPos = (nHashPos + 1)%DCHASH_SIZE;
		if (nHashPos == nHashStart)
			return 0;
	}

	((*HashMg)+nHashPos)->bExists = 1;
	((*HashMg)+nHashPos)->nHashA = nHashA;
	((*HashMg)+nHashPos)->nHashB = nHashB;

    if(pmkey != NULL && *pmkey != 0)
	{
		ln = strlen(pmkey);
		((*HashMg)+nHashPos)->pwcombkey = (char *)malloc(ln+1);
		strncpy(((*HashMg)+nHashPos)->pwcombkey, pmkey, ln);
		*(((*HashMg)+nHashPos)->pwcombkey + ln) = 0;	 
	}
    ((*HashMg)+nHashPos)->gtnum = 0;
	//printf("11 ===>	%s	%s	%d\n", pcorscen, pscen, inval);
	((*HashMg)+nHashPos)->gtnum = intenssmglist(&(((*HashMg)+nHashPos)->islist), pcorscen, pscen, inval);
	
	return 1;
}
////////////////////////////////////////////////////////////////
///function: 确认数据进入hashchu处理
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
///////////////////////////////////////////////////////////////
void Dtinshashmg(hashtable * HashMg, char *pmkey, char * pcorscen, char * pscen, int inval)
{
	long ksitv = -1;

	ksitv = -1;
	ksitv = GetHashmg(*HashMg, pmkey);
	if(ksitv >= 0)
	{
		///printf("6666===>\t%s\t%s\t%s\t%d\n", pmkey, pcorscen, pscen, inval);
		((*HashMg)+ksitv)->gtnum += intenssmglist(&(((*HashMg)+ksitv)->islist), pcorscen, pscen, inval);
	}
	else
	{
		///printf("intto<\t%s\t%s\t%s\t%d\n", pmkey, pcorscen, pscen, inval);
		SetHashmg(HashMg, pmkey, pcorscen, pscen, inval);
	}

}
////////////////////////////////////////////////////////////////
///function:切分后的去除停用词，词数组
//parameter: 
//author: wuxiaoqi
//time: 2016-7-10
///////////////////////////////////////////////////////////////
int segmtw2warry(char * pymword, char ** PWarry)
{
	int ln, znum = 0;
	char *p, *q;

	if(pymword==NULL||*pymword == 0)
		return znum;
    znum = 0;
	p = pymword;
	while(*p != 0)
	{
		q = NULL;
		q = strchr(p, 0x20);
		if(q != NULL)
		{
			ln = 0;
			ln = q - p;
			*(PWarry + znum) = NULL;
			*(PWarry + znum) = (char *)malloc(ln+1);
            strncpy(*(PWarry + znum), p, ln);
			*(*(PWarry + znum) + ln) = 0;
            ++znum;
			p = q + 1;
		}
		else
		{
			ln = 0;
			ln = strlen(p);
			*(PWarry + znum) = NULL;
			*(PWarry + znum) = (char *)malloc(ln+1);
            strncpy(*(PWarry + znum), p, ln);
			*(*(PWarry + znum) + ln) = 0;
            ++znum;
			break;
		}
	}
    return znum;
}
//////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////
void printWarry(char ** PWarry, int gnum)
{
	int i;
	for(i =0; i< gnum; i++)
	{
		if(*(PWarry+i) != NULL)
			printf(" di %d == %s\n", i, *(PWarry+i));
	}
}
////////////////////////////////////////////////////////////////
///function:切分后, 选词组合
//parameter:        (1) 顺序组合  (2) 重要优先组合  (3) 最大长度词优先组合 (4) 两种多种合组合
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
char * segmWcmbored(char ** PWarry, int gnum, char * prescmbw)
{
	int i,j,s;
	for(j = gnum; j > 1; j--)
	{
		for(i =0; i < j; i++)
		{
			strcat(prescmbw, *(PWarry+i));
            strcat(prescmbw, "-##-");
		}
		strcat(prescmbw, "--:--");
	}

	for(j = 0; j < gnum-1; j++)
	{
		for(i =j; i < gnum; i++)
		{
			strcat(prescmbw, *(PWarry+i));
            strcat(prescmbw, "-##-");
		}
		strcat(prescmbw, "--:--");
	}
    for(s = 0; s < gnum; s++)
	{
		for(j = gnum; j > 0; j--)
		{
			if(j > s)
			{
				for(i =s; i < j; i++)
				{
					strcat(prescmbw, *(PWarry+i));
					strcat(prescmbw, "-##-");
				}
				strcat(prescmbw, "--:--");
			}
		}
	}
	return prescmbw;
}

////////////////////////////////////////////////////////////////
///function:切分后, 选词组合
//parameter:        (1) 顺序组合  (2) 重要优先组合  (3) 最大长度词优先组合 (4) 两种多种合组合
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////////
int segmorderWcmb(char * pscensegm, char * pwcmbstr)
{
	int znum = 0;

    if(pscensegm == NULL && *pscensegm == 0)
		return 0;
    
	return 0;
}
////////////////////////////////////////////////////////////////
///function:多个组合串往管理hash里插入
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
void wcmb2cormg(hashtable * HashMg, char *pmwcmbs, char * pcorscen, char * pscen, int inval)
{
	char * pmwkey, *p, *q;
	int ln;
	if(pmwcmbs == NULL || *pmwcmbs == 0)
		return ;
	pmwkey = (char *)malloc(2048);
    *pmwkey = 0;
    p = pmwcmbs;
	while(*p != 0)
	{
		q = NULL;
		q = strstr(p, "--:--");
		if(q != NULL)
		{
			ln = 0;
			ln = q - p;
			*pmwkey = 0;
			strncpy(pmwkey, p, ln);
			*(pmwkey + ln) = 0;
			Dtinshashmg(HashMg, pmwkey, pcorscen, pscen, inval);
            p = q + 5;
		}
		else
		{
            Dtinshashmg(HashMg, p, pcorscen, pscen, inval);
			break;
		}
	}
    free(pmwkey);
}
////////////////////////////////////////////////////////////////
///function:Scene corpus segmentation 
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
void wmcbScenCorp2Hash(hashtable * HashMg, TrieNode *root, char ** PWarry, char * pscorpath)
{
	char * pbuf, *p, *q, *pzjk;
	int cnum, ln, inteval, slen, wlen, ires, i;
	long * parsitay;
	char * pintscen, *pseck, *parcmbk, * psegmet;

    FILE * fp;

	if(pscorpath == NULL||* pscorpath == 0)
		return ;

	fp = NULL;
	fp = fopen(pscorpath, "rb");
    if(fp == NULL)
		return ;
   
    pbuf = (char *)malloc(1<<20);
	*pbuf = 0;
	pintscen = (char * )malloc(512);
	*pintscen = 0;
	pseck = (char * )malloc(32);
	*pseck = 0;
	parcmbk = (char * )malloc(2048);
    *parcmbk = 0;
	psegmet = (char * )malloc(2048);

	pzjk = (char *)malloc(1<<20);
	*pzjk = 0;


	while(fgets(pbuf, 1<<20, fp))
	{
		ln = 0;
		ln = GetRealString(pbuf);

		if(ln <= 0)
			continue;
		p = NULL;
		p = strchr(pbuf, 0x09);
		if(p == NULL)
			continue;

		ln = 0;
		ln = p - pbuf;
		*pintscen = 0;
		strncpy(pintscen, pbuf, ln);
		*(pintscen + ln) = 0;
        
		memset(psegmet, 0, 2048);
		slen = ln;
		wlen = 2048;
        ires = 0;
        ires = repqiefen(pintscen, slen, psegmet, wlen);

		*parcmbk = 0;
	    parcmbk = Removdisabw(root, psegmet, parcmbk);

		for(i = 0; i< 32; i++)
			*(PWarry +i) = NULL;

		ires = 0;
	    ires = segmtw2warry(parcmbk, PWarry);
        *pzjk = 0;
        pzjk = segmWcmbored(PWarry, ires, pzjk);
        p++;
        
		q = NULL;
		q = strchr(p, 0x09);
		if(q == NULL)
			continue;

		ln = 0;
		ln = q - p;
		*pseck = 0;
		strncpy(pseck, p, ln);
		*(pseck + ln) = 0;
        ++q;

		parsitay = NULL;
		cnum = 0;
        inteval = 0;
		inteval = atoi(q);

        wcmb2cormg(HashMg, pzjk, pintscen, pseck, inteval);
        *pbuf = 0;
    }
	free(pzjk);
	free(psegmet);
	free(parcmbk);
	free(pseck);
	free(pintscen);
	free(pbuf);
	fclose(fp);
}

////////////////////////////////////////////////////////////////
///function:相似在链表中，查询分组
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
char * simlquer2scen(isenmglist ilist, char * pustatqk, char *pintscen, char *pscenk, int * Intuval)
{
	double smval = 0.0001;
	int i, slen, wlen, distance;
    int **temp;
	isenmglist pd;

	if(ilist == NULL)
		return pintscen;
	if(pustatqk== NULL || *pustatqk == 0)
		return pintscen;
	slen = 0;
    slen = strlen(pustatqk);
    
	pd = ilist;
	while(pd != NULL)
	{
		wlen = 0;
		wlen = strlen(pd->pintscen);
        temp = (int**)malloc(sizeof(int*) * (slen + 1));
		for(i = 0; i<slen+1; i++)
		{
			temp[i] = (int*)malloc(sizeof(int) * (wlen + 1));
			memset(temp[i], 0, sizeof(int) * (wlen + 1));
		}
		distance = 0;
        distance = compute_distance(pustatqk, slen, pd->pintscen, wlen, temp);
        //printf(" ...  %d\n", distance);
		smval = 0.00001;
		smval = 1.0 - (1.0 * distance * distance)/((slen *slen)+(wlen *wlen));
		if(smval >= SIMVALD)
		{
			strcpy(pintscen, pd->pintscen);
			strcpy(pscenk, pd->pseck);
            *Intuval = pd->inteval;
			break;
		}
		for(i = 0; i<slen+1; i++)
		{
			free(temp[i]);
			temp[i] = NULL;
		}
        free(temp);
		pd = pd->pnext;
	}
    return pintscen;
}

////////////////////////////////////////////////////////////////
///function:User statement  查询分组
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
char * ustatAquery(hashtable hashmg, TrieNode *root, char ** PWarry, char * pustatqk, char *pintscen, char *pscenk, int * Intuval)
{
	char * psegmet, *delstop, *pzjk, *p, *q, *pwck;
    int ln, i, slen, wlen, ires;
	long ksitv;

	if(pustatqk == NULL || *pustatqk ==0)
		return pintscen;
    
    psegmet = (char * )malloc(2048);
	delstop = (char * )malloc(2048);
	pzjk = (char * )malloc(1<<20);
	pwck = (char * )malloc(2048);
    memset(psegmet, 0, 2048);

	slen = strlen(pustatqk);
	wlen = 2048;
    ires = 0;
    ires = repqiefen(pustatqk, slen, psegmet, wlen);

	*delstop = 0;
	delstop = Removdisabw(root, psegmet, delstop);
    for(i = 0; i< 32; i++)
		*(PWarry +i) = NULL;

	ires = 0;
	ires = segmtw2warry(delstop, PWarry);
    *pzjk = 0;
    pzjk = segmWcmbored(PWarry, ires, pzjk);

	p = pzjk;
	while(p!= NULL && *p != 0)
	{
		q = NULL;
		q = strstr(p, "--:--");
		if(q != NULL)
		{
			ln = 0;
			ln = q - p;
			*pwck = 0;
			strncpy(pwck, p, ln);
			*(pwck +ln) = 0;
            //
			ksitv = -1;
			ksitv = GetHashmg(hashmg, pwck);
			if(ksitv >= 0)
			{
				pintscen = simlquer2scen((hashmg+ksitv)->islist, pustatqk, pintscen, pscenk, Intuval);
				if(*pintscen != 0)
				{
					if(pwck != NULL)
						free(pwck);
					if(pzjk != NULL)
						free(pzjk);
					if(delstop != NULL)
						free(delstop);
					if(psegmet != NULL)
						free(psegmet);
					return pintscen;
				}
			}
			p = q + 5;
		}
		else
		{
			ksitv = -1;
			ksitv = GetHashmg(hashmg, p);
			if(ksitv >= 0)
			{
				pintscen = simlquer2scen((hashmg+ksitv)->islist, pustatqk, pintscen, pscenk, Intuval);
				if(*pintscen != 0)
				{
                    if(pwck != NULL)
						free(pwck);
					if(pzjk != NULL)
						free(pzjk);
					if(delstop != NULL)
						free(delstop);
					if(psegmet != NULL)
						free(psegmet);
					return pintscen;
				}
			}
			break;
		}
	}
	return pintscen;  
}
