/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_serial_url.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:51
*
*Description: Class(csf_serial_url) ��ʾ���ڵ�ַ��Ϣ
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_SERIAL_URL_H_INCLUDED_)
#define CSF_SERIAL_URL_H_INCLUDED_

#include "csf_url.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * ��ʾ���ڵ�ַ��Ϣ
			 * @author f
			 * @version 1.0
			 * @created 01-10��-2018 12:54:51
			 */
			class csf_serial_url : public csf::core::module::connect::csf_url
			{

			public:
				/**
				 * ��ʾ���ڵ�����������
				 * @author f
				 * @version 1.0
				 * @created 01-10��-2018 12:54:51
				 */
				typedef enum csf_serial_flow_control_type_enum
				{
					/**
					 * ��ʾδ֪�Ĵ�������������
					 */
					csf_serial_flow_control_type_none = 0,
					/**
					 * ��ʾ�����
					 */
					csf_serial_flow_control_type_software,
					/**
					 * ��ʾӲ����
					 */
					csf_serial_flow_control_type_hardware
				} csf_serial_flow_control_type;

				/**
				 * ��ʾ����У������
				 * @author f
				 * @version 1.0
				 * @created 01-10��-2018 12:54:51
				 */
				typedef enum csf_serial_parity_type_enum
				{
					/**
					 * ��ʾδ֪������У��
					 */
					csf_serial_parity_type_none = 0,
					/**
					 * ��ʾδ֪����У��
					 */
					csf_serial_parity_type_odd,
					/**
					 * ��ʾδ֪����У��
					 */
					csf_serial_parity_type_even
				} csf_serial_parity_type;

				/**
				 * ��ʾֹͣλ����
				 * @author f
				 * @version 1.0
				 * @created 01-10��-2018 12:54:51
				 */
				typedef enum csf_serial_stop_bits_type_enum
				{
					/**
					 * ��ʾδ֪��ֹͣλ
					 */
					csf_serial_stop_bits_type_none = 0,
					/**
					 * ��ʾ1λֹͣλ
					 */
					csf_serial_stop_bits_type_one,
					/**
					 * ��ʾ1.5λֹͣλ
					 */
					csf_serial_stop_bits_type_one_point_five,
					/**
					 * ��ʾ2λֹͣλ
					 */
					csf_serial_stop_bits_type_two
				}csf_serial_stop_bits_type;


				csf_serial_url();
				virtual ~csf_serial_url();

				/**
				 * ��ʾ���ڵĲ�����ֵ
				 */
				inline csf_int32 get_baud_rate() {

					return m_baud_rate;
				}
				/**
				 * ��ʾ�ַ��ĳ���
				 */
				inline csf_uchar get_character_size() {

					return m_character_size;
				}
				/**
				 * ��ʾ���ڵĲ�����ֵ
				 * 
				 * @param new_value
				 */
				inline void set_baud_rate(const csf_int32 new_value) {

					m_baud_rate = new_value;
				}
				/**
				 * ��ʾ�ַ��ĳ���
				 * 
				 * @param new_value
				 */
				inline void set_character_size(const csf_uchar new_value) {

					m_character_size = new_value;
				}
				/**
				 * ��ʾ�����豸
				 */
				inline csf_string & get_dev() {

					return m_dev;
				}
				/**
				 * ��ʾ������ַ����
				 * 
				 * @param url    ��ʾurl��ַ�ַ�������
				 */
				inline virtual csf_int32 parse(csf_string& url) {

					return 0;
				}
				/**
				 * ��ʾ�����豸
				 * 
				 * @param new_value
				 */
				inline void set_dev(const csf_char* new_value) {

					m_dev = new_value;
				}
				/**
				 * ��ʾ��������
				 */
				inline csf::modules::connect::csf_serial_url::csf_serial_flow_control_type get_flow_control() {

					return m_flow_control;
				}
				/**
				 * ��ʾ��������
				 * 
				 * @param new_value
				 */
				inline void set_flow_control(const csf::modules::connect::csf_serial_url::csf_serial_flow_control_type new_value) {

					m_flow_control = new_value;
				}
				/**
				 * ��ʾ��żУ������
				 */
				inline csf::modules::connect::csf_serial_url::csf_serial_parity_type get_parity() {

					return m_parity;
				}
				/**
				 * ��ʾ��żУ������
				 * 
				 * @param new_value
				 */
				inline void set_parity(const csf::modules::connect::csf_serial_url::csf_serial_parity_type new_value) {

					m_parity = new_value;
				}
				/**
				 * ��ʾֹͣλ����
				 */
				inline csf::modules::connect::csf_serial_url::csf_serial_stop_bits_type get_stop_bits() {

					return m_stop_bits;
				}
				/**
				 * ��ʾֹͣλ����
				 * 
				 * @param new_value
				 */
				inline void set_stop_bits(const csf::modules::connect::csf_serial_url::csf_serial_stop_bits_type new_value) {

					m_stop_bits = new_value;
				}
				/**
				 * ��ʾ���ڵĶ˿ں�
				 */
				inline csf_uint32 get_port() {

					return m_port;
				}
				/**
				 * ��ʾ���ڵĶ˿ں�
				 * 
				 * @param new_value
				 */
				inline void set_port(const csf_uint32 new_value) {

					m_port = new_value;
				}
				/**
				 * ��ʾ�����豸
				 * 
				 * @param new_value
				 */
				inline void set_dev(csf_string& new_value) {

					m_dev = new_value;
				}
				/**
				 * ��ʾ������ַ����
				 * 
				 * @param url    ��ʾurl��ַ�ַ�������
				 */
				inline virtual csf_int32 parse(const csf_char* url) {

					return 0;
				}

			private:
				/**
				 * ��ʾ���ڵĲ�����ֵ
				 */
				csf_int32 m_baud_rate = 0;
				/**
				 * ��ʾ�ַ��ĳ���
				 */
				csf_uchar m_character_size = 0;
				/**
				 * ��ʾ��������
				 */
				csf::modules::connect::csf_serial_url::csf_serial_flow_control_type m_flow_control = csf_serial_flow_control_type_none;
				/**
				 * ��ʾ�����豸
				 */
				csf_string m_dev = "";
				/**
				 * ��ʾ��żУ������
				 */
				csf::modules::connect::csf_serial_url::csf_serial_parity_type m_parity = csf_serial_parity_type_none;
				/**
				 * ��ʾֹͣλ����
				 */
				csf::modules::connect::csf_serial_url::csf_serial_stop_bits_type m_stop_bits = csf_serial_stop_bits_type_none;
				/**
				 * ��ʾ���ڵĶ˿ں�
				 */
				csf_uint32 m_port = 0;

			};

		}

	}

}
#endif // !defined(CSF_SERIAL_URL_H_INCLUDED_)
