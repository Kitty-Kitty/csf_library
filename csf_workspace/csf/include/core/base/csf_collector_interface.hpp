/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_collector_interface.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:35
*
*Description: Interface(csf_collector_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_COLLECTOR_INTERFACE_INCLUDED_)
#define CSF_COLLECTOR_INTERFACE_INCLUDED_

#include "csf_typedef.h"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示收集器操作接口
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6月-2018 17:28:35
			 */
			class csf_collector_interface
			{

			public:
				csf_collector_interface() {

				}

				virtual ~csf_collector_interface() {

				}

				/**
				 * 查询收集器的元素总个数。
				 * 返回：>=0表示元素的总个数。
				 */
				virtual csf_int32 size() const =0;
				/**
				 * 表示清空收集器中的所有元素
				 */
				virtual csf_bool clear() =0;

			};

		}

	}

}
#endif // !defined(CSF_COLLECTOR_INTERFACE_INCLUDED_)
