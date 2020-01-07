/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: vdu_shape_svg.hpp
*
*Version: 1.0
*
*Date: 24-9��-2018 14:09:58
*
*Description: Class(vdu_shape_svg) ��ʾsvg���е�vdu_shape��������
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_SHAPE_SVG_H_INCLUDED_)
#define VDU_SHAPE_SVG_H_INCLUDED_

#include "csf_base_include.h"

#include "vdu_shape.hpp"

namespace vdu
{
	namespace core
	{
		namespace base
		{
			/**
			 * ��ʾsvg���е�vdu_shape��������
			 * @author fangzhenmu
			 * @version 1.0
			 * @created 24-9��-2018 14:09:58
			 */
			class vdu_shape_svg : public vdu::core::base::vdu_shape
			{

			public:
				vdu_shape_svg();
				virtual ~vdu_shape_svg();

			};

		}

	}

}
#endif // !defined(VDU_SHAPE_SVG_H_INCLUDED_)
