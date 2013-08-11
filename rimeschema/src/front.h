#ifndef FRONT_H
#define FRONT_H

#include <gtk/gtk.h>

#define TEXT_COLUMN 0
typedef struct _ARGV_HANDLE_ {
	GtkWindow* mwin;
	GtkComboBox* combobox;
	GtkLabel* label;
	GtkBox* box;
	GtkCellRenderer* renderer;
	RimeSchemaTable* head;
} ArgvHandle;

char* newstrcat(int num, char* newstart, ...);
GtkTreeModel* createmodel(ArgvHandle* handle);
gboolean combox_changed_value(GtkComboBox* combobox, ArgvHandle* handle);
gboolean initwindow(ArgvHandle* handle);

#endif
