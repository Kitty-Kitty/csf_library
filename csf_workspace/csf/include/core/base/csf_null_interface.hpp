/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_null_interface.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 30-6月-2018 10:06:13
*
*Description: Interface(csf_null_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_NULL_INTERFACE_INCLUDED_)
#define CSF_NULL_INTERFACE_INCLUDED_

#include "csf_typedef.h"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示csf基础数据类型的null判断操作接口。
			 * @author f
			 * @version 1.0
			 * @created 30-6月-2018 10:06:13
			 */
			class csf_null_interface
			{

			public:
				csf_null_interface() {

				}

				virtual ~csf_null_interface() {

				}

				/**
				 * 表示判断是否为空。
				 * 返回：true表示为空；false表示不为空。
				 */
				virtual csf_bool is_null() =0;
				/**
				 * 表示判断是否不为空。
				 * 返回：true表示不为空；false表示为空。
				 */
				virtual csf_bool not_null() =0;

			};

		}

	}

}
#endif // !defined(CSF_NULL_INTERFACE_INCLUDED_)
