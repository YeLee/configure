#include "rimecfg.h"

void* tmalloc(size_t i)
{
	static int imalloc = 0;
	if (i == 0) {
		printf("Allocated:%d\n", imalloc);
		return NULL;
	}
	imalloc ++;

	return malloc(i);
}

void tfree(void* mem)
{
	static int ifree = 0;
	if (mem == NULL) {
		printf("Recovered:%d\n", ifree);
		return;
	}
	ifree ++;
	free(mem);
	return;
}

RimeSchemaTable* gethead()
{
	RimeSchemaTable* head = NULL;
	DIR* rimedir;
	rimedir = opendir(RIME_DATA_DIR);
	if (rimedir) {
		struct dirent* dirinfo = {0};
		while (dirinfo = readdir(rimedir)) {
			int len = strlen(dirinfo->d_name);
			if (len > 12 &&
					!strcmp(".schema.yaml", dirinfo->d_name + len - 12)) {
				char* file = tmalloc((len + strlen(RIME_DATA_DIR) + 2)
						* sizeof(char));
				strcpy(file, RIME_DATA_DIR);
				strcat(file, "/");
				strcat(file, dirinfo->d_name);
				head = (RimeSchemaTable *) savelist(POINTLIST(head),
						getschemainfo(file));
				tfree(file);
			}
		}
	}
	closedir(rimedir);
	return head;
}

PointList* savelist(PointList* head, void* data)
{
	if (!data) return head;
	PointList* current = tmalloc(sizeof(PointList));
	current->next = NULL;
	if (!head) {
		head = current;
	} else {
		PointList* prev = head;
		while (prev->next)
			prev = prev->next;
		prev->next = current;
	}
	current->data = data;
	return head;
}

void freelist(RimeSchemaTable* head)
{
	RimeSchemaTable* current;
	while(head)
	{
		current = head;
		tfree(current->data->id);
		tfree(current->data->name);
		RimeNameList* currentauthor = current->data->author;
		while(currentauthor) {
			RimeNameList* prevauthor = currentauthor;
			if (currentauthor->next) {
				currentauthor = currentauthor->next;
			} else {
				currentauthor = NULL;
			}
			tfree(prevauthor->data);
			tfree(prevauthor);
		}
		tfree(current->data->desc);
		tfree(current->data);
		tfree(current);
		head = head->next;
	}
	return;
}

RimeSchemaInfo* getschemainfo(const char* id)
{
	FILE* file = {0};
	yaml_parser_t parser = {0};
	yaml_token_t token = {0};
	file = fopen(id, "r");
	if (!file) return NULL;
	if (!yaml_parser_initialize(&parser)) return NULL;
	yaml_parser_set_input_file(&parser, file);
	int block = 0;
	bitint mark = VOIDBIT, stat = VOIDBIT, type = VOIDBIT;
	RimeSchemaInfo* result = tmalloc(sizeof(RimeSchemaInfo));
	memset(result, '\0', sizeof(RimeSchemaInfo));
	do {
		yaml_parser_scan(&parser, &token);
		if ((~mark & MARK_PROC) && token.type == YAML_KEY_TOKEN) {
			mark |= MARK_MATCH;
		} else if ((mark & MARK_MATCH) && token.type == YAML_SCALAR_TOKEN &&
				!strcmp(token.data.scalar.value, "schema")) {
			mark |= MARK_PROC;
			mark &= ~MARK_MATCH;
		} else if ((mark & MARK_PROC) &&
				token.type == YAML_BLOCK_MAPPING_START_TOKEN) {
			mark |= MARK_MATCH;
		} else if ((mark & MARK_PROC) && (mark & MARK_MATCH)) {
			if (token.type == YAML_SCALAR_TOKEN) {
				if (stat & STAT_KEY) {
					stat = VOIDBIT;
					if (!strcmp("schema_id", _TOKEN_DATA_)) {
						type = TYPE_ID;
					} else if (!strcmp("name", _TOKEN_DATA_)) {
						type = TYPE_NAME;
					} else if (!strcmp("author", _TOKEN_DATA_)) {
						type = TYPE_AUTHOR;
					} else if (!strcmp("description", _TOKEN_DATA_)) {
						type = TYPE_DESC;
					}
				} else if (stat & STAT_VALUE) {
					if ((type & TYPE_ID) && !result->id) {
						result->id = tmalloc((strlen(_TOKEN_DATA_) + 1) *
									sizeof(char));
						strcpy(result->id, _TOKEN_DATA_);
					} else if ((type & TYPE_NAME) && !result->name) {
						result->name = tmalloc((strlen(_TOKEN_DATA_) + 1) *
									sizeof(char));
						strcpy(result->name, _TOKEN_DATA_);
					} else if ((type & TYPE_AUTHOR)) {
						char* author = NULL;
						if (_TOKEN_DATA_) {
							author = tmalloc((strlen(_TOKEN_DATA_) + 1) *
										sizeof(char));
							strcpy(author, _TOKEN_DATA_);
						}
						result->author = (RimeNameList*) savelist(
								POINTLIST(result->author), author);
					} else if ((type & TYPE_DESC) && !result->desc) {
						result->desc = tmalloc((strlen(_TOKEN_DATA_) + 1) *
									sizeof(char));
						strcpy(result->desc, _TOKEN_DATA_);
					}
				}
			} else if (token.type == YAML_KEY_TOKEN) {
				stat = STAT_KEY;
			} else if (token.type == YAML_VALUE_TOKEN) {
				stat = STAT_VALUE;
			} else if (token.type == YAML_BLOCK_ENTRY_TOKEN) {
				block++;
			} else if (token.type == YAML_BLOCK_END_TOKEN) {
				if (block == 0) {
					yaml_token_delete(&token);
					break;
				}
				block--;
			}
		}
		if (token.type != YAML_STREAM_END_TOKEN)
			yaml_token_delete(&token);
	} while(token.type != YAML_STREAM_END_TOKEN);
	yaml_parser_delete(&parser);
	fclose(file);
	return result;
}

