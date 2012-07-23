//用来测试的接口
int process()
{
	downloadhtml();
	PWTARGET pinfo = parhtml(cuthtml(szcontent));
	printf("信息来源于:%s\n%s\t%s\n", szurl, pinfo->szplace, \
	       pinfo->sztime);
	PWEATHER_INFO ppre = pinfo->weatherinfo;

	do
	{
		PWEATHER_INFO pcur = ppre;
		printf("%s\t%s\t%s\t%s\n", pcur->time, pcur->temp, \
		       pcur->winfo, pcur->wind);
		ppre = ppre->next;
	}
	while(ppre);

	nulwtarget(pinfo);
	sleep(10);
	process();
	return 0;
}

