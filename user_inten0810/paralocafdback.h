
#ifndef _PARAMETER_LOCATION_FEEDBACK_H_
#define _PARAMETER_LOCATION_FEEDBACK_H_

typedef struct Hashclofdnode
{
	long nHashA;
	long nHashB;
	int  bExists;

	char * parlockey;           //Parameter location key 
	char * pfdback;             //反馈句子
	double dscore;              //关联关系分值
	char * pckind;              //
	char * pscenk;              //场景编码
	int intuval;                //意图编码
}HASHPRLCNODE, *hashploctable;

void Init_plochash(hashploctable * HC);
void free_plochash(hashploctable * HC);

void writ_plochash(hashploctable, const char * pnduppath);
long GetHashploc(hashploctable hploc, const char *pmkey);

////////
int SetHashploc(hashploctable * HC, char *parlockey, char * pfdback, char * pscenk, int inval, char * pckind, double dscore);


void parclocd2hash(hashploctable * HC, const char * pscorpath);
#endif


