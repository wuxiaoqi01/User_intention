
#ifndef _SCENE_RANDOM_CHOICE_H_
#define _SCENE_RANDOM_CHOICE_H_

#define	SCEN_RANDCHOI_LEN 128

typedef char * wchps;

void loadrandsong(wchps  WsN[], const char * randsgpath);
//����������¸���
char * randplaynewsg(wchps  WsN[], char * newsgkey);

//����������Ÿ���
char * randplayhotsg (wchps  WsN[], char * hotsgkey);

//�������80�������
char * randplay80sg (wchps  WsN[], char * sg80key);

//�������70�������
char * randplay70sg (wchps  WsN[], char * sg70key);

//��������赸
char * randplaysgdanc (wchps  WsN[], char * sgdanc);

//������ŵ�Ӱ
//char * randplay (wchps  WsN[], char * sgdanc);

#endif

