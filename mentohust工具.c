#include <string.h>
#include <stdio.h>
#include <stdlib.h>
static const unsigned char base64Tab[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};
static const char xorRuijie[] = {"~!:?$*<(qw2e5o7i8x12c6m67s98w43d2l45we82q3iuu1z4xle23rt4oxclle34e54u6r8m"};

static int encodePass(char *dst, const char *osrc) {
    unsigned char in[3], buf[70];
	unsigned char *src = buf;
	int sz = strlen(osrc);
    int i, len;
	if (sizeof(xorRuijie) < sz)
		return -1;
	for(i=0; i<sz; i++)
		src[i] = osrc[i] ^ xorRuijie[i];
    while (sz > 0) {
        for (len=0, i=0; i<3; i++, sz--) {
			if (sz > 0) {
				len++;
				in[i] = src[i];
            } else in[i] = 0;
        }
        src += 3;
        if (len) {
			dst[0] = base64Tab[ in[0] >> 2 ];
			dst[1] = base64Tab[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
			dst[2] = len > 1 ? base64Tab[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=';
			dst[3] = len > 2 ? base64Tab[ in[2] & 0x3f ] : '=';
            dst += 4;
        }
    }
    *dst = '\0';
	return 0;
}

static int decodePass(char *dst, const char *src) {
	unsigned esi = 0, idx = 0;
	int i=0, j=0, equal=0;
	for(; src[i]!='\0'; i++) {
		if (src[i] == '=') {
			if (++equal > 2)
				return -1;
		} else {
			for(idx=0; base64Tab[idx]!='\0'; idx++) {
				if(base64Tab[idx] == src[i])
					break;
			}
			if (idx == 64)
				return -1;
			esi += idx;
		}
		if(i%4 == 3) {
			dst[j++] = (char)(esi>>16);
			if(equal < 2)
				dst[j++] = (char)(esi>>8);
			if(equal < 1)
				dst[j++] = (char)esi;
			esi = 0;
			equal = 0;
		}
		esi <<= 6;
	}
	if (i%4!=0 || sizeof(xorRuijie)<j)
		return -1;
	for(i=0; i<j; i++)
		dst[i] ^= xorRuijie[i];
	dst[j] = '\0';
	return 0;
}

int usage(const char *szargv)
{
    printf("%s [-d] string\n",szargv);
    return 0;
}
int main(int argc , char **argv)
{
    if(argc != 2 && argc != 3)
    {
        usage(argv[0]);
        exit(0);
    }
    if(argc == 3)
    {
        if(strcmp("-d",argv[1]) != 0)
        {
            usage(argv[0]);
            exit(1);
        }
    }
    char szdst[2028];
    if (argc == 2)
    {
        encodePass(szdst,argv[1]) ;
    }
    if(argc == 3)
    {
        decodePass(szdst,argv[2]);
    }
    printf("%s\n",szdst);
    return 0;
}
