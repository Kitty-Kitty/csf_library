/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: csf_filter.hpp
*
*Version: 1.0
*
*Date: 28-3月-2019 14:56:49
*
*Description: Class(csf_filter) 各种类型的数据过滤器，用于解析和校验数据，判断和确定请求类型。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_FILTER_H_INCLUDED_)
#define CSF_FILTER_H_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * 各种类型的数据过滤器，用于解析和校验数据，判断和确定请求类型。
				 * @author fangzhenmu
				 * @version 1.0
				 * @created 28-3月-2019 14:56:49
				 */
				class csf_filter
				{

				public:
					csf_filter();
					virtual ~csf_filter();

				};

			}

		}

	}

}
#endif // !defined(CSF_FILTER_H_INCLUDED_)
