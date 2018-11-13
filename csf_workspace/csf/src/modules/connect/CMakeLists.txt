
#define macro for get sub module directories
MACRO(SUB_MODULE_SOURCE_DIRECTORY_LIST dest_paramete src_directory)
	#find ./ -type d
	EXECUTE_PROCESS(
		COMMAND find ${src_directory} -mindepth 2 -maxdepth 2 -name "CMakeLists.txt" -type f
		COMMAND sed "s/CMakeLists.txt.*//g"
		OUTPUT_VARIABLE tmp_directories
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	STRING(REGEX REPLACE "\n" ";" ${dest_paramete} "${tmp_directories}")
	#SET(${dest_paramete} ${tmp_directories})
ENDMACRO()

#get source in sub module directories
SUB_MODULE_SOURCE_DIRECTORY_LIST(SUB_SRC_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})

#MESSAGE(STATUS "build library SUB_SRC_DIRECTORIES:[${SUB_SRC_DIRECTORIES}]")

FOREACH(SUB_SRC_DIRECTORY ${SUB_SRC_DIRECTORIES})
  #MESSAGE(STATUS "into directory:[${SUB_SRC_DIRECTORY}]")
  ADD_SUBDIRECTORY(${SUB_SRC_DIRECTORY})
ENDFOREACH()

