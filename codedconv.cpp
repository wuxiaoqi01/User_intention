#include "codedconv.h"
int code_convert(const char *from_charset,const char *to_charset,char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
		iconv_t cd;
		int rc;
		char **pin = &inbuf;
		char **pout = &outbuf;
		cd = iconv_open(to_charset,from_charset);
		if (cd==0) return -1;
		if (iconv(cd,pin,(size_t *)&inlen,pout,(size_t *)&outlen)==((size_t)(-1))) {
				iconv_close(cd);
				return -1;
		}
		iconv_close(cd);
		return 0;
}

int u2g(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
			return code_convert("utf-8","gbk",inbuf,inlen,outbuf,outlen);
}

int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
			return code_convert("gbk","utf-8",inbuf,inlen,outbuf,outlen);
}

int g2w(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
			return code_convert("gbk","utf-16",inbuf,inlen,outbuf,outlen);
}

int w2g(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
			return code_convert("utf-16","gbk",inbuf,inlen,outbuf,outlen);
}

int u2w(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
			return code_convert("utf-8","utf-16",inbuf,inlen,outbuf,outlen);
}

int w2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
			return code_convert("utf-16","utf-8",inbuf,inlen,outbuf,outlen);
}
