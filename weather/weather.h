//一个用C写的天气预报的小东西，信息来源是天气网。
//为保证程序能正常使用，建议先到下面的网站查询城市代码。
//http://wap.weather.com.cn/wap
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk-2.0/gtk/gtk.h>
#include "dlhtml.h"
#include "htmlparse.h"

#define HEIGHT 0
#define WIDTH 0
#define GDK_S 0x073
#define GDK_ALT_LEFT 0xffe9
#define GDK_MOUSE_LEFT 1

//都扔给全局变量吧，懒得处理了。
GtkWidget *mainwindow;
GtkWidget *label;
gboolean drag = FALSE;
gboolean pralt = FALSE;
gint Xoff = 0;
gint Yoff = 0;
GTimer *timer;
gint gtime;

int isnum(const char *sznum)//判断是否数字
{
	int i;

	for(i = 0; sznum[i] != '\0'; i++) if(!isdigit(sznum[i])) return 0;

	return 1;
}

int usage(const char *szargv)//Usage：
{
	fprintf(stderr, "Usage: %s citycode interval(min)\n", szargv);
	return 0;
}

void key_press_event(GtkWidget *widget, GdkEventKey *event, gpointer data)
//几个按键的函数
{
	if(event->keyval == GDK_ALT_LEFT)pralt = TRUE;

	if(event->keyval == GDK_S)if(pralt == TRUE)gtk_main_quit();
}

void key_release_event(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	if(event->keyval == GDK_ALT_LEFT)pralt = FALSE;
}

void button_press_event(GtkWidget *widget, GdkEventButton *event, \
                        gpointer data)
{
	if(event->button == GDK_MOUSE_LEFT)
	{
		drag = TRUE;
		Xoff = event->x;
		Yoff = event->y;
	}
}

void button_release_event(GtkWidget * widget, GdkEventButton * event, \
                          gpointer data)
{
	if(event->button == GDK_MOUSE_LEFT)drag = FALSE;
}

void motion_notify_event(GtkWidget *widget, GdkEventButton *event, \
                         gpointer data)
{
	if(drag)
	{
		int x, y;
		GtkWidget *t_window = (GtkWidget *)data;
		gtk_window_get_position((GtkWindow *)t_window, &x, &y);
		gtk_window_move((GtkWindow *)t_window, \
		                x + event->x - Xoff, y + event->y - Yoff);
	}
}

static gboolean time_handler(GtkWidget *widget)//定时器
{
	downloadhtml();
	PWTARGET pinfo = parhtml(cuthtml(szcontent));
	sprintf(szcontent, "\n\t信息来源于%s\n\t%s\t%s\t\n", szurl, pinfo->szplace, \
	        pinfo->sztime);
	PWEATHER_INFO ppre = pinfo->weatherinfo;

	do
	{
		PWEATHER_INFO pcur = ppre;
		sprintf(szcontent + strlen(szcontent), "\t%s\t%s\t%s\t%s\t\n", \
		        pcur->time, pcur->temp, pcur->winfo, pcur->wind);
		ppre = ppre->next;
	}
	while(ppre);

	nulwtarget(pinfo);
	gtk_label_set_text(GTK_LABEL(label), szcontent);
	return TRUE;
}

GtkWidget *create_window() //创建窗口
{
	GtkWidget *t_window;
	t_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(t_window), WIDTH, HEIGHT);
	gtk_window_set_position(GTK_WINDOW(t_window), GTK_WIN_POS_MOUSE);
	gtk_window_set_skip_taskbar_hint(GTK_WINDOW(t_window), TRUE);
	gtk_window_set_skip_pager_hint(GTK_WINDOW(t_window), TRUE);
	gtk_window_set_decorated(GTK_WINDOW(t_window), FALSE);
	gtk_window_set_opacity(GTK_WINDOW(t_window), 0.5);
	gtk_window_set_keep_above(GTK_WINDOW(t_window), TRUE);
	gtk_widget_set_events(t_window, GDK_EXPOSURE_MASK| \
		GDK_LEAVE_NOTIFY_MASK| GDK_BUTTON_PRESS_MASK| \
		GDK_BUTTON_RELEASE_MASK| GDK_POINTER_MOTION_MASK| \
		GDK_POINTER_MOTION_HINT_MASK);
	gtk_signal_connect(GTK_OBJECT(t_window), "key_press_event", \
	                   (GtkSignalFunc)key_press_event, t_window);
	gtk_signal_connect(GTK_OBJECT(t_window), "key_release_event", \
	                   (GtkSignalFunc)key_release_event, t_window);
	gtk_signal_connect(GTK_OBJECT(t_window), "button_press_event", \
	                   (GtkSignalFunc)button_press_event, t_window);
	gtk_signal_connect(GTK_OBJECT(t_window), "button_release_event",\
	                   (GtkSignalFunc)button_release_event, t_window);
	gtk_signal_connect(GTK_OBJECT(t_window), "motion_notify_event", \
	                   (GtkSignalFunc)motion_notify_event, t_window);
	g_timeout_add(gtime * 1000 * 60, (GSourceFunc)time_handler, \
	              (gpointer)t_window);
	label = gtk_label_new(NULL);
	gtk_container_add(GTK_CONTAINER(t_window), label);
	return t_window;
}

