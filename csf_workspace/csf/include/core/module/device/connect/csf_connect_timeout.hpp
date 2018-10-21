/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_connect_timeout.hpp
*
*Version: 1.0
*
*Date: 21-10��-2018 13:54:44
*
*Description: Class(csf_connect_timeout) ��ʾ��ʱ������������
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_TIMEOUT_H_INCLUDED_)
#define CSF_CONNECT_TIMEOUT_H_INCLUDED_

#include "csf_base_include.h"

#include "csf_connect_callback.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * ��ʾ��ʱ������������
				 * @author f
				 * @version 1.0
				 * @created 21-10��-2018 13:54:44
				 */
				class csf_connect_timeout
				{

				public:
					csf_connect_timeout();
					virtual ~csf_connect_timeout();

					/**
					 * 
					 * @param time    ��ʾ��ǰ��ʱ��ʱ����ֵ����λΪ���루ms��
					 * 
					 * @param handle    ��ʾ��ʱ��Ļص�����
					 */
					csf_connect_timeout(const csf_uint32 time, const csf::core::module::connect::csf_connect_callback handle);
					/**
					 * ��ʾ��ǰ��ʱ��ʱ����ֵ����λΪ���루ms��
					 */
					inline csf_uint32 get_time() {

						return m_time;
					}
					/**
					 * ��ʾ��ǰ��ʱ��ʱ����ֵ����λΪ���루ms��
					 * 
					 * @param newVal
					 */
					inline void set_time(csf_uint32 newVal) {

						m_time = newVal;
					}
					/**
					 * ��ʾ��ʱ��Ļص�����
					 */
					inline csf::core::module::connect::csf_connect_callback get_handle() {

						return m_handle;
					}
					/**
					 * ��ʾ��ʱ��Ļص�����
					 * 
					 * @param newVal
					 */
					inline void set_handle(csf::core::module::connect::csf_connect_callback newVal) {

						m_handle = newVal;
					}

				private:
					/**
					 * ��ʾ��ǰ��ʱ��ʱ����ֵ����λΪ���루ms��
					 */
					csf_uint32 m_time = 0;
					/**
					 * ��ʾ��ʱ��Ļص�����
					 */
					csf::core::module::connect::csf_connect_callback m_handle = csf_nullptr;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_TIMEOUT_H_INCLUDED_)
