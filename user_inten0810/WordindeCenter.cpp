
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"sharfuct.h"
#include"segment.h"
#include"WordindeCenter.h"
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
int Inswmoplist(wmoplist * WL, char * pword, int weight, long wbsit)
{
	int cbval, ln;
	wmoplist pn, pr, pk;

	if(pword == NULL || *pword == 0)
		return 0;
    if(weight <= 0)
		return 0;

	pr = NULL;
	pk = *WL;
	while(pk != NULL)
	{
		cbval = -1;
		cbval = strcmp(pword, pk->pword);
		if(cbval == 0)
		    break;
		if(weight > pk->weight)
			break;
		pr = pk;
		pk = pk->pnext;
	}

	if(pk != NULL && cbval == 0)
		return 0;
    pn = NULL;
	pn = (WIMORPNODE *)malloc(sizeof(WIMORPNODE));
	if(pn!= NULL)
	{
		ln = 0;
		ln = strlen(pword);
		pn->pword = NULL;
		pn->pword = (char *)malloc(ln+1);
		strncpy(pn->pword, pword, ln);
		*(pn->pword + ln) = 0;

        pn->wbsit = wbsit;
		pn->weight = weight;
		pn->pnext = NULL;

		if(pr == NULL)
		{
			pn->pnext = *WL;
			*WL = pn;
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
void freewmoplist(wmoplist * WL)
{
	wmoplist pk, pa;
	if(*WL == NULL)
		return ;
    pa = NULL;
	pk = *WL;
	while(pk != NULL)
	{
		pa = pk;
		pk = pk->pnext;

		if(pa->pword != NULL)
		{
			free(pa->pword);
			pa->pword = NULL;
		}

		pa->wbsit = -1;
        pa->weight = 0;

		free(pa);
		pa = NULL;
	}
	*WL =NULL;
}
void printmoplist(wmoplist wplist)
{
	wmoplist pk;
	if(wplist == NULL)
		return ;
	pk = wplist;
	while(pk != NULL)
	{
	    if(pk->pword != NULL)
			printf("%s\t", pk->pword);
        printf("%d\t", pk->weight);
		printf("%ld\n", pk->wbsit);
		pk = pk->pnext;
	}
}
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
int Inscorplist(corpmglist * CL, char * psenck, int sclen, int intval, int edsit, char * pfdback, char * pkind)
{
	corpmglist pn, pr, pk;
	int kbit, sbit, ln;

	if(psenck == NULL ||* psenck == 0)
		return 0;

	pr = NULL;
	pk = *CL;
	while(pk != NULL)
	{
		kbit = -1;
		kbit = strcmp(pkind, pk->pkind);

		sbit = -1;
		sbit = strcmp(psenck, pk->psenck);

        if(kbit == 0 && sbit ==0 && intval== pk->inteval)
			break;
		 
		pr = pk;
		pk = pk->pnext;
	}

    if(pk!= NULL && kbit == 0 && sbit ==0 && intval== pk->inteval)
	{
		return 0;
	}
    pn = NULL;
	pn = (CORPMGNODE *)malloc(sizeof(CORPMGNODE));
	if(pn != NULL)
	{
		ln = 0;
		ln = strlen(psenck);
		pn->psenck = NULL;
		pn->psenck = (char *)malloc(ln+1);
		strncpy(pn->psenck, psenck, ln);
		*(pn->psenck + ln) = 0;

        pn->inteval = intval;
		pn->endsit = edsit;
		pn->sclen = sclen;

        ln = 0;
		ln = strlen(pfdback);
        pn->pfdbak = NULL;
		pn->pfdbak = (char *)malloc(ln+1);
		strncpy(pn->pfdbak, pfdback, ln);
		*(pn->pfdbak + ln) = 0;

        ln = 0;
		ln = strlen(pkind);
        pn->pkind = NULL;
		pn->pkind = (char *)malloc(ln+1);
		strncpy(pn->pkind, pkind, ln);
		*(pn->pkind + ln) = 0;
		pn->pnext = NULL;

		if(pr == NULL)
		{
			pn->pnext = *CL;
			*CL = pn;
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
//time: 2016-7-23
///////////////////////////////////////////////////////////////
void cpcorplist(corpmglist * CL, corpmglist cylist)
{
	corpmglist pk;
	if(cylist == NULL)
		return ;
	pk = cylist;
	while(pk != NULL)
	{
        Inscorplist(CL,pk->psenck,pk->sclen, pk->inteval, pk->endsit, pk->pfdbak, pk->pkind);
		pk = pk->pnext;
	}

}
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
corpmglist listeamsearch(corpmglist crlist, char * psenck, int intval, char * pkind)
{
	int ksbit, kdbit;
	corpmglist pc;

	if(crlist == NULL)
		return NULL;
	pc = crlist;
	while(pc != NULL)
	{
		ksbit = -1;
        ksbit = strcmp(psenck, pc->psenck);
		kdbit = -1;
		kdbit = strcmp(pkind, pc->pkind);

		if(ksbit == 0 && kdbit == 0 && intval == pc->inteval)
			return pc;
	    pc = pc->pnext;
	}
    return NULL;
}
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
void freecrplist(corpmglist * CL)
{
	corpmglist pk, pa;
	if(*CL == NULL)
		return ;
    pa = NULL;
	pk = *CL;
	while(pk != NULL)
	{
		pa = pk;
		pk = pk->pnext;

		if(pa->pfdbak != NULL)
		{
			free(pa->pfdbak);
			pa->pfdbak = NULL;
		}
		
        if(pa->pkind != NULL)
		{
			free(pa->pkind);
			pa->pkind = NULL;
		}

		if(pa->psenck != NULL)
		{
			free(pa->psenck);
			pa->psenck = NULL;
		}
		pa->inteval = 0;
        pa->endsit = 0;
		pa->sclen = 0;

		free(pa);
		pa = NULL;
	}
	*CL =NULL;
}
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
void writindwlist(corpmglist clist, FILE * fp)
{
	corpmglist pk;
	if(clist == NULL)
		return ;
	pk = clist;
	while(pk != NULL)
	{
		if(pk->pfdbak != NULL)
             fprintf(fp, "%s\t", pk->pfdbak);
        if(pk->pkind != NULL)
			fprintf(fp, "%s\t", pk->pkind);
		if(pk->psenck != NULL)
			fprintf(fp, "%s\t", pk->psenck);

		fprintf(fp, "%d\t", pk->inteval);
		fprintf(fp, "%d\t", pk->endsit);
		fprintf(fp, "%d\t", pk->sclen);
		pk = pk->pnext;
	}
}
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
void printindwlist(corpmglist clist)
{
	corpmglist pk;
	if(clist == NULL)
		return ;
	pk = clist;
	while(pk != NULL)
	{
		if(pk->pfdbak != NULL)
             printf("%s\t", pk->pfdbak);
        if(pk->pkind != NULL)
			printf("%s\t", pk->pkind);
		if(pk->psenck != NULL)
			printf("%s\t", pk->psenck);

		printf("%d\t", pk->inteval);
		printf("%d\t", pk->endsit);
		printf("%d\n", pk->sclen);
		pk = pk->pnext;
	}
}
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
void Init_indexhash(hashindex * HashX)
{
	long i;
	prepareCryptTable();
	*HashX = (HASHINDNODE*)malloc(sizeof(HASHINDNODE) * DCHASH_SIZE);
	if(*HashX == NULL)
		return ;
	
	for(i = 0; i<DCHASH_SIZE; i++)
	{
		((*HashX)+i)->bExists = 0;
		((*HashX)+i)->nHashA = -1;
		((*HashX)+i)->nHashB = -1;
        
		((*HashX)+i)->cmglist = NULL;
        ((*HashX)+i)->gtnum = 0;
		((*HashX)+i)->pwordkey = NULL;
		((*HashX)+i)->wdlen = 0;
		((*HashX)+i)->weight = 0;
	}
}
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
void free_indexhash(hashindex * HashX)
{
	long i;
	if(*HashX == NULL)
	{
		HashX = NULL;
		return ;
	}
	for(i = 0; i<DCHASH_SIZE; i++)
	{
		if(	((*HashX)+i)->bExists != 0)
		{
			((*HashX)+i)->bExists = 0;
			((*HashX)+i)->nHashA = -1;
			((*HashX)+i)->nHashB = -1;

			if(((*HashX)+i)->pwordkey != NULL)
			{
				free(((*HashX)+i)->pwordkey);
				((*HashX)+i)->pwordkey = NULL;
			}
		
			((*HashX)+i)->gtnum = 0;
			((*HashX)+i)->wdlen = 0;
			((*HashX)+i)->weight = 0;

			if(((*HashX)+i)->cmglist != NULL)
			{
				freecrplist(&(((*HashX)+i)->cmglist));
                ((*HashX)+i)->cmglist = NULL;
			}	
		}
	}
	free(*HashX);
	*HashX = NULL;
}
////////////////////////////////////////////////////////////////
///function:
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
void writ_indexhash(hashindex hashxc, const char * pnduppath)
{
    FILE * fw;
    long i;

	if(pnduppath == NULL || * pnduppath== 0)
		return ;
    fw = fopen(pnduppath, "wb");
	if(fw == NULL)
		return ;
	if(hashxc == NULL)
		return ;
	for(i = 0; i<DCHASH_SIZE; i++)
	{
		if((hashxc+i)->bExists != 0)
		{
			fprintf(fw, "%s\t", (hashxc+i)->pwordkey);
	        fprintf(fw, "%d\t", (hashxc+i)->wdlen);
			fprintf(fw, "%d\t", (hashxc+i)->gtnum);
			fprintf(fw, "%d-:-", (hashxc+i)->weight);
		    writindwlist((hashxc+i)->cmglist, fw);
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
long GetHashindex(hashindex hash_xc, const char *pmkey)
{
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString(pmkey, HASH_OFFSET);
	unsigned long nHashA = HashString(pmkey, HASH_A);
	unsigned long nHashB = HashString(pmkey, HASH_B);
	unsigned long nHashStart = nHash % DCHASH_SIZE, nHashPos = nHashStart;
	
	while((hash_xc +nHashPos)->bExists)
	{
		if((hash_xc +nHashPos)->nHashA == (long) nHashA && (hash_xc +nHashPos)->nHashB == (long) nHashB)
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
int SetHashindex(hashindex * HashX, char *pwkey, int weight, char * pscenk, int inval, int sclen, int edsit, char * pfdback, char * pkind)
{
    int ln;
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString(pwkey, HASH_OFFSET);
	unsigned long nHashA = HashString(pwkey, HASH_A);
	unsigned long nHashB = HashString(pwkey, HASH_B);
	unsigned long nHashStart = nHash%DCHASH_SIZE, nHashPos = nHashStart;
	while(((*HashX)+nHashPos)->bExists)
	{
		nHashPos = (nHashPos + 1)%DCHASH_SIZE;
		if (nHashPos == nHashStart)
			return 0;
	}
	((*HashX)+nHashPos)->bExists = 1;
	((*HashX)+nHashPos)->nHashA = nHashA;
	((*HashX)+nHashPos)->nHashB = nHashB;
    ((*HashX)+nHashPos)->wdlen = 0;
    if(pwkey != NULL && *pwkey != 0)
	{
		ln = 0;
		ln = strlen(pwkey);
		((*HashX)+nHashPos)->wdlen = ln;
		((*HashX)+nHashPos)->pwordkey = (char *)malloc(ln+1);
		strncpy(((*HashX)+nHashPos)->pwordkey, pwkey, ln);
		*(((*HashX)+nHashPos)->pwordkey + ln) = 0;	 
	}
	((*HashX)+nHashPos)->weight = weight;
    ((*HashX)+nHashPos)->gtnum = 0;
	((*HashX)+nHashPos)->gtnum = Inscorplist(&(((*HashX)+nHashPos)->cmglist), pscenk, sclen, inval, edsit, pfdback, pkind);
	return 1;
}
////////////////////////////////////////////////////////////////
///function:语料语句按照词倒排进hash
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
///////////////////////////////////////////////////////////////
void winfo_2hash(TrieNode * sroot, TrieNode * mroot, hashindex * HashX, char * corpdpath)
{
	FILE * fp;
	char * pbuf, *p, *q, *pa, *pcorps, *psecnk, *pfdback, *psegment, * ptmpk, *pkind, *pword;
    int ln, spbit, ktbit, edsit, itval, sclen, wlen;
	long wxbit;
    
	if(corpdpath == NULL || *corpdpath == 0)
		return ;

    fp = NULL;
	fp = fopen(corpdpath, "rb");
    if(fp == NULL)
		return ;
	
	pbuf = (char *)malloc(1<<20);
    pcorps = (char *)malloc(512);
	psecnk = (char *)malloc(128);
	pfdback = (char *)malloc(2048);
	psegment = (char *)malloc(2048);
	ptmpk = (char *)malloc(2048);
	pkind = (char *)malloc(128);
	pword = (char *)malloc(256);
    *pbuf = 0;
	while(fgets(pbuf, 1<<20, fp))
	{
		ln = 0;
		ln = GetRealString(pbuf);
		if(ln <= 0)
			continue;
		sclen = 0;
		p = NULL;
        p = strchr(pbuf, 0x09);
        if(p == NULL)
			continue;
		
        sclen = p - pbuf;
		*pcorps = 0;
		strncpy(pcorps, pbuf, sclen);
		*(pcorps+sclen) = 0;
		q = p + 1;
        edsit = 0;
        edsit = atoi(q);
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
		*psecnk = 0;
		strncpy(psecnk, q, ln);
		*(psecnk+ln) = 0;
        q = p + 1;
		itval = 0;
        itval = atoi(q);
		p = NULL;
        p = strchr(q, 0x09);
        if(p == NULL)
			continue;
		q = p + 1;
		*pkind = 0;
		*pfdback = 0;
        p = NULL;
		p = strstr(q, "-:-");
        if(p != NULL)
		{
			ln = 0;
			ln = p - q;
            *ptmpk = 0;
			strncpy(ptmpk, q, ln);
			*(ptmpk + ln) = 0;

			pa = NULL;
			pa = strstr(ptmpk, "-##-");
			
            if(pa != NULL)
			{
				 ln = 0;
				 ln = pa - ptmpk;
				 strncpy(pkind, ptmpk, ln);
				 *(pkind + ln) = 0;
				 pa += 4;
				 strcpy(pfdback, pa);
				 //printf("==== %s\n", pa);
			}
			else
			{
                 strcpy(pfdback, ptmpk);
			}
		}
		//printf(" %s ==== %s\n", pkind, pfdback);
		memset(psegment, 0, 2048);
		wlen = 2048;
		ln = 0;
		ln = repqiefen(pcorps, sclen, psegment, wlen);
        p = psegment;
		while(*p != 0)
		{
			q = NULL;
			q = strchr(p, 0x20);
			if(q!= NULL)
			{
				wlen = 0;
				wlen = q - p;
				*pword = 0;
				strncpy(pword, p, wlen);
				*(pword +wlen) = 0;
				spbit = 0;
				spbit = Find(sroot,(unsigned char *)pword);
				if(spbit == 0)
				{
					ktbit = 1;
					ktbit = Find(mroot,(unsigned char *)pword);
					if(ktbit == 0)
						ktbit = 1;
					wxbit = -1;
					wxbit = GetHashindex(*HashX, pword);
					if(wxbit >= 0)
						((*HashX)+wxbit)->gtnum += Inscorplist(&(((*HashX)+wxbit)->cmglist), psecnk, sclen, itval, edsit, pfdback, pkind);
					else
                        SetHashindex(HashX, pword, ktbit, psecnk, itval, sclen, edsit, pfdback, pkind);
				}
				p = q + 1;
			}
			else
			{
				spbit = 0;
				spbit = Find(sroot,(unsigned char *)p);
				if(spbit == 0)
				{
					ktbit = 1;
					ktbit = Find(mroot,(unsigned char *)p);
					if(ktbit == 0)
						ktbit = 1;
					wxbit = -1;
					wxbit = GetHashindex(*HashX, p);
					if(wxbit >= 0)
                        ((*HashX)+wxbit)->gtnum += Inscorplist(&(((*HashX)+wxbit)->cmglist), psecnk, sclen, itval, edsit, pfdback, pkind);
					else
						SetHashindex(HashX, p, ktbit, psecnk, itval, sclen, edsit, pfdback, pkind);
				}
				break;
			}
		}
        *pbuf = 0;
    }
	free(pword);
    free(pkind);
    free(ptmpk);
    free(psegment);
    free(pfdback);
    free(psecnk);
    free(pcorps);
    free(pbuf);
	fclose(fp);
}
////////////////////////////////////////////////////////////////
///function：记录词，权重 ，在场景中的位置
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
//////////////////////////////////////////////////////////////
int lexweightsort(hashindex windtable,TrieNode * sroot, TrieNode * mroot, char * puserquery, wmoplist * WL)
{
    int slen, wlen, ires,spbit, ktbit, gnum;
	char * pgbkdel, *pcmbkk, *p, *q;
	long lwbitk;

	if(puserquery == NULL || *puserquery == 0)
		return 0;

	slen = 0;
    slen = strlen(puserquery);
	pgbkdel = (char *)malloc(2048);
	*pgbkdel = 0;
	wlen = 2048;
	ires = 0;
	memset(pgbkdel, 0, 2048);
	ires = repqiefen(puserquery, slen, pgbkdel, wlen);
	pcmbkk = (char *)malloc(2048);
    p = pgbkdel;
	gnum = 0;
    while(*p != 0)
	{
		q = NULL;
		q = strchr(p, 0x20);
		if(q!= NULL)
		{
			wlen = 0;
			wlen = q - p;
			*pcmbkk = 0;
			strncpy(pcmbkk, p, wlen);
			*(pcmbkk +wlen) = 0;

            spbit = 0;
			spbit = Find(sroot,(unsigned char *)pcmbkk);
			if(spbit == 0)
			{
				ktbit = 1;
				ktbit = Find(mroot,(unsigned char *)pcmbkk);
				if(ktbit == 0)
					ktbit = 1;
			    lwbitk = GetHashindex(windtable, pcmbkk);
				if(lwbitk >= 0)
				{
                    Inswmoplist(WL, pcmbkk, ktbit, lwbitk);
					++gnum;
				}
			}
			p = q + 1;
		}
		else
		{
            spbit = 0;
			spbit = Find(sroot,(unsigned char *)p);
			if(spbit == 0)
			{
				ktbit = 1;
				ktbit = Find(mroot,(unsigned char *)p);
				if(ktbit == 0)
					ktbit = 1;
                lwbitk = GetHashindex(windtable, p);
				if(lwbitk >= 0)
				{
					Inswmoplist(WL, pcmbkk, ktbit, lwbitk);
					++gnum;
				}
			}
			break;
		}
	}
    free(pcmbkk);
    free(pgbkdel);
    return gnum;
}
////////////////////////////////////////////////////////////////
///function： 两链表交集
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
//////////////////////////////////////////////////////////////
void intersectionlist(corpmglist clista, corpmglist clistb, corpmglist * iCL)
{
	corpmglist pb, pj;

	if(clistb != NULL && clista != NULL)
	{
		pb = clistb;
        while(pb!= NULL)
		{
			pj = NULL;
     		pj = listeamsearch(clista, pb->psenck, pb->inteval, pb->pkind);
			if(pj != NULL)
				Inscorplist(iCL, pj->psenck, pj->sclen, pj->inteval, pj->endsit, pj->pfdbak, pj->pkind);
			pb = pb->pnext;
		}
	}
}
////////////////////////////////////////////////////////////////
///function： 表示词进行“与” 
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
//////////////////////////////////////////////////////////////
void MwordAnd(hashindex windtable, wmoplist wlist, int gnum, corpmglist *MwL)
{
	corpmglist tmlist = NULL, crlist = NULL;
	corpmglist * pArry;
    int i;
	wmoplist pk;

	pArry = (corpmglist *)malloc(sizeof(corpmglist) * gnum);
	if(pArry == NULL)
		return ;
    pk = wlist;
	for(i = 0; i<gnum; i++)
	{
		if((windtable+(pk->wbsit))->cmglist != NULL)
			*(pArry+i) = (windtable+(pk->wbsit))->cmglist; 
		pk = pk->pnext;
	}
  if(gnum <= 0)
  	return ;
	if(gnum == 1)
	{
		  if(*(pArry+0) != NULL)
		  	cpcorplist(MwL, *(pArry+0));
      return ;
	}
	else if(gnum == 2)
	{
		tmlist = NULL;
		intersectionlist(*(pArry+0), *(pArry+1), &tmlist);
		if(tmlist != NULL)
		{
				cpcorplist(MwL, tmlist);
				if(tmlist != NULL)
				{
					freecrplist(&tmlist);
					tmlist = NULL;
				}
				return ;
		}
		else
		{
			  if(*(pArry+0) != NULL)
			  {
			  		cpcorplist(MwL, *(pArry+0));
			  }
			  else
			  {
			  	  cpcorplist(MwL, *(pArry+1));
			  }
		    return ;
		}
	}

    tmlist = NULL;
    intersectionlist(*(pArry+0), *(pArry+1), &tmlist);

	if(tmlist != NULL)
	{
		
		for(i = 2; i<gnum; i++)
		{
			crlist = NULL;
			intersectionlist(tmlist, *(pArry+i), &crlist);
			if(crlist != NULL)
			{
				if(tmlist != NULL)
					freecrplist(&tmlist);
				cpcorplist(&tmlist, crlist);
				freecrplist(&crlist);
			}
			else
				break;
		}
        cpcorplist(MwL, tmlist);
        if(tmlist != NULL)
			freecrplist(&tmlist);
		return ;
	}
	else
	{
		tmlist = NULL;
		intersectionlist(*(pArry+0), *(pArry+2), &tmlist);
		if(tmlist != NULL)
		{
			for(i = 3; i<gnum; i++)
			{
				crlist = NULL;
				intersectionlist(tmlist, *(pArry+i), &crlist);
				if(crlist != NULL)
				{
					if(tmlist != NULL)
						freecrplist(&tmlist);
					cpcorplist(&tmlist, crlist);
					freecrplist(&crlist);
				}
				else
					break;
			}
			cpcorplist(MwL, tmlist);
			if(tmlist != NULL)
				freecrplist(&tmlist);
			return ;
		}
		else
		{
			tmlist = NULL;
			intersectionlist(*(pArry+1), *(pArry+2), &tmlist);
			if(tmlist != NULL)
			{
				for(i = 3; i<gnum; i++)
				{
					crlist = NULL;
					intersectionlist(tmlist, *(pArry+i), &crlist);
					if(crlist != NULL)
					{
						if(tmlist != NULL)
							freecrplist(&tmlist);
						cpcorplist(&tmlist, crlist);
						freecrplist(&crlist);
					}
					else
						break;
				}
                cpcorplist(MwL, tmlist);
				if(tmlist != NULL)
					freecrplist(&tmlist);
				return ;
			}
			else
			{
				 cpcorplist(MwL, *(pArry+0));
			}
		}
	}
	free(pArry);
}
////////////////////////////////////////////////////////////////
///function:long 
//parameter: 
//author: wuxiaoqi
//time: 2016-7-23
//////////////////////////////////////////////////////////////
void mWindxsearch(hashindex windtable, TrieNode * sroot, TrieNode * mroot, char * puquerys, corpmglist *WrL)
{
	int slen, wlen, ires, gnum, spbit, ktbit;
	char * pgbkdel, *pcmbkk, *p, *q;
	long lwbitk;
	wmoplist wmlist = NULL;

	if(puquerys == NULL ||*puquerys == 0)
		return  ;
	slen = 0;
    slen = strlen(puquerys);
	pgbkdel = (char *)malloc(2048);
	*pgbkdel = 0;
	wlen = 2048;
	ires = 0;
	memset(pgbkdel, 0, 2048);
	ires = repqiefen(puquerys, slen, pgbkdel, wlen);
	pcmbkk = (char *)malloc(2048);
    p = pgbkdel;
	gnum = 0;
	while(*p != 0)
	{
		q = NULL;
		q = strchr(p, 0x20);
		if(q!= NULL)
		{
			wlen = 0;
			wlen = q - p;
			*pcmbkk = 0;
			strncpy(pcmbkk, p, wlen);
			*(pcmbkk +wlen) = 0;

            spbit = 0;
			spbit = Find(sroot,(unsigned char *)pcmbkk);
			if(spbit == 0)
			{
				ktbit = 1;
				ktbit = Find(mroot,(unsigned char *)pcmbkk);
				if(ktbit == 0)
					ktbit = 1;
			    lwbitk = GetHashindex(windtable, pcmbkk);
				if(lwbitk >= 0)
                    gnum += Inswmoplist(&wmlist, pcmbkk, ktbit, lwbitk);
			}
			p = q + 1;
		}
		else
		{
            spbit = 0;
			spbit = Find(sroot,(unsigned char *)p);
			if(spbit == 0)
			{
				ktbit = 1;
				ktbit = Find(mroot,(unsigned char *)p);
				if(ktbit == 0)
					ktbit = 1;
                lwbitk = GetHashindex(windtable, pcmbkk);
				if(lwbitk >= 0)
                     gnum += Inswmoplist(&wmlist, p, ktbit, lwbitk);
			}
			break;
		}
	}
    //printmoplist(wmlist);
	MwordAnd(windtable, wmlist, gnum, WrL);
	printindwlist(*WrL);

	if(wmlist != NULL)
        freewmoplist(&wmlist);
    if(pcmbkk!= NULL)
		free(pcmbkk);
    if(pgbkdel!= NULL)
		free(pgbkdel);
}


