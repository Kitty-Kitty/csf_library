/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: vdu_shape_convert.hpp
*
*Version: 1.0
*
*Date: 24-9月-2018 14:09:58
*
*Description: Class(vdu_shape_convert) 主要实现将其他的数据格式转换为vdu_shape数据类型
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_SHAPE_CONVERT_H_INCLUDED_)
#define VDU_SHAPE_CONVERT_H_INCLUDED_

#include "csf_base_include.h"

namespace vdu
{
	namespace core
	{
		namespace base
		{
			/**
			 * 主要实现将其他的数据格式转换为vdu_shape数据类型
			 * @author fangzhenmu
			 * @version 1.0
			 * @created 24-9月-2018 14:09:58
			 */
			class vdu_shape_convert
			{

			public:
				vdu_shape_convert();
				virtual ~vdu_shape_convert();

			};

		}

	}

}
#endif // !defined(VDU_SHAPE_CONVERT_H_INCLUDED_)
