
#define macro for get all sub directories
MACRO(ALL_SOURCE_DIRECTORY_LIST dest_paramete src_directory)
	#find ./ -type d
	EXECUTE_PROCESS(
		COMMAND find ${src_directory} -mindepth 2 -name "CMakeLists.txt" -type f
		COMMAND sed "s/CMakeLists.txt.*//g"
		OUTPUT_VARIABLE tmp_directories
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	STRING(REGEX REPLACE "\n" ";" ${dest_paramete} "${tmp_directories}")
	#SET(${dest_paramete} ${tmp_directories})
ENDMACRO()


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

#set core directory
SET(CSF_SRC_CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/core)
#set modules directory
SET(CSF_SRC_MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules)


#add core source
ADD_SUBDIRECTORY(${CSF_SRC_CORE_DIR})

#add modules source
ADD_SUBDIRECTORY(${CSF_SRC_MODULES_DIR})