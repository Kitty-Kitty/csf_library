/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: vdu_shape.hpp
*
*Version: 1.0
*
*Date: 24-9月-2018 14:09:58
*
*Description: Class(vdu_shape) vdu处理时采用的特定结构的程序可接受的标准结构，任何其他数据结构都需要转化为该结构处理。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_SHAPE_H_INCLUDED_)
#define VDU_SHAPE_H_INCLUDED_

#include "csf_base_include.h"

namespace vdu
{
	namespace core
	{
		namespace base
		{
			/**
			 * vdu处理时采用的特定结构的程序可接受的标准结构，任何其他数据结构都需要转化为该结构处理。
			 * @author fangzhenmu
			 * @version 1.0
			 * @created 24-9月-2018 14:09:58
			 */
			class vdu_shape
			{

			public:
				vdu_shape();
				virtual ~vdu_shape();

			};

		}

	}

}
#endif // !defined(VDU_SHAPE_H_INCLUDED_)
