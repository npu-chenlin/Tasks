AUX_SOURCE_DIRECTORY(. LIB_SRC)
message(${LIB_SRC})
add_library(libfloyd ${LIB_SRC})
#set_target_properties(libfloyd PROPERTIES OUTPUT_NAME "floyd")