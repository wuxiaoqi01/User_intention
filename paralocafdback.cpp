#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"sharfuct.h"
#include"paralocafdback.h"
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
void Init_plochash(hashploctable * HC)
{
	long i;
	prepareCryptTable();
	*HC = (HASHPRLCNODE*)malloc(sizeof(HASHPRLCNODE) * DCHASH_SIZE);
	if(* HC ==NULL)
		return ;
	
	for(i = 0; i<DCHASH_SIZE; i++)
	{
		((*HC)+i)->bExists = 0;
		((*HC)+i)->nHashA = -1;
		((*HC)+i)->nHashB = -1;
        
		((*HC)+i)->dscore = 0.0001;
        ((*HC)+i)->intuval = 0;
		((*HC)+i)->parlockey = NULL;
		((*HC)+i)->pfdback = NULL;
		((*HC)+i)->pscenk = NULL;
		((*HC)+i)->pckind= NULL;
	}
}
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
void free_plochash(hashploctable * HC)
{
	long i;

	if(* HC == NULL)
	{
		HC = NULL;
		return ;
	}
	for(i = 0; i<DCHASH_SIZE; i++)
	{
		if(	((*HC)+i)->bExists != 0)
		{
			((*HC)+i)->bExists = 0;
			((*HC)+i)->nHashA = -1;
			((*HC)+i)->nHashB = -1;

			if(((*HC)+i)->parlockey != NULL)
			{
				free(((*HC)+i)->parlockey);
				((*HC)+i)->parlockey = NULL;
			}
		
			((*HC)+i)->dscore = 0.00001;
			((*HC)+i)->intuval = 0;

			if(((*HC)+i)->pfdback != NULL)
			{
				free(((*HC)+i)->pfdback);
				((*HC)+i)->pfdback = NULL;
				
			}
			if(((*HC)+i)->pscenk != NULL)
			{
				free(((*HC)+i)->pscenk);
				((*HC)+i)->pscenk = NULL;		
			}
			if(((*HC)+i)->pckind != NULL)
			{
				free(((*HC)+i)->pckind);
				((*HC)+i)->pckind = NULL;		
			}
		}
	}
	free(*HC);
	*HC = NULL;
}
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
void writ_plochash(hashploctable hploc, const char * pnduppath)
{
	FILE * fw;
    long i;

	if(pnduppath == NULL || * pnduppath== 0)
		return ;
	if(hploc == NULL)
		return ;
    fw = fopen(pnduppath, "wb");
	if(fw == NULL)
		return ;
	
	for(i = 0; i<DCHASH_SIZE; i++)
	{
		if((hploc+i)->bExists != 0)
		{
			fprintf(fw, "%s--#--", (hploc+i)->parlockey);
			fprintf(fw, "%s--#--", (hploc+i)->pfdback);
			fprintf(fw, "%s--#--", (hploc+i)->pscenk);
			fprintf(fw, "%d--#--", (hploc+i)->intuval);
			fprintf(fw, "%f", (hploc+i)->dscore);
			fprintf(fw, "\n");
		}
	}
	fclose(fw);
}
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
long GetHashploc(hashploctable hploc, const char *pmkey)
{
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString(pmkey, HASH_OFFSET);
	unsigned long nHashA = HashString(pmkey, HASH_A);
	unsigned long nHashB = HashString(pmkey, HASH_B);
	unsigned long nHashStart = nHash % DCHASH_SIZE, nHashPos = nHashStart;
	
	while((hploc +nHashPos)->bExists)
	{
		if((hploc +nHashPos)->nHashA == (long) nHashA && (hploc +nHashPos)->nHashB == (long) nHashB)
			return nHashPos;
		else
			nHashPos = (nHashPos + 1)%DCHASH_SIZE;
		if(nHashPos == nHashStart)
			break;
	}
	return -1;
}
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
int SetHashploc(hashploctable * HC, char *parlockey, char * pfdback, char * pscenk, int inval, char * pckind, double dscore)
{
	int ln;
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString(parlockey, HASH_OFFSET);
	unsigned long nHashA = HashString(parlockey, HASH_A);
	unsigned long nHashB = HashString(parlockey, HASH_B);
	unsigned long nHashStart = nHash%DCHASH_SIZE, nHashPos = nHashStart;
	while(((*HC)+nHashPos)->bExists)
	{
		nHashPos = (nHashPos + 1)%DCHASH_SIZE;
		if (nHashPos == nHashStart)
			return 0;
	}

	((*HC)+nHashPos)->bExists = 1;
	((*HC)+nHashPos)->nHashA = nHashA;
	((*HC)+nHashPos)->nHashB = nHashB;

    if(parlockey != NULL && *parlockey != 0)
	{
		ln = strlen(parlockey);
		((*HC)+nHashPos)->parlockey = (char *)malloc(ln+1);
		strncpy(((*HC)+nHashPos)->parlockey, parlockey, ln);
		*(((*HC)+nHashPos)->parlockey + ln) = 0;	 
	}
    ((*HC)+nHashPos)->intuval = inval;
	if(pfdback != NULL && *pfdback != 0)
	{
		ln = strlen(pfdback);
		((*HC)+nHashPos)->pfdback = (char *)malloc(ln+1);
		strncpy(((*HC)+nHashPos)->pfdback, pfdback, ln);
		*(((*HC)+nHashPos)->pfdback + ln) = 0;	 
	}
    ((*HC)+nHashPos)->dscore = dscore;
	if(pscenk != NULL && *pscenk != 0)
	{
		ln = strlen(pscenk);
		((*HC)+nHashPos)->pscenk = (char *)malloc(ln+1);
		strncpy(((*HC)+nHashPos)->pscenk, pscenk, ln);
		*(((*HC)+nHashPos)->pscenk + ln) = 0;	 
	}

	if(pckind != NULL && *pckind != 0)
	{
		ln = strlen(pckind);
		((*HC)+nHashPos)->pckind = (char *)malloc(ln+1);
		strncpy(((*HC)+nHashPos)->pckind, pckind, ln);
		*(((*HC)+nHashPos)->pckind + ln) = 0;	 
	}
	return 0;
}
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
void parclocd2hash(hashploctable * HC, const char * pscorpath)
{
    int ln, intuval;
	char *pbuf, *parlockey, *pseck,*pfdkind;
	char *p, *q;
	FILE * fp;
	long lpcsit;

	if(pscorpath == NULL||* pscorpath == 0)
		return ;

	fp = NULL;
	fp = fopen(pscorpath, "rb");
    if(fp == NULL)
		return ;
   
    pbuf = (char *)malloc(1<<20);
	*pbuf = 0;
	parlockey = (char * )malloc(512);
	*parlockey = 0;
	pseck = (char * )malloc(32);
	*pseck = 0;
	pfdkind = (char * )malloc(256);
    *pfdkind = 0;

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
		*pseck = 0;
		strncpy(pseck, pbuf, ln);
		*(pseck + ln) = 0;
		p = p+1;

		intuval = 0;
		intuval = atoi(p);
		q = NULL;
		q = strchr(p, 0x09);
		if(q == NULL)
			continue;
		p = q + 1;

		q = NULL;
		q = strchr(p, 0x09);
		if(q == NULL)
			continue;
		ln = 0;
        ln = q - p;
		*pfdkind = 0;
		strncpy(pfdkind, p, ln);
		*(pfdkind + ln) = 0;

		p = q +1;

        *parlockey = 0;
		sprintf(parlockey,"%s--:--%d--:--%s", pseck, intuval, pfdkind);
		//printf("== %s\n", parlockey);
        lpcsit = -1;
		lpcsit = GetHashploc(*HC, parlockey);
		if(lpcsit >= 0)
		{
             
		}
		else
		{
			SetHashploc(HC, parlockey, p, pseck, intuval, pfdkind, 0.0001);
		}
        *pbuf = 0;
	}
	free(pfdkind);
	free(pseck);
	free(parlockey);
	free(pbuf);
	fclose(fp);
}