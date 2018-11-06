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
*Date: 07-10��-2018 16:50:30
*
*Description: Enumeration(css_packet_type) ��ʾ�������
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
		 * ��ʾ�������
		 * @author Administrator
		 * @version 1.0
		 * @created 07-10��-2018 16:50:30
		 */
		enum css_packet_type
		{
			/**
			 * ��ʾδ֪�Ĵ������
			 */
			m_css_packet_type_none = 0x00000000,
			/**
			 * ��ʾ�������Ĵ����ʽ
			 */
			m_css_packet_type_player = 0x00000030,
			/**
			 * ��ʾzip�Ĵ����ʽ
			 */
			m_css_packet_type_zip = 0x00000040
		};

	}

}
#endif // !defined(CSS_PACKET_TYPE_H_INCLUDED_)
