

#set library name
SET(CSF_GLOBAL_PROJECT_NAME "")

#set csf library name
SET(CSF_GLOBAL_LIBRARY_NAME "")

#set executable name
SET(CSF_GLOBAL_EXECUTABLE_NAME "")
SET(CSF_GLOBAL_PROJECT_LIBRARY_STATIC_NAME "")
SET(CSF_GLOBAL_PROJECT_LIBRARY_SHARED_NAME "")

#set include directories
SET(CSF_GLOBAL_INCLUDE_DIRECTORIES "")

#set library directories
SET(CSF_GLOBAL_LIBRARY_DIRECTORIES "")


#define macro for get sub project directories
MACRO(SUB_PROJECT_SOURCE_DIRECTORY_LIST dest_paramete src_directory)
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

#get source in all sub directories
SUB_PROJECT_SOURCE_DIRECTORY_LIST(SUB_PROJECT_SRC_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})

#MESSAGE(STATUS "build library SRC_DIR:[${CMAKE_CURRENT_SOURCE_DIR}]")

FOREACH(SUB_SRC_DIRECTORY ${SUB_PROJECT_SRC_DIRECTORIES})
  #MESSAGE(STATUS "into directory:[${SUB_SRC_DIRECTORY}]")
  ADD_SUBDIRECTORY(${SUB_SRC_DIRECTORY})
ENDFOREACH()
