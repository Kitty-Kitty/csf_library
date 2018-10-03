/*******************************************************************************
*
*Copyright:fz
*
*File name: csf_stdcplusplus.hpp
*
*Author:armuxinxian@aliyun.com
*
*Version: 1.0
*
*Date:2018/06/27
*
*Description: create (csf_stdcplusplus.hpp),包含C++部分标准
*
*Others:
*
*History:
*******************************************************************************/


#if !defined(_CSF_STDCPLUSPLUS_H_)
#define _CSF_STDCPLUSPLUS_H_


#ifdef __cplusplus
#include <iostream>
#include <memory>
#endif


#ifdef __cplusplus
namespace csf
{
	namespace core
	{
		namespace base
		{
			#define csf_shared_ptr						std::shared_ptr



		}
	}
}
#endif


#endif // !defined(_CSF_STDCPLUSPLUS_H_)