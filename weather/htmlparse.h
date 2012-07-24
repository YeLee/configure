//解析html文件的一大堆函数
typedef struct _WEATHER_INFO//保存某天天气信息的结构体
{
	char *time;//时间
	char *winfo;//当天天气
	char *temp;//当天温度
	char *wind;//当天风况
	struct _WEATHER_INFO *next;
} WEATHER_INFO, *PWEATHER_INFO;
typedef struct _WTARGET//解析得到的目标信息
{
	char *szplace;//城市
	char *sztime;//发布时间
	PWEATHER_INFO weatherinfo;
} WTARGET, *PWTARGET;

int lenofstr(const char *szsta)//到下一个'<'的字串长度
{
	int ilong = 0;

	for(ilong = 0; szsta[ilong] != '<'; ilong++);

	return ilong + 1;
}

char *pushstr(char *szsrc, char cflag)//查找cflag，返回下一个字符
{
	char *szswap;
	szswap = strchr(szsrc, cflag);
	return szswap + 1;
}

char *strincpy(char *szdst, char *szsrc, char cflag)
//拷贝字串，直到遇到cflag。
{
	int i;
	for(i = 0; szsrc[i] != cflag; i++) szdst[i]=szsrc[i];
	szdst[i]='\0';
	return szdst;
}

int formtime(char *szdst, char *szsrc)//格式化天气信息的发布时间
{
	char sztmp[16];
	sprintf(szdst,"%s年",strincpy(sztmp, szsrc ,'-'));
	sprintf(szdst+strlen(szdst), "%s月",\
		strincpy(sztmp, pushstr(szsrc,'-') ,'-'));
	sprintf(szdst+strlen(szdst), "%s日",\
		strincpy(sztmp, pushstr(pushstr(szsrc,'-'), '-') ,' '));
	sprintf(szdst+strlen(szdst),"%s",\
		strincpy(sztmp, pushstr(szsrc, ' '), '<' ));
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
		if(isdigit(szsrc[i]))//遇到数字则开始处理
		{
			is = 1;
		}

		if(is)
		{
			sztemp[j] = szsrc[i];
			j++;
			szsrc[i] = '<';//把'<'前面的字符修改，方便后面处理。
		}
	}

	return sztemp;
}

PWTARGET parhtml(char *szpar)//解析html文档的主函数
{
	PWTARGET pw = malloc(sizeof(WTARGET));//保存天气信息的指针
	memset(pw, '\0', sizeof(WTARGET));
	static char * sztemp;
	szpar = pushstr(pushstr(szpar, '>'), '>');
	char *szplace = malloc(sizeof(char) * lenofstr(szpar));
	strincpy(szplace, szpar, '<'); //城市信息
	pw->szplace = szplace;
	szpar = strstr(szpar, "<h3>") + 4;
	char *sztime = malloc(sizeof(char) * 30);
	formtime(sztime, szpar);//发布时间
	pw->sztime = sztime;
	PWEATHER_INFO ppre;//指向先前链表
	int i;

	for(i = 0; i < 5; i++)//保存五天的天气信息
	{
		PWEATHER_INFO pcurrent = malloc(sizeof(WEATHER_INFO));
		//保存指针指向的当前天的天气信息

		if(pw->weatherinfo == NULL)
		{
			pw->weatherinfo = pcurrent;//保存链表头
		}

		else
		{
			ppre->next = pcurrent;//把数据接到链表
		}

		memset(pcurrent, '\0', sizeof(WEATHER_INFO));
		szpar = strstr(szpar, "<dd>") + 4;
		pcurrent->time = malloc(sizeof(char) * lenofstr(szpar));
		strincpy(pcurrent->time, szpar, '<');//当天时间
		szpar = strstr(szpar, "<dt>") + 5;
		sztemp = savetemp(szpar);
		pcurrent->temp = malloc(sizeof(char) * (strlen(sztemp) + 1));
		strcpy(pcurrent->temp, sztemp);//当天温度
		pcurrent->winfo = malloc(sizeof(char) * lenofstr(szpar));
		strincpy(pcurrent->winfo, szpar, '<');//当天天气
		szpar = strchr(szpar, ';') + 1;
		pcurrent->wind = malloc(sizeof(char) * lenofstr(szpar));
		strincpy(pcurrent->wind, szpar, '<' );//当天风况
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

