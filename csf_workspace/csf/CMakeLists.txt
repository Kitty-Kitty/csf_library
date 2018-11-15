#project main CMakeList
CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)

#project name 
PROJECT(CSF_PROJECT C CXX ASM)

# this one is important
SET(CMAKE_SYSTEM_NAME Linux)

#set library name
SET(CSF_PROJECT_NAME csf)
SET(ENV{CSF_PROJECT_NAME} csf)

#set csf library name
SET(CSF_LIBRARY_NAME libcsf)

#set executable name
SET(CSF_EXECUTABLE_NAME csf_library)
SET(CSF_PROJECT_LIBRARY_STATIC_NAME lib${CSF_PROJECT_NAME}.a)
SET(CSF_PROJECT_LIBRARY_SHARED_NAME lib${CSF_PROJECT_NAME}.so)
SET(ENV{CSF_PROJECT_LIBRARY_STATIC_NAME} ${CSF_PROJECT_LIBRARY_STATIC_NAME})
SET(ENV{CSF_PROJECT_LIBRARY_SHARED_NAME} ${CSF_PROJECT_LIBRARY_SHARED_NAME})

#set csf source directory
SET(CSF_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR})

#grep "\"V" include/core/base/csf_version.hpp -m 1 | awk '{print $3}' | awk -F "\"" '{print $2}' | awk -F "V" '{print $2}'
EXECUTE_PROCESS(
    COMMAND grep "\"V" ${CSF_PROJECT_SOURCE_DIR}/include/core/base/csf_version.hpp -m 1
    COMMAND awk "{print $3}"
    COMMAND awk -F "\"" "{print $2}"
    COMMAND awk -F "V" "{print $2}"
    OUTPUT_VARIABLE CSF_PROJECT_LIBRARY_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

IF( CSF_PROJECT_LIBRARY_VERSION )
    SET(CSF_PROJECT_LIBRARY_STATIC_NAME lib${CSF_PROJECT_NAME}-${CSF_PROJECT_LIBRARY_VERSION}.a)
    SET(CSF_PROJECT_LIBRARY_SHARED_NAME lib${CSF_PROJECT_NAME}-${CSF_PROJECT_LIBRARY_VERSION}.so)
ENDIF()

#set system support platform
SET(CSF_PLATFORM_LIST "x86" "hisiv100" "hisiv300" "hisiv400" "cpptestscan")


#select a mode
IF(DEBUG_MODE)        #cmake -D DEBUG_MODE=ON ../
    SET(CMAKE_BUILD_TYPE "Debug")
    #set csf output debug directory
    SET(CSF_PROJECT_OUTPUT_TOP_DIR ${PROJECT_BINARY_DIR}/debug)
    SET(CSF_OUTPUT_EXECUTABLE_DIR ${CSF_PROJECT_OUTPUT_TOP_DIR}/${CSF_EXECUTABLE_NAME})
    SET(CSF_OUTPUT_LIBRARY_DIR ${CSF_PROJECT_OUTPUT_TOP_DIR}/${CSF_LIBRARY_NAME})
    SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} ${CMAKE_C_FLAGS_DEBUG} -ggdb3  -pthread -Wl,--no-as-needed -ldl -lrt")
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -std=c++11 -pthread -Wl,--no-as-needed -ldl -lrt")
    MESSAGE(STATUS "use the [debug] mode! output_path:" ${CSF_PROJECT_OUTPUT_TOP_DIR})
ELSE()
    SET(CMAKE_BUILD_TYPE "Release")
    #set csf output release directory
    SET(CSF_PROJECT_OUTPUT_TOP_DIR ${PROJECT_BINARY_DIR}/release)
    SET(CSF_OUTPUT_EXECUTABLE_DIR ${CSF_PROJECT_OUTPUT_TOP_DIR}/${CSF_EXECUTABLE_NAME})
    SET(CSF_OUTPUT_LIBRARY_DIR ${CSF_PROJECT_OUTPUT_TOP_DIR}/${CSF_LIBRARY_NAME})
    SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} ${CMAKE_C_FLAGS_RELEASE}  -Wl,--no-as-needed -pipe -lpthread_nonshared -ldl -lrt")
	SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -Wl,--no-as-needed -pipe -pthread -ldl -lrt")
    MESSAGE(STATUS "use the [release] mode! output_path:" ${CSF_PROJECT_OUTPUT_TOP_DIR})
ENDIF()


IF(NOT DEFINED PLATFORM)
    SET(CSF_PLATFORM "x86")
	MESSAGE(WARNING "set platform warning. parameter[PLATFORM] not defined. used default [PLATFORM = x86]")
	MESSAGE(STATUS "[ctrl + c] to stop; usage: [cmake -DPLATFORM=${CSF_PLATFORM} ../] ; wait [5] seconds for you ...")
	#CTEST_SLEEP(5)
ELSE()
    SET(CSF_PLATFORM ${PLATFORM})
	MESSAGE(STATUS "set parameter[PLATFORM = ${PLATFORM}] ")
ENDIF()

#LIST(FIND CSF_PLATFORM_LIST CSF_PLATFORM FIND_LIST_RETURN)
#IF(${FIND_LIST_RETURN} EQUAL -1)
	#MESSAGE(STATUS "usage: [cmake CSF_PLATFORM=x86 ../] " "  ${FIND_LIST_RETURN}")
	#MESSAGE(FATAL_ERROR "system usupport[CSF_PLATFORM = ${CSF_PLATFORM}]. support system list[${CSF_PLATFORM_LIST}]")
#ENDIF()


#set general x86 platform
IF(CSF_PLATFORM STREQUAL "x86")
  SET(CMAKE_ASM_NASM_COMPILER "as")
  SET(CMAKE_C_COMPILER "gcc")
  SET(CMAKE_CXX_COMPILER "g++")
  SET(CMAKE_CXX_COMPILER_FULLPATH "/usr/bin/g++")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings -Wl,-Bsymbolic")
  
  SET(SYSTEM_USR_INCLUDE_DIR /usr/include/)
  SET(SYSTEM_USR_LOCAL_INCLUDE_DIR /usr/local/include/)
  SET(SYSTEM_USR_LIBRARY_DIR /usr/lib/)
  SET(SYSTEM_USR_LOCAL_LIBRARY_DIR /usr/local/lib/)
  
  SET(CSF_THIRD_PARTY_PLATFORM_NAME "linux_x86")
    
ENDIF()


#set x86_64 flag
IF(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
	ADD_DEFINITIONS(-fPIC)
ENDIF(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")


#set hisiv100 platform
IF(CSF_PLATFORM STREQUAL "hisiv100")
  SET(CMAKE_ASM_NASM_COMPILER "as")
  SET(CMAKE_C_COMPILER "arm-hisiv100nptl-linux-gcc")
  SET(CMAKE_CXX_COMPILER "arm-hisiv100nptl-linux-g++")
  SET(CMAKE_CXX_COMPILER_FULLPATH "/opt/hisi-linux-nptl/arm-hisiv100-linux/target/bin/arm-hisiv100-linux-gcc")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings -Wl,-Bsymbolic")
  
  SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} ${CMAKE_C_FLAGS_DEBUG} -ggdb3 -lpthread -lrt")
  SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} ${CMAKE_C_FLAGS_RELEASE} -pipe -lpthread -lrt")
  
  SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -lpthread -lrt")
  SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -pipe -lpthread -lrt")
  
  SET(SYSTEM_USR_INCLUDE_DIR /opt/hisi-linux-nptl/arm-hisiv100-linux/target/usr/include)
  SET(SYSTEM_USR_LIBRARY_DIR /opt/hisi-linux-nptl/arm-hisiv100-linux/target/usr/lib/)
	
  SET(CSF_THIRD_PARTY_PLATFORM_NAME "arm-hisiv100npt")
    
  ADD_DEFINITIONS(-DPLATEFORM_HISIV)
  
ENDIF()


#set hisiv300 platform
IF(CSF_PLATFORM STREQUAL "hisiv300")
  SET(CMAKE_ASM_NASM_COMPILER "as")
  SET(CMAKE_C_COMPILER "arm-hisiv300-linux-gcc")
  SET(CMAKE_CXX_COMPILER "arm-hisiv300-linux-g++")
  SET(CMAKE_CXX_COMPILER_FULLPATH "/opt/hisi-linux/x86-arm/arm-hisiv300-linux/target/bin/")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings -Wl,-Bsymbolic")
  
  SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} ${CMAKE_C_FLAGS_DEBUG} -ggdb3 -lpthread -lrt -Wl,--no-as-needed -ldl")
  SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} ${CMAKE_C_FLAGS_RELEASE} -pipe -lpthread -lrt -Wl,--no-as-needed -ldl")
  
  SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -lpthread -Wl,--no-as-needed -ldl -lrt")
  SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -pipe -lpthread -Wl,--no-as-needed -ldl -lrt")
  
  SET(SYSTEM_USR_INCLUDE_DIR /opt/hisi-linux/x86-arm/arm-hisiv300-linux/target/usr/include)
  SET(SYSTEM_USR_LIBRARY_DIR /opt/hisi-linux/x86-arm/arm-hisiv300-linux/target/usr/lib/)
	
  SET(CSF_THIRD_PARTY_PLATFORM_NAME "arm-hisiv300")
    
  ADD_DEFINITIONS(-DPLATEFORM_HISIV)

ENDIF()


#set hisiv400 platform
IF(CSF_PLATFORM STREQUAL "hisiv400")
  SET(CMAKE_ASM_NASM_COMPILER "as")
  SET(CMAKE_C_COMPILER "arm-hisiv400-linux-gcc")
  SET(CMAKE_CXX_COMPILER "arm-hisiv400-linux-g++")
  SET(CMAKE_CXX_COMPILER_FULLPATH "/opt/hisi-linux/x86-arm/arm-hisiv400-linux/target/bin/")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings -Wl,-Bsymbolic")
  
  SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} ${CMAKE_C_FLAGS_DEBUG} -ggdb3 -lpthread -lrt")
  SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} ${CMAKE_C_FLAGS_RELEASE} -pipe -lpthread -lrt")
  
  SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -lpthread -lrt")
  SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -pipe -lpthread -lrt")
  
  SET(SYSTEM_USR_INCLUDE_DIR /opt/hisi-linux/x86-arm/arm-hisiv400-linux/target/usr/include)
  SET(SYSTEM_USR_LIBRARY_DIR /opt/hisi-linux/x86-arm/arm-hisiv400-linux/target/usr/lib/)
	
  SET(CSF_THIRD_PARTY_PLATFORM_NAME "arm-hisiv400")
    
  ADD_DEFINITIONS(-DPLATEFORM_HISIV)
  
ENDIF()


#set cpptestscan platform
IF(CSF_PLATFORM STREQUAL "cpptestscan")
  SET(CMAKE_ASM_NASM_COMPILER "as")
  SET(CMAKE_C_COMPILER "cpptestscan")
  SET(CMAKE_CXX_COMPILER "cpptestscan")
  SET(CMAKE_CXX_COMPILER_FULLPATH "/root/Project/Parasoft/parasoft/cpptest/9.0")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --cpptestscanOutputFile=/home/CpptestProject/MyProject.bdf --cpptestscanProjectName=MyProject g++ -Wno-write-strings")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --cpptestscanOutputFile=/home/CpptestProject/MyProject.bdf --cpptestscanProjectName=MyProject gcc")
  
  SET(CSF_THIRD_PARTY_PLATFORM_NAME ${CSF_PLATFORM})
  
ENDIF()

EXECUTE_PROCESS(
		COMMAND ${CMAKE_CXX_COMPILER} --version
		COMMAND grep "g++"
		OUTPUT_VARIABLE CSF_GCC_COMPILE_VERSION_STRING
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
ADD_DEFINITIONS(-DCSF_GCC_COMPILE_VERSION="${CSF_GCC_COMPILE_VERSION_STRING}")

MESSAGE(STATUS "system platform[${CSF_PLATFORM}] used CMAKE_CXX_COMPILER[${CSF_GCC_COMPILE_VERSION_STRING}].")
MESSAGE(STATUS "system platform[${CSF_PLATFORM}] used third library [${CSF_THIRD_PARTY_PLATFORM_NAME}].")

#define macro for get sub directories
MACRO(SUB_DIRECTORY_LIST dest_paramete src_directory)
  FILE(GLOB children RELATIVE ${src_directory} ${src_directory}/*)
  SET(tmp_directories "")
  FOREACH(tem_item ${children})
    IF(IS_DIRECTORY ${src_directory}/${tem_item})
      LIST(APPEND tmp_directories ${src_directory}/${tem_item})      
    ENDIF()
  ENDFOREACH()
  SET(${dest_paramete} ${tmp_directories})
ENDMACRO()

#define macro for get all sub directories
MACRO(ALL_SUB_DIRECTORY_LIST dest_paramete src_directory)
	#find ./ -type d
	EXECUTE_PROCESS(
		COMMAND find ${src_directory} -type d
		OUTPUT_VARIABLE tmp_directories
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	STRING(REGEX REPLACE "\n" ";" ${dest_paramete} "${tmp_directories}")
	#SET(${dest_paramete} ${tmp_directories})
ENDMACRO()

#set include directory
SET(CSF_INCLUDE_DIR ${CSF_PROJECT_SOURCE_DIR}/include)
SET(CSF_INCLUDE_DIRECTORIES ${CSF_INCLUDE_DIR})

#set src directory
SET(CSF_SRC_DIR ${CSF_PROJECT_SOURCE_DIR}/src)

#set third-party directory
SET(CSF_THIRD_PARTY_DIR ${CSF_PROJECT_SOURCE_DIR}/third-party)

#set tests directory
SET(CSF_TESTS_DIR ${CSF_PROJECT_SOURCE_DIR}/test)

#set library directory
SET(CSF_LIBRARY_DIR ${CSF_PROJECT_OUTPUT_TOP_DIR})
    
#into include directory
ADD_SUBDIRECTORY(${CSF_INCLUDE_DIR})

#build third party directory
ADD_SUBDIRECTORY(${CSF_THIRD_PARTY_DIR})


#MESSAGE(STATUS "add include CSF_INCLUDE_DIR:[${CSF_INCLUDE_DIR}]")
#MESSAGE(STATUS "add include CSF_INCLUDE_DIRECTORIES:[${CSF_INCLUDE_DIRECTORIES}]")


#add include direntories
INCLUDE_DIRECTORIES(
    ${SYSTEM_USR_INCLUDE_DIR}
    ${SYSTEM_USR_LOCAL_INCLUDE_DIR}
    ${CSF_INCLUDE_DIR}
	${CSF_INCLUDE_DIRECTORIES}
    )

SET(ENV{C_INCLUDE_PATH} $ENV{C_INCLUDE_PATH} ${CSF_INCLUDE_DIR} ${CSF_INCLUDE_DIRECTORIES})
SET(ENV{CPLUS_INCLUDE_PATH} $ENV{CPLUS_INCLUDE_PATH} $ENV{C_INCLUDE_PATH})

#MESSAGE(STATUS "update include path : "${CSF_INCLUDE_DIR})

#add library directories 
LINK_DIRECTORIES(
    ${SYSTEM_USR_LIBRARY_DIR}
    ${SYSTEM_USR_LOCAL_LIBRARY_DIR}
    ${CSF_PROJECT_OUTPUT_TOP_DIR}
	${CSF_LIBRARY_DIR}
    )

SET(ENV{LIBRARY_PATH} $ENV{LIBRARY_PATH} ${CSF_PROJECT_OUTPUT_TOP_DIR} ${CSF_LIBRARY_DIR})
#MESSAGE(STATUS "library directories: "${CSF_LIBRARY_DIR})


IF(CSF_GLOBAL_PROJECT_NAME)
	#update global parameters
	#set library name
	SET(CSF_GLOBAL_PROJECT_NAME ${CSF_PROJECT_NAME} PARENT_SCOPE)

	#set csf library name
	SET(CSF_GLOBAL_LIBRARY_NAME ${CSF_LIBRARY_NAME} PARENT_SCOPE)

	#set executable name
	SET(CSF_GLOBAL_EXECUTABLE_NAME ${CSF_EXECUTABLE_NAME} PARENT_SCOPE)
	SET(CSF_GLOBAL_PROJECT_LIBRARY_STATIC_NAME ${CSF_PROJECT_LIBRARY_STATIC_NAME} PARENT_SCOPE)
	SET(CSF_GLOBAL_PROJECT_LIBRARY_SHARED_NAME ${CSF_PROJECT_LIBRARY_SHARED_NAME} PARENT_SCOPE)

	#set include directories
	SET(CSF_GLOBAL_INCLUDE_DIRECTORIES
		{CSF_INCLUDE_DIR}
		${CSF_INCLUDE_DIRECTORIES}
		PARENT_SCOPE)

	#set library directories
	SET(CSF_GLOBAL_LIBRARY_DIRECTORIES
		${CSF_PROJECT_OUTPUT_TOP_DIR}
		${CSF_LIBRARY_DIR}
		PARENT_SCOPE)
ENDIF(CSF_GLOBAL_PROJECT_NAME)


#add all subdirectory
ADD_SUBDIRECTORY(${CSF_SRC_DIR})
ADD_SUBDIRECTORY(${CSF_TESTS_DIR})

