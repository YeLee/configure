#include "weather.h"
//#include "process.h"
int main(int argc, char *argv[])//入口函数
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}

	if(strlen(argv[1]) > 15)
	{
		fprintf(stderr, "%s is too LONG!\n", argv[1]);
		return 1;
	}

	if(!isnum(argv[1]))
	{
		fprintf(stderr, "%s isn't a NUMBER!\n", argv[1]);
		return 1;
	}

	if(!isnum(argv[2]))
	{
		fprintf(stderr, "%s isn't a NUMBER!\n", argv[2]);
		return 1;
	}

	memset(szurl, 0, sizeof(szurl));
	strcpy(szurl, "http://wap.weather.com.cn/wap/weather/");
	strcpy(szurl + 38, argv[1]);
	strcat(szurl, ".shtml");
	init_libcurl();
	//process();

	gtime = atol(argv[2]);
	gtk_init(&argc, &argv);
	timer = g_timer_new();
	mainwindow = create_window();
	gtk_widget_show_all(mainwindow);
	time_handler(mainwindow);
	gtk_main();

	curl_easy_cleanup(curl_handle);
	curl_global_cleanup();
	return 0;
}
