// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "UserIntentService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <stdio.h>
#include <string.h>
#include"codedconv.h"
#include"sharfuct.h"
#include"segment.h"
#include"intentsentmg.h"
#include"WordindeCenter.h"
#include"paralocafdback.h"
#include"hashinfoadm.h"
#include"scenbpointsave.h"
#include"sencparampai.h"
#include"Intentdecision.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::intentionreg;
//typedef char* wpchr;
hashinfotabl schash = NULL;
hashinfotabl ephash = NULL;
hashsptable sptable = NULL;
hashpacomb cmbtable = NULL;
hashindex wtable = NULL;
TrieNode *root = NULL;
TrieNode *mroot = NULL;
char ** PWarry;
hashtable mwhash = NULL;
hashploctable clohash = NULL;

class UserIntentServiceHandler : virtual public UserIntentServiceIf {
 public:
  UserIntentServiceHandler() {
    // Your initialization goes here
    const char * singlepath = "/data/lexcion/singlegbk.txt";
		const char * wordpath = "/data/lexcion/wordgbk.txt";
    const char * entyparmpd = "/data/lexcion/newaddlecion.txt";
    const char * stopwpath = "/data/lexcion/stopword1.txt";
                               
    const char * plocwpath = "/data/sintdata/corpusloc.txt";
    const char * imopwpath = "/data/sintdata/intwordset.txt";
		const char * pathsenccorp = "/data/sintdata/feedback.txt";
		const char * pathparmglov = "/data/sintdata/target.txt";  
		const char * pathparcombd = "/data/sintdata/word_relation.txt";
		
		
		int ires;
		ires = 0;
		ires = Initlex3maj((char *)singlepath, (char*)wordpath, (char*)entyparmpd);
    if (ires == -1)
    {
				printf("ci dian jiazai shibai!!!\n");
    }
    PWarry = NULL;
		PWarry = (char **)malloc(sizeof(char*) *32);
		if(PWarry == NULL)
		{
				printf(" shibai!!!\n");
		}
		//去除停用词
    StopW_instrie(root, stopwpath);
    impW_instrie(mroot, imopwpath);
    
    schash = NULL;//语料管理hash
		ephash = NULL;//参数管理hash
		sptable = NULL;//场景上下文管理hash
		cmbtable = NULL;//参数对语料管理hash
		wtable = NULL;
		
		Init_infhash(&schash);		//场景语料带反馈   == hash
    scencorp2hash(&schash, pathsenccorp);
    
		Init_infhash(&ephash);		//参数带种类和场景    == hash
		entyparm2hash(&ephash, pathparmglov);
		
		Init_indexhash(&wtable);
    winfo_2hash(root, mroot, &wtable, (char*)pathsenccorp);

		Init_sckhash(&sptable);		//断点保存 根据机器人ID   == hash

		Init_pcmbhash(&cmbtable);	//参数对 带场景意图id    == hash 
		parmcombpair2hash(&cmbtable, pathparcombd);
		
		Init_mghash(&mwhash);   //多词定位 场景语料
		wmcbScenCorp2Hash(&mwhash, root, PWarry, (char *)pathsenccorp);
		
		Init_plochash(&clohash); //参数场景意图 定位 反馈
    parclocd2hash(&clohash, plocwpath);
    
  }

  void getUserIntent(UserIntent& _return, const std::string& robotid, const std::string& inforsent) {
    // Your implementation goes here
      int ires, nowintv =0;
      char *p, *q, *pgbk, *pfdbkey,*nowscen, *presutf, *pzjk;
	    unsigned int slen, wlen;
	    
	    //printf(" input 1>>>> %s\n", robotid.c_str());
	    //printf(" input 2>>>> %s\n", inforsent.c_str());
	   
			pfdbkey = (char *)malloc(2048*4);
			*pfdbkey = 0;
	    
	    q = NULL;
	    q = (char*)robotid.c_str();
	    if(q == NULL||*q ==0)
	    {
	    	  sprintf(pfdbkey, "{\"robotid\" : \"Robot id is empty! \"}\n");
	    	  _return.sceneid = "NSCE";
    	    _return.inventv = 0;
    	    _return.feedback = pfdbkey;
	    
			    if(pfdbkey != NULL)
			    	  free(pfdbkey);
			    return ;
	    }
	    
	    presutf = (char *)malloc(2048*4);
			pzjk = (char *)malloc(2048*4);
	    p = NULL;
	    p = (char*)inforsent.c_str();
	    if( p == NULL || *p == 0)
	    {
	    	  *pfdbkey = 0;
	    	  *pzjk = 0;
	    	  sprintf(pzjk, "{\"robotid\":\"%s\",\n", q);
	    	  strcat(pfdbkey, pzjk);
	    	  strcat(pfdbkey, "\"scene\":\"Null scene\",\n");
	    		strcat(pfdbkey, "\"Intent\":\"0\"\n");
	    		strcat(pfdbkey, "\"feedback\":\"主人，你的输入是NULL，回归到空场景和空意图..... \"}\n" );
	    		
	    		memset(presutf, 0, 2048*4);
	    		slen = strlen(pfdbkey);
			    wlen = 2048*4;
	    		ires = 0;
			    ires = g2u(pfdbkey, slen, presutf, wlen);
			    
			     _return.robotid = q;
	    		 _return.sceneid = "NSCE";
    	     _return.inventv = 0;
    	     _return.feedback = presutf;
    	     
	        if(presutf != NULL)
			    	  free(presutf);
			    if(pfdbkey != NULL)
			    	  free(pfdbkey);
			    return ;
	    }
	    
	    pgbk = NULL;
	    pgbk = (char *)malloc(2048*4);
	    memset(pgbk, 0, 2048*4);
	    slen = strlen(p);
	    wlen = 2048*4;
	    ires = 0;
	    ires = u2g(p, slen, pgbk, wlen);
	    nowscen = (char *)malloc(32);
			*nowscen = 0;
			nowintv = 0;
			//printf(" ip111 ===   %s\n", pgbk);
			*pzjk = 0;
			if( strcmp(pgbk, "好的")== 0 ||strcmp(pgbk, "是的")== 0||strcmp(pgbk, "ok")== 0||strcmp(pgbk, "OK")== 0||strcmp(pgbk, "可以切换")== 0)
			{
				  ///printf(" input111 ===   %s\n", pgbk);
				  pzjk = Deterswitchscen(sptable, ephash, clohash, q, pgbk, nowscen, &nowintv, pzjk);
		  }
		  else
		  {
					pzjk = Userinteninparmg(&sptable, schash, wtable, mwhash, root, mroot, PWarry, ephash, cmbtable, clohash, q, pgbk, nowscen, &nowintv, pzjk);
			}
			
	    *pfdbkey = 0;
	    *pgbk = 0;
	    sprintf(pgbk, "{\"robotid\":\"%s\",\n", q);
	    strcat(pfdbkey, pgbk);
	    *pgbk = 0;
	    sprintf(pgbk, "\"scene\":\"%s\",\n", nowscen);
	    strcat(pfdbkey, pgbk);
	    *pgbk = 0;
	    sprintf(pgbk, "\"Intent\":\"%d\",\n", nowintv);
	    strcat(pfdbkey, pgbk);
	    *pgbk = 0;
	    sprintf(pgbk, "\"feedback\":\"%s\"}\n", pzjk);
	    strcat(pfdbkey, pgbk);
	    //printf("++ === %s\n", pfdbkey);
	    slen = strlen(pfdbkey);
	    memset(presutf, 0, 2048*4); 
			wlen = 2048*4;
			ires = g2u(pfdbkey, slen, presutf, wlen);
		
	    _return.robotid = q;
	    _return.sceneid = nowscen;
    	_return.inventv = nowintv;
    	_return.feedback = presutf;
    	
    	if(nowscen != NULL)
	    	  free(nowscen);
	    if(pgbk != NULL)
	    	  free(pgbk);
	    	  
    	if(pzjk != NULL)
	    {
	    		free(pzjk);
	    		pzjk = NULL;
	    }
	    
	    if(pfdbkey != NULL)
	    	  free(pfdbkey);
	    	  
	    if(presutf != NULL)
	    	  free(presutf);
  }

};

int main(int argc, char **argv) {
  int port = 9875;
  shared_ptr<UserIntentServiceHandler> handler(new UserIntentServiceHandler());
  shared_ptr<TProcessor> processor(new UserIntentServiceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

