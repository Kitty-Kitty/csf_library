

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


#set lib directory
SET(CSF_THIRD_PARTY_LIB_DIR ${CSF_THIRD_PARTY_DIR}/lib)
#set src directory
SET(CSF_THIRD_PARTY_SRC_DIR ${CSF_THIRD_PARTY_DIR}/src)


#add all subdirectory
ADD_SUBDIRECTORY(${CSF_THIRD_PARTY_LIB_DIR})
ADD_SUBDIRECTORY(${CSF_THIRD_PARTY_SRC_DIR})


#add include dir
SET(CSF_INCLUDE_DIR	${CSF_INCLUDE_DIR} PARENT_SCOPE)
#add lib dir
SET(CSF_LIBRARY_DIR	${CSF_LIBRARY_DIR} PARENT_SCOPE)


#更新平台使用第三方库目录根地址
SET(CSF_THIRD_PARTY_ROOT_DIR ${CSF_THIRD_PARTY_ROOT_DIR} PARENT_SCOPE)