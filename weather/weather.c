#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <gtk-2.0/gtk/gtk.h>
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
gchar *output;
GTimer *timer;
gchar gargv[260];
gint gtime;

void key_press_event(GtkWidget *widget, GdkEventKey *event, gpointer data)//几个按键的函数
{
	if(event->keyval == GDK_ALT_LEFT)pralt = TRUE;
	if(event->keyval == GDK_S)if(pralt == TRUE)gtk_main_quit();
}
void key_release_event(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	if(event->keyval == GDK_ALT_LEFT)pralt = FALSE;
}
void button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
        if(event->button == GDK_MOUSE_LEFT) 
        {
		drag = TRUE;
		Xoff = event->x;
		Yoff = event->y;
        }
}
void button_release_event(GtkWidget * widget, GdkEventButton * event, gpointer data)
{
        if(event->button == GDK_MOUSE_LEFT)drag = FALSE;
}
void motion_notify_event(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	if(drag)
	{
		int x, y;
		GtkWidget *t_window = (GtkWidget *)data;
		gtk_window_get_position((GtkWindow *)t_window, &x, &y);
		gtk_window_move((GtkWindow *)t_window, x + event->x - Xoff, y + event->y - Yoff);
        }
}


static gboolean time_handler(GtkWidget *widget)//定时器
{
	g_spawn_command_line_sync(gargv, &output, NULL, NULL, NULL);
	gtk_label_set_text(GTK_LABEL(label), output);
	return TRUE;
}


GtkWidget *create_window ()//创建窗口
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
	gtk_widget_set_events(t_window, GDK_EXPOSURE_MASK| GDK_LEAVE_NOTIFY_MASK| GDK_BUTTON_PRESS_MASK| GDK_BUTTON_RELEASE_MASK| GDK_POINTER_MOTION_MASK| GDK_POINTER_MOTION_HINT_MASK);
	gtk_signal_connect(GTK_OBJECT(t_window), "key_press_event", (GtkSignalFunc)key_press_event, t_window);
	gtk_signal_connect(GTK_OBJECT(t_window), "key_release_event", (GtkSignalFunc)key_release_event, t_window);
	gtk_signal_connect(GTK_OBJECT(t_window), "button_press_event", (GtkSignalFunc)button_press_event, t_window);
	gtk_signal_connect(GTK_OBJECT(t_window), "button_release_event",(GtkSignalFunc)button_release_event, t_window);
	gtk_signal_connect(GTK_OBJECT(t_window), "motion_notify_event", (GtkSignalFunc)motion_notify_event, t_window);
	g_timeout_add(gtime * 1000, (GSourceFunc)time_handler, (gpointer)t_window);
	label = gtk_label_new(NULL);
	gtk_container_add(GTK_CONTAINER(t_window), label);
	return t_window;
}
int isnum(const char *sznum)//判断是否数字
{
	int i;
	for(i = 0; sznum[i] != '\0'; i++)if(!isdigit(sznum[i]))return 0;
	return 1;
}

int usage(const char *szargv)//Usage：
{
	printf("%s filename interval(s)\n",szargv);
	return 0;
}

int main(int argc, char **argv)//入口函数
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}
	gtk_init(&argc, &argv);

	if(!g_file_test(argv[1], G_FILE_TEST_EXISTS))
	{
		printf("%s isn't EXIST!\n",argv[1]);
		return 1;
	}

	if(g_file_test(argv[1], G_FILE_TEST_IS_DIR))
	{
		printf("%s is a DIR!\n",argv[1]);
		return 1;
	}

/*	if(!g_file_test(argv[1], G_FILE_TEST_IS_EXECUTABLE))
	{
		printf("%s isn't EXECUTABLE!\n",argv[1]);
		return 1;
	}
*/
	if(strlen(argv[1]) > 255)
	{
		printf("%s is too LONG!\n", argv[1]);
		return 1;
	}

	if(!isnum(argv[2]))
	{
		printf("%s isn't a NUMBER!\n", argv[2]);
		return 1;
	}

	gtime = atol(argv[2]);
	memset(gargv, 0, sizeof(gargv));
	gargv[0] = 's';
	gargv[1] = 'h';
	gargv[2] = ' ';
	strncpy(gargv + 3, argv[1], strlen(argv[1]));
	timer = g_timer_new();
	mainwindow = create_window ();
	gtk_widget_show_all(mainwindow); 
	time_handler(mainwindow);
	gtk_main();
	return 0;
}

