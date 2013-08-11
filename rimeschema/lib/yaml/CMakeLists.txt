set(LIBSRC_LIST yaml_private.h api.c reader.c scanner.c parser.c loader.c
	writer.c emitter.c dumper.c)
add_library(yaml SHARED ${LIBSRC_LIST})
add_library(yaml_static STATIC ${LIBSRC_LIST})
set_target_properties(yaml PROPERTIES VERSION 0.1.4 SOVERSION 0)
set_target_properties(yaml_static PROPERTIES OUTPUT_NAME "yaml")
