#add all include directories

ALL_SUB_DIRECTORY_LIST(SUB_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})

#add include directories
SET(CSF_INCLUDE_DIRECTORIES
	${CSF_INCLUDE_DIRECTORIES} 
	${SUB_INCLUDE_DIRECTORIES}

	PARENT_SCOPE
)
INCLUDE_DIRECTORIES(${SUB_INCLUDE_DIRECTORIES})

#MESSAGE(STATUS "add include SUB_INCLUDE_DIRECTORIES:[${SUB_INCLUDE_DIRECTORIES}]")
#MESSAGE(STATUS "add include CSF_INCLUDE_DIRECTORIES:[${CSF_INCLUDE_DIRECTORIES}]")

ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/app)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/device/ec_device)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/device_io/ec_device_io)
