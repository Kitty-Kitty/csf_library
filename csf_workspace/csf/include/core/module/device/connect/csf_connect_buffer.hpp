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
						: m_container(csf_nullptr)
						, m_length(0)
						, m_is_sync(csf_false)
						, m_is_free(csf_false)
						, m_is_filled(csf_false) {

					}
					/**
					* ��Ҫ�����ǣ����ݶ�Ӧ���ȴ���csf_connect_buffer
					* ���أ���
					*
					* @param len    ��ʾ��Ҫ���͵Ļ��泤��
					*/
					inline explicit csf_connect_buffer(const csf_uint32 len)
						: csf_connect_buffer(new ValueType(len), len) {
						m_is_free(csf_true);

					}
					/**
					* ��Ҫ�����ǣ�����buufer����Ͷ�Ӧ���ȴ���csf_connect_buffer
					* ���أ���
					*
					* @param buffer    ��ʾcsf_connect_buffer�����������ַ
					* @param len    ��ʾ��Ҫ���͵Ļ��泤��
					*/
					inline explicit csf_connect_buffer(ValueType* buffer, const csf_uint32 len)
						: m_container(buffer)
						, m_length(len)
						, m_is_sync(csf_false)
						, m_is_free(csf_false)
						, m_is_filled(csf_false) {

					}

					virtual ~csf_connect_buffer() {

						destroy();
					}
					/**
					* ��ʾcsf_connect_buffer��������ʵ����Ҫ������������������������:csf_buffer��csf_csfstring�����
					*
					* @param newVal
					*/
					inline void set_container(ValueType* newVal) {

						if (csf_nullptr != newVal) {
							set_container(newVal, newVal->length());
						}
					}
					/**
					* ��ʾcsf_connect_buffer��������ʵ����Ҫ������������������������:csf_buffer��csf_csfstring�����
					*
					* @param newVal    ��ʾcsf_connect_buffer�����������ַ
					* @param len    ��ʾ��Ҫ���͵Ļ��泤��
					*/
					inline void set_container(ValueType* newVal, const csf_uint32 len) {

						m_container = newVal;
						set_is_free(csf_false);
						set_length(len);
					}
					/**
					* ��ʾcsf_connect_buffer��������ʵ����Ҫ������������������������:csf_buffer��csf_csfstring�����
					*/
					inline ValueType* get_container() {

						return m_container;
					}
					/**
					* ��ʾ��ǰ�Ļ�����������
					*/
					inline csf_uchar* get_buffer() {

						if (csf_nullptr != get_container()) {
							return get_container()->get_buffer();
						}
						return csf_nullptr;
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
					inline csf_int32 create(const csf_uint32 len) {

						if (get_buffer()) {
							return csf_failure;
						}
						set_container(new ValueType(len));
						set_is_free(csf_true);
						set_length(len);
						return csf_succeed;
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
					/**
					* ��Ҫ�����ǣ�������л���ռ����ݣ�
					* ���أ���
					*/
					inline csf_void clear() {

						set_length(0);
						set_is_sync(csf_false);
						set_is_free(csf_false);
						set_is_filled(csf_false);
						if (csf_nullptr != get_container()) {
							return get_container()->clear();
						}
					}
					/**
					* ��Ҫ�����ǣ����ݶ����Ƿ�Ϊ�գ������Ƿ�Ϊ�գ��жϵ�ǰ��csf_connect_buffer�Ƿ�Ϸ���
					* ���أ�����Ϊ�գ����Ȳ�Ϊ0�򷵻�true�������������false
					*/
					inline csf_bool is_valid() {

						if (csf_nullptr == get_buffer()
							|| length() <= 0) {

							return csf_false;
						}
						return csf_true;
					}
					/**
					* ��ʾ������־λ���豸�ñ�ʶλ��ǿ�ƽ�������ʱ�Ƿ�������󷵻ء���sync=true��ʾ��������ʱ����Ҫ��ȡ�㹻������ݺ�ŷ��ء�����һ���շ����ܵ��Ż�������ƣ�
					* ������߲�������Ӧ�õ����ܡ�
					*/
					inline csf_bool get_is_filled() {

						return m_is_filled;
					}
					/**
					* ��ʾ������־λ���豸�ñ�ʶλ��ǿ�ƽ�������ʱ�Ƿ�������󷵻ء���sync=true��ʾ��������ʱ����Ҫ��ȡ�㹻������ݺ�ŷ��ء�����һ���շ����ܵ��Ż�������ƣ�
					* ������߲�������Ӧ�õ����ܡ�
					*
					* @param newVal
					*/
					inline void set_is_filled(csf_bool newVal) {

						m_is_filled = newVal;
					}
					/**
					* ��ʾ��ȡbuffer�ܻ��泤��
					*/
					inline csf_uint32 size() {

						if (csf_nullptr != get_container()) {
							return get_container()->size();
						}
						return 0;
					}
					/**
					* ��ʾ��ȡbufferδʹ�õĿռ䳤��
					*/
					inline csf_uint32 avail() {

						if (csf_nullptr != get_container()) {
							return get_container()->avail();
						}
						return 0;
					}

					/**
					* ��ʾ��ǰʵ���Ѿ�ʹ�õĻ���ĳ���
					*/
					inline csf_uint32 length() {

						if (csf_nullptr != get_container()) {
							return get_container()->length();
						}
						return 0;
					}
					/**
					* ���ڴ�������ӵ�buffer�С� ���أ�>=0��ʾʵ����ӵ��ַ�������<0��ʾ�����룻
					*
					* @param buf    ��ʾ�����ڴ����ʼ��ַ
					* @param len    ��ʾ�ڴ����ݵĳ���
					*/
					inline csf_int32 cat(const csf_uchar* buf, const csf_uint32 len) {

						if (csf_nullptr != get_container()) {
							return get_container()->cat(buf, len);
						}
						return 0;
					}
					/**
					* ��ʾbuffer�Ƿ�Ϊ�գ�Ϊ�շ���true,���򷵻�false������Ϊ0��null��Ϊ�գ�����true��
					*/
					inline csf_bool empty() {

						if (csf_nullptr != get_container()) {
							return get_container()->empty();
						}
						return csf_true;
					}
					/**
					* ��ʾ��csf_string���뵽csf_buffer�С� ���أ�>=0��ʾʵ����ӵ��ַ�������<0��ʾ�����룻
					*
					* @param str    ��ʾ��׼�ַ�����
					*/
					inline csf_int32 cat(const csf_string& str) {

						if (csf_nullptr != get_container()) {
							return get_container()->cat(str);
						}
						return 0;
					}
					/**
					* ��ʾ��һ��char*�ַ������뵽buffer�С� ���أ�>=0��ʾʵ����ӵ��ַ�������<0��ʾ�����룻
					*
					* @param buf    ��ʾ����char*����
					*/
					inline csf_int32 cat(const csf_char* buf) {

						if (csf_nullptr != get_container()) {
							return get_container()->cat(buf);
						}
						return 0;
					}
					/**
					* ��ʾ��csf_buffer���뵽csf_buffer�С� ���أ�>=0��ʾʵ����ӵ��ַ�������<0��ʾ�����룻
					*
					* @param buffer    ��ʾ��Ҫ��ӵ�buffer����
					*/
					inline csf_int32 cat(csf_buffer& buffer) {

						if (csf_nullptr != get_container()) {
							return get_container()->cat(buffer);
						}
						return 0;
					}
//				protected:
					/**
					* ��ʾ�ͷ�buffer�е�startָ�����ڴ棬����buffer���Ϊnull
					*/
					inline csf_void destroy() {

						if (get_is_free() && get_container()) {
							delete get_container();
							set_is_free(csf_false);
							set_container(csf_nullptr);
						}
					}
				private:
					/**
					* ��ʾʵ�����ڽ��պͷ��͵Ļ��泤��
					*
					* @param newVal
					*/
					inline void set_size(csf_uint32 newVal) {

						m_size = newVal;
					}
					/**
					* ��ʾʵ�����ڽ��պͷ��͵Ļ��泤��
					*/
					inline csf_uint32 get_size() {

						return m_size;
					}
				private:
					/**
					 * ��ʾ�Ƿ����ͬ���ķ�ʽ���ͣ�false��ʾ�첽��true��ʾͬ����Ĭ��Ϊ�첽��ʽ
					 */
					csf_bool m_is_sync = csf_false;
					/**
					* ��ʾcsf_connect_buffer��������ʵ����Ҫ������������������������:csf_buffer��csf_csfstring�����
					*/
					ValueType* m_container;
					/**
					* ��ʾ���ͻ���յ����ݳ���
					*/
					csf_uint32 m_length = 0;
					/**
					* ��ʾʵ�����ڽ��պͷ��͵Ļ��泤��
					*/
					csf_uint32 m_size = 0;
					/**
					 * ��ʾ�Ƿ��ڶ�������ʱ���ͷ��ڴ档true��ʾ��Ҫ�ͷţ�false��ʾ����Ҫ�ͷţ�Ĭ��Ϊtrue����Ϊfalseʱע���������ط���ʾ�ͷţ������ڴ�й¶��
					 */
					csf_bool m_is_free = csf_false;
					/**
					* ��ʾ������־λ���豸�ñ�ʶλ��ǿ�ƽ�������ʱ�Ƿ�������󷵻ء���sync=true��ʾ��������ʱ����Ҫ��ȡ�㹻������ݺ�ŷ��ء�����һ���շ����ܵ��Ż�������ƣ�
					* ������߲�������Ӧ�õ����ܡ�
					*/
					csf_bool m_is_filled = csf_false;
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_BUFFER_H_INCLUDED_)
