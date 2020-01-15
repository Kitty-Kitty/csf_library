/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_csftype.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 30-6月-2018 10:06:03
*
*Description: Class(csf_csftype)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CSFTYPE_INCLUDED_)
#define CSF_CSFTYPE_INCLUDED_

#include "csf_null_interface.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示csf定义的基础数据类型。
			 * @author f
			 * @version 1.0
			 * @created 30-6月-2018 10:06:03
			 */
			class csf_csftype : public csf::core::base::csf_null_interface
			{

			public:
				csf_csftype();
				virtual ~csf_csftype();

				/**
				 * 表示判断是否为空。
				 * 返回：true表示为空；false表示不为空。
				 */
				inline virtual csf_bool is_null() {

					return csf_true;
				}
				/**
				 * 表示判断是否不为空。
				 * 返回：true表示不为空；false表示为空。
				 */
				inline virtual csf_bool not_null() {

					return csf_true;
				}

			};

		}

	}

}
#endif // !defined(CSF_CSFTYPE_INCLUDED_)
