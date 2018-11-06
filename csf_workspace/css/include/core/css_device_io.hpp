/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fz
*
*File name: css_device_io.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:26
*
*Description: Class(css_device_io) ��ʾ��cf_device���ɵ��࣬��Ҫ����cssʹ��
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_DEVICE_IO_H_INCLUDED_)
#define CSS_DEVICE_IO_H_INCLUDED_

#include "csf_message_callback.hpp"
#include "csf_message.hpp"
#include "csf_device_io.hpp"
#include "css_device_io_interface.hpp"

namespace css
{
	namespace core
	{
		/**
		 * ��ʾ��cf_device���ɵ��࣬��Ҫ����cssʹ��
		 * @author fz
		 * @version 1.0
		 * @created 07-10��-2018 16:50:26
		 */
		class css_device_io : public csf::core::module::csf_device_io, public css::core::css_device_io_interface
		{

		public:
			css_device_io();
			virtual ~css_device_io();

			/**
			 * ģ���ʼ��
			 * 
			 * @param conf_mg    ��ʾ�����ļ���Ϣ
			 */
			virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
			/**
			 * ��ʾ����һ��message����
			 * 
			 * @param message    ��ʾ��ӵ���Ϣ����
			 */
			virtual csf_int32 post(csf_message& message);
			/**
			 * �������͡��ص���������Ϣ���ݴ�����Ϣ
			 * 
			 * @param type    ��ʾ��Ϣ����
			 * @param callback    ��ʾ�ص�����
			 * @param element    ��ʾ��Ϣ����
			 */
			virtual csf_int32 post(csf::core::system::message::csf_message_type type, csf::core::system::message::csf_message_callback callback, csf_element& element);
			/**
			 * ģ������
			 * 
			 * @param conf_mg    ��ʾ�����ļ���Ϣ
			 */
			virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
			/**
			 * ��ʾ������Ϣ����
			 */
			virtual csf::core::system::message::csf_message pop();
			/**
			 * ģ��ֹͣ
			 * 
			 * @param conf_mg    ��ʾ�����ļ���Ϣ
			 */
			virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
			/**
			 * ��ʾ����һ��message����
			 * 
			 * @param message    ��ʾ��ӵ���Ϣ����
			 */
			virtual csf_int32 post(const csf_message& message);
			/**
			 * �������͡��ص���������Ϣ���ݴ�����Ϣ
			 * 
			 * @param type    ��ʾ��Ϣ����
			 * @param callback    ��ʾ�ص�����
			 * @param element    ��ʾ��Ϣ����
			 */
			virtual csf_int32 post(const csf::core::system::message::csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element);
			/**
			 * ��ʾ������Ϣ����
			 */
			virtual csf::core::system::message::csf_message pop();

		};

	}

}
#endif // !defined(CSS_DEVICE_IO_H_INCLUDED_)
