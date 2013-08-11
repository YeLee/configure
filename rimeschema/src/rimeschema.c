#include "rimecfg.c"
#include "front.c"

int main(int argc, char* argv[])
{
	ArgvHandle handle = {0};
	handle.head = gethead();
	gtk_init(&argc, &argv);

	if (!initwindow(&handle)) {
		freelist(handle.head);
		return 1;
	}
	gtk_main();

	freelist(handle.head);
	tmalloc(0);
	tfree(NULL);
	return 0;
}
