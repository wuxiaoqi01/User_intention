#ifndef netTransport
#define netTransport

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


#define BUFSIZE 256
enum {BEG = 0, NORMAL1 = 1,NORMAL2 = 2,NORMAL3 = 3,NORMAL4 = 4,FIND_END = 5, NOT_FIND_END = 6};

char * ran_result_replace(char *feedback,char *scence);

#endif
