
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"sharfuct.h"
#include"sencparampai.h"
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
void Init_pcmbhash(hashpacomb * HashCB)
{
	long i;
	prepareCryptTable();
	*HashCB = (HASHPRCOMBNODE*)malloc(sizeof(HASHPRCOMBNODE) * DCHASH_SIZE);
	if(*HashCB ==NULL)
		return ;
	
	for(i = 0; i<DCHASH_SIZE; i++)
	{
		((*HashCB)+i)->bExists = 0;
		((*HashCB)+i)->nHashA = -1;
		((*HashCB)+i)->nHashB = -1;
        
		((*HashCB)+i)->parcombk = NULL;
        ((*HashCB)+i)->pcombky = NULL;
        ((*HashCB)+i)->intenval = 0;
        ((*HashCB)+i)->psenckey = NULL;
	}
}
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
void free_pcmbhash(hashpacomb * HashCB)
{
	long i;
	if(*HashCB == NULL)
	{
		//HashCB = NULL;
		return ;
	}
	for(i = 0; i<DCHASH_SIZE; i++)
	{
		if(	((*HashCB)+i)->bExists != 0)
		{
			((*HashCB)+i)->bExists = 0;
			((*HashCB)+i)->nHashA = -1;
			((*HashCB)+i)->nHashB = -1;

			if(((*HashCB)+i)->parcombk != NULL)
			{
				free(((*HashCB)+i)->parcombk);
				((*HashCB)+i)->parcombk = NULL;
			}
		    
            if(((*HashCB)+i)->psenckey != NULL)
			{
				free(((*HashCB)+i)->psenckey);
				((*HashCB)+i)->psenckey = NULL;
			}
			if(((*HashCB)+i)->pcombky != NULL)
			{
				free(((*HashCB)+i)->pcombky);
				((*HashCB)+i)->pcombky = NULL;
			}
			((*HashCB)+i)->intenval = 0;
		}
	}
	free(*HashCB);
	*HashCB = NULL;
}
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
void writ_pcmbhash(hashpacomb hashcb, const char * pcmbpath)
{
	FILE * fw;
	long i;

	if(pcmbpath == NULL || * pcmbpath== 0)
		return ;
    fw = fopen(pcmbpath, "wb");
	if(fw == NULL)
		return ;

	if(hashcb == NULL)
		return ;

    for(i = 0; i<DCHASH_SIZE; i++)
	{
		if((hashcb+i)->bExists != 0)
		{
			if((hashcb+i)->parcombk != NULL)
				fprintf(fw, "%s\t", (hashcb+i)->parcombk);
			if((hashcb+i)->pcombky != NULL)
				fprintf(fw, "%s\t", (hashcb+i)->pcombky);
			if((hashcb+i)->psenckey != NULL)
				fprintf(fw, "%s\t", (hashcb+i)->psenckey);
            fprintf(fw, "%d\n", (hashcb+i)->intenval);
		}
	}
	fclose(fw);
}
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
long GetHashpcmb(hashpacomb hash_cb, const char *parcombkey)
{
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString(parcombkey, HASH_OFFSET);
	unsigned long nHashA = HashString(parcombkey, HASH_A);
	unsigned long nHashB = HashString(parcombkey, HASH_B);
	unsigned long nHashStart = nHash % DCHASH_SIZE, nHashPos = nHashStart;
	
	while((hash_cb +nHashPos)->bExists)
	{
		if((hash_cb +nHashPos)->nHashA == (long) nHashA && (hash_cb +nHashPos)->nHashB == (long) nHashB)
			return nHashPos;
		else
			nHashPos = (nHashPos + 1)%DCHASH_SIZE;
		if(nHashPos == nHashStart)
			break;
	}
	return -1;
}
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
int SetHashpcmb(hashpacomb * HashCB, const char *parcombky, const char * senckey, int intenval, const char * pcombkz)
{
	int ln;
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString(parcombky, HASH_OFFSET);
	unsigned long nHashA = HashString(parcombky, HASH_A);
	unsigned long nHashB = HashString(parcombky, HASH_B);
	unsigned long nHashStart = nHash%DCHASH_SIZE, nHashPos = nHashStart;

	while(((*HashCB)+nHashPos)->bExists)
	{
		nHashPos = (nHashPos + 1)%DCHASH_SIZE;
		if (nHashPos == nHashStart)
			return 0;
	}
	((*HashCB)+nHashPos)->bExists = 1;
	((*HashCB)+nHashPos)->nHashA = nHashA;
	((*HashCB)+nHashPos)->nHashB = nHashB;

    if(parcombky != NULL && *parcombky != 0)
	{
		ln = 0;
		ln = strlen(parcombky);
		((*HashCB)+nHashPos)->parcombk = (char *)malloc(ln+1);
		strncpy(((*HashCB)+nHashPos)->parcombk, parcombky, ln);
		*(((*HashCB)+nHashPos)->parcombk + ln) = 0;	 
	}
    ((*HashCB)+nHashPos)->intenval = intenval;

	if(senckey != NULL && *senckey != 0)
	{
		ln = 0;
		ln = strlen(senckey);
		((*HashCB)+nHashPos)->psenckey = (char *)malloc(ln+1);
		strncpy(((*HashCB)+nHashPos)->psenckey, senckey, ln);
		*(((*HashCB)+nHashPos)->psenckey + ln) = 0;	 
	}

	if(pcombkz != NULL && *pcombkz != 0)
	{
		ln = 0;
		ln = strlen(pcombkz);
		((*HashCB)+nHashPos)->pcombky = (char *)malloc(ln+1);
		strncpy(((*HashCB)+nHashPos)->pcombky, pcombkz, ln);
		*(((*HashCB)+nHashPos)->pcombky + ln) = 0;	 
	}
	return 1;
}
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
void parmcombpair2hash(hashpacomb * HashCB, const char * prcombpath)
{
	FILE * fp;
	int ln, intenvl;
	char * pbuf, *p, *q, *s, *parcombk, * psenck;
	long lckbit = -1;
    
	if(prcombpath == NULL || *prcombpath == 0)
		return ;
    fp = NULL;
	fp = fopen(prcombpath, "rb");
	if(fp == NULL)
		return ;
    parcombk = (char *)malloc(8192);
	psenck = (char *)malloc(64);
	pbuf = (char *)malloc(1<<20);
	*pbuf = 0;
	while(fgets(pbuf, 1<<20, fp))
	{
		ln = 0;
		ln = GetRealString(pbuf);

		if(ln <= 0)
			continue;

		p = NULL;
		p = strstr(pbuf, "####-:-");
		if(p == NULL)
			continue;
		ln = 0;
		ln = p - pbuf;
		*parcombk = 0;
		strncpy(parcombk, pbuf, ln);
		*(parcombk+ln) = 0;

		p += 7;
		q = NULL;
        q = strstr(p, "-:-");
		if(q == NULL)
            continue;
		ln = 0;
		ln = q - p;
		*psenck = 0;
        strncpy(psenck, p, ln);
		*(psenck+ln) = 0;

		q += 3;
        intenvl = 0;
		intenvl = atoi(q);

		s = NULL;
		s = strstr(q, "-:-");
		if(s == NULL)
			continue;
		s += 3;

		lckbit = -1;
        lckbit = GetHashpcmb(*HashCB, parcombk);
        if(lckbit >= 0)
		{

		}
		else
		{
			SetHashpcmb(HashCB, parcombk, psenck, intenvl, s);
		}
		*pbuf = 0;
	}
    free(pbuf);
	pbuf = NULL;
	free(psenck);
	psenck = NULL;
	free(parcombk);
	parcombk = NULL;
    fclose(fp);
}