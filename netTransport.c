#include "netTransport.h"





int split_to_fb_rule(char *strSrc, char *dst1, char *rule)
{
	if(strlen(strSrc)>BUFSIZE)
	return -1;
	
    int i = 0,j=0;
    int state = BEG;    /* ��ʼ״̬ */
	
 	memset(dst1,0,BUFSIZE); //���ݳ�ʼ��--����
	memset(rule,0,BUFSIZE); //���ݳ�ʼ��--����	
	state = BEG;
	
	while ('\0' != *(strSrc+i) && NULL !=(strSrc+i))
		{
			switch (state)
			{
			case BEG:		
				if (*(strSrc+i) =='[') 
				{
					state = NORMAL1;
				}
				break;
			case NORMAL1:	  
				if (*(strSrc+i) == '<') 
				{
					state = NORMAL2;
				}
				else state = BEG;
				break;
			case NORMAL2:	  
				if (*(strSrc+i) == '>') 
				{
					state = NORMAL3;
				}
				else state = BEG;
				break;
			case NORMAL3:	  
				if (*(strSrc+i) == ']') 
				{
					state = FIND_END;
				}
				else state = BEG;
				break;
			default:
				state = BEG;
				break;
			}
			i++;
			if(state==FIND_END)break;
		}
	 if(state!=FIND_END)
		return 1;//Ѱ�ҹ�����,û�оͷ���
	else
	{
	memcpy(dst1,strSrc,i-4);//��1��
	memcpy(rule,strSrc+i,BUFSIZE-i);//��2�� ����
	//printf("aaaa:%s %s\n",dst1,rule);
	*(dst1+BUFSIZE-1)=0;
	*(rule+BUFSIZE-1)=0;
	}
return 0;
}



int split_to_fb_fb(char *strSrc, char *dst1, char *dst2)
{
 	

    int i = 0,j=0;
    int state = BEG;    /* ��ʼ״̬ */

	if(strlen(strSrc)>BUFSIZE)
	return -1;
    
 	memset(dst1,0,BUFSIZE); //���ݳ�ʼ��--����
 	memset(dst2,0,BUFSIZE); //���ݳ�ʼ��--����
 
    while ('\0' != *(strSrc+i) && NULL !=(strSrc+i))
    {
        switch (state)
        {
        case BEG:       
            if (*(strSrc+i) == '[') 
            {
                state = NORMAL1;
            }
            break;
		case NORMAL1:     
            if (*(strSrc+i) == '>') 
            {
				state = NORMAL2;
            }
			else state = BEG;
			break;
		case NORMAL2:     
			if (*(strSrc+i) =='@') 
            {
				state = NORMAL3;
            }		
			else state = BEG;
			break;
		case NORMAL3:	  
			if (*(strSrc+i) =='<') 
			{
				state = NORMAL4;
			}
			else state = BEG;
			break;
		case NORMAL4:	  
			if (*(strSrc+i) ==']') 
			{
				state = FIND_END;
				
			}
			else state = BEG;
			break;
		default: 
			state = BEG;
			break;
        }
		
		i++;
		if(state==FIND_END)break;
    }
 
if(state!=FIND_END)
	return 1;
else
{
memcpy(dst1,strSrc,i-5);//��1��
memcpy(dst2,strSrc+i,BUFSIZE-i);//��2��
*(dst1+BUFSIZE-1)=0;
*(dst2+BUFSIZE-1)=0;

//printf("bbbb:%s %s\n",dst1,dst2);

}

return 0;
}


char * ran_result_replace(char *feedback,char *scence)
{
int client_sockfd;
int len,ret=0,i=0,j=0;

char *rule_buf;
char *send_buf;
char *ret_buf;
char *wait_split;
char *tmp_buf;
struct timeval timeout={0,100000};

char *feedback_buf[32];
char *replace_str_buf[32];
if(feedback==NULL or scence == NULL or strlen(scence) == 0){
	printf("feedback or scence error!!\n");
	return feedback;
}

memset(feedback_buf,0,sizeof(feedback_buf));
memset(replace_str_buf,0,sizeof(replace_str_buf));//ָ��ȫ����

rule_buf=(char*)malloc(BUFSIZE);
send_buf=(char*)malloc(BUFSIZE);
ret_buf=(char*)malloc(BUFSIZE);
wait_split=(char*)malloc(BUFSIZE);
tmp_buf=(char*)malloc(BUFSIZE);



if(split_to_fb_rule(feedback,wait_split,rule_buf)==1)goto error;//�ѹ���ŵ�rule_buf,���������ŵ�tmp_buf

i=0;feedback_buf[0]=(char*)malloc(BUFSIZE);
while( 0 == split_to_fb_fb(wait_split, feedback_buf[i],tmp_buf))
{
memcpy(wait_split,tmp_buf,BUFSIZE);//�ѷָ������е��ֶηŵ�tmp_buf
i++;
feedback_buf[i]=(char*)malloc(BUFSIZE);//Ϊ�´��������ռ�
}
if(i>0)memcpy(feedback_buf[i],wait_split,BUFSIZE);//�����һ�ηŽ�����
else goto error;

/*
strcpy(feedback_buf1,strtok_s( feedback, "[>@<]", &feedback_buf3));//��һ��
printf("feedback_buf1:%s",feedback_buf1);
strcpy(feedback_buf2,strtok_s( feedback_buf3, "[<>]", &rule_buf));//�ڶ��κ͹������
*/
//if(ret==1 || ret==-1)return feedback;


struct sockaddr_in remote_addr; //�������������ַ�ṹ��
 //���ݴ��͵Ļ�����
memset(&remote_addr,0,sizeof(remote_addr)); //���ݳ�ʼ��--����
remote_addr.sin_family=AF_INET; //����ΪIPͨ��
remote_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//������IP��ַ
remote_addr.sin_port=htons(8001); //�������˿ں�
if((client_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)
{
perror("socket");
strcpy(feedback,"��ʼ���׽��ִ���,��ȥ������Ȼ���������껻�����ô?���ž������Ĵ���");
goto error;
}
setsockopt(client_sockfd,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(struct timeval));
//printf("feedback :%s -----  sce:%s",feedback,scence);
//printf("feedback -----  \n");
//fflush(stdout);

if(connect(client_sockfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))<0)
{
perror("connect");
strcpy(feedback,"���Ӳ��Ϸ�����,��ȥ�������������ǲ����пյ���͵��");
goto error;
}
sprintf(send_buf, "%s+%s", scence,rule_buf);//����MUSIC+�������
//printf("---%s----%s",send_buf,scence);
len=send(client_sockfd,send_buf,strlen(send_buf),0);
if(len==-1){
	strcpy(feedback,"����������,��ȥ������Ȼ���������껻�����ô?���ž������Ĵ���");
	goto error;
	}

memset(wait_split,0,BUFSIZE); //���ݳ�ʼ��--����
len=recv(client_sockfd,wait_split,BUFSIZE,0);//���ܷ��ص��ִ�,��[>@<]�ָ�
if(len==-1){
	strcpy(feedback,"���ղ�������,��ȥ�������������ǲ����пյ���͵��");
	goto error;
	}

//printf("wait_split--%s--send_buf--%s  len : %d\n",wait_split,send_buf,len);




j=0;replace_str_buf[0]=(char*)malloc(BUFSIZE);
while( 0 == split_to_fb_fb(wait_split, replace_str_buf[j],tmp_buf))
{
memcpy(wait_split,tmp_buf,BUFSIZE);//�ѷָ������е��ֶηŵ�tmp_buf
j++;
replace_str_buf[j]=(char*)malloc(BUFSIZE);//Ϊ�´��������ռ�
}
memcpy(replace_str_buf[j],wait_split,BUFSIZE);





memset(ret_buf,0,BUFSIZE);
for(i=0;feedback_buf[i]!=NULL;i++)
{
	//printf("ret---%s---\n",feedback_buf[i]);
	strcat(ret_buf, feedback_buf[i]);
	if(replace_str_buf[i]!=NULL)
		strcat(ret_buf, replace_str_buf[i]);
}






close(client_sockfd);//�ر��׽���

free(rule_buf);
free(send_buf);
free(wait_split);


//�ͷ��ڴ�
for(i=0;feedback_buf[i]!=NULL;i++)
{
free(feedback_buf[i]);
}
for(i=0;replace_str_buf[i]!=NULL;i++)
{
free(replace_str_buf[i]);
}
free(feedback);
return ret_buf;

error:
	
	for(i=0;feedback_buf[i]!=NULL;i++)
	{
	free(feedback_buf[i]);
	}
	for(i=0;replace_str_buf[i]!=NULL;i++)
	{
	free(replace_str_buf[i]);
	}
	free(rule_buf);
	free(send_buf);
	free(ret_buf);
	free(wait_split);
	free(tmp_buf);
	return feedback;
}
