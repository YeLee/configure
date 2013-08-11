#include "front.h"

char* newstrcat(int num, char* newstart, ...)
{
	int len = 0;
	int i;
	va_list ap;
	char* newstr = NULL;
	char* argstr = NULL;

	if (newstart) len = strlen(newstart);

	va_start(ap, newstart);

		for (i = 1; i < num; i++) {
			argstr = (char*) va_arg(ap, char*);
			len += strlen(argstr);
		}

	va_end(ap);
	
	newstr = tmalloc((len + 1) * sizeof(char));
	memset(newstr, '\0', sizeof(newstr));
	if (newstart) {
		strcpy(newstr, newstart);
		tfree(newstart);
	}

	va_start(ap, newstart);

		for (i = 1; i < num; i++) {
			argstr = (char*) va_arg(ap, char*);
			strcat(newstr, argstr);
		}

	va_end(ap);

	return newstr;
}

GtkTreeModel* createmodel(ArgvHandle* handle)
{
	GtkListStore* list = gtk_list_store_new(1, G_TYPE_STRING);
	GtkTreeIter tree = {0};
	RimeSchemaTable* current = handle->head;

	while(current) {
		gtk_list_store_append(list, &tree);
		gtk_list_store_set(list, &tree, TEXT_COLUMN, current->data->name, -1);

		if (current->next) {
			current = current->next;
		} else {
			current = NULL;
		}

	}

	return GTK_TREE_MODEL(list);
}

gboolean combox_changed_value(GtkComboBox* combobox, ArgvHandle* handle)
{
	GtkTreeModel* model = gtk_combo_box_get_model(combobox);
	GtkTreeIter tree;
	char* schema_name;
	char* str = NULL;
	RimeSchemaTable* current = handle->head;

	gtk_combo_box_get_active_iter(combobox, &tree);
	gtk_tree_model_get(model, &tree, TEXT_COLUMN, &schema_name, -1);

	while(current) {
		if (!strcmp(current->data->name, schema_name)) {
			str = newstrcat(6, NULL, "Schema_id:\n\t", current->data->id,
					"\nSchema_name:\n\t", current->data->name,
					"\nSchema_author:");
			RimeNameList* currentauthor = current->data->author;

			while(currentauthor) {
				str = newstrcat(3, str, "\n\t", currentauthor->data);
				RimeNameList* prevauthor = currentauthor;

				if (currentauthor->next) {
					currentauthor = currentauthor->next;
				} else {
					currentauthor = NULL;
				}

			}

			str = newstrcat(3, str,
					"\nSchema_description:\n", current->data->desc);
	 		gtk_label_set_text(handle->label, str);
			tfree(str);
		}

		if (current->next) {
			current = current->next;
		} else {
			current = NULL;
		}

	}
}

gboolean initwindow(ArgvHandle* handle)
{
	handle->mwin = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
	if (!handle->mwin) return FALSE;

	gtk_window_set_title(handle->mwin, "Rime Schema List");
	gtk_window_set_default_size(handle->mwin, 300, 200);
	gtk_window_set_position(handle->mwin, GTK_WIN_POS_CENTER);
	gtk_window_set_opacity(handle->mwin, 0.9);
	//gtk_window_set_skip_taskbar_hint(handle->mwin, TRUE);
	//gtk_window_set_skip_pager_hint(handle->mwin, TRUE);
	g_signal_connect(handle->mwin, "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	handle->combobox = GTK_COMBO_BOX(gtk_combo_box_new_with_model
			(createmodel(handle)));
	if (!handle->combobox) return FALSE;

	handle->renderer = gtk_cell_renderer_text_new();
	if (!handle->renderer) return FALSE;
	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(handle->combobox),
			handle->renderer, FALSE);
	gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(handle->combobox),
			handle->renderer, "text", TEXT_COLUMN, NULL);

	handle->label = GTK_LABEL(gtk_label_new(NULL));
	if (!handle->label) return FALSE;
	#ifdef ENABLE_GTK3_SUPPORT
	handle->box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_VERTICAL, 0));
	#else
	handle->box = GTK_BOX(gtk_vbox_new(FALSE, 0));
	#endif
	if (!handle->box) return FALSE;
	gtk_box_pack_start(handle->box,
			GTK_WIDGET(handle->combobox), FALSE, FALSE, 0);
	gtk_box_pack_start(handle->box,
			GTK_WIDGET(handle->label), TRUE, TRUE, 0);

	gtk_container_add(GTK_CONTAINER(handle->mwin), GTK_WIDGET(handle->box));
	g_signal_connect(handle->combobox, "changed",
			G_CALLBACK(combox_changed_value), handle);

	gtk_widget_show_all(GTK_WIDGET(handle->mwin));
	return TRUE;
}

