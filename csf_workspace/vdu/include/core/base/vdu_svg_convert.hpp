/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: vdu_svg_convert.hpp
*
*Version: 1.0
*
*Date: 24-9��-2018 14:09:59
*
*Description: Class(vdu_svg_convert) ��Ҫ����svg��������ת��Ϊvdu_shape����
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_SVG_CONVERT_H_INCLUDED_)
#define VDU_SVG_CONVERT_H_INCLUDED_

#include "csf_base_include.h"

#include "vdu_shape_convert.hpp"

namespace vdu
{
	namespace core
	{
		namespace base
		{
			/**
			 * ��Ҫ����svg��������ת��Ϊvdu_shape����
			 * @author fangzhenmu
			 * @version 1.0
			 * @created 24-9��-2018 14:09:59
			 */
			class vdu_svg_convert : public vdu::core::base::vdu_shape_convert
			{

			public:
				vdu_svg_convert();
				virtual ~vdu_svg_convert();

			};

		}

	}

}
#endif // !defined(VDU_SVG_CONVERT_H_INCLUDED_)
