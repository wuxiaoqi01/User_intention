#include "netTransport.h"





int split_to_fb_rule(char *strSrc, char *dst1, char *rule)
{
	if(strlen(strSrc)>BUFSIZE)
	return -1;
	
    int i = 0,j=0;
    int state = BEG;    /* 初始状态 */
	
 	memset(dst1,0,BUFSIZE); //数据初始化--清零
	memset(rule,0,BUFSIZE); //数据初始化--清零	
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
		return 1;//寻找规则标记,没有就返回
	else
	{
	memcpy(dst1,strSrc,i-4);//第1段
	memcpy(rule,strSrc+i,BUFSIZE-i);//第2段 规则
	//printf("aaaa:%s %s\n",dst1,rule);
	*(dst1+BUFSIZE-1)=0;
	*(rule+BUFSIZE-1)=0;
	}
return 0;
}



int split_to_fb_fb(char *strSrc, char *dst1, char *dst2)
{
 	

    int i = 0,j=0;
    int state = BEG;    /* 初始状态 */

	if(strlen(strSrc)>BUFSIZE)
	return -1;
    
 	memset(dst1,0,BUFSIZE); //数据初始化--清零
 	memset(dst2,0,BUFSIZE); //数据初始化--清零
 
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
memcpy(dst1,strSrc,i-5);//第1段
memcpy(dst2,strSrc+i,BUFSIZE-i);//第2段
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
memset(replace_str_buf,0,sizeof(replace_str_buf));//指针全置零

rule_buf=(char*)malloc(BUFSIZE);
send_buf=(char*)malloc(BUFSIZE);
ret_buf=(char*)malloc(BUFSIZE);
wait_split=(char*)malloc(BUFSIZE);
tmp_buf=(char*)malloc(BUFSIZE);



if(split_to_fb_rule(feedback,wait_split,rule_buf)==1)goto error;//把规则放到rule_buf,而反馈语句放到tmp_buf

i=0;feedback_buf[0]=(char*)malloc(BUFSIZE);
while( 0 == split_to_fb_fb(wait_split, feedback_buf[i],tmp_buf))
{
memcpy(wait_split,tmp_buf,BUFSIZE);//把分隔过程中的字段放到tmp_buf
i++;
feedback_buf[i]=(char*)malloc(BUFSIZE);//为下次填充申请空间
}
if(i>0)memcpy(feedback_buf[i],wait_split,BUFSIZE);//把最后一段放进数组
else goto error;

/*
strcpy(feedback_buf1,strtok_s( feedback, "[>@<]", &feedback_buf3));//第一段
printf("feedback_buf1:%s",feedback_buf1);
strcpy(feedback_buf2,strtok_s( feedback_buf3, "[<>]", &rule_buf));//第二段和规则语句
*/
//if(ret==1 || ret==-1)return feedback;


struct sockaddr_in remote_addr; //服务器端网络地址结构体
 //数据传送的缓冲区
memset(&remote_addr,0,sizeof(remote_addr)); //数据初始化--清零
remote_addr.sin_family=AF_INET; //设置为IP通信
remote_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//服务器IP地址
remote_addr.sin_port=htons(8001); //服务器端口号
if((client_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)
{
perror("socket");
strcpy(feedback,"初始化套接字错误,快去看看自然语言组的闫昊还活着么?活着就起来改代码");
goto error;
}
setsockopt(client_sockfd,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(struct timeval));
//printf("feedback :%s -----  sce:%s",feedback,scence);
//printf("feedback -----  \n");
//fflush(stdout);

if(connect(client_sockfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))<0)
{
perror("connect");
strcpy(feedback,"连接不上服务器,快去看看服务器组是不是有空调被偷了");
goto error;
}
sprintf(send_buf, "%s+%s", scence,rule_buf);//发送MUSIC+规则语句
//printf("---%s----%s",send_buf,scence);
len=send(client_sockfd,send_buf,strlen(send_buf),0);
if(len==-1){
	strcpy(feedback,"发不出数据,快去看看自然语言组的闫昊还活着么?活着就起来改代码");
	goto error;
	}

memset(wait_split,0,BUFSIZE); //数据初始化--清零
len=recv(client_sockfd,wait_split,BUFSIZE,0);//接受返回的字串,以[>@<]分隔
if(len==-1){
	strcpy(feedback,"接收不到数据,快去看看服务器组是不是有空调被偷了");
	goto error;
	}

//printf("wait_split--%s--send_buf--%s  len : %d\n",wait_split,send_buf,len);




j=0;replace_str_buf[0]=(char*)malloc(BUFSIZE);
while( 0 == split_to_fb_fb(wait_split, replace_str_buf[j],tmp_buf))
{
memcpy(wait_split,tmp_buf,BUFSIZE);//把分隔过程中的字段放到tmp_buf
j++;
replace_str_buf[j]=(char*)malloc(BUFSIZE);//为下次填充申请空间
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






close(client_sockfd);//关闭套接字

free(rule_buf);
free(send_buf);
free(wait_split);


//释放内存
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
