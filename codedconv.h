#ifndef CODEDCONV_H_
#define CODEDCONV_H_
//#pragma once
#include <iconv.h>
#include <stddef.h>

int u2g(char *inbuf,size_t inlen,char *outbuf,size_t outlen);
int code_convert(const char *from_charset,const char *to_charset,char *inbuf,size_t inlen,char *outbuf,size_t outlen);

int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen);
int g2w(char *inbuf,size_t inlen,char *outbuf,size_t outlen);
int w2g(char *inbuf,size_t inlen,char *outbuf,size_t outlen);
int u2w(char *inbuf,size_t inlen,char *outbuf,size_t outlen);
int w2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen);
#endif 