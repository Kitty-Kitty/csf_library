

CMAKE_MINIMUM_REQUIRED(VERSION 2.5 FATAL_ERROR)



#project name 
PROJECT(PC_PROJECT C ASM)




IF(platform)

# this one is important
SET(CMAKE_C_COMPILER "arm-hisiv100nptl-linux-g++")
SET(CMAKE_CXX_COMPILER "arm-hisiv100nptl-linux-g++")
SET(CMAKE_CXX_COMPILER_FULLPATH "/opt/hisi-linux-nptl/arm-hisiv100-linux/target/bin/arm-hisiv100nptl-linux-g++")

SET(CMAKE_CFLAGS "$ENV{CXXFLAGS} -ggdb3 -Dhi3531 -rdynamic -Wall -Wl,-E")
SET(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -ggdb3 -Dhi3531 -rdynamic -Wall -Wl,-E")

ELSE()

# this one is important
SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")
#SET(CMAKE_CXX_COMPILER_FULLPATH "/opt/hisi-linux-nptl/arm-hisiv100-linux/target/bin/arm-hisiv100nptl-linux-g++")

SET(CMAKE_CFLAGS "$ENV{CXXFLAGS} -ggdb3 -rdynamic -Wall -Wl,-E")
SET(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -ggdb3 -rdynamic -Wall -Wl,-E")

ENDIF()

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
        ADD_DEFINITIONS(-fPIC)
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )

SET(SYSTEM_USR_INCLUDE_DIR /usr/include/)
SET(SYSTEM_USR_LOCAL_INCLUDE_DIR /usr/local/include/)

SET(SYSTEM_USR_LIBRARY_DIR /usr/lib/)
SET(SYSTEM_USR_LOCAL_LIBRARY_DIR /usr/local/lib/)



#select a mode
IF(DEBUG_MODE)        #cmake -D DEBUG_MODE=ON ../

		SET(CMAKE_BUILD_TYPE Debug)
    SET(PC_OUTPUT_TOP_DIR ${PROJECT_BINARY_DIR}/debug)
		
    MESSAGE(STATUS "use the debug mode! output_path: "${PC_OUTPUT_TOP_DIR})
ELSE()

    SET(CMAKE_BUILD_TYPE Release)
    SET(PC_OUTPUT_TOP_DIR ${PROJECT_BINARY_DIR}/release)
    
    MESSAGE(STATUS "use the release mode! output_path: "${PC_OUTPUT_TOP_DIR})
ENDIF()

#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -ggdb3 -Dhi3531 -rdynamic -Wall -fPIC -Wl,-E")
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -pipe -Dhi3531 -Wall -fPIC -Wl,-E")

#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-E -Wl,--unresolved-symbols=ignore-in-shared-libs  -pthread  -lrt -ldl")
#SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-E -Wl,--unresolved-symbols=ignore-in-shared-libs  -pthread -lrt -ldl")

#add system/boost include direntories
INCLUDE_DIRECTORIES(
		${SYSTEM_USR_INCLUDE_DIR}
    ${SYSTEM_USR_LOCAL_INCLUDE_DIR})


#add system/boost library directories 
LINK_DIRECTORIES(${SYSTEM_USR_LIBRARY_DIR}
    ${SYSTEM_USR_LOCAL_LIBRARY_DIR})

#set gmf_parser executable name
SET(PC_EXECUTABLE_NAME gmf_parser)


AUX_SOURCE_DIRECTORY(${PC_PROJECT_SOURCE_DIR}/prot_gmp GMP_PARSER_FILES_LIST)

INCLUDE_DIRECTORIES(${PC_PROJECT_SOURCE_DIR})

#set gmf_parser library name
SET(PC_LIBRARY_NAME gmf_parser)
SET(LIBRARY_STATIC_NAME lib${PC_LIBRARY_NAME}.a)
SET(LIBRARY_SHARED_NAME lib${PC_LIBRARY_NAME}.so)

add_library (all_sources OBJECT ${GMP_PARSER_FILES_LIST})
ADD_LIBRARY(${LIBRARY_STATIC_NAME} STATIC $<TARGET_OBJECTS:all_sources>)
ADD_LIBRARY(${LIBRARY_SHARED_NAME} SHARED $<TARGET_OBJECTS:all_sources>)

set_target_properties(${LIBRARY_STATIC_NAME} PROPERTIES OUTPUT_NAME ${PC_LIBRARY_NAME}) 
set_target_properties(${LIBRARY_SHARED_NAME} PROPERTIES OUTPUT_NAME ${PC_LIBRARY_NAME}) 



SET(EXECUTABLE_OUTPUT_PATH ${PC_OUTPUT_TOP_DIR})
ADD_EXECUTABLE(${PC_EXECUTABLE_NAME} $<TARGET_OBJECTS:all_sources> prot_gmp_gmf_test.c)








