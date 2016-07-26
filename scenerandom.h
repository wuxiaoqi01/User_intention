
#ifndef _SCENE_RANDOM_CHOICE_H_
#define _SCENE_RANDOM_CHOICE_H_

#define	SCEN_RANDCHOI_LEN 128

typedef char * wchps;

void loadrandsong(wchps  WsN[], const char * randsgpath);
//随机播放最新歌曲
char * randplaynewsg(wchps  WsN[], char * newsgkey);

//随机播放热门歌曲
char * randplayhotsg (wchps  WsN[], char * hotsgkey);

//随机播放80年代歌曲
char * randplay80sg (wchps  WsN[], char * sg80key);

//随机播放70年代歌曲
char * randplay70sg (wchps  WsN[], char * sg70key);

//随机歌曲舞蹈
char * randplaysgdanc (wchps  WsN[], char * sgdanc);

//随机播放电影
//char * randplay (wchps  WsN[], char * sgdanc);

#endif

