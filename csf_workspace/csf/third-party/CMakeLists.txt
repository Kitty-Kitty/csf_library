#set src files list


#set lib directory
SET(CSF_THIRD_PARTY_LIB_DIR ${CSF_THIRD_PARTY_DIR}/lib)
#set src directory
SET(CSF_THIRD_PARTY_SRC_DIR ${CSF_THIRD_PARTY_DIR}/src)





#set src files list
#set boost include directory
SET(CSF_THIRD_PARTY_BOOST_INCLUDE_DIR ${CSF_THIRD_PARTY_SRC_DIR}/boost_1_65_0)


#set library files list
#set boost library directory
SET(CSF_THIRD_PARTY_BOOST_LIB_DIR ${CSF_THIRD_PARTY_LIB_DIR}/${CSF_THIRD_PARTY_PLATFORM_NAME}/boost_1_65_0/lib)




#add include dir
SET(CSF_INCLUDE_DIR
	${CSF_INCLUDE_DIR} 
	${CSF_THIRD_PARTY_BOOST_INCLUDE_DIR}
		
	PARENT_SCOPE
)



#add lib dir
SET(CSF_LIBRARY_DIR
	${CSF_LIBRARY_DIR} 
	${CSF_THIRD_PARTY_BOOST_LIB_DIR}
	
	PARENT_SCOPE
)
	




