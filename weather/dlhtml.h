//libcurl下载文件
#include <curl/curl.h>
//为了减少处理的麻烦，全部换了全局变量。
char szurl[128];//保存URL
static char szcontent[32767];//保存网页信息
int ioff;//保存网页数据流指针的偏移量
const int HTTP_SUCCESS = 200;//HTTP成功操作的返回码
CURL *curl_handle;//CURL的句柄
CURLcode curl_code;//CURL错误码

size_t write2var(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	//网页流数据的回调函数
	int ires;
	ires = size * nmemb;

	if((ioff + ires) > sizeof(szcontent))
	{
		fprintf(stderr, "Error!Buffer overflow!");
		exit(3);
	}

	strncpy(szcontent + ioff , ptr , ires / sizeof(char));
	ioff += ires;
	return ires;
}

int init_libcurl()//libcurl初始化
{
	curl_code = curl_global_init(CURL_GLOBAL_ALL);

	if(curl_code != CURLE_OK)
	{
		fprintf(stderr, "Error!%s!\n", curl_easy_strerror(curl_code));
		exit(2);
	}

	curl_handle = curl_easy_init();

	if(curl_handle == NULL)
	{
		fprintf(stderr, "Error!Can't init handle!\n");
		exit(2);
	}

	curl_code = curl_easy_setopt(curl_handle, CURLOPT_URL, szurl);

	if(curl_code != CURLE_OK)
	{
		fprintf(stderr, "Error!%s!\n", curl_easy_strerror(curl_code));
		exit(2);
	}

	curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 10);

	if(curl_code != CURLE_OK)
	{
		fprintf(stderr, "Error!%s!\n", curl_easy_strerror(curl_code));
		exit(2);
	}

	curl_code = curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, \
	                             "Mozilla/5.0");

	if(curl_code != CURLE_OK)
	{
		fprintf(stderr, "Error!%s!\n", curl_easy_strerror(curl_code));
		exit(2);
	}

	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write2var);

	if(curl_code != CURLE_OK)
	{
		fprintf(stderr, "Error!%s!\n", curl_easy_strerror(curl_code));
		exit(2);
	}

	return 0;
}

int downloadhtml()//下载html文件
{
	ioff = 0;
	int http_code=0;
	curl_code = curl_easy_perform(curl_handle);

	if(curl_code != CURLE_OK)
	{
		fprintf(stderr, "Error!%s!\n", curl_easy_strerror(curl_code));
		exit(2);
	}

	curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_code);

	if(http_code != HTTP_SUCCESS)
	{
		fprintf(stderr, "Error!Connection Error!\n");
		exit(2);
	}

	ioff = 0;
	return 0;
}

char *cuthtml(char *szsrc)//截断html，减少要处理的信息。
{
	char * szpar , * sztmp;
	szpar = strstr(szsrc, "<h2><strong>");
	sztmp = strstr(szpar, "</div>");
	memset(sztmp, '\0', 6);
	return szpar;
}

