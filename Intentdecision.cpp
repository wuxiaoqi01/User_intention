#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"sharfuct.h"
#include"segment.h"
#include"paralocafdback.h"
#include"hashinfoadm.h"
#include"intentsentmg.h"
#include"scenbpointsave.h"
#include"sencparampai.h"
#include"Intentdecision.h"
#include"netTransport.h"
#include"WordindeCenter.h"

///////////////////////////////////////////////////////////
//function:�����û����� -> ���� 
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
int segparareplace(hashinfotabl cptable, const char * purequisegmt, long * parmsitay)
{
	char *p, *q, *pkey;
	int ln, i, gnum = 0;
	long ksbit;

	if(purequisegmt == NULL || * purequisegmt == 0)
		return gnum;

	if(cptable == NULL)
        return gnum;

	pkey = (char *)malloc(1024);
	*pkey = 0;
    p = (char *) purequisegmt;
	while(*p != 0)
	{
		q = NULL;
		q = strchr(p, 0x20);
		if(q != NULL)
		{
			ln = 0;
			ln = q - p;
			*pkey = 0;
			strncpy(pkey, p, ln);
			*(pkey +ln)= 0;
            ksbit = -1;
            ksbit = GetHashinf(cptable, pkey);
			if(ksbit >= 0)
			{
				i = 0;
				while(i< gnum)
				{
					if(*(parmsitay+i) != ksbit)
						i++;
					else
						break;
				}
				if(i >= gnum)
					*(parmsitay+gnum) = ksbit;
				++gnum;
			}
			p = q + 1;
		}
		else
		{
			ksbit = -1;
            ksbit = GetHashinf(cptable, p);
			if(ksbit >= 0)
			{
				i = 0;
				while(i< gnum)
				{
					if(*(parmsitay+i) != ksbit)
						i++;
					else
						break;
				}
				if(i >= gnum)
					*(parmsitay+gnum) = ksbit;
				++gnum;
			}
			break;
		}
	}
    if(pkey != NULL)
	{
		free(pkey);
		pkey = NULL;
	}
	return gnum;
}
////////////////////////////////
///function:  
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
/////////////////////////////////
int ins_PCmbList(parmaylist *DL, const char * parmpaty, const char * parcmbkey, const char * psenckey, const char * parkdcmb, int intenval)
{
    parmaylist pn, pr, pk;
	int ln, kbit;

	if(parmpaty == NULL || *parmpaty == 0)
		return 0;

	pr = NULL;
	pk = *DL;
	while(pk != NULL)
	{
		kbit = -1;
		kbit = strcmp(parmpaty, pk->parmpaty);
		if(kbit == 0)
			break;

		pr = pk;
		pk = pk->pnext;
	}
    if(kbit == 0 && pk != NULL)
		return 0;
	else
	{
		pn = NULL;
		pn = (PARANRYKNODE *)malloc(sizeof(PARANRYKNODE));
		if(pn != NULL)
		{
			pn->parmpaty = NULL;
			ln = 0;
			ln = strlen(parmpaty);
			if(ln >=0)
			{
				pn->parmpaty = (char *)malloc(ln+1);
				strncpy(pn->parmpaty, parmpaty, ln);
				*(pn->parmpaty + ln) = 0;
			}

			pn->parmback = NULL;
			ln = 0;
			ln = strlen(parcmbkey);
			if(ln >= 0)
			{
					pn->parmback = (char *)malloc(ln+1);
          strncpy(pn->parmback, parcmbkey, ln);
			    *(pn->parmback + ln) = 0;
			}

			pn->psencek = NULL;
			ln = 0;
			ln = strlen(psenckey);
			if(ln >=0)
			{
				pn->psencek = (char *)malloc(ln+1);
				strncpy(pn->psencek, psenckey, ln);
				*(pn->psencek + ln) = 0;
			}

			pn->parkcmb = NULL;
			ln = 0;
			ln = strlen(parkdcmb);
			if(ln >= 0)
			{
				pn->parkcmb = (char *)malloc(ln+1);
                strncpy(pn->parkcmb, parkdcmb, ln);
			    *(pn->parkcmb + ln) = 0;
			}

			pn->intenval = intenval;
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
void prinpmlist(parmaylist mlist)
{
		parmaylist pk;
		if(mlist == NULL)
	     	return ;
		pk = mlist;
		while(pk != NULL)
		{
			  printf("%s\n",pk->parmpaty);
			  printf("%s\n",pk->parmback);
			  printf("%s\n",pk->psencek);
			  printf("%s\n",pk->parkcmb);
			  printf("%d\n",pk->intenval);
	      pk = pk->pnext;
		}
}
////////////////////////////////
///function:  
//parameter: 
//author: wuxiaoqi
//time: 2016-3-23
/////////////////////////////////
void freePMblist(parmaylist *DL)
{
	parmaylist pk, pa;
	if(*DL == NULL)
		return ;
    pa = NULL;
	pk = *DL;
	while(pk != NULL)
	{
		pa = pk;
		pk = pk->pnext;

		if(pa->parkcmb != NULL)
		{
			free(pa->parkcmb);
			pa->parkcmb = NULL;
		}
		if(pa->parmback != NULL)
		{
			free(pa->parmback);
			pa->parmback = NULL;
		}
		if(pa->parmpaty != NULL)
		{
			free(pa->parmpaty);
			pa->parmpaty = NULL;
		}
		if(pa->psencek != NULL)
		{
			free(pa->psencek);
			pa->psencek = NULL;
		}
		
		pa->intenval = 0;
		free(pa);
		pa = NULL;
	}
	*DL =NULL;
}
///////////////////////////////////////////////////////////
//function: ���ݲ����˻����˻�������������Ͼ��Ӧ
//parameter:        #A-Y;#B-Y
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
int Analyparfdbkind(hashinfotabl cptable, hashpacomb cmbtable, char * puquerys, long * parmsitay, int gnum, parmaylist * KL)
{
		int zsval = 0, ln, scval,kdval;
		long zhbit, fhbit;
		descklist pd, pk;
		char * p, *q;
		char * pzjkmp, * pthkey, *ptkind, *ptgut;

		if(puquerys == NULL && *puquerys == 0)
				return zsval;

		pzjkmp = (char *)malloc(2048);  //�����˻���Ĵ�
		ptgut = (char *)malloc(2048);   //������ϴ�
		pthkey = (char *)malloc(2048);
    ptkind = (char *)malloc(512);   //#A-y;#B-Y

		if(gnum == 0)
		{
					zsval += ins_PCmbList(KL, puquerys, "", "", "", 0);
	        return zsval;
		}
		else if(gnum == 1)
		{
			   *pzjkmp = 0;
					pd = NULL;
					pd = (cptable+(*parmsitay))->fdlist;
					while(pd != NULL)
					{
						    p = NULL;
								p = strstr(puquerys, (cptable+(*parmsitay))->primarykey);
								if(p != NULL)
								{
											ln = 0;
											ln = p - puquerys;
											strncpy(pzjkmp, puquerys, ln);
											*(pzjkmp + ln) = 0;
										  strcat(pzjkmp, pd->corrule);
											p += strlen((cptable+(*parmsitay))->primarykey);
											strcat(pzjkmp, p);
								}
							  *ptkind = 0;
								strcat(ptkind, pd->corrule);
								strcat(ptkind, "-Y");
				        zsval += ins_PCmbList(KL, pzjkmp, (cptable+(*parmsitay))->primarykey, pd->desckey, ptkind, pd->dsval);
						    pd = pd->pnext;
					}
	  }
    else if(gnum == 2)
	  {
	  	  // #A-y;#B-n
	  	  *pzjkmp = 0;
		    pd = NULL;
			  pd = (cptable+(*parmsitay))->fdlist;
			  pk = NULL;
			  pk = (cptable+(*(parmsitay+1)))->fdlist;
			  while(pd != NULL)
			  {
			  	  while(pk!=NULL)
			  	  {
			  	  	  scval = -1;
								scval = strcmp(pd->desckey, pk->desckey);
								kdval = -1;
								kdval = strcmp(pd->corrule, pk->corrule);
                if(scval == 0&& kdval != 0)
								{
									  p = NULL;
										p = strstr(puquerys, (cptable+(*parmsitay))->primarykey);
										if(p != NULL)
										{
													ln = 0;
													ln = p - puquerys;
													strncpy(pzjkmp, puquerys, ln);
													*(pzjkmp + ln) = 0;
												  strcat(pzjkmp, pd->corrule);
												  p += strlen((cptable+(*parmsitay))->primarykey);
												  q = NULL;
												  q = strstr(p, (cptable+(*(parmsitay+1)))->primarykey);
												  if(q != NULL)
												  {
												  	  ln = 0;
												  	  ln = q - p;
												  	  *pthkey = 0;
												  	  strncpy(pthkey, p, ln);
													    *(pthkey + ln) = 0;
													    strcat(pzjkmp, pthkey);
												  	  strcat(pzjkmp, pk->corrule);
												  	  q += strlen((cptable+(*(parmsitay+1)))->primarykey);
												  	  strcat(pzjkmp, q);
												  }
												  else
												  {
												  		strcat(pzjkmp, p);
												  }
										}
									  
									  *ptgut = 0;
									  strcat(ptgut, (cptable+(*parmsitay))->primarykey);
									  strcat(ptgut, "####");
									  strcat(ptgut, (cptable+(*(parmsitay+1)))->primarykey); 
									  *ptkind = 0;
									  zhbit = -1;
									  zhbit = GetHashpcmb(cmbtable, ptgut);
									  if(zhbit >= 0)
									  {
									  		strcat(ptkind, pd->corrule);
												strcat(ptkind, "-Y,");
												strcat(ptkind, pk->corrule);
												strcat(ptkind, "-Y");
												printf(" %s \n",ptkind);
												zsval += ins_PCmbList(KL, pzjkmp, ptgut, pd->desckey, ptkind, pd->dsval);
												if(ptkind != NULL)
													   free(ptkind);
												if(pthkey != NULL)
													   free(pthkey);
											  if(ptgut != NULL)
													   free(ptgut);
												if(pzjkmp != NULL)
													   free(pzjkmp);
										    return zsval;
									  }
									  else
									  {
									  		*ptgut = 0;
										  	strcat(ptgut, (cptable+(*(parmsitay+1)))->primarykey);
										  	strcat(ptgut, "####");
										  	strcat(ptgut, (cptable+(*parmsitay))->primarykey);
										  	fhbit = -1;
											  fhbit = GetHashpcmb(cmbtable, ptgut);
											  if(fhbit >= 0)
											  {
											  	  strcat(ptkind, pd->corrule);
														strcat(ptkind, "-Y,");
											  	  strcat(ptkind, pk->corrule);
														strcat(ptkind, "-Y");
														
														zsval += ins_PCmbList(KL, pzjkmp, ptgut, pd->desckey, ptkind, pd->dsval);
														if(ptkind != NULL)
													   			free(ptkind);
														if(pthkey != NULL)
															   free(pthkey);
													  if(ptgut != NULL)
															   free(ptgut);
														if(pzjkmp != NULL)
															   free(pzjkmp);
												    return zsval;	
											  }
										 		else
										 		{
											  	  strcat(ptkind, pd->corrule);  ///=====>������hash ����ȫ��������������
														strcat(ptkind, "-Y,");
														strcat(ptkind, pk->corrule);
														strcat(ptkind, "-N");	//  
														zsval += ins_PCmbList(KL, pzjkmp, ptgut, pd->desckey, ptkind, pd->dsval);
														if(ptkind != NULL)
																   free(ptkind);
															if(pthkey != NULL)
																   free(pthkey);
														  if(ptgut != NULL)
																   free(ptgut);
															if(pzjkmp != NULL)
																   free(pzjkmp);
												    return zsval;
										   }
									  }
								}
			  	  	  pk = pk->pnext;
			  	  }
			  	  pd = pd->pnext;
			  }
			  //#A-Y
			  if(zsval <= 0)
			  {
					  *pzjkmp = 0;
						pd = NULL;
						pd = (cptable+(*parmsitay))->fdlist;
						while(pd != NULL)
						{
								    p = NULL;
										p = strstr(puquerys, (cptable+(*parmsitay))->primarykey);
										if(p != NULL)
										{
													ln = 0;
													ln = p - puquerys;
													strncpy(pzjkmp, puquerys, ln);
													*(pzjkmp + ln) = 0;
												  strcat(pzjkmp, pd->corrule);
													p += strlen((cptable+(*parmsitay))->primarykey);
													strcat(pzjkmp, p);
										}
									  *ptkind = 0;
										strcat(ptkind, pd->corrule);
										strcat(ptkind, "-Y,");
						        zsval += ins_PCmbList(KL, pzjkmp, (cptable+(*parmsitay))->primarykey, pd->desckey, ptkind, pd->dsval);
								    pd = pd->pnext;
							}
							//#B-y
						  *pzjkmp = 0;
							pd = NULL;
							pd = (cptable+(*(parmsitay+1)))->fdlist;
							while(pd != NULL)
							{
									    p = NULL;
											p = strstr(puquerys, (cptable+(*parmsitay))->primarykey);
											if(p != NULL)
											{
														ln = 0;
														ln = p - puquerys;
														strncpy(pzjkmp, puquerys, ln);
														*(pzjkmp + ln) = 0;
													  strcat(pzjkmp, pd->corrule);
														p += strlen((cptable+(*parmsitay))->primarykey);
														strcat(pzjkmp, p);
											}
										  *ptkind = 0;
											strcat(ptkind, pd->corrule);
											strcat(ptkind, "-Y");
							        zsval += ins_PCmbList(KL, pzjkmp, (cptable+(*parmsitay))->primarykey, pd->desckey, ptkind, pd->dsval);
									    pd = pd->pnext;
						}
			  }
	  }
	  else if(gnum > 2)
	  { 
	  	   //#A#B#C
	       //else   #A#B #A#c #B#C
	       //else   #A  #B   #C
	  }
	// #A#B#C#D
	// else   #A#B#C #A#C#D #B#C#D
	// else   #A#B #A#c #AD #B#C #BD #CD
	// else   #A #B #C #D
	  if(ptkind != NULL)
			   free(ptkind);
		if(pthkey != NULL)
			   free(pthkey);
	  if(ptgut != NULL)
			   free(ptgut);
		if(pzjkmp != NULL)
			   free(pzjkmp);
	  return zsval;
}
///////////////////////////////////////////////////////////
//function: feedback ʵ�ʲ�����
//parameter:        
//author��yanhao
//time: 2016-6-23
///////////////////////////////////////////////////////////
char * fdbackparaminst(hashinfotabl cptable, char * kypfdback, char * psenc, int itenval, long * parmsit, int gnum, char * pfeedback)
{
	  char *p, *q;
	  int ln;
		descklist pd;
		char *buf1,*buf2,tmp;
		int i,foundnum=0,foundtag=0,BufLenth=2048;
		
	  if(kypfdback == NULL || *kypfdback == 0 || gnum == 0)
	  {
	  	  strcpy(pfeedback, kypfdback);
	  	  return pfeedback;
	  }
	  
	  *pfeedback = 0;
	  //strcpy(pfeedback, kypfdback);
		buf1=(char*)malloc(BufLenth);
		buf2=(char*)malloc(BufLenth);
	  memset(buf1,0,BufLenth);
	  memset(buf2,0,BufLenth);
	  strcpy(buf1,kypfdback);
	  while(1)
	  {
			  foundtag=0;
			  p = strchr(buf1, '#');
			  if(p!= NULL )
			  { //�ҵ�һ������
				  foundtag=2;
				  tmp=*(p+1);//ȡ��#�ź�����ַ�
				  for(i=0;*(parmsit+i)!=-1;i++)
				  {//�������м�¼�Ĳ���ƫ��
						  pd = (cptable+*(parmsit+i))->fdlist;
						  while(pd != NULL )
						  {
							  	if(itenval == pd->dsval && !strcmp(psenc,pd->desckey))
									    if(strchr(pd->corrule, tmp) != NULL)
									    {   //����ҵ�A B C..
												  foundtag=1;
												  break;
										  }//�������A B C ֻ�ǵ����ľ��� ,���Ǳ���2
							  	pd=pd->pnext;
						  }
				  }
				  if(foundtag==1)
				  {
						  ln = 0;
						  ln = p - buf1;
						  memcpy(buf2,buf1,ln);
						  strcat(pfeedback, buf2);
						  strcat(pfeedback,(cptable+(*parmsit))->primarykey);//������Ҳ����ȥ
						  ln=BufLenth-ln-2;
						  memset(buf2,0,BufLenth);
						  memcpy(buf2,p+2,ln);
						  memset(buf1,0,BufLenth);
						  memcpy(buf1,buf2,BufLenth);
						  memset(buf2,0,BufLenth);
				  }
				  else if(foundtag==2)
				  {
						  ln = 0;
						  ln = p - buf1+1;
						  memcpy(buf2,buf1,ln);
						  strcat(pfeedback, buf2);
						  ln=BufLenth-ln;
						  memset(buf2,0,BufLenth);
						  memcpy(buf2,p+1,ln);
						  memset(buf1,0,BufLenth);
						  memcpy(buf1,buf2,BufLenth);
						  memset(buf2,0,BufLenth);
				  }
			  }
			  else 
			  		break;	  
	  }//��Ϊ�Ҳ��������˳�ѭ��
	  //����֮ǰ��û���ҵ�������,��ʱһ���ֻ�ȫ��������buf1
	  strcat(pfeedback, buf1);
	  free(buf1);
	  free(buf2);
	  char *temp_fb;
	  temp_fb = ran_result_replace(pfeedback,psenc);
	  //*pfeedback=0;
	  //strcpy(pfeedback,temp_fb);
	  //free(temp_fb);
	  return temp_fb;
}
///////////////////////////////////////////////////////////
//function:  ��ȫ��������Ӵ�ƥ��
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
char * FULL_SUB_MATCH(hashinfotabl schash, char * kuquery, char * psenck, int *Ituval, char * presfdback)
{
		long scbit;
		int slen;
		char  *p, *pkey;
		
		scbit = -1;
	  scbit = GetHashinf(schash, kuquery);
		if(scbit >= 0)
		{//���Ͼ�ֱ������
			 	  *psenck = 0;
					strcpy(psenck, (schash+scbit)->sencdkey);
					*Ituval = (schash+scbit)->rimval;
					*presfdback = 0;
					if((schash+scbit)->fdlist != NULL)
					{
							if(((schash+scbit)->fdlist)->desckey != NULL)
									strcpy(presfdback, ((schash+scbit)->fdlist)->desckey);
				  }
					return presfdback;
		}
		
		pkey = (char *) malloc(2048);
		slen = strlen(kuquery);
		p = kuquery;
		while(p!= NULL && *p != 0)
		{
				slen = strlen(p);
				while(slen > 1) // Ϊ������������
				{
		      	  *pkey = 0;
	            strncpy(pkey, p, slen);
							*(pkey+slen) = 0;
							*presfdback = 0;
							 scbit = -1;
							 scbit = GetHashinf(schash, pkey);
							 if(scbit >= 0)
							 {
							 	   *psenck = 0;
									 strcpy(psenck, (schash+scbit)->sencdkey);
									 *Ituval = (schash+scbit)->rimval;
									 *presfdback = 0;
									 if((schash+scbit)->fdlist != NULL)
										{
												if(((schash+scbit)->fdlist)->desckey != NULL)
														strcpy(presfdback, ((schash+scbit)->fdlist)->desckey);
									  }
									 //strcpy(presfdback, ((schash+scbit)->fdlist)->desckey);
									 free(pkey);
									 return presfdback;
							 }
							 if(*(p+(slen - 2)) <0 && *(p+(slen-1)) < 0)
									 slen  -= 2;
							 else
									 --slen;
					}
					if(*p < 0)
							p += 2;
					else
							++p;
		 }
		 free(pkey);
		 return presfdback;
}
///////////////////////////////////////////////////////////
//function: ������
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
char * usercontextanys(hashsptable * HMP, hashinfotabl cptable, hashpacomb cmbtable, hashploctable clohash, char * probotid, long * parmsit, int gnum, char * psenck, int *Ituval, char * presfdback)
{
	  int i, j, scval, s2val, kdval;
	  long pssit = -1, zhbit = -1, locsit = -1;
	  bpoinlist pb;
	  descklist pd, pk, pm;
	  char *ptgut, *pcmbar, *ps;
	  
	  ptgut = (char *)malloc(2048);
	  *ptgut = 0;
	  pcmbar = (char *)malloc(2048);
	  *pcmbar = 0;
	  printf(" %s ==  %d \n",probotid, gnum);
	  pssit = -1;
		pssit = GetHashsck(*HMP, probotid);//robot id
		printf(" idsit ==  %ld \n",pssit);
		if(pssit >= 0)
		{
			  printf("222222222222222222\n");
			   //���β���
				pb = ((*HMP)+pssit)->bplist;
				if(pb == NULL)//�ϴ�û��
				{  
					   //��һ��û����
					   // ���ڲ�������> cmbtable 
					   if(gnum == 0)
					   {
					   	   *psenck = 0;
								 strcpy(psenck, "NULL");
					   	   *presfdback = 0;
			         	 sprintf(presfdback, "�������ϴξ�û�г���, ��������С�ֲ�֪������˵ʲô");
			         	 *Ituval = 0;
			         	 if(ptgut != NULL)
										free(ptgut);
								 if(pcmbar != NULL)
										free(pcmbar);
								 return presfdback; 
					   }    	
					   if(gnum == 1)
		         {
		         	   printf("pb == NULL gnum == 1\n");
		         	   if((cptable+(*parmsit))->egnum == 1)
		         	   {
		         	   	   *psenck = 0;
								 		 strcpy(psenck, "NULL");
		         	   	   *presfdback = 0;
									   strcat(presfdback, "�ɵ���ĳ�����");
			         	   	 pd = NULL;
									 	 pd = (cptable+(*parmsit))->fdlist;
									 	 while(pd!= NULL)
									 	 {
									 	 	   ps = NULL;
									 	 	   ps = strstr(presfdback, pd->desckey);
									 	 	   if(ps == NULL)
									 	 	   {
									 	 	   		strcat(presfdback, pd->desckey);
									 	 	   		strcat(presfdback, ",");
									 	 	   }
									 	 	   pd = pd->pnext;	 
										 }
										 strcat(presfdback, ";������Ҫ���ĸ�?");
										 *Ituval = 0;
					         	 if(ptgut != NULL)
												free(ptgut);
										 if(pcmbar != NULL)
												free(pcmbar);
										 return presfdback;
								 }
		         }
		         else if(gnum == 2)
		         {  	
		         	   	pd = NULL;
									pd = (cptable+(*parmsit))->fdlist;
									pk = NULL;
									pk = (cptable+(*(parmsit+1)))->fdlist;
									
									while(pd != NULL)
								  {
								  	  while(pk!=NULL)
								  	  {
								  	  	  scval = -1;
													scval = strcmp(pd->desckey, pk->desckey);
													kdval = -1;
													kdval = strcmp(pd->corrule, pk->corrule);
					                if(scval == 0&& kdval != 0)
													{
														  if(kdval < 0)
														  {
																  *ptgut = 0;
																  strcat(ptgut, (cptable+(*parmsit))->primarykey);
																  strcat(ptgut, "####");
																  strcat(ptgut, (cptable+(*(parmsit+1)))->primarykey);
																  zhbit = -1;
																  zhbit = GetHashpcmb(cmbtable, ptgut);
																  if(zhbit >= 0)
											  					{
									  						      *pcmbar = 0;
																	    sprintf(pcmbar, "%s--:--%d--:--%s-Y,%s-Y", pd->desckey, pd->dsval, pd->corrule, pk->corrule);
																	    *presfdback = 0;
																			locsit = -1;
																			locsit = GetHashploc(clohash, pcmbar);
																			if(locsit >= 0)
																			{
																					*psenck = 0;
																					strcpy(psenck, (clohash+locsit)->pscenk);
																					*Ituval = (clohash+locsit)->intuval;
																				  strcpy(presfdback, (clohash+locsit)->pfdback);
																				  if(ptgut != NULL)
																						  		free(ptgut);
																				  if(pcmbar != NULL)
																						  		free(pcmbar);
																				  return presfdback;
																			}
									  					    }
									  					}
									  					else if(kdval > 0)
									  					{
											  					*ptgut = 0;
																  strcat(ptgut, (cptable+(*(parmsit+1)))->primarykey);
																  strcat(ptgut, "####");
																  strcat(ptgut, (cptable+(*parmsit))->primarykey);
																  zhbit = -1;
																  zhbit = GetHashpcmb(cmbtable, ptgut);
																  if(zhbit >= 0)
											  					{
											  						  *pcmbar = 0;
																			sprintf(pcmbar, "%s--:--%d--:--%s-Y,%s-Y", pd->desckey, pd->dsval, pk->corrule, pd->corrule);
																			*presfdback = 0;
																			locsit = -1;
																			locsit = GetHashploc(clohash, pcmbar);
																			if(locsit >= 0)
																			{
																					*psenck = 0;
																					strcpy(psenck, (clohash+locsit)->pscenk);
																					*Ituval = (clohash+locsit)->intuval;
																				  strcpy(presfdback, (clohash+locsit)->pfdback);
																				  if(ptgut != NULL)
																				  		free(ptgut);
																				  if(pcmbar != NULL)
																				  		free(pcmbar);
																				  return presfdback;
																			}	  
											  					}
									  				  }	
													}
													pk = pk->pnext;
											}
											pd = pd->pnext;
									}
									*psenck = 0;
								  strcpy(psenck, "NULL");
									*presfdback = 0;
									strcat(presfdback, "�ɵ���ĳ�����");
									while(pd != NULL)
								  {
								  	  kdval = -1;
											kdval = strcmp(pd->corrule, "#A");
								  	  if(kdval ==0)
								  	  {
								  	  	  ps = NULL;
									 	 	    ps = strstr(presfdback, pd->desckey);
									 	 	    if(ps == NULL)
									 	 	    {
										  	  		strcat(presfdback, pd->desckey);
											 	 			strcat(presfdback, ",");
											 	  }
									 	  }
								  	  pd = pd->pnext;
								  }
								  while(pk != NULL)
								  {
								  	  kdval = -1;
											kdval = strcmp(pk->corrule, "#A");
								  	  if(kdval ==0)
								  	  {
										  	  strcat(presfdback, pk->desckey);
											 	 	strcat(presfdback, ",");
									 	  }
								  	  pk = pk->pnext;
								  }
								  strcat(presfdback, ";������Ҫ���ĸ�?");
								  *Ituval = 0;
			         	  if(ptgut != NULL)
										  free(ptgut);
								  if(pcmbar != NULL)
										  free(pcmbar);
								  return presfdback;
		         } 
		         else if(gnum == 3)
		         {
		         }
		         else
		         {
		         			
		         }
		         if(ptgut != NULL)
						  		free(ptgut);
						  if(pcmbar != NULL)
						  		free(pcmbar);
             return presfdback; 
				}
				else
				{
						printf("sc === %s\n", pb->psenckey);
						printf("Last scene without parameters ......\n");
						while(pb != NULL)
						{
							  printf(" gnum ==  === \n");
							  if(gnum == 0)
							  {
							  	  *psenck = 0;
								 		strcpy(psenck, "NULL");
							  	  *presfdback = 0;
				         	 	sprintf(presfdback, "�������ϴ�%s����, ��������С�ֲ�֪������˵ʲô", pb->psenckey);
				         	 	*Ituval = 0;
				         	 	if(ptgut != NULL)
												free(ptgut);
									 	if(pcmbar != NULL)
											free(pcmbar);
									 	return presfdback; 
							  }
							  else if(gnum == 1)
							  {
							  	  printf(" pb->paranum == %d \n", pb->paranum);
							  	  printf(" gnum == 1 \n");
							  	  if(pb->paranum <= 0)
									  {
									  	  printf(" pb->paranum == 0 \n");
									  	  pd = NULL;
									  	  pd = (cptable+(*parmsit))->fdlist;
									  	  while(pd!= NULL)
					   	   	      {
					   	   	      	  scval = -1;
					   	   	      	  printf( " pb->psenckey, pd->desckey ==  %s,%s \n ", pb->psenckey, pd->desckey);
													  scval = strcmp(pb->psenckey, pd->desckey);
						   	   	    	  if(scval == 0)
						   	   	    	  {
						   	   	    	  	  *pcmbar = 0;
						   	   	    	  	  sprintf(pcmbar, "%s--:--%d--:--%s-Y", pd->desckey, pd->dsval, pd->corrule);
								   	   	    	  *presfdback = 0;
																locsit = -1;
																locsit = GetHashploc(clohash, pcmbar);
																if(locsit >= 0)
																{
																		*psenck = 0;
																		strcpy(psenck, pd->desckey);
																		*Ituval = pd->dsval;
																	  strcpy(presfdback, (clohash+locsit)->pfdback);
																	  if(ptgut != NULL)
																	  	free(ptgut);
																	  if(pcmbar != NULL)
																	  	free(pcmbar);
																		return presfdback;
																}
						   	   	    	  }
					   	   	      	  pd = pd->pnext;
					   	   	      }
					   	   	      pd = NULL;
									  	  pd = (cptable+(*parmsit))->fdlist;
									  	  while(pd!= NULL)
					   	   	      {
					   	   	      	  scval = -1;
													  scval = strcmp(pb->psenckey, pd->desckey);
													  kdval = -1;
											      kdval = strcmp(pd->corrule, "#B");
						   	   	    	  if(scval != 0 && kdval == 0)
					   	   	      	  {//�߼�����
						   	   	    	  	  *pcmbar = 0;
						   	   	    	  	  sprintf(pcmbar, "%s--:--%d--:--%s-N", pd->desckey, pd->dsval, pd->corrule);
								   	   	    	  *presfdback = 0;
																locsit = -1;
																locsit = GetHashploc(clohash, pcmbar);
																if(locsit >= 0)
																{
																		*psenck = 0;
																		strcpy(psenck, pd->desckey);
																		*Ituval = pd->dsval;
																	  strcpy(presfdback, (clohash+locsit)->pfdback);
																	  if(ptgut != NULL)
																	  	free(ptgut);
																	  if(pcmbar != NULL)
																	  	free(pcmbar);
																		return presfdback;
																}
						   	   	    	  }
					   	   	      	  pd = pd->pnext;
					   	   	      }
					   	   	      
					   	   	      *psenck = 0;
										 		 strcpy(psenck, "NULL");
				         	   	   *presfdback = 0;
											   sprintf(presfdback, "�������ϴ�%s���������ο��Խ���", pb->psenckey);
					         	   	 pd = NULL;
											 	 pd = (cptable+(*parmsit))->fdlist;
											 	 while(pd!= NULL)
											 	 {
											 	 	   ps = NULL;
											 	 	   ps = strstr(presfdback, pd->desckey);
											 	 	   if(ps == NULL)
											 	 	   {
													 	 	   strcat(presfdback, pd->desckey);
													 	 	   strcat(presfdback, ",");
											 	 	   }
											 	 	   pd = pd->pnext;	 
												 }
												 strcat(presfdback, ";������Ҫ���ĸ�?");
												 *Ituval = 0;
							         	 if(ptgut != NULL)
														free(ptgut);
												 if(pcmbar != NULL)
														free(pcmbar);
												 return presfdback;
									  }
									  else if(pb->paranum ==1)
									  {
									  	  pd = NULL;
									  	  pd = (cptable+(*parmsit))->fdlist;
									  	  pk = NULL;
					   	       	  pk = (cptable+(*(pb->lparsity)))->fdlist;
									  	  while(pd!= NULL)
					   	   	      {
					   	   	      	  while(pk!= NULL)
					   	   	          {
							   	   	      	  s2val = -1;
							   	   	      	  s2val = strcmp(pk->desckey, pd->desckey);
							   	   	      	  scval = -1;
															  scval = strcmp(pb->psenckey, pd->desckey);
								   	   	    	  if(scval == 0 && s2val == 0)
								   	   	    	  {
								   	   	    	  	   kdval = -1;
																     kdval = strcmp(pk->corrule, pd->corrule);
																     if(kdval < 0)
																     {
																     	   *ptgut = 0;
																			   strcat(ptgut, (cptable+ *(pb->lparsity))->primarykey);
																			   strcat(ptgut, "####");
																			   strcat(ptgut, (cptable+ *parmsit)->primarykey);
																			   zhbit = -1;
																			   zhbit = GetHashpcmb(cmbtable, ptgut);
																			   if(zhbit >= 0)
														  					 {
														  					 	    *pcmbar = 0;
																						  sprintf(pcmbar, "%s--:--%d--:--%s-Y,%s-Y", pd->desckey, pd->dsval, pk->corrule, pd->corrule);
																						  *presfdback = 0;
																						  locsit = -1;
																						  locsit = GetHashploc(clohash, pcmbar);
																						  if(locsit >= 0)
																						  {
																								  *psenck = 0;
																								  strcpy(psenck, (clohash+locsit)->pscenk);
																								  *Ituval = (clohash+locsit)->intuval;
																							    strcpy(presfdback, (clohash+locsit)->pfdback);
																							    if(ptgut != NULL)
																							  		  free(ptgut);
																							    if(pcmbar != NULL)
																							  		  free(pcmbar);
																							    return presfdback;
																						  }
														  					 }  
																     }
																     else if(kdval > 0)
																     {
																     	   *ptgut = 0;
																			   strcat(ptgut, (cptable+ *parmsit)->primarykey);
																			   strcat(ptgut, "####");
																			   strcat(ptgut, (cptable+ *(pb->lparsity))->primarykey);
																			   zhbit = -1;
																			   zhbit = GetHashpcmb(cmbtable, ptgut);
																			   if(zhbit >= 0)
														  					 {
														  					 	    *pcmbar = 0;
																						  sprintf(pcmbar, "%s--:--%d--:--%s-Y,%s-Y", pd->desckey, pd->dsval, pd->corrule, pk->corrule);
																						  *presfdback = 0;
																						  locsit = -1;
																						  locsit = GetHashploc(clohash, pcmbar);
																						  if(locsit >= 0)
																						  {
																								  *psenck = 0;
																								  strcpy(psenck, (clohash+locsit)->pscenk);
																								  *Ituval = (clohash+locsit)->intuval;
																							    strcpy(presfdback, (clohash+locsit)->pfdback);
																							    if(ptgut != NULL)
																							  		  free(ptgut);
																							    if(pcmbar != NULL)
																							  		  free(pcmbar);
																							    return presfdback;
																						  }
														  					 }
																     }
								   	   	    	  }
						   	   	    	      pk = pk->pnext;
						   	   	    	  }
					   	   	      	  pd = pd->pnext;
					   	   	      }
					   	   	      //#A-Y#B-N
					   	   	      *psenck = 0;
										 		 strcpy(psenck, "NULL");
				         	   	   *presfdback = 0;
											   sprintf(presfdback, "�������ϴ�%s���������ο��Խ���", pb->psenckey);
					         	   	 pd = NULL;
											 	 pd = (cptable+(*parmsit))->fdlist;
											 	 while(pd!= NULL)
											 	 {
											 	 	   strcat(presfdback, pd->desckey);
											 	 	   strcat(presfdback, ","); 
											 	 	   pd = pd->pnext;	 
												 }
												 strcat(presfdback, ";������Ҫ���ĸ�?");
												 *Ituval = 0;
							         	 if(ptgut != NULL)
														free(ptgut);
												 if(pcmbar != NULL)
														free(pcmbar);
												 return presfdback;
									  }
									  else if(pb->paranum ==2)
									  {
									  	  for(j=0; j<pb->paranum; j++)
					   	          {
					   	          	  pk = NULL;
					   	       	      pk = (cptable+(*((pb->lparsity)+j)))->fdlist;
					   	       	      pd = NULL;
									  	      pd = (cptable+(*parmsit))->fdlist;
									  	      while(pd!= NULL)
							   	   	      {
							   	   	      	  while(pk!= NULL)
							   	   	          {
									   	   	      	  s2val = -1;
									   	   	      	  s2val = strcmp(pk->desckey, pd->desckey);
									   	   	      	  scval = -1;
																	  scval = strcmp(pb->psenckey, pd->desckey);
										   	   	    	  if(scval == 0 && s2val == 0)
										   	   	    	  {
										   	   	    	  	   kdval = -1;
																		     kdval = strcmp(pk->corrule, pd->corrule);
																		     if(kdval < 0)
																		     {
																		     	   *ptgut = 0;
																					   strcat(ptgut, (cptable+ *(pb->lparsity))->primarykey);
																					   strcat(ptgut, "####");
																					   strcat(ptgut, (cptable+ *parmsit)->primarykey);
																					   zhbit = -1;
																					   zhbit = GetHashpcmb(cmbtable, ptgut);
																					   if(zhbit >= 0)
																  					 {
																  					 	    *pcmbar = 0;
																								  sprintf(pcmbar, "%s--:--%d--:--%s-Y,%s-Y", pd->desckey, pd->dsval, pk->corrule, pd->corrule);
																								  *presfdback = 0;
																								  locsit = -1;
																								  locsit = GetHashploc(clohash, pcmbar);
																								  if(locsit >= 0)
																								  {
																										  *psenck = 0;
																										  strcpy(psenck, (clohash+locsit)->pscenk);
																										  *Ituval = (clohash+locsit)->intuval;
																									    strcpy(presfdback, (clohash+locsit)->pfdback);
																									    if(ptgut != NULL)
																									  		  free(ptgut);
																									    if(pcmbar != NULL)
																									  		  free(pcmbar);
																									    return presfdback;
																								  }
																  					 }  
																		     }
																		     else if(kdval > 0)
																		     {
																		     	   *ptgut = 0;
																					   strcat(ptgut, (cptable+ *parmsit)->primarykey);
																					   strcat(ptgut, "####");
																					   strcat(ptgut, (cptable+ *(pb->lparsity))->primarykey);
																					   zhbit = -1;
																					   zhbit = GetHashpcmb(cmbtable, ptgut);
																					   if(zhbit >= 0)
																  					 {
																  					 	    *pcmbar = 0;
																								  sprintf(pcmbar, "%s--:--%d--:--%s-Y,%s-Y", pd->desckey, pd->dsval, pd->corrule, pk->corrule);
																								  *presfdback = 0;
																								  locsit = -1;
																								  locsit = GetHashploc(clohash, pcmbar);
																								  if(locsit >= 0)
																								  {
																										  *psenck = 0;
																										  strcpy(psenck, (clohash+locsit)->pscenk);
																										  *Ituval = (clohash+locsit)->intuval;
																									    strcpy(presfdback, (clohash+locsit)->pfdback);
																									    if(ptgut != NULL)
																									  		  free(ptgut);
																									    if(pcmbar != NULL)
																									  		  free(pcmbar);
																									    return presfdback;
																								  }
																  					 }
																		     }
										   	   	    	  }
								   	   	    	      pk = pk->pnext;
								   	   	    	  }
							   	   	      	  pd = pd->pnext;
							   	   	      }
					   	          }
					   	          //#A-Y#B-N
					   	          
					   	          *psenck = 0;
										 		 strcpy(psenck, "NULL");
				         	   	   *presfdback = 0;
											   sprintf(presfdback, "�������ϴ�%s���������ο��Խ���", pb->psenckey);
					         	   	 pd = NULL;
											 	 pd = (cptable+(*parmsit))->fdlist;
											 	 while(pd!= NULL)
											 	 {
											 	 	   ps = NULL;
											 	 	   ps = strstr(presfdback, pd->desckey);
											 	 	   if(ps == NULL)
											 	 	   {
													 	 	   strcat(presfdback, pd->desckey);
													 	 	   strcat(presfdback, ",");
											 	 	   }
											 	 	   pd = pd->pnext;	 
												 }
												 strcat(presfdback, ";������Ҫ���ĸ�?");
												 *Ituval = 0;
							         	 if(ptgut != NULL)
														free(ptgut);
												 if(pcmbar != NULL)
														free(pcmbar);
												 return presfdback;
									  }
									  else
									  {
									  }
							  }
							  else if(gnum == 2)
							  {
							  	  //�������  ����== 
							  	  pd = NULL;
			   	       		pd = (cptable+ *parmsit)->fdlist;
			   	       		pk = NULL;
			   	       		pk = (cptable+*(parmsit+1))->fdlist;
			   	       	  s2val = -1;
	   	   	      	  s2val = strcmp(pk->desckey, pd->desckey);
	   	   	      	  scval = -1;
									  scval = strcmp(pb->psenckey, pd->desckey);
		   	   	    	  if(scval == 0 && s2val == 0)
		   	   	    	  {
		   	   	    	  	   kdval = -1;
										     kdval = strcmp(pk->corrule, pd->corrule);
										     if(kdval < 0)
										     {
										     	   *ptgut = 0;
													   strcat(ptgut, (cptable+ *(parmsit+1))->primarykey);
													   strcat(ptgut, "####");
													   strcat(ptgut, (cptable+ *parmsit)->primarykey);
													   zhbit = -1;
													   zhbit = GetHashpcmb(cmbtable, ptgut);
													   if(zhbit >= 0)
								  					 {
								  					 	    *pcmbar = 0;
																  sprintf(pcmbar, "%s--:--%d--:--%s-Y,%s-Y", pd->desckey, pd->dsval, pk->corrule, pd->corrule);
																  *presfdback = 0;
																  locsit = -1;
																  locsit = GetHashploc(clohash, pcmbar);
																  if(locsit >= 0)
																  {
																		  *psenck = 0;
																		  strcpy(psenck, (clohash+locsit)->pscenk);
																		  *Ituval = (clohash+locsit)->intuval;
																	    strcpy(presfdback, (clohash+locsit)->pfdback);
																	    if(ptgut != NULL)
																	  		  free(ptgut);
																	    if(pcmbar != NULL)
																	  		  free(pcmbar);
																	    return presfdback;
																  }
								  					 }  
										     }
										     else if(kdval > 0)
										     {
										     	   *ptgut = 0;
													   strcat(ptgut, (cptable+ *parmsit)->primarykey);
													   strcat(ptgut, "####");
													   strcat(ptgut, (cptable+ *(parmsit+1))->primarykey);
													   zhbit = -1;
													   zhbit = GetHashpcmb(cmbtable, ptgut);
													   if(zhbit >= 0)
								  					 {
								  					 	    *pcmbar = 0;
																  sprintf(pcmbar, "%s--:--%d--:--%s-Y,%s-Y", pd->desckey, pd->dsval, pd->corrule, pk->corrule);
																  *presfdback = 0;
																  locsit = -1;
																  locsit = GetHashploc(clohash, pcmbar);
																  if(locsit >= 0)
																  {
																		  *psenck = 0;
																		  strcpy(psenck, (clohash+locsit)->pscenk);
																		  *Ituval = (clohash+locsit)->intuval;
																	    strcpy(presfdback, (clohash+locsit)->pfdback);
																	    if(ptgut != NULL)
																	  		  free(ptgut);
																	    if(pcmbar != NULL)
																	  		  free(pcmbar);
																	    return presfdback;
																  }
								  					 }
										     }
		   	   	    	  }
		   	   	    	  else if(scval != 0 && s2val == 0)
		   	   	    	  {
		   	   	    	  	  *psenck = 0;
										 		strcpy(psenck, "NULL");
									  	  *presfdback = 0;
						         	 	sprintf(presfdback, "�������ϴ�%s����, ��������С�ֿ���������ȵ���%s����", pb->psenckey, pd->desckey);
						         	 	*Ituval = 0;
						         	 	if(ptgut != NULL)
														free(ptgut);
											 	if(pcmbar != NULL)
													free(pcmbar);
											 	return presfdback;
		   	   	    	  }
		   	   	    	  //
									  if(pb->paranum ==1)
									  {
									  	  //�ϴΣ��������
									  	  
									  	  pk = NULL;
					   	       	  pk = (cptable+(*(pb->lparsity)))->fdlist;
					   	       	  for(i = 0; i<2; i++)
					   	       	  {
														pd = NULL;
														pd = (cptable+(*(parmsit+i)))->fdlist;
														kdval = -1;
												    kdval = strcmp(pk->corrule, pd->corrule);
												    if(kdval < 0)
												    {
												    	   *ptgut = 0;
															   strcat(ptgut, (cptable+ *(pb->lparsity))->primarykey);
															   strcat(ptgut, "####");
															   strcat(ptgut, (cptable+ *(parmsit+i))->primarykey);
															   zhbit = -1;
															   zhbit = GetHashpcmb(cmbtable, ptgut);
															   if(zhbit >= 0)
										  					 {
										  					 	   scval = -1;
									  								 scval = strcmp(pb->psenckey, (cmbtable+zhbit)->psenckey);
									  								 if(scval == 0)
									  								 {
									  								 		  *pcmbar = 0;
																				  sprintf(pcmbar, "%s--:--%d--:--%s-Y,%s-Y", pb->psenckey, (cmbtable+zhbit)->intenval, pk->corrule, pd->corrule);
																				  *presfdback = 0;
																				  locsit = -1;
																				  locsit = GetHashploc(clohash, pcmbar);
																				  if(locsit >= 0)
																				  {
																						  *psenck = 0;
																						  strcpy(psenck, (clohash+locsit)->pscenk);
																						  *Ituval = (clohash+locsit)->intuval;
																					    strcpy(presfdback, (clohash+locsit)->pfdback);
																					    if(ptgut != NULL)
																					  		  free(ptgut);
																					    if(pcmbar != NULL)
																					  		  free(pcmbar);
																					    return presfdback;
																				  }
									  								 }
									  								 else
									  								 {
									  								 	   *psenck = 0;
																		 		 strcpy(psenck, "NULL");
												         	   	   *presfdback = 0;
																			   sprintf(presfdback, "�������ϴ�%s���������ο��Խ���%s����", pb->psenckey,(cmbtable+zhbit)->psenckey);
																			   *Ituval = 0;
																			   if(ptgut != NULL)
																							free(ptgut);
																				 if(pcmbar != NULL)
																					  		  free(pcmbar);
																				 return presfdback;
									  								 }	
										  					 }	
												    }
												    else if(kdval > 0)
												    {
												    	  *ptgut = 0;
															   strcat(ptgut, (cptable+ *(parmsit+i))->primarykey);
															   strcat(ptgut, "####");
															   strcat(ptgut, (cptable+ *(pb->lparsity))->primarykey);
															   zhbit = -1;
															   zhbit = GetHashpcmb(cmbtable, ptgut);
															   if(zhbit >= 0)
										  					 {
										  					 	   scval = -1;
									  								 scval = strcmp(pb->psenckey, (cmbtable+zhbit)->psenckey);
									  								 if(scval == 0)
									  								 {
									  								 	    *pcmbar = 0;
																				  sprintf(pcmbar, "%s--:--%d--:--%s-Y,%s-Y", pb->psenckey, (cmbtable+zhbit)->intenval, pd->corrule, pk->corrule);
																				  *presfdback = 0;
																				  locsit = -1;
																				  locsit = GetHashploc(clohash, pcmbar);
																				  if(locsit >= 0)
																				  {
																						  *psenck = 0;
																						  strcpy(psenck, (clohash+locsit)->pscenk);
																						  *Ituval = (clohash+locsit)->intuval;
																					    strcpy(presfdback, (clohash+locsit)->pfdback);
																					    if(ptgut != NULL)
																					  		  free(ptgut);
																					    if(pcmbar != NULL)
																					  		  free(pcmbar);
																					    return presfdback;
																				  }
									  								 	   
									  								 }
									  								 else
									  								 {
									  								 	   *psenck = 0;
																		 		 strcpy(psenck, "NULL");
												         	   	   *presfdback = 0;
																			   sprintf(presfdback, "�������ϴ�%s���������ο��Խ���%s����", pb->psenckey,(cmbtable+zhbit)->psenckey);
																			   *Ituval = 0;
																			   if(ptgut != NULL)
																							free(ptgut);
																				 if(pcmbar != NULL)
																					  		  free(pcmbar);
																				 return presfdback;
									  								 }	
										  					 }
												    }
									  	  }
									  }
									  if(pb->paranum ==2)
									  {
									  	   //�ϴΣ��������
									  	   for(j=0; j<2; j++)
									  	   {
									  	   	    pk = NULL;
								   	       	  pk = (cptable+(*(pb->lparsity+j)))->fdlist;
								   	       	  for(i = 0; i<2; i++)
								   	       	  {
																	pd = NULL;
																	pd = (cptable+(*(parmsit+i)))->fdlist;
																	kdval = -1;
															    kdval = strcmp(pk->corrule, pd->corrule);
															    if(kdval < 0)
															    {
															    	   *ptgut = 0;
																		   strcat(ptgut, (cptable+ *(pb->lparsity))->primarykey);
																		   strcat(ptgut, "####");
																		   strcat(ptgut, (cptable+ *(parmsit+i))->primarykey);
																		   zhbit = -1;
																		   zhbit = GetHashpcmb(cmbtable, ptgut);
																		   if(zhbit >= 0)
													  					 {
													  					 	   scval = -1;
												  								 scval = strcmp(pb->psenckey, (cmbtable+zhbit)->psenckey);
												  								 if(scval == 0)
												  								 {
												  								 		  *pcmbar = 0;
																							  sprintf(pcmbar, "%s--:--%d--:--%s-Y,%s-Y", pb->psenckey, (cmbtable+zhbit)->intenval, pk->corrule, pd->corrule);
																							  *presfdback = 0;
																							  locsit = -1;
																							  locsit = GetHashploc(clohash, pcmbar);
																							  if(locsit >= 0)
																							  {
																									  *psenck = 0;
																									  strcpy(psenck, (clohash+locsit)->pscenk);
																									  *Ituval = (clohash+locsit)->intuval;
																								    strcpy(presfdback, (clohash+locsit)->pfdback);
																								    if(ptgut != NULL)
																								  		  free(ptgut);
																								    if(pcmbar != NULL)
																								  		  free(pcmbar);
																								    return presfdback;
																							  }
												  								 }
												  								 else
												  								 {
												  								 	   *psenck = 0;
																					 		 strcpy(psenck, "NULL");
															         	   	   *presfdback = 0;
																						   sprintf(presfdback, "�������ϴ�%s���������ο��Խ���%s����", pb->psenckey,(cmbtable+zhbit)->psenckey);
																						   *Ituval = 0;
																						   if(ptgut != NULL)
																										free(ptgut);
																							 if(pcmbar != NULL)
																								  		  free(pcmbar);
																							 return presfdback;
												  								 }	
													  					 }	
															    }
															    else if(kdval > 0)
															    {
															    	  *ptgut = 0;
																		   strcat(ptgut, (cptable+ *(parmsit+i))->primarykey);
																		   strcat(ptgut, "####");
																		   strcat(ptgut, (cptable+ *(pb->lparsity))->primarykey);
																		   zhbit = -1;
																		   zhbit = GetHashpcmb(cmbtable, ptgut);
																		   if(zhbit >= 0)
													  					 {
													  					 	   scval = -1;
												  								 scval = strcmp(pb->psenckey, (cmbtable+zhbit)->psenckey);
												  								 if(scval == 0)
												  								 {
												  								 	    *pcmbar = 0;
																							  sprintf(pcmbar, "%s--:--%d--:--%s-Y,%s-Y", pb->psenckey, (cmbtable+zhbit)->intenval, pd->corrule, pk->corrule);
																							  *presfdback = 0;
																							  locsit = -1;
																							  locsit = GetHashploc(clohash, pcmbar);
																							  if(locsit >= 0)
																							  {
																									  *psenck = 0;
																									  strcpy(psenck, (clohash+locsit)->pscenk);
																									  *Ituval = (clohash+locsit)->intuval;
																								    strcpy(presfdback, (clohash+locsit)->pfdback);
																								    if(ptgut != NULL)
																								  		  free(ptgut);
																								    if(pcmbar != NULL)
																								  		  free(pcmbar);
																								    return presfdback;
																							  }
												  								 	   
												  								 }
												  								 else
												  								 {
												  								 	   *psenck = 0;
																					 		 strcpy(psenck, "NULL");
															         	   	   *presfdback = 0;
																						   sprintf(presfdback, "�������ϴ�%s���������ο��Խ���%s����", pb->psenckey,(cmbtable+zhbit)->psenckey);
																						   *Ituval = 0;
																						   if(ptgut != NULL)
																										free(ptgut);
																							 if(pcmbar != NULL)
																								  		  free(pcmbar);
																							 return presfdback;
												  								 }	
													  					 }
															    }
												  	  }
									  	   }
									  }
									  
									  	  //��2������Ϊ#A��
							  }
							  else if(gnum == 3)
							  {
							  }
							  else
		            {
		         			
		            }
							  pb = pb->pnext;
						}
						//while(pb != NULL)
						//{
							  
							  pb = pb->pnext;
						//}
			  }		
		}
		if(ptgut != NULL)
	  		free(ptgut);
	  if(pcmbar != NULL)
	  		free(pcmbar);
	  return presfdback;
}
///////////////////////////////////////////////////////////
//function:  �û������˻� -> KL������
//parameter:
//char * parmpaty;   //����䰴���������˻�
//	char * parmback;   //������϶�
//    char * psencek;    //��������
//	char * parkcmb;    //�������������� #A-Y;#B-Y 
//	int intenval;      //��ͼid
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
int Dfbackusintent(hashsptable hspt, char * probotid, hashinfotabl schash, hashindex windtable, hashtable mwhash, TrieNode *root, TrieNode * mroot, char ** PWarry, parmaylist ptlist, char * psenck, int *Ituval, char * presfdback)
{
		parmaylist pl;
		char * pk, *pkey, *p, *ptmk;
		long scbit, rbsit;
		int slen, wlen, kdbit, snbit;
		descklist pd;
		corpmglist pm, mwnlist = NULL;
		
		if(ptlist == NULL)
				return 1;
		prinpmlist(ptlist);
		pl = ptlist;
		while(pl != NULL)
		{
			 if(strcmp(pl->parmpaty, "#A#B")== 0 || strcmp(pl->parmpaty, "#B#A")== 0 ||strcmp(pl->parmpaty, "#A")== 0||strcmp(pl->parmpaty, "#B")== 0)
			 {
			 	    *psenck = 0;
			 	    rbsit = -1;
			 	    rbsit = GetHashsck(hspt, probotid);
			 	    if(rbsit >= 0)
			 	    {
			 	    	  strcpy(psenck, (hspt+rbsit)->bplist->psenckey);
			 	    		*Ituval = (hspt+rbsit)->bplist->itentval;
			 	    }
				 	  *presfdback = 0;
				 	  return 1;
			 }
			 scbit = -1;
			 scbit = GetHashinf(schash, pl->parmpaty);
			 if(scbit >= 0)
			 {//���Ͼ�ֱ������
			 	  *psenck = 0;
					strcpy(psenck, (schash+scbit)->sencdkey);
					*Ituval = (schash+scbit)->rimval;
					pd = (schash+scbit)->fdlist;
					printf("==== 1 ===\n");
					while(pd != NULL)
					{
						  slen = -1;
						  slen = strcmp(pl->parkcmb, pd->corrule);
						  if(slen == 0)
						  {
						  		    *presfdback = 0;
								  	  strcpy(presfdback, pd->desckey);
								  	  return 0;
						  }
						  else
						  {
								  slen = strlen(pl->parkcmb);
								  wlen = strlen(pd->corrule);
								  if(wlen > 0)
								  {
										  pk = NULL;
										  if(slen >wlen)
												  pk = strstr(pl->parkcmb, pd->corrule);
										  else
										  	  pk = strstr(pd->corrule, pl->parkcmb);
										  	 
										  if(pk != NULL)
										  {
										  	  *presfdback = 0;
										  	  strcpy(presfdback, pd->desckey);
										  	  return 0;
										  }
								  }
						  }
						  pd = pd->pnext;
					} 
			 }
			 else
			 {
					  //������Ӵ�
					  pkey = (char *) malloc(2048);
		        slen = strlen(pl->parmpaty);
		        p = pl->parmpaty;
		        
		        while(p!= NULL && *p != 0)
			      {
			      	  slen = strlen(p);
			      	  if(slen <= 2)
			      	  	  break;
			      	  printf("==== 2 ===%s\n", p);
						    while(slen > 1) // Ϊ������������
						    {
					      	  *pkey = 0;
				            strncpy(pkey, p, slen);
										*(pkey+slen) = 0;
										*presfdback = 0;
										scbit = -1;
										scbit = GetHashinf(schash, pkey);
										if(scbit >= 0)
										{
										 	  *psenck = 0;
												strcpy(psenck, (schash+scbit)->sencdkey);
												*Ituval = (schash+scbit)->rimval;
												pd = (schash+scbit)->fdlist;
												while(pd != NULL)
												{
													  slen = -1;
													  slen = strcmp(pl->parkcmb, pd->corrule);
													  if(slen == 0)
													  {
													  		    *presfdback = 0;
															  	  strcpy(presfdback, pd->desckey);
															  	  if(pkey != NULL)
											  								free(pkey);
															  	  return 0;
													  }
													  else
													  {
															  slen = strlen(pl->parkcmb);
															  wlen = strlen(pd->corrule);
															  if(wlen > 0)
															  {
																	  pk = NULL;
																	  if(slen >wlen)
																			  pk = strstr(pl->parkcmb, pd->corrule);
																	  else
																	  	  pk = strstr(pd->corrule, pl->parkcmb);
																	  	 
																	  if(pk != NULL)
																	  {
																	  	  *presfdback = 0;
																	  	  strcpy(presfdback, pd->desckey);
																	  	  if(pkey != NULL)
											  										free(pkey);
																	  	  return 0;
																	  }
															  }
													  }
													  pd = pd->pnext;
												} 
										}
										if(*(p+(slen - 2)) <0 && *(p+(slen-1)) < 0)
												slen  -= 2;
										else
												--slen;
							  }
								if(*p < 0)
										p += 2;
								else
										p++;
			      }
			      
			     /* printf(" 2 ==== 2 ===\n");
			      if(*presfdback == 0)
			      {
					      //�������㷨��λ
					      *pkey = 0;
					      pkey = ustatAquery(mwhash, root, PWarry, pl->parmpaty, pkey, psenck, Ituval);
					      scbit = -1;
							 	scbit = GetHashinf(schash, pkey);
							 	if(scbit >= 0)
							 	{
										pd = (schash+scbit)->fdlist;
										while(pd != NULL)
										{
										  	slen = -1;
										  	slen = strcmp(pl->parkcmb, pd->corrule);
											  if(slen == 0)
											  {
											  		    *presfdback = 0;
													  	  strcpy(presfdback, pd->desckey);
													  	  if(pkey !=NULL)
													  	  		free(pkey);
													  	  return presfdback;
											  }
											  else
											  {
													  slen = strlen(pl->parkcmb);
													  wlen = strlen(pd->corrule);
													  if(wlen > 0)
													  {
															  pk = NULL;
															  if(slen >wlen)
																	  pk = strstr(pl->parkcmb, pd->corrule);
															  else
															  	  pk = strstr(pd->corrule, pl->parkcmb);
															  	 
															  if(pk != NULL)
															  {
															  	  *presfdback = 0;
															  	  strcpy(presfdback, pd->desckey);
															  	  if(pkey !=NULL)
													  	  				free(pkey);
															  	  return presfdback;
															  }
													  }
											  }
											  pd = pd->pnext;
									  } 
							  }
					  }*/
					  printf(" 3 ==== %s ===\n",pl->parmpaty);
			      if(*presfdback == 0)
			      { 
			      		mWindxsearch(windtable, root, mroot, pl->parmpaty, &mwnlist);
			      		printf(" 3 ==== 3 ===>\n" );	
			      		if(mwnlist != NULL)
			      		{
			      			  if(mwnlist->pnext == NULL)
			      			  {
			      			  	  *psenck = 0;
			      			  	  strcpy(psenck, mwnlist->psenck);
			      			  	  *Ituval = mwnlist->inteval;
			      			  	  *presfdback = 0;
												strcpy(presfdback, mwnlist->pfdbak);
			      			  	  if(pkey !=NULL)
						  	  				  free(pkey);
						  	  			if(mwnlist != NULL)
										  	  	freecrplist(&mwnlist);
								  	    return 0;
			      			  }
			      			  else
			      			  {
							      		pm = NULL;
							      		pm = mwnlist;
							      		while(pm!= NULL)
							      		{
							      			  snbit = -1;
							      			  snbit = strcmp(pm->psenck, pl->psencek);
							      			  if(snbit ==0)
							      			  { 
										      			  kdbit = -1;
										      			  kdbit = strcmp(pm->pkind, pl->parkcmb);
										      			  if(kdbit == 0)
										      			  {
										      			  	  *psenck = 0;
										      			  	  strcpy(psenck, pm->psenck);
										      			  	  *Ituval = pm->inteval;
										      			  	  *presfdback = 0;
																			strcpy(presfdback, pm->pfdbak);
										      			  	  if(pkey !=NULL)
													  	  				  free(pkey);
													  	  			if(mwnlist != NULL)
													  	  		  		freecrplist(&mwnlist);
															  	    return 0; 
										      			  }
										      			  else
										      			  {
										      			  	  p = NULL;
										      			  	  p =strchr(pl->parkcmb, ',');
										      			  	  if(p != NULL)
										      			  	  {
										      			  	  	  ptmk = NULL;
										      			  	  	 
										      			  	  	  slen = 0;
										      			  	  	  slen = p - pl->parkcmb;
										      			  	  	  ptmk = (char *)malloc(slen +1);
										      			  	  	  *ptmk = 0;
										      			  	  	  strncpy(ptmk, pl->parkcmb, slen);
										      			  	  	  *(ptmk +slen) = 0;
										      			  	  	  
										      			  	  	  ++p;
										      			  	  	  *pkey = 0;
										      			  	  	  strcpy(pkey, p);
										      			  	  	  strcat(pkey, ",");
										      			  	  	  strcat(pkey,ptmk);
										      			  	  	  kdbit = -1;
														      			  kdbit = strcmp(pm->pkind, pkey);
														      			  if(kdbit == 0)
														      			  {
														      			  	  *psenck = 0;
														      			  	  strcpy(psenck, pm->psenck);
														      			  	  *Ituval = pm->inteval;
														      			  	  *presfdback = 0;
																							strcpy(presfdback, pm->pfdbak);
														      			  	  if(pkey !=NULL)
																	  	  				  free(pkey);
																	  	  		  if(ptmk != NULL)
										      			  	  	  				free(ptmk);
																	  	  			if(mwnlist != NULL)
																	  	  		  		freecrplist(&mwnlist);
																			  	    return 0; 
														      			  }
										      			  	  	  if(ptmk != NULL)
										      			  	  	  		free(ptmk);
										      			  	  }
										      			  }
							      			  }
							      			  
							      			  if(*pl->psencek == 0)
							      			  {
							      			  	  *psenck = 0;
							      			  	  strcpy(psenck, mwnlist->psenck);
							      			  	  *Ituval = mwnlist->inteval;
							      			  	  *presfdback = 0;
																strcpy(presfdback, mwnlist->pfdbak);
							      			  	  if(pkey !=NULL)
										  	  				  free(pkey);
										  	  			if(mwnlist != NULL)
														  	  	freecrplist(&mwnlist);
												  	    return 0;
							      			  }
							      			  pm = pm->pnext;
							      		}
					      	  }
			      	  }
			      	  /*else
			      	  {
			      	  	   printf(" 3 ==== 13 ===>\n" );
			      	  	   *psenck = 0;
	      			  	   strcpy(psenck, "NULL");
	      			  	   *Ituval = 0;
	      			  	   *presfdback = 0;
										 strcpy(presfdback, "���ˣ���˵�Ļ�С��ʶ���ˣ����仰���ԣ�");
	      			  	   if(pkey !=NULL)
				  	  				  free(pkey);
			      	  	   
			      	  	   return 0; 
			      	  }*/
			      	  if(mwnlist != NULL)
										freecrplist(&mwnlist);
			      }
			      if(pkey != NULL)
			      {
			      	   free(pkey);
			      	   pkey = NULL;
			      }
	     } 
			 pl = pl->pnext;
		}
		/*
		*psenck = 0;
	  strcpy(psenck, "NULL");
	  *Ituval = 0;
	  *presfdback = 0;
		strcpy(presfdback, "���ˣ���˵�Ļ�С��ʶ���ˣ����仰���ԣ�");
		*/
	  return 1;
}
///////////////////////////////////////////////////////////
//function: robotid���������Ķϵ� ������ ��ͼ������ 
////  ����ϵ�Ҫ��  
////        1������˲��ֵ���û�дﵽĿ�����
////        2������ֱ���л��µĳ���
//parameter:                   //���� //��ͼ
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
void robotpointmg(hashsptable * HMP, char * probotid, char * psenck, int itenval, int endbit, long *yparsit, int gum)
{
		long ridsit;
	
		if(probotid == NULL || *probotid == 0)
	     return ;
    
		ridsit = -1;
		ridsit = GetHashsck(*HMP, probotid);
		if(ridsit >= 0)
		{
				((*HMP)+ridsit)->spnum += ins_bplist(&(((*HMP)+ridsit)->bplist), psenck, itenval, endbit, yparsit, gum);
        return ;
		}
		else
		{
				SetHashsck(HMP, probotid, psenck, itenval, endbit, yparsit, gum);
        return ;
		}
    return ;
}

///////////////////////////////////////////////////////////
//function: �����û����� ->ֱ�����з������û���userid�����ϵ㳡��
//parameter:
//author: wuxiaoqi
//time: 2016-6-23
///////////////////////////////////////////////////////////
char *Userinteninparmg(hashsptable * HMP, hashinfotabl schash, hashindex windtable, hashtable mwhash, TrieNode *root, TrieNode * mroot, char ** PWarry, hashinfotabl cptable, hashpacomb cmbtable,
                                     hashploctable clohash, char * probotid, char * kuquery, char * psenck, int *Ituval, char * presfdback)
{
	  unsigned int slen, wlen;
		int i, srnum, grnum, akval, jsbv, endsit = 0;
		long * parmsit;
		char * pfdback, *presk;
		parmaylist palist = NULL;
		long ddsit = -1, scbit = -1;
		bpoinlist pb;
		
		pfdback = (char *)malloc(4096);
	  *pfdback = 0;
	  parmsit = (long *)malloc(sizeof(long)*32);
		if(parmsit == NULL)
				return presfdback;
		for(i = 0; i<32; i++)
				*(parmsit + i) = -1;
		srnum = 0;		
	  pfdback = FULL_SUB_MATCH(schash, kuquery, psenck, Ituval, pfdback); 
	  if(*pfdback != 0)
	  {
	  	  *presfdback = 0;
	  	  strcpy(presfdback, pfdback);
	  	  endsit = 0;
	  	  printf("in 0 sav senc %s == %d \n", psenck, *Ituval);
			  robotpointmg(HMP, probotid, psenck, *Ituval, 1, parmsit, srnum);
			  if(pfdback != NULL)
	  	  		free(pfdback);
	  	  return presfdback; 
	  }
	  else
	  {
				slen = strlen(kuquery);
				wlen = 4*slen;
				presk = (char *)malloc(wlen+1);
				*presk = 0;
		    srnum = 0;
				srnum = repqiefen(kuquery, slen, presk, wlen);
			  srnum = 0;
				srnum = segparareplace(cptable, presk, parmsit);//�滻����
				free(presk);
				presk = NULL;
				grnum = 0;
				grnum = Analyparfdbkind(cptable, cmbtable, kuquery, parmsit, srnum, &palist);
				//printf("22 == %s\n", kuquery);
				jsbv = -1;
			  *pfdback = 0;
				jsbv = Dfbackusintent(*HMP, probotid, schash, windtable, mwhash, root, mroot, PWarry, palist, psenck, Ituval, pfdback);//��ȡ������,ȫ������ �ִ�ƥ�� �ַ�������.
				printf("in 1 sav senc %s == %d \n", psenck, *Ituval);
				//if(psenck != NULL &&*psenck != 0)   //*Ituval
				//robotpointmg(HMP, probotid, psenck, *Ituval, 1, parmsit, srnum);
				if(jsbv == 1)   //����������
				{
					  pfdback = usercontextanys(HMP, cptable, cmbtable, clohash, probotid, parmsit, srnum, psenck, Ituval, pfdback);
					  printf("in 2 sav senc %s == %d \n", psenck, *Ituval);
					  robotpointmg(HMP, probotid, psenck, *Ituval, 1, parmsit, srnum);
					  
					  if(*pfdback == 0)
					  {
					     *psenck = 0;
			      		strcpy(psenck, "NULL");
			      	  *Ituval = 0;
			      		*presfdback = 0;
								strcpy(presfdback, "���ˣ���˵�Ļ�С��ʶ���ˣ����仰���ԣ�");
					  }
					  
					  ddsit = -1;
					  ddsit = GetHashsck(*HMP, probotid);
					  if(ddsit >= 0)
					  {
					  		 pb = NULL;
					  		 pb = ((*HMP)+ddsit)->bplist;
					  		 while(pb != NULL)
					  		 {
					  		 	   for(i = 0; i<32; i++)
					  		 	   {
					  		 	   		if(*(pb->lparsity +i)<0)
					  		 	   			  break;
					  		 	   }
					  		 	   pb = pb->pnext;
					  		 }
					  }
				}
				else
			  {
					    
							//robotpointmg(HMP, probotid, psenck, *Ituval, 1, parmsit, srnum);
				}
	  }
		*presfdback = 0;
		
		//3��ֱ�ӿɴ�ķ��� ֱ��hash ����Ӵ�hash ������hash
		presfdback = fdbackparaminst(cptable, pfdback, psenck,*Ituval, parmsit, srnum, presfdback);
		
		/*
	  if(*presfdback != 0)
	  {//�б���ͼƪ�����
	  	   akval = -1;
	  	   akval = strcmp(psenck, "MUSIC");
	  	   if(akval = 0)
	  	   {
				  	   if(*Ituval == 1 || *Ituval == 7)
				  	   	  	robotpointmg(HMP, probotid, psenck, *Ituval, 1, parmsit, srnum);
				  	   else
				  	   {
				  	   	   srnum = 0;//�������մ���
					  	   	 for(i = 0; i<32; i++)
											*(parmsit + i) = -1;
					  	   	 robotpointmg(HMP, probotid, psenck, *Ituval, 1, parmsit, srnum);
				  	   }
	  	   }
	  	   else
	  	   {    
	  	   	    srnum = 0;//�������մ���
		  	   	  for(i = 0; i<32; i++)
								*(parmsit + i) = -1;
		  	   	  robotpointmg(HMP, probotid, psenck, *Ituval, 1, parmsit, srnum);
	  	   }
	  }
	  */
	  free(presk);
	  free(pfdback);
	  if(palist != NULL)
	  {
	  		freePMblist(&palist);
	  		palist = NULL;
	  }
		free(parmsit);
		return presfdback;  
}