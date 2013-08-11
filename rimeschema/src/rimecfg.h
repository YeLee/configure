#ifndef RIMECFG_H
#define RIMECFG_H

#include <dirent.h>

#ifdef NOLIBYAML
#include <yaml/api.c>
#include <yaml/scanner.c>
#include <yaml/reader.c>
#else
#include <yaml/yaml_private.h>
#endif

#define _TOKEN_DATA_ token.data.scalar.value
#define MARK_PROC 0X0001
#define MARK_MATCH 0X0002
#define STAT_KEY 0X0001
#define STAT_VALUE 0X0002
#define TYPE_ID 0X0001
#define TYPE_NAME 0X0002
#define TYPE_AUTHOR 0X0004
#define TYPE_DESC 0X0008
#define VOIDBIT 0x0000
typedef unsigned short bitint;

#define POINTLIST(obj) (PointList *) obj

typedef struct _RIME_NAME_LIST_ {
	char* data;
	struct _RIME_NAME_LIST_* next;
}RimeNameList;

typedef struct _STRUCT_RIME_SCHEMA_INFO_ {
	char* id;
	char* name;
	RimeNameList* author;
	char* desc;
} RimeSchemaInfo;

typedef struct _STRUCT_RIME_SCHEMA_TABLE_ {
	RimeSchemaInfo* data;
	struct _STRUCT_RIME_SCHEMA_TABLE_* next;
} RimeSchemaTable;

typedef struct _STRUCT_POINT_LIST_ {
	void* data;
	struct _STRUCT_POINT_LIST_* next;
} PointList;

RimeSchemaTable* gethead();
PointList* savelist(PointList* head, void* data);
void freelist(RimeSchemaTable* head);
RimeSchemaInfo* getschemainfo(const char* id);

#endif
