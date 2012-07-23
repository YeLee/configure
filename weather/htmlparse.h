//解析html文件的一大堆函数
typedef struct _WEATHER_INFO//保存某天天气信息的结构体
{
	char *time;
	char *winfo;
	char *temp;
	char *wind;
	struct _WEATHER_INFO *next;
} WEATHER_INFO, *PWEATHER_INFO;
typedef struct _WTARGET//解析得到的目标信息
{
	char *szplace;
	char *sztime;
	PWEATHER_INFO weatherinfo;
} WTARGET, *PWTARGET;

int lenofstr(const char *szsta)//判断'>'和'<'两个符号之间的长度
{
	if(szsta[0] != '>') return 0;

	int ilong = 0;

	for(ilong = 0; szsta[ilong] != '<'; ilong++);

	return ilong + 1;
}

char *nulstr(char *szsrc)//查找'<'并置零，返回下一个字符
{
	char *szswap;
	szswap = strchr(szsrc, '<');
	szswap[0] = '\0';
	return szswap + 1;
}

char * strnull(char *szsrc)//查找'\0'并返回下一个字符
{
	int i;

	for(i = 0; szsrc[i] != '\0'; i++);

	return (szsrc + i + 1);
}

int nullfirstchar(char *szchar)//置零字串的首个字符
{
	szchar[0] = '\0';
	return 0;
}

int formtime(char *szdst, char *szsrc)//格式化天气信息的发布时间
{
	char *szswap = szsrc;
	szswap = strchr(szswap, '-');
	nullfirstchar(szswap);
	szswap = strchr(szswap + 1, '-');
	nullfirstchar(szswap);
	szswap = strchr(szswap + 1, ' ');
	nullfirstchar(szswap);
	sprintf(szdst, "%s年%s月%s日%s", szsrc, strnull(szsrc), strnull(\
	        strnull(szsrc)), strnull(strnull(strnull(szsrc))));
	return 0;
}

static char *savetemp(char * szsrc)//保存字串中的温度信息
{
	static char sztemp[16];
	int i = 0, j = 0;
	int is = 0;
	memset(sztemp, '\0', sizeof(sztemp));

	for(i = 0; szsrc[i] != '<'; i++)
	{
		if(isdigit(szsrc[i]))
		{
			is = 1;
		}

		if(is)
		{
			sztemp[j] = szsrc[i];
			j++;
			szsrc[i] = '\0';
		}
	}

	return sztemp;
}

PWTARGET parhtml(char *szpar)//解析html文档的主函数
{
	PWTARGET pw = malloc(sizeof(WTARGET));//保存天气信息的指针
	memset(pw, '\0', sizeof(WTARGET));
	char *szswap;
	static char * sztemp;
	szpar = strchr(szpar, '>');
	szpar = strchr(szpar + 1, '>');
	char *szplace = malloc(sizeof(char) * lenofstr(szpar));
	szswap = nulstr(szpar);
	strcpy(szplace, szpar + 1);
	pw->szplace = szplace;
	szpar = szswap;
	szpar = strstr(szpar, "<h3>");
	szpar = strchr(szpar, '>');
	szswap = nulstr(szpar) + 1;
	char *sztime = malloc(sizeof(char) * 30);
	formtime(sztime, szpar + 1);
	pw->sztime = sztime;
	PWEATHER_INFO ppre;
	int i;

	for(i = 0; i < 5; i++)//保存五天的天气信息
	{
		PWEATHER_INFO pcurrent = malloc(sizeof(WEATHER_INFO));
		//保存指针指向的当前天的天气信息

		if(pw->weatherinfo == NULL)
		{
			pw->weatherinfo = pcurrent;
		}

		else
		{
			ppre->next = pcurrent;
		}

		memset(pcurrent, '\0', sizeof(WEATHER_INFO));
		szpar = strstr(szswap, "<dd>");
		szpar = strchr(szpar, '>');
		pcurrent->time = malloc(sizeof(char) * lenofstr(szpar));
		szswap = nulstr(szpar);
		strcpy(pcurrent->time, szpar + 1);
		szpar = strstr(szswap, "<dt>");
		szpar = strchr(szpar, '>');
		szswap = strstr(szpar, "<br");
		sztemp = savetemp(szpar);
		pcurrent->temp = malloc(sizeof(char) * (strlen(sztemp) + 1));
		strcpy(pcurrent->temp, sztemp);
		pcurrent->winfo = malloc(sizeof(char) * (strlen(szpar) + 1));
		strcpy(pcurrent->winfo, szpar + 2);
		szpar = strchr(szswap, ';');
		szpar[0] = '>';
		pcurrent->wind = malloc(sizeof(char) * lenofstr(szpar));
		szswap = nulstr(szpar);
		strcpy(pcurrent->wind, szpar + 1);
		ppre = pcurrent;
	}

	return pw;
}

int nulwtarget(PWTARGET pw)//释放内存，防止内存泄漏。
{
	free(pw->szplace);
	free(pw->sztime);
	PWEATHER_INFO ppre = pw->weatherinfo;

	do
	{
		PWEATHER_INFO pcurrent = ppre;
		free(pcurrent->time);
		free(pcurrent->winfo);
		free(pcurrent->temp);
		free(pcurrent->wind);
		ppre = ppre->next;
		free(pcurrent);
	}
	while(ppre);

	free(pw);
	return 0;
}

