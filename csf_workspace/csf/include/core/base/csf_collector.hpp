/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_collector.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:35
*
*Description: Class(csf_collector)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_COLLECTOR_INCLUDED_)
#define CSF_COLLECTOR_INCLUDED_

#include "csf_collector_interface.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示收集器抽象类
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6月-2018 17:28:35
			 */
			class csf_collector : public csf::core::base::csf_collector_interface
			{

			public:
				csf_collector() {

				}

				virtual ~csf_collector() {

				}

				/**
				 * 查询收集器的元素总个数。
				 * 返回：>=0表示元素的总个数。
				 */
				virtual csf_int32 size() const {

					return 0;
				}
				/**
				 * 表示清空收集器中的所有元素
				 */
				virtual csf_bool clear() {

					return csf_true;
				}

			};

		}

	}

}
#endif // !defined(CSF_COLLECTOR_INCLUDED_)
