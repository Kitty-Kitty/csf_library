/*******************************************************************************
*
*Copyright:fz
*
*File name: csf_preprocessor.hpp
*
*Author:armuxinxian@aliyun.com
*
*Version: 1.0
*
*Date:2018/06/27
*
*Description: create (csf_preprocessor.hpp),重新定义各种集合数据类型成为csf自已的数据类型
*
*Others:
*
*History:
*******************************************************************************/


#if !defined(_CSF_PREPROCESSOR_H_)
#define _CSF_PREPROCESSOR_H_


#ifdef __cplusplus

#include <boost/preprocessor/arithmetic/add.hpp>

namespace csf
{
	namespace core
	{
		namespace base
		{

			#define csf_pp_add						BOOST_PP_ADD
		}
	}
}
#endif


#endif // !defined(_CSF_PREPROCESSOR_H_)