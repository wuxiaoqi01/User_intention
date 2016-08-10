
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"sharfuct.h"
#include"scenbpointsave.h"
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
int mparms2sitary(long * parsitym, long *yparsit, int gum)
{
	int znum = 0, i;

	if(yparsit == NULL)
	     return znum;
	for(i = 0; i<gum; i++)
	{
		if(*(yparsit+i) >= 0)
		{
        *(parsitym+znum) = *(yparsit+i);
			   ++znum;
		}
	}
    return znum;
}
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
int ins_bplist(bpoinlist *BL, const char * senckey, int inttval, int endstat, long *yparsit, int gum)
{
			bpoinlist pn, pk;
			int ln, i, bpbit = -1;
			pk = *BL;
		  if(pk != NULL)
		  {
				  if(pk->psenckey != NULL)
				  {
						 free(pk->psenckey);
						 pk->psenckey = NULL;
					}	
					ln = 0;
					ln = strlen(senckey);
					pk->psenckey = (char *)malloc(ln+1);
				  strncpy(pk->psenckey, senckey, ln);
					*(pk->psenckey + ln) = 0;
				 
					pk->itentval = inttval;
					pk->endbit = endstat;
				  pk->paranum = 0;
					pk->paranum = gum;
					for(i = 0;i < 32; i++)
							   *(pk->lparsity +i) = -1;
					if(gum > 0 && gum < 32)
			           mparms2sitary(pk->lparsity, yparsit, gum);
			    pk->pnext = NULL;
			    return 0;
		  }
	    else
	    {	  
					pn = NULL;
					pn = (SBKPOINTNODE *)malloc(sizeof(SBKPOINTNODE));
					if(pn != NULL)
					{
				      ln = 0;
							ln = strlen(senckey);
							pn->psenckey = (char *)malloc(ln+1);
							strncpy(pn->psenckey, senckey, ln);
							*(pn->psenckey + ln) = 0;
					
							pn->itentval = inttval;
							pn->endbit = endstat;
					    pn->paranum = 0;
							pn->paranum = gum;
						  pn->lparsity  = (long *)malloc(sizeof(long) *32);
						  for(i = 0;i < 32; i++)
							    *(pn->lparsity +i) = -1;
						  if(gum > 0 && gum < 32)
				           mparms2sitary(pn->lparsity, yparsit, gum);
				      pn->pnext = NULL;
				      pn->pnext = *BL;
							*BL = pn;
						  return 1;
					}
		  }
	    return 0;
}


///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
int ins_bplist_1(bpoinlist *BL, const char * senckey, int inttval, int endstat, long *yparsit, int gum)
{
			bpoinlist pn, pk, pr;
			int ln, i, bpbit = -1;
		  
			pr = NULL;
			pk = *BL;
	
		while(pk != NULL)
		{
				bpbit = -1;
		    bpbit = strcmp(senckey, pk->psenckey);
		    if(bpbit == 0)
		    //if(bpbit == 0 && inttval == pk->itentval)
						break;
		
				pr = pk;
				pk = pk->pnext;
		}
	   if(pk!= NULL && bpbit == 0)
    //if(pk!= NULL &&bpbit == 0 && inttval == pk->itentval)
	  {
	  	  //int paranum;            //已有参数个数
	  	  pk->itentval = inttval;
	  	  pk->paranum = gum;
	  	  if(yparsit != NULL && gum > 0 && gum < 32)
	  	  {
						for(i = 0;i < 32; i++)
							  *(pk->lparsity +i) = -1;
						mparms2sitary(pk->lparsity, yparsit, gum);
			  }
				return 0;
	  }
	pn = NULL;
	pn = (SBKPOINTNODE *)malloc(sizeof(SBKPOINTNODE));
	if(pn != NULL)
	{
        ln = 0;
		ln = strlen(senckey);
		pn->psenckey = (char *)malloc(ln+1);
		strncpy(pn->psenckey, senckey, ln);
		*(pn->psenckey + ln) = 0;

		pn->itentval = inttval;
		pn->endbit = endstat;
    pn->paranum = 0;
		pn->paranum = gum;
		pn->lparsity  = (long *)malloc(sizeof(long) *32);
		for(i = 0;i < 32; i++)
			*(pn->lparsity +i) = -1;
		if(gum > 0 && gum < 32)
        mparms2sitary(pn->lparsity, yparsit, gum);
	
        pn->pnext = NULL;

        if(pr == NULL)
		{
			pn->pnext = *BL;
			*BL = pn;
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
		printf("");
		return 0;
	}
	return 0;
}
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
void freeBPList(bpoinlist *BL)
{
	bpoinlist pa, pk;

	if(*BL == NULL)
	    return ;
	pk = *BL;
	while(pk != NULL)
	{
		pa = pk;
		pk = pk->pnext;

		if(pa->psenckey != NULL)
		{
			free(pa->psenckey);
			pa->psenckey = NULL;
		}

		pa->paranum = 0;
		pa->itentval= 0;
		if(pa->lparsity != NULL)
		{
			free(pa->lparsity);
			pa->lparsity = NULL;
		}
		pa->pnext= NULL;
		free(pa);
		pa = NULL;
	}
    *BL = NULL;
}
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
void Init_sckhash(hashsptable * HashSP)
{
	long i;
	prepareCryptTable();
	*HashSP = (HASHSCKSNODE*)malloc(sizeof(HASHSCKSNODE) * DCHASH_SIZE);
	if(*HashSP == NULL)
		return ;
	
	for(i = 0; i < DCHASH_SIZE; i++)
	{
		((*HashSP)+i)->bExists = 0;
		((*HashSP)+i)->nHashA = -1;
		((*HashSP)+i)->nHashB = -1;
        
		((*HashSP)+i)->robotid = NULL;
        ((*HashSP)+i)->bplist = NULL;
        ((*HashSP)+i)->spnum = 0;
	}
}
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
void free_sckhash(hashsptable * HashSP)
{
	long i;
	if(*HashSP == NULL)
	{
		return ;
	}
	for(i = 0; i<DCHASH_SIZE; i++)
	{
		if(	((*HashSP)+i)->bExists != 0)
		{
			((*HashSP)+i)->bExists = 0;
			((*HashSP)+i)->nHashA = -1;
			((*HashSP)+i)->nHashB = -1;

			if(((*HashSP)+i)->robotid != NULL)
			{
				free(((*HashSP)+i)->robotid);
				((*HashSP)+i)->robotid = NULL;
			}
		    
			((*HashSP)+i)->spnum = 0;
			if(((*HashSP)+i)->bplist != NULL)
			{
			    freeBPList(&(((*HashSP)+i)->bplist));
				((*HashSP)+i)->bplist = NULL;
			}
		}
	}
	free(*HashSP);
	*HashSP = NULL;
}
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
void writ_sckhash(hashsptable hashtb, const char * phtbpath)
{
	long i;
	FILE * fp;

	if(phtbpath == NULL || *phtbpath == 0)
		return ;

	if(hashtb == NULL)
		return ;

    fp = NULL;
	fp = fopen(phtbpath, "wb");
	if(fp == NULL)
		return ;


	for(i = 0; i<DCHASH_SIZE; i++)
	{
		if((hashtb+i)->bExists != 0)
			fprintf(fp, "%s,%d\n", (hashtb+i)->robotid, (hashtb+i)->spnum);
	}
}
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
long GetHashsck(hashsptable hash_tb, const char *primkey)
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
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
int SetHashsck(hashsptable * HashtB, const char *probtid, const char * senckey, int intenval, int endbit, long *yparsit, int gum)
{
	int ln;
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString(probtid, HASH_OFFSET);
	unsigned long nHashA = HashString(probtid, HASH_A);
	unsigned long nHashB = HashString(probtid, HASH_B);
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

    if(probtid != NULL && *probtid != 0)
	{
		ln = 0;
		ln = strlen(probtid);
       
		((*HashtB)+nHashPos)->robotid = (char *)malloc(ln+1);
		strncpy(((*HashtB)+nHashPos)->robotid, probtid, ln);
		*(((*HashtB)+nHashPos)->robotid + ln) = 0;

        ((*HashtB)+nHashPos)->spnum = 0;
        ((*HashtB)+nHashPos)->spnum += ins_bplist(&(((*HashtB)+nHashPos)->bplist), senckey, intenval, endbit, yparsit, gum);
	}
	return 1;
}
///////////////////////////////////////////////////////////
//function:
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////




