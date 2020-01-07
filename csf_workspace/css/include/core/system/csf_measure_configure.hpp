/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_measure_configure.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 01-7��-2018 12:10:40
*
*Description: Class(csf_measure_configure)��ʾϵͳ����������
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MEASURE_CONFIGURE_INCLUDED_)
#define CSF_MEASURE_CONFIGURE_INCLUDED_


#include "csf_typedef.h"
#include "csf_default.h"
#include "csf_stddef.h"

using namespace csf::core::base;


namespace csf
{
	namespace core
	{
		namespace system
		{
			//��ʾmeasure_configure�ַ�����ʽ�������Ĭ�ϳ���
			#define csf_measure_configure_string_length					256

			/**
			 * ��ʾϵͳ����������
			 * @author f
			 * @version 1.0
			 * @created 01-7��-2018 12:10:40
			 */
			class csf_measure_configure
			{

			public:
				inline explicit csf_measure_configure()
				    : m_device_limit(csf_default_device_limit)
					, m_device_io_limit(csf_default_device_io_limit)
					, m_timer_resolution(csf_default_timer_resolution)
					, m_connect_limit(csf_default_connect_limit)
					, m_time_resolution(csf_default_time_resolution)
				 {

				}
				inline virtual ~csf_measure_configure() {

				}
				/**
				 * ��ʾ�豸device���������
				 */
				inline csf_uint32 get_device_limit() {

					return m_device_limit;
				}
				/**
				 * ��ʾ�豸device���������
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_device_limit(const csf_uint32 newVal) {

					m_device_limit = newVal;
				}
				/**
				 * ��ʾ�豸device_io���������
				 */
				inline csf_uint32 get_device_io_limit() {

					return m_device_io_limit;
				}
				/**
				 * ��ʾ�豸device_io���������
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_device_io_limit(const csf_uint32 newVal) {

					m_device_io_limit = newVal;
				}
				/**
				 * ��ʾ��ʱ����ʱ�侫�ȣ����Ƕ�ʱ��ÿһ�β�ѯ�ļ��
				 */
				inline csf_uint64 get_timer_resolution() {

					return m_timer_resolution;
				}
				/**
				 * ��ʾ��ʱ����ʱ�侫�ȣ����Ƕ�ʱ��ÿһ�β�ѯ�ļ��
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_timer_resolution(const csf_uint64 newVal) {

					m_timer_resolution = newVal;
				}
				/**
				 * ��ʾϵͳʱ���ʱ�侫�ȣ���Ҫ������ϵͳ����ά����ʱ������
				 */
				inline csf_uint64 get_time_resolution() {

					return m_time_resolution;
				}
				/**
				 * ��ʾϵͳʱ���ʱ�侫�ȣ���Ҫ������ϵͳ����ά����ʱ������
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_time_resolution(const csf_uint64 newVal) {

					m_time_resolution = newVal;
				}
				/**
				 * ��ʾ���ӵļ�������
				 */
				inline csf_uint32 get_connect_limit() {

					return m_connect_limit;
				}
				/**
				 * ��ʾ���ӵļ�������
				 * 
				 * @param newVal
				 */
				inline csf_void set_connect_limit(const csf_uint32 newVal) {

					m_connect_limit = newVal;
				}
				/**
				* ��ʾ��������Ϣ��ʽ�����
				*/
				inline csf_string to_string() {

					csf_char				tmp_buf[csf_measure_configure_string_length] = { 0, };

					csf_snprintf(tmp_buf, csf_sizeof(tmp_buf)
						, "measure_configure[device_measure:%d  device_io_measure:%d  connect_measure:%d time_resolution:%lld ms  timer_resolution: %lld ms]."
						, m_device_limit
						, m_device_io_limit
						, m_connect_limit
						, m_time_resolution
						, m_timer_resolution
					);

					return tmp_buf;
				}
			private:
				/**
				 * ��ʾ�豸device���������
				 */
				csf_uint32 m_device_limit = csf_default_device_limit;
				/**
				 * ��ʾ�豸device_io���������
				 */
				csf_uint32 m_device_io_limit = csf_default_device_io_limit;
				/**
				 * ��ʾ��ʱ����ʱ�侫�ȣ����Ƕ�ʱ��ÿһ�β�ѯ�ļ������λ�����롣
				 */
				csf_uint64 m_timer_resolution = csf_default_timer_resolution;
				/**
				 * ��ʾ���ӵļ�������
				 */
				csf_uint32 m_connect_limit = csf_default_connect_limit;
				/**
				 * ��ʾϵͳʱ���ʱ�侫�ȣ���Ҫ������ϵͳ����ά����ʱ�����ݣ���λ�����롣
				 */
				csf_uint64 m_time_resolution = csf_default_time_resolution;

			};

		}

	}

}
#endif // !defined(CSF_MEASURE_CONFIGURE_INCLUDED_)
