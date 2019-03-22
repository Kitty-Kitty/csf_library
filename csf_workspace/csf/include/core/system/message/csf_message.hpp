/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_message.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:43
*
*Description: Class(csf_message)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MESSAGE_INCLUDED_)
#define CSF_MESSAGE_INCLUDED_

#include "csf_message_callback.hpp"
#include "csf_element.hpp"

using namespace csf::core::system;

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace message
			{
				/**
				 * ��ʾcsfģ��ʹ�õ�message��Ϣ���У�������Ϣ�Ĵ���
				 * @author f
				 * @version 1.0
				 * @created 27-6��-2018 17:28:43
				 */
				class csf_message
				{

				public:
					/**
					* ��ʾ��Ϣ������
					* @author f
					* @version 1.0
					* @updated 22-3��-2019 15:22:05
					*/
					typedef enum csf_message_type_enum
					{
						/**
						* ��ʾδ֪����Ϣ����
						*/
						csf_message_type_none = 0x00000000,
						/**
						* ��ʾ�����Ϣ����
						*/
						csf_message_type_add = 0x00010000,
						/**
						* ��ʾɾ����Ϣ����
						*/
						csf_message_type_delete = 0x00020000,
						/**
						* ��ʾ������Ϣ����
						*/
						csf_message_type_update = 0x00040000,
						/**
						* ��ʾ������Ϣ����
						*/
						csf_message_type_ctrl = 0x00080000,
						/**
						* ��ʾ��ʼ����Ϣ����
						*/
						csf_message_type_init = 0x00100000,
						/**
						* ��ʾ������Ϣ����
						*/
						csf_message_type_start = 0x00200000,
						/**
						* ��ʾֹͣ��Ϣ����
						*/
						csf_message_type_stop = 0x00400000,
						/**
						* ��ʾ������Ϣ����
						*/
						csf_message_type_create = 0x00800000,
						/**
						* ��ʾ������Ϣ����
						*/
						csf_message_type_destroy = 0x01000000
					}csf_message_type;

				public:
					csf_message();
					virtual ~csf_message();

					/**
					 * ����csf_message_type��callback����һ��csf_message
					 * 
					 * @param type    ��ʾmessage������
					 * @param callback    ��ʾmessage�Ļص�����
					 */
					csf_message(const csf_message_type type, const csf::core::system::message::csf_message_callback callback);
					/**
					 * ����csf_message_type��callback����һ��csf_message
					 * 
					 * @param type    ��ʾmessage������
					 * @param callback    ��ʾmessage�Ļص�����
					 * @param element
					 */
					csf_message(const csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element);
					/**
					 * ��ʾ��Ϣ�ص�����
					 */
					inline csf::core::system::message::csf_message_callback get_callback() {

						return m_callback;
					}
					/**
					 * ��ʾ��Ϣ�ص�����
					 * 
					 * @param newVal
					 */
					inline void set_callback(const csf::core::system::message::csf_message_callback newVal) {

						m_callback = newVal;
					}
					/**
					 * ��ʾ��Ϣ������
					 */
					inline csf_message_type get_type() {

						return m_type;
					}
					/**
					 * ��ʾ��Ϣ������
					 * 
					 * @param newVal
					 */
					inline void set_type(const csf_message_type newVal) {

						m_type = newVal;
					}
					/**
					 * ��ʾmessage�Դ�����Ϣ����
					 */
					inline csf_element& get_element() {

						return m_element;
					}
					/**
					 * ��ʾmessage�Դ�����Ϣ����
					 * 
					 * @param newVal
					 */
					inline void set_element(const csf_element& newVal) {

						m_element = newVal;
					}

				private:
					/**
					 * ��ʾ��Ϣ�ص�����
					 */
					csf::core::system::message::csf_message_callback m_callback = csf_null;
					/**
					 * ��ʾ��Ϣ������
					 */
					csf_message_type m_type = csf_message_type_none;
					/**
					 * ��ʾmessage�Դ�����Ϣ����
					 */
					csf::core::system::csf_element m_element;

				};

			}

		}

	}

}
#endif // !defined(CSF_MESSAGE_INCLUDED_)
