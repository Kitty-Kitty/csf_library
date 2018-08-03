/*******************************************************************************
*
*Copyright:fz
*
*File name: csf_stdcollector.hpp
*
*Author:armuxinxian@aliyun.com
*
*Version: 1.0
*
*Date:2018/06/27
*
*Description: create (csf_stdcollector.hpp),重新定义各种集合数据类型成为csf自已的数据类型
*
*Others:
*
*History:
*******************************************************************************/


#if !defined(_CSF_STDCOLLECTOR_H_)
#define _CSF_STDCOLLECTOR_H_


#ifdef __cplusplus
#include <iostream>
#include <unordered_map>
#endif


#ifdef __cplusplus
namespace csf
{
	namespace core
	{
		namespace base
		{
#endif
#ifdef __cplusplus
			#define csf_list						std::list
			#define csf_stack						std::stack
			#define csf_queue						std::queue
			#define csf_set							std::set
			#define csf_vector						std::vector
			#define csf_map							std::map
			#define csf_unordered_map				std::unordered_map
#endif



#ifdef __cplusplus
		}
	}
}
#endif


#endif // !defined(_CSF_STDCOLLECTOR_H_)