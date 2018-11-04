/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_connect_buffer.hpp
*
*Version: 1.0
*
*Date: 20-10��-2018 21:30:24
*
*Description: Class(csf_connect_buffer) Ϊ����ʵ�ָ����������������ĸýṹ����ҪΪ�������ӷ��ͽ��ն�ʹ��buffer��Ϣ��
�����ݽṹ��Ҫ�Ƕ�unsigned char*��csf_buffer��csf_csfstring��csf_chain��ԭ�����ͣ�������緢������������ա�
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_BUFFER_H_INCLUDED_)
#define CSF_CONNECT_BUFFER_H_INCLUDED_

#include "csf_typedef.h"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * Ϊ����ʵ�ָ����������������ĸýṹ����ҪΪ�������ӷ��ͽ��ն�ʹ��buffer��Ϣ��
				 * �����ݽṹ��Ҫ�Ƕ�unsigned char*��csf_buffer��csf_csfstring��csf_chain��ԭ�����ͣ�������緢������������ա�
				 * @author f
				 * @version 1.0
				 * @created 20-10��-2018 21:30:24
				 */
				template<typename ValueType = csf_buffer>
				class csf_connect_buffer
				{

				public:
					inline explicit csf_connect_buffer()
						: m_buffer(csf_nullptr)
						, m_length(0)
						, m_is_sync(csf_false)
						, m_is_free(csf_false) {

					}
					/**
					* ��Ҫ�����ǣ����ݶ�Ӧ���ȴ���csf_connect_buffer
					* ���أ���
					*
					* @param len    ��ʾ��Ҫ���͵Ļ��泤��
					*/
					inline explicit csf_connect_buffer(const csf_uint32 len)
						: csf_connect_buffer(new ValueType(len), len) {

					}
					/**
					* ��Ҫ�����ǣ�����buufer����Ͷ�Ӧ���ȴ���csf_connect_buffer
					* ���أ���
					*
					* @param buffer    ��ʾcsf_connect_buffer�����������ַ
					* @param len    ��ʾ��Ҫ���͵Ļ��泤��
					*/
					inline explicit csf_connect_buffer(ValueType* buffer, const csf_uint32 len)
						: m_buffer(buffer)
						, m_length(len)
						, m_is_sync(csf_false)
						, m_is_free(csf_false) {

					}

					virtual ~csf_connect_buffer() {

					}
					/**
					* ��Ҫ�����ǣ��������������������buffer����.
					* ���أ���
					*
					* @param newVal    ��ʾcsf_connect_buffer�����������ַ
					* @param len    ��ʾ��Ҫ���͵Ļ��泤��
					*/
					inline void set_buffer(ValueType* newVal, const csf_uint32 len) {

						m_buffer = newVal;
						set_is_free(csf_false);
						set_length(len);
					}
					/**
					* ��ʾ��ǰ�Ļ�����������
					*/
					inline ValueType* get_buffer() {

						return m_buffer;
					}
					/**
					 * ��ʾ�Ƿ����ͬ���ķ�ʽ���ͣ�false��ʾ�첽��true��ʾͬ����Ĭ��Ϊ�첽��ʽ
					 * 
					 * @param newVal    ��ʾ�Ƿ����ͬ���ķ�ʽ���ͣ�false��ʾ�첽��true��ʾͬ����
					 */
					inline void set_is_sync(const csf_bool newVal) {

						m_is_sync = newVal;
					}
					/**
					 * ��ʾ�Ƿ����ͬ���ķ�ʽ���ͣ�false��ʾ�첽��true��ʾͬ����Ĭ��Ϊ�첽��ʽ
					 */
					inline csf_bool get_is_sync() {

						return m_is_sync;
					}
					/**
					 * ��ʾ���ͻ���յ����ݳ���
					 * 
					 * @param newVal    ��ʾ��Ҫ���͵����ݳ���
					 */
					inline void set_length(const csf_uint32 newVal) {

						m_length = newVal;
					}
					/**
					* ��ʾ���ͻ���յ����ݳ���
					*/
					inline csf_uint32 get_length() {

						return m_length;
					}
					/**
					 * ��Ҫ�����ǣ��������ݳ��ȴ���һ����������
					 * ���أ���
					 * 
					 * @param len    ��ʾ��Ҫ���͵Ļ��泤��
					 */
					inline void create(const csf_uint32 len) {

						m_buffer = new ValueType(len);
						set_is_free(csf_true);
					}
					/**
					 * ��ʾ�Ƿ��ڶ�������ʱ���ͷ��ڴ档true��ʾ��Ҫ�ͷţ�false��ʾ����Ҫ�ͷţ�Ĭ��Ϊtrue����Ϊfalseʱע���������ط���ʾ�ͷţ������ڴ�й¶��
					 */
					inline csf_bool get_is_free() {

						return m_is_free;
					}
					/**
					 * ��ʾ�Ƿ��ڶ�������ʱ���ͷ��ڴ档true��ʾ��Ҫ�ͷţ�false��ʾ����Ҫ�ͷţ�Ĭ��Ϊtrue����Ϊfalseʱע���������ط���ʾ�ͷţ������ڴ�й¶��
					 * 
					 * @param newVal
					 * ��ʾ�Ƿ��ڶ�������ʱ���ͷ��ڴ档true��ʾ��Ҫ�ͷţ�false��ʾ����Ҫ�ͷţ�Ĭ��Ϊtrue����Ϊfalseʱע���������ط���ʾ�ͷţ������ڴ�й¶��
					 * 
					 */
					inline void set_is_free(const csf_bool newVal) {

						m_is_free = newVal;
					}

				private:
					/**
					 * ��ʾ�Ƿ����ͬ���ķ�ʽ���ͣ�false��ʾ�첽��true��ʾͬ����Ĭ��Ϊ�첽��ʽ
					 */
					csf_bool m_is_sync = csf_false;
					/**
					 * ��ʾ��ǰ�Ļ�����������
					 */
					ValueType* m_buffer;
					/**
					 * ��ʾ���ͻ���յ����ݳ���
					 */
					csf_uint32 m_length = 0;
					/**
					 * ��ʾ�Ƿ��ڶ�������ʱ���ͷ��ڴ档true��ʾ��Ҫ�ͷţ�false��ʾ����Ҫ�ͷţ�Ĭ��Ϊtrue����Ϊfalseʱע���������ط���ʾ�ͷţ������ڴ�й¶��
					 */
					csf_bool m_is_free = csf_false;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_BUFFER_H_INCLUDED_)
