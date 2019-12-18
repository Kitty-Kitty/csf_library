#pc_server project main CmakeList
CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)


#project name 
PROJECT(PC_PROJECT C CXX ASM)


# this one is important
SET(CMAKE_SYSTEM_NAME Linux)


#set library name
SET(PC_PROJECT_NAME pc_server)
#set cp library name
SET(PC_LIBRARY_NAME pc_server_lib)
#set css_server executable name
SET(PC_EXECUTABLE_NAME css_server)
SET(PC_PROJECT_LIBRARY_STATIC_NAME lib${PC_PROJECT_NAME}.a)
SET(PC_PROJECT_LIBRARY_SHARED_NAME lib${PC_PROJECT_NAME}.so)

#set cp source directory
SET(PC_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR})

#set system support platform
SET(PC_PLATFORM_LIST "x86" "hisiv100" "hisiv300" "hisiv400" "cpptestscan")



#select a mode
IF(DEBUG_MODE)        #cmake -D DEBUG_MODE=ON ../
    SET(CMAKE_BUILD_TYPE "Debug")
    #set cp output debug directory
    SET(PC_PROJECT_OUTPUT_TOP_DIR ${PROJECT_BINARY_DIR}/debug)
    SET(PC_OUTPUT_EXECUTABLE_DIR ${PC_PROJECT_OUTPUT_TOP_DIR}/${PC_EXECUTABLE_NAME})
    SET(PC_OUTPUT_LIBRARY_DIR ${PC_PROJECT_OUTPUT_TOP_DIR}/${PC_LIBRARY_NAME})
    SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} ${CMAKE_C_FLAGS_DEBUG} -ggdb3 -pthread -Wl,--no-as-needed -ldl -lrt")
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -pthread -Wl,--no-as-needed -ldl -lrt")
    MESSAGE(STATUS "use the [debug] mode! output_path:" ${PC_PROJECT_OUTPUT_TOP_DIR})
ELSE()
    SET(CMAKE_BUILD_TYPE "Release")
    #set cp output release directory
    SET(PC_PROJECT_OUTPUT_TOP_DIR ${PROJECT_BINARY_DIR}/release)
    SET(PC_OUTPUT_EXECUTABLE_DIR ${PC_PROJECT_OUTPUT_TOP_DIR}/${PC_EXECUTABLE_NAME})
    SET(PC_OUTPUT_LIBRARY_DIR ${PC_PROJECT_OUTPUT_TOP_DIR}/${PC_LIBRARY_NAME})
    SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} ${CMAKE_C_FLAGS_RELEASE} -Wl,--no-as-needed -pipe -lpthread_nonshared -ldl -lrt")
	SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -Wl,--no-as-needed -pipe -pthread -ldl -lrt")
    MESSAGE(STATUS "use the [release] mode! output_path:" ${PC_PROJECT_OUTPUT_TOP_DIR})
ENDIF()


IF(NOT DEFINED PLATFORM)
    SET(PC_PLATFORM "x86")
	MESSAGE(WARNING "set platform warning. parameter[PLATFORM] not defined. used default [PLATFORM = x86]")
	MESSAGE(STATUS "[ctrl + c] to stop; usage: [cmake -DPLATFORM=${PC_PLATFORM} ../] ; wait [5] seconds for you ...")
	#CTEST_SLEEP(5)
ELSE()
    SET(PC_PLATFORM ${PLATFORM})
	MESSAGE(STATUS "set parameter[PLATFORM = ${PLATFORM}] ")
ENDIF()

#LIST(FIND PC_PLATFORM_LIST PC_PLATFORM FIND_LIST_RETURN)
#IF(${FIND_LIST_RETURN} EQUAL -1)
	#MESSAGE(STATUS "usage: [cmake PC_PLATFORM=x86 ../] " "  ${FIND_LIST_RETURN}")
	#MESSAGE(FATAL_ERROR "system usupport[PC_PLATFORM = ${PC_PLATFORM}]. support system list[${PC_PLATFORM_LIST}]")
#ENDIF()

#set general x86 platform
IF(PC_PLATFORM STREQUAL "x86")
  SET(CMAKE_ASM_NASM_COMPILER "as")
  SET(CMAKE_C_COMPILER "gcc")
  SET(CMAKE_CXX_COMPILER "g++")
  SET(CMAKE_CXX_COMPILER_FULLPATH "/usr/bin/g++")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings -Wl,-Bsymbolic")
  
  SET(SYSTEM_USR_INCLUDE_DIR /usr/include/)
  SET(SYSTEM_USR_LOCAL_INCLUDE_DIR /usr/local/include/)
  SET(SYSTEM_USR_LIBRARY_DIR /usr/lib/)
  SET(SYSTEM_USR_LOCAL_LIBRARY_DIR /usr/local/lib/)
  
  SET(PC_THIRD_PARTY_PLATFORM_NAME "Linux_x86")
  
  #set third-party directory
  SET(PC_THIRD_PARTY_DIR ${PC_PROJECT_SOURCE_DIR}/third-party)
  
  #set third-party lib directory
  SET(PC_THIRD_PARTY_LIB_DIR ${PC_THIRD_PARTY_DIR}/lib)
  
ENDIF()

#set x86_64 flag
IF(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
	ADD_DEFINITIONS(-fPIC)
ENDIF(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")

#set hisiv100 platform
IF(PC_PLATFORM STREQUAL "hisiv100")
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
	
  SET(PC_THIRD_PARTY_PLATFORM_NAME "arm-hisiv100nptl")
  
  #set third-party directory
  SET(PC_THIRD_PARTY_DIR ${PC_PROJECT_SOURCE_DIR}/third-party)

  #set third-party lib directory
  SET(PC_THIRD_PARTY_LIB_DIR ${PC_THIRD_PARTY_DIR}/lib/Arm/hisiv100)
  
  ADD_DEFINITIONS(-DPLATEFORM_HISIV)
  
ENDIF()

#set hisiv300 platform
IF(PC_PLATFORM STREQUAL "hisiv300")
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
	
  SET(PC_THIRD_PARTY_PLATFORM_NAME "hisiv300")
  
  #set third-party directory
  SET(PC_THIRD_PARTY_DIR ${PC_PROJECT_SOURCE_DIR}/third-party)

  #set third-party lib directory
  SET(PC_THIRD_PARTY_LIB_DIR ${PC_THIRD_PARTY_DIR}/lib/Arm/hisiv300)
  
  ADD_DEFINITIONS(-DPLATEFORM_HISIV)

ENDIF()

#set hisiv400 platform
IF(PC_PLATFORM STREQUAL "hisiv400")
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
	
  SET(PC_THIRD_PARTY_PLATFORM_NAME "hisiv400")
  
  #set third-party directory
  SET(PC_THIRD_PARTY_DIR ${PC_PROJECT_SOURCE_DIR}/third-party)

  #set third-party lib directory
  SET(PC_THIRD_PARTY_LIB_DIR ${PC_THIRD_PARTY_DIR}/lib/Arm/hisiv400)
  
  ADD_DEFINITIONS(-DPLATEFORM_HISIV)
  
ENDIF()

#set cpptestscan platform
IF(PC_PLATFORM STREQUAL "cpptestscan")
  SET(CMAKE_ASM_NASM_COMPILER "as")
  SET(CMAKE_C_COMPILER "cpptestscan")
  SET(CMAKE_CXX_COMPILER "cpptestscan")
  SET(CMAKE_CXX_COMPILER_FULLPATH "/root/Project/Parasoft/parasoft/cpptest/9.0")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --cpptestscanOutputFile=/home/CpptestProject/MyProject.bdf --cpptestscanProjectName=MyProject g++ -Wno-write-strings")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --cpptestscanOutputFile=/home/CpptestProject/MyProject.bdf --cpptestscanProjectName=MyProject gcc")
  
  SET(PC_THIRD_PARTY_PLATFORM_NAME "cpptestscan" )
  
ENDIF()

MESSAGE(STATUS "system platform[${PC_PLATFORM}] used third library [${PC_THIRD_PARTY_PLATFORM_NAME}].")


#set include directory
SET(PC_INCLUDE_DIR ${PC_PROJECT_SOURCE_DIR}/include)

#set src directory
SET(PC_SRC_DIR ${PC_PROJECT_SOURCE_DIR}/src)

#set tests directory
SET(PC_TESTS_DIR ${PC_PROJECT_SOURCE_DIR}/test)

#set library directory
SET(PC_LIBRARY_DIR ${PC_PROJECT_OUTPUT_TOP_DIR})
    
#build third party directory
ADD_SUBDIRECTORY(${PC_THIRD_PARTY_DIR})

#add include direntories
INCLUDE_DIRECTORIES(
    ${SYSTEM_USR_INCLUDE_DIR}
    ${SYSTEM_USR_LOCAL_INCLUDE_DIR}
    ${PC_INCLUDE_DIR}
    )
	#MESSAGE(STATUS "update include path : "${PC_INCLUDE_DIR})

#add library directories 
LINK_DIRECTORIES(
    ${SYSTEM_USR_LIBRARY_DIR}
    ${SYSTEM_USR_LOCAL_LIBRARY_DIR}
    ${PC_PROJECT_OUTPUT_TOP_DIR}
	${PC_LIBRARY_DIR}
    )
	#MESSAGE(STATUS "library directories: "${PC_LIBRARY_DIR})




ADD_SUBDIRECTORY(${PC_SRC_DIR})
ADD_SUBDIRECTORY(${PC_TESTS_DIR})




