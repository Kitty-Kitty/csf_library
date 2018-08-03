/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: f
*
*Author: fz
*
*Version: 1.0
*
*Date: 29-7��-2018 15:13:17
*
*Description: Class(csf_serial_url) ��ʾ���ڵ�ַ��Ϣ
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_SERIAL_URL_INCLUDED_)
#define CSF_SERIAL_URL_INCLUDED_

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
			 * @created 29-7��-2018 15:13:17
			 */
			class csf_serial_url : public csf::core::module::connect::csf_url
			{

			public:
				/**
				 * ��ʾ���ڵ�����������
				 * @author f
				 * @version 1.0
				 * @created 29-7��-2018 15:13:17
				 */
				enum csf_serial_flow_control_type
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
				};

				/**
				 * ��ʾ����У������
				 * @author f
				 * @version 1.0
				 * @created 29-7��-2018 15:13:17
				 */
				enum csf_serial_parity_type
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
				};

				/**
				 * ��ʾֹͣλ����
				 * @author f
				 * @version 1.0
				 * @created 29-7��-2018 15:13:17
				 */
				enum csf_serial_stop_bits_type
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
				};

				inline explicit csf_serial_url()
					: csf_url(csf_url_type_serial)
					, m_baud_rate(0)
					, m_character_size(0)
					, m_flow_control(csf_serial_flow_control_type_none)
					, m_dev("")
					, m_parity(csf_serial_parity_type_none)
					, m_stop_bits(csf_serial_stop_bits_type_none)
					, m_port(0) {
				}

				inline virtual ~csf_serial_url() {

				}

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
				 * @param newVal
				 */
				inline void set_baud_rate(const csf_int32 newVal) {

					m_baud_rate = newVal;
				}
				/**
				 * ��ʾ�ַ��ĳ���
				 * 
				 * @param newVal
				 */
				inline void set_character_size(const csf_uchar newVal) {

					m_character_size = newVal;
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
				 * @param newVal
				 */
				inline void set_dev(const csf_char* newVal) {

					m_dev = newVal;
				}
				/**
				 * ��ʾ��������
				 */
				inline csf_serial_flow_control_type get_flow_control() {

					return m_flow_control;
				}
				/**
				 * ��ʾ��������
				 * 
				 * @param newVal
				 */
				inline void set_flow_control(const csf_serial_flow_control_type newVal) {

					m_flow_control = newVal;
				}
				/**
				 * ��ʾ��żУ������
				 */
				inline csf_serial_parity_type get_parity() {

					return m_parity;
				}
				/**
				 * ��ʾ��żУ������
				 * 
				 * @param newVal
				 */
				inline void set_parity(const csf_serial_parity_type newVal) {

					m_parity = newVal;
				}
				/**
				 * ��ʾֹͣλ����
				 */
				inline csf_serial_stop_bits_type get_stop_bits() {

					return m_stop_bits;
				}
				/**
				 * ��ʾֹͣλ����
				 * 
				 * @param newVal
				 */
				inline void set_stop_bits(const csf_serial_stop_bits_type newVal) {

					m_stop_bits = newVal;
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
				 * @param newVal
				 */
				inline void set_port(const csf_uint32 newVal) {

					m_port = newVal;
				}
				/**
				 * ��ʾ�����豸
				 * 
				 * @param newVal
				 */
				inline void set_dev(csf_string& newVal) {

					m_dev = newVal;
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
				csf_serial_flow_control_type m_flow_control = csf_serial_flow_control_type_none;
				/**
				 * ��ʾ�����豸
				 */
				csf_string m_dev = "";
				/**
				 * ��ʾ��żУ������
				 */
				csf_serial_parity_type m_parity = csf_serial_parity_type_none;
				/**
				 * ��ʾֹͣλ����
				 */
				csf_serial_stop_bits_type m_stop_bits = csf_serial_stop_bits_type_none;
				/**
				 * ��ʾ���ڵĶ˿ں�
				 */
				csf_uint32 m_port = 0;

			};

		}

	}

}
#endif // !defined(CSF_SERIAL_URL_INCLUDED_)
