
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"sharfuct.h"
#include"hashinfoadm.h"
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
void Init_infhash(hashinfotabl * HashtB)
{
	long i;
	prepareCryptTable();
	* HashtB = (HASHINFONODE*)malloc(sizeof(HASHINFONODE) * DCHASH_SIZE);
	if(* HashtB ==NULL)
		return ;
	
	for(i = 0; i<DCHASH_SIZE; i++)
	{
		((*HashtB)+i)->bExists = 0;
		((*HashtB)+i)->nHashA = -1;
		((*HashtB)+i)->nHashB = -1;
        
		((*HashtB)+i)->primarykey = NULL;
        ((*HashtB)+i)->sencdkey = NULL;
        ((*HashtB)+i)->rimval = 0;
        ((*HashtB)+i)->egnum = 0;
        ((*HashtB)+i)->endbit = 0;
		((*HashtB)+i)->fdlist = NULL;
	}
}
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
void free_infhash(hashinfotabl * HashtB)
{
	long i;
	if(*HashtB == NULL)
	{
		//HashtB = NULL;
		return ;
	}
	for(i = 0; i<DCHASH_SIZE; i++)
	{
		if(	((*HashtB)+i)->bExists != 0)
		{
			((*HashtB)+i)->bExists = 0;
			((*HashtB)+i)->nHashA = -1;
			((*HashtB)+i)->nHashB = -1;

			if(((*HashtB)+i)->primarykey != NULL)
			{
				free(((*HashtB)+i)->primarykey);
				((*HashtB)+i)->primarykey = NULL;
			}
		    
            if(((*HashtB)+i)->sencdkey != NULL)
			{
				free(((*HashtB)+i)->sencdkey);
				((*HashtB)+i)->sencdkey = NULL;
			}
			((*HashtB)+i)->rimval = 0;
			((*HashtB)+i)->endbit = 0;
			((*HashtB)+i)->egnum = 0;
			if(((*HashtB)+i)->fdlist != NULL)
			    freeDeslist(&(((*HashtB)+i)->fdlist));
		}
	}
	free(*HashtB);
	*HashtB = NULL;
}
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
void writ_infhash(hashinfotabl hashtb, const char * phtbpath)
{
	FILE * fw;
	long i;

	if(phtbpath == NULL || * phtbpath== 0)
		return ;
    fw = fopen(phtbpath, "wb");
	if(fw == NULL)
		return ;

	if(hashtb == NULL)
		return ;

    for(i = 0; i<DCHASH_SIZE; i++)
	{
		if((hashtb+i)->bExists != 0)
		{
			if((hashtb+i)->primarykey != NULL)
				fprintf(fw, "%s\t", (hashtb+i)->primarykey);
			if((hashtb+i)->sencdkey != NULL)
				fprintf(fw, "%s\t", (hashtb+i)->sencdkey);
				fprintf(fw, "%d\t", (hashtb+i)->endbit);
			fprintf(fw, "%d\t", (hashtb+i)->rimval);
			writcpdlist((hashtb+i)->fdlist, fw);
            fprintf(fw, "\n");
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
long GetHashinf(hashinfotabl hash_tb, const char *primkey)
{
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString(primkey, HASH_OFFSET);
	unsigned long nHashA = HashString(primkey, HASH_A);
	unsigned long nHashB = HashString(primkey, HASH_B);
	unsigned long nHashStart = nHash % DCHASH_SIZE, nHashPos = nHashStart;
	
	while((hash_tb +nHashPos)->bExists)
	{
		if((hash_tb +nHashPos)->nHashA == (long) nHashA && (hash_tb +nHashPos)->nHashB == (long) nHashB)
			return nHashPos;
		else
			nHashPos = (nHashPos + 1)%DCHASH_SIZE;
		if(nHashPos == nHashStart)
			break;
	}
	return -1;
}
///////////////////////////////////////////////////////////
//function: 参数信息进入hash操作
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
//////////////////////////////////////////////////////////
int sethashentpar(hashinfotabl * HashtB, const char *primkey, int rimval, int edbit, const char * psenckey, const char * pkind, int dparnb)
{
	int ln;
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString(primkey, HASH_OFFSET);
	unsigned long nHashA = HashString(primkey, HASH_A);
	unsigned long nHashB = HashString(primkey, HASH_B);
	unsigned long nHashStart = nHash%DCHASH_SIZE, nHashPos = nHashStart;

	while(((*HashtB)+nHashPos)->bExists)
	{
		nHashPos = (nHashPos + 1)%DCHASH_SIZE;
		if (nHashPos == nHashStart)
			return 0;
	}
	((*HashtB)+nHashPos)->bExists = 1;
	((*HashtB)+nHashPos)->nHashA = nHashA;
	((*HashtB)+nHashPos)->nHashB = nHashB;

    if(primkey != NULL && *primkey != 0)
	{
		ln = 0;
		ln = strlen(primkey);
		((*HashtB)+nHashPos)->primarykey = (char *)malloc(ln+1);
		strncpy(((*HashtB)+nHashPos)->primarykey, primkey, ln);
		*(((*HashtB)+nHashPos)->primarykey + ln) = 0;	 
	}
    ((*HashtB)+nHashPos)->rimval = rimval;
    ((*HashtB)+nHashPos)->endbit = edbit;
    ((*HashtB)+nHashPos)->egnum = 0;
	((*HashtB)+nHashPos)->egnum += ins_DeskList(&(((*HashtB)+nHashPos)->fdlist), psenckey, pkind, dparnb);
	return 1;
}
///////////////////////////////////////////////////////////
//function: 语料信息进入hash操作
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
int SetHashinf(hashinfotabl * HashtB, const char *primkey, const char * sencdkey, int rimval, int edbit, const char * potherkey)
{
	int ln;
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString(primkey, HASH_OFFSET);
	unsigned long nHashA = HashString(primkey, HASH_A);
	unsigned long nHashB = HashString(primkey, HASH_B);
	unsigned long nHashStart = nHash%DCHASH_SIZE, nHashPos = nHashStart;

	while(((*HashtB)+nHashPos)->bExists)
	{
		nHashPos = (nHashPos + 1)%DCHASH_SIZE;
		if (nHashPos == nHashStart)
			return 0;
	}
	((*HashtB)+nHashPos)->bExists = 1;
	((*HashtB)+nHashPos)->nHashA = nHashA;
	((*HashtB)+nHashPos)->nHashB = nHashB;

    if(primkey != NULL && *primkey != 0)
	{
		ln = 0;
		ln = strlen(primkey);
		((*HashtB)+nHashPos)->primarykey = (char *)malloc(ln+1);
		strncpy(((*HashtB)+nHashPos)->primarykey, primkey, ln);
		*(((*HashtB)+nHashPos)->primarykey + ln) = 0;	 
	}
	((*HashtB)+nHashPos)->rimval = rimval;
	((*HashtB)+nHashPos)->endbit = edbit;
	if(sencdkey != NULL && *sencdkey!= 0)
	{
		ln = 0;
		ln = strlen(sencdkey);
		((*HashtB)+nHashPos)->sencdkey = (char *)malloc(ln+1);
		strncpy(((*HashtB)+nHashPos)->sencdkey, sencdkey, ln);
		*(((*HashtB)+nHashPos)->sencdkey + ln) = 0;	 
	}
	
	((*HashtB)+nHashPos)->egnum = 0;
	((*HashtB)+nHashPos)->egnum = multfdback2list(&(((*HashtB)+nHashPos)->fdlist), potherkey);
	return 0;
}
///////////////////////////////////////////////////
//function: 场景语句，数据 2 hash
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
/////////////////////////////////////////////////
void scencorp2hash(hashinfotabl * HashtB, const char * pscecpath)
{
	FILE * fp;
	char * pbuf, *p, *q;
	int ln, gbit, znum = 0;
	long lkbit;
	char * psencbitk, * pintnkey, * pincorpus;
	int intentval, edbit; 

	if(pscecpath == NULL || *pscecpath == 0)
		return ;
    fp = NULL;
	fp = fopen(pscecpath, "rb");
	if(fp == NULL)
		return ;

	psencbitk = (char *)malloc(32);
	pintnkey = (char *)malloc(1024);
	pincorpus = (char *)malloc(1024);

	pbuf =(char *)malloc(1<<20);
	*pbuf = 0;
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
		//yuliao
		ln = 0;
		ln = p - pbuf;
        *pincorpus = 0;
        strncpy(pincorpus, pbuf, ln);
		*(pincorpus + ln) = 0;
        q = p + 1;
        //
    edbit = 0;
    edbit = atoi(q);
    p = NULL;
		p = strchr(q, 0x09);
		if(p == NULL)
			continue;
    q = p + 1;
    
		p = NULL;
		p = strchr(q, 0x09);
		if(p == NULL)
			continue;
		ln = 0;
		ln = p - q;
        * psencbitk = 0;
		strncpy(psencbitk, q, ln);
		*(psencbitk + ln) = 0;
		q = p + 1;
        //   
        intentval = 0;
		intentval = atoi(q);
        p = NULL;
		p = strchr(q, 0x09);
		if(p == NULL)
			continue;
        q = p + 1;
		lkbit = -1;
        lkbit = GetHashinf(*HashtB, pincorpus);
		if(lkbit >= 0)
		{
		}
		else
		{
			gbit = 0;
			gbit = SetHashinf(HashtB, pincorpus, psencbitk, intentval, edbit, q);
		}
        *pbuf = 0;
	}
	free(psencbitk);
	psencbitk = NULL;
	free(pintnkey);
    pintnkey = NULL;
	free(pincorpus);
	pincorpus = NULL;
    free(pbuf);
	pbuf = NULL;
    fclose(fp);
}
///////////////////////////////////////////////////
//function: 不想去学校-:-1-:-#A-:-MUSIC	3,MUSIC	6,MUSIC	9
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
/////////////////////////////////////////////////
void entyparbuf2hash(hashinfotabl * HashtB, char * pentparbuf)
{
	char * parmkey, *pzjkmt, *psenck, *pkind, *p, *q, *s;
	int ln, armval, itenval;
	long kbit;

	if(pentparbuf == NULL || *pentparbuf == 0)
		return ;

	psenck = (char *)malloc(128);
	*psenck = 0;
     
	pkind = (char *)malloc(128);
	*pkind = 0;

	parmkey = (char *)malloc(1024);
    *parmkey = 0;

	pzjkmt = (char *)malloc(512);
    *pzjkmt = 0;

	p = pentparbuf;
	q = NULL;
	q = strstr(p, "-:-");
	if(q == NULL)
        return ;
    
	ln = 0;
	ln = q - p;
	*parmkey = 0;
    strncpy(parmkey, p, ln);
	*(parmkey + ln) = 0;
	p = q +3;

	q = NULL;
	q = strstr(p, "-:-");
	if(q == NULL)
        return ;
    armval = 0;
    armval = atoi(p);
    p = q +3;

    q = NULL;
	q = strstr(p, "-:-");
	if(q == NULL)
        return ;
	ln = 0;
	ln = q - p;
	*pkind = 0;
    strncpy(pkind, p, ln);
	*(pkind + ln) = 0;
    p = q + 3;

	while(*p != 0)
	{
		q = NULL;
		q = strchr(p, ',');
		if(q != NULL)
		{
			ln = 0;
			ln = q - p;
			*pzjkmt = 0;
			strncpy(pzjkmt, p, ln);
			*(pzjkmt+ln) = 0;
            
			s = NULL;
			s = strchr(pzjkmt, 0x20);
			if(s != NULL)
			{
				ln = 0;
				ln = s - pzjkmt;
                *psenck = 0;
                strncpy(psenck, pzjkmt, ln);
				*(psenck + ln) = 0;
				++s;
                itenval = 0;
				itenval =atoi(s);
                kbit = -1;
				kbit = GetHashinf(*HashtB, parmkey);
				if(kbit >= 0)
					((*HashtB)+kbit)->egnum += ins_DeskList(&(((*HashtB)+kbit)->fdlist), psenck, pkind, itenval);
				else
					sethashentpar(HashtB, parmkey, armval, 0, psenck, pkind, itenval);  
			}
			p = q + 1;
		}
		else
		{
			s = NULL;
			s = strchr(p, 0x20);
			if(s != NULL)
			{
				ln = 0;
				ln = s - p;
                *psenck = 0;
                strncpy(psenck, p, ln);
				*(psenck + ln) = 0;
				++s;
                itenval = 0;
				itenval =atoi(s);
                kbit = -1;
				kbit = GetHashinf(*HashtB, parmkey);
				if(kbit >= 0)
					((*HashtB)+kbit)->egnum += ins_DeskList(&(((*HashtB)+kbit)->fdlist), psenck, pkind, itenval);
				else
					sethashentpar(HashtB, parmkey, armval, 0, psenck, pkind, itenval);
			}
			break;
		}
	}
    if(pzjkmt != NULL)
	{
		free(pzjkmt);
		pzjkmt = NULL;
	}
	if(parmkey != NULL)
	{
		free(parmkey);
		parmkey = NULL;
	}
	if(pkind != NULL)
	{
		free(pkind);
		pkind = NULL;
	}
	if(psenck != NULL)
	{
		free(psenck);
		psenck = NULL;
	}
}
////////////////////////////////////////////////
//function:实体参数带等级，数据 2 hash
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
/////////////////////////////////////////////////
void entyparm2hash(hashinfotabl * HashtB, const char * pentppath)
{
	FILE * fp;
	int ln;
	char * pbuf;
    
	if(pentppath == NULL || *pentppath == 0)
		return ;

    fp = NULL;
	fp = fopen(pentppath, "rb");
	if(fp == NULL)
		return ;
	pbuf =(char *)malloc(1<<20);
	*pbuf = 0;
	while(fgets(pbuf, 1<<20, fp))
	{
		ln = 0;
		ln = GetRealString(pbuf);

		if(ln <= 0)
			continue;
		entyparbuf2hash(HashtB, pbuf);
	}
    free(pbuf);
	pbuf = NULL;
    fclose(fp);
}
////////////////////////////////////////////////
//function:SC
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////
