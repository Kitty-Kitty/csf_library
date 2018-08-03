/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_pfstring.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6月-2018 17:50:22
*
*Description: Class(csf_pfstring)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_PFSTRING_INCLUDED_)
#define CSF_PFSTRING_INCLUDED_

#include "csf_memblock.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示指针标识字符类型，该类型不包括实际内容。仅由一个描述字符串起始的指针和字符串的长度两个属性组成。
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6月-2018 17:50:22
			 */
			class csf_pfstring : public csf::core::base::csf_memblock
			{

			public:
				csf_pfstring() {

				}
				virtual ~csf_pfstring() {

				}

				/**
				 * 根据缓存地址和长度创建对象
				 * 
				 * @param buf    表示根据缓存地址和长度创建一个csf_csfstring
				 * @param len    len
				 */
				inline explicit csf_pfstring(const csf_uchar* buf, const csf_int32 len)
					: csf_memblock(buf, len) {

				}

			};

		}

	}

}
#endif // !defined(CSF_PFSTRING_INCLUDED_)
