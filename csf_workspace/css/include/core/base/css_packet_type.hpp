/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: Administrator
*
*File name: css_packet_type.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:30
*
*Description: Enumeration(css_packet_type) 表示打包类型
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_PACKET_TYPE_H_INCLUDED_)
#define CSS_PACKET_TYPE_H_INCLUDED_

namespace css
{
	namespace core
	{
		/**
		 * 表示打包类型
		 * @author Administrator
		 * @version 1.0
		 * @created 07-10月-2018 16:50:30
		 */
		enum css_packet_type
		{
			/**
			 * 表示未知的打包类型
			 */
			m_css_packet_type_none = 0x00000000,
			/**
			 * 表示控制器的打包方式
			 */
			m_css_packet_type_player = 0x00000030,
			/**
			 * 表示zip的打包方式
			 */
			m_css_packet_type_zip = 0x00000040
		};

	}

}
#endif // !defined(CSS_PACKET_TYPE_H_INCLUDED_)
