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
				/************************************************************************/
				/* ��ʾĬ�ϵĳ�ʱʱ�䣬��λ�����루ms����Ĭ��Ϊ��5000ms						*/
				/************************************************************************/
				#define csf_connect_timeout_default_ms						5000		//��ʾĬ�ϵĳ�ʱʱ�䣬��λ�����루ms����Ĭ��Ϊ��5000ms
				/**
				 * ��ʾ��ʱ������������
				 * @author f
				 * @version 1.0
				 * @created 21-10��-2018 13:54:44
				 */
				class csf_connect_timeout
				{

				public:
					inline explicit csf_connect_timeout()
						: m_time(0)
						, m_timeout(csf_connect_timeout_default_ms)
						, m_handle(csf_nullptr) {

					}
					/**
					*
					* @param time    ��ʾ��ǰ��ʱ��ʱ����ֵ����λΪ���루ms��
					*
					* @param handle    ��ʾ��ʱ��Ļص�����
					*/
					inline explicit csf_connect_timeout(const csf_uint64 time
						, const csf::core::module::connect::csf_connect_callback handle)
						: m_time(time)
						, m_timeout(csf_connect_timeout_default_ms)
						, m_handle(handle) {
					}
					/**
					* ��Ҫ�����ǣ�ͨ��ʱ�䡢��ʱʱ��ͻص���������һ����ʱ����
					*
					* @param time    ��ʾ��ǰ��ʱ��ʱ����ֵ����λΪ���루ms��
					*
					* @param timeout
					* @param handle    ��ʾ��ʱ��Ļص�����
					*/
					inline explicit csf_connect_timeout(const csf_uint64 time
						, csf_uint64 timeout
						, const csf::core::module::connect::csf_connect_callback handle)
						: m_time(time)
						, m_timeout(timeout)
						, m_handle(handle) {

					}
					inline virtual ~csf_connect_timeout() {

					}
					/**
					* ��Ҫ�����ǣ�timeout����ĸ�ֵ����
					* ���أ�timeout����
					*
					* @param timeout    ��ʾ��Ҫ����ֵ��timeout����
					*/
					inline csf_connect_timeout& operator = (csf_connect_timeout& timeout) {

						set_time(timeout.get_time());
						set_timeout(timeout.get_timeout());
						set_handle(timeout.get_handle());

						return *this;
					}
					/**
					* ��Ҫ�����ǣ�timeout�����Ƿ���ͬ
					* ���أ�true��ʾ��ͬ��false��ʾ����ͬ��
					*
					* @param timeout    ��ʾ��Ҫ����ֵ��timeout����
					*/
					inline csf_bool operator ==(csf_connect_timeout & timeout) {

						if (get_time() == timeout.get_time()
							&& get_timeout() == timeout.get_timeout()) {

							return csf_true;
						}

						return csf_false;
					}
					/**
					* ��Ҫ�����ǣ�timeout�����Ƿ���ͬ
					* ���أ�true��ʾ��ͬ��false��ʾ����ͬ��
					*
					* @param timeout    ��ʾ��Ҫ����ֵ��timeout����
					*/
					inline csf_bool operator !=(csf_connect_timeout & timeout) {

						if (*this == timeout) {
							return csf_false;
						}
						return csf_true;
					}
					/**
					 * ��ʾ��ǰ��ʱ��ʱ����ֵ����λΪ���루ms��
					 */
					inline csf_uint64 get_time() const {

						return m_time;
					}
					/**
					 * ��ʾ��ǰ��ʱ��ʱ����ֵ����λΪ���루ms��
					 *
					 * @param newVal
					 */
					inline void set_time(csf_uint64 newVal) {

						m_time = newVal;
					}
					/**
					 * ��ʾ��ʱ��Ļص�����
					 */
					inline csf::core::module::connect::csf_connect_callback get_handle() const {

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
					/**
					* ��ʾ��ǰ��ʱ��ʱ����ֵ����λΪ���루ms��
					*/
					inline csf_uint64 get_timeout() const {

						return m_timeout;
					}
					/**
					* ��ʾ��ǰ��ʱ��ʱ����ֵ����λΪ���루ms��
					*
					* @param newVal
					*/
					inline void set_timeout(csf_uint64 newVal) {

						m_timeout = newVal;
					}
					/**
					* ��Ҫ�����ǣ������������ڣ��������������һ������ʱ�䡣
					* ���أ���
					*/
					inline void set_forever() {

						set_timeout(csf_min_uint64);
					}
					/**
					* ��Ҫ�����ǣ������������ڣ��������������һ����С��ʱ�䣬��֤���ڡ�
					* ���أ���
					*/
					inline void set_expired() {

						set_time(csf_dec_abs(get_time(), get_timeout()));
					}
					/**
					* ��Ҫ�����ǣ��ж������Ƿ��Ѿ���ʱ
					* ���أ�true��ʾ�Ѿ���ʱ��false��ʾû�г�ʱ��
					*
					* @param time
					* ��ʾ����У��ĵ�ǰʱ���׼����ʱ����connect_timeout�е�time���м��㣬������ֵ��timeout��ֵ�Ƚϣ����жϾ����Ƿ�ʱ��
					*/
					inline csf_bool is_expired(const csf_uint64& time) const {

						if (expired_time(time) >= get_timeout()) {

							return csf_true;
						}

						return csf_false;
					}
					
				protected:
					/**
					* ��Ҫ�����ǣ���ʾ�õ�ǰʱ���׼��connect_timeout�е�time���м��㣬������ֵ��Ϊ������ֵ��
					* ���أ���ʱʱ���ֵ
					*
					* @param time    ��ʾ����У��ĵ�ǰʱ���׼����ʱ����connect_timeout�е�time���м��㣬������ֵ��Ϊ������ֵ��
					*/
					inline csf_uint64 expired_time(const csf_uint64& time) const {

						return csf_dec_abs(time, get_time());
					}
				private:
					/**
					 * ��ʾ��ǰ��ʱ����ֵ����λΪ���루ms��
					 */
					csf_atomic_uint64 m_time;
					/**
					* ��ʾ��ǰ��ʱ��ʱ����ֵ����λΪ���루ms��
					*/
					csf_atomic_uint64 m_timeout;
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
