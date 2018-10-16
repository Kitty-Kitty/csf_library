/*******************************************************************************
*
*Copyright:fz
*
*File name: csf_stdbind.hpp
*
*Author:armuxinxian@aliyun.com
*
*Version: 1.0
*
*Date:2018/06/27
*
*Description: create (csf_stdbind.hpp),重新定义各种集合数据类型成为csf自已的数据类型
*
*Others:
*
*History:
*******************************************************************************/


#if !defined(_CSF_STDBIND_H_)
#define _CSF_STDBIND_H_


#ifdef __cplusplus
#include <iostream>
#include <functional>
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
			#define csf_function						std::function
			#define csf_bind							std::bind
#endif



#ifdef __cplusplus
		}
	}
}
#endif


#endif // !defined(_CSF_STDBIND_H_)