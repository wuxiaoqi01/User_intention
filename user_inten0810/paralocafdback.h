
#ifndef _PARAMETER_LOCATION_FEEDBACK_H_
#define _PARAMETER_LOCATION_FEEDBACK_H_

typedef struct Hashclofdnode
{
	long nHashA;
	long nHashB;
	int  bExists;

	char * parlockey;           //Parameter location key 
	char * pfdback;             //��������
	double dscore;              //������ϵ��ֵ
	char * pckind;              //
	char * pscenk;              //��������
	int intuval;                //��ͼ����
}HASHPRLCNODE, *hashploctable;

void Init_plochash(hashploctable * HC);
void free_plochash(hashploctable * HC);

void writ_plochash(hashploctable, const char * pnduppath);
long GetHashploc(hashploctable hploc, const char *pmkey);

////////
int SetHashploc(hashploctable * HC, char *parlockey, char * pfdback, char * pscenk, int inval, char * pckind, double dscore);


void parclocd2hash(hashploctable * HC, const char * pscorpath);
#endif


