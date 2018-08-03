/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_memblock.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 16:53:41
*
*Description: Class(csf_memblock)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MEMBLOCK_INCLUDED_)
#define CSF_MEMBLOCK_INCLUDED_

#include "csf_stddef.h"
#include "csf_container.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * ��ʾcsfʹ�õ��ڴ�ռ���
			 * @author f
			 * @version 1.0
			 * @created 27-6��-2018 16:53:41
			 */
			class csf_memblock : public csf::core::base::csf_container
			{

			public:
				inline csf_memblock() :
					m_buffer(csf_nullptr)
					, m_size(0)
					, m_is_free(csf_true) {

				}
				virtual ~csf_memblock()
				{
					clear();
				}

				/**
				 * ���ݻ����ַ�ͳ��ȴ�������
				 * 
				 * @param buf    ��ʾ���ݻ����ַ�ͳ��ȴ���һ��csf_csfstring
				 * @param len    len
				 * @param is_free
				 * ��ʾ�Ƿ��ڶ�������ʱ���ͷ��ڴ档true��ʾ��Ҫ�ͷţ�false��ʾ����Ҫ�ͷţ�Ĭ��Ϊtrue����Ϊfalseʱע���������ط���ʾ�ͷţ������ڴ�й¶��
				 * 
				 */
				inline explicit csf_memblock(const csf_uchar* buf, const csf_int32 len, const csf_bool is_free = csf_false)
					: m_buffer((csf_uchar*)buf)
					, m_size(len)
					, m_is_free(is_free) {
					if (len < 0) {
						throw csf_nullptr;
					}
				}
				/**
				 * ���ݳ�������һ���ڴ棬����һ������
				 * 
				 * @param len    ��ʾ��Ҫ������csf_csfstring����ĳ���
				 */
				inline explicit csf_memblock(const csf_int32 len)
					: m_buffer(csf_nullptr)
					, m_size(len)
					, m_is_free(csf_true) {
					if (len < 0) {
						throw csf_nullptr;
					}
					else {
						reset(len);
					}
				}
				/**
				* ��ʾ�ж��Ƿ�Ϊ�ա�
				* ���أ�true��ʾΪ�գ�false��ʾ��Ϊ�ա�
				*/
				inline csf_bool is_null() {

					return empty();
				}
				/**
				* ��ʾ�ж��Ƿ�Ϊ�ա�
				* ���أ�true��ʾ��Ϊ�գ�false��ʾΪ�ա�
				*/
				inline csf_bool not_null() {

					return !empty();
				}
				/**
				 * ��ʾ�����Ƿ�Ϊ�գ�Ϊ�շ���true,���򷵻�false������Ϊ0��nullΪ�գ�����true��
				 */
				inline csf_bool empty() {

					if (!m_buffer || size() <= 0) {
						return csf_true;
					}

					return csf_false;
				}
				/**
				 * ��ʾ��ȡ������ʵ�����ݳ��ȣ�û������Ϊ0
				 */
				inline csf_uint32 length() {

					return size();
				}
				/**
				 * ��ʾ��ȡ�����Ŀռ䳤�ȡ�û��Ԥ�����ڴ���࣬��size=length������csf_string��length=size����Ԥ�����ڴ���࣬size>=lengt
				 * h������csf_buffer��size>=length��
				 */
				inline csf_uint32 size() {

					return m_size;
				}
				/**
				 * ��ʾ�����������Щ����Ҫ�ͷſռ䣨���磺csf_chain������Щ�ռ�����õ�������������(���磺csf_buffer)��
				 */
				inline csf_void clear() {

					if (m_buffer && get_is_free()) {
						delete m_buffer;
					}

					set_buffer(csf_nullptr);
					m_size = 0;
					set_is_free(csf_true);
				}
				/**
				 * ��ʾ����ڴ�ռ�
				 */
				inline csf_void memzero() {

					if (m_buffer && size() > 0) {
						csf_memset(m_buffer, 0, size());
					}
				}
				/**
				 * ��ʾ�������ݵĻ����ַ
				 */
				inline csf_uchar* get_buffer() {

					return m_buffer;
				}
				/**
				* ���ݻ����ַ�ͳ�������һ�����󣬸��¶�����Ϣ��
				* ����:true��ʾ�ɹ���false��ʾʧ�ܡ�
				*
				* @param buf    ��ʾ���ݻ����ַ�ͳ��ȴ���һ��csf_csfstring
				* @param len    len
				* @param is_free
				* ��ʾ�Ƿ��ڶ�������ʱ���ͷ��ڴ档true��ʾ��Ҫ�ͷţ�false��ʾ����Ҫ�ͷţ�Ĭ��Ϊtrue����Ϊfalseʱע���������ط���ʾ�ͷţ������ڴ�й¶��
				*
				*/
				inline csf_bool set_buffer(const csf_uchar* buf, const csf_int32 len, const csf_bool is_free = csf_false) {

					if (len < 0) {
						return csf_false;
					}

					set_buffer(buf);
					set_size(len);
					set_is_free(is_free);

					return csf_true;
				}
				/**
				* ��ʾ�������ݵĻ��泤��
				*/
				inline csf_uint32 get_size() {

					return m_size;
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
				 */
				inline csf_void set_is_free(const csf_bool newVal) {

					m_is_free = newVal;
				}

			protected:
				/**
				* ��ʾ�������ݵĻ��泤��
				*
				* @param newVal
				*/
				inline csf_void set_size(const csf_uint32 newVal) {

					m_size = newVal;
				}
				/**
				* ��ʾ�������ݵĻ����ַ
				*
				* @param newVal    newVal
				*/
				inline void set_buffer(const csf_uchar* newVal) {

					m_buffer = (csf_uchar*)newVal;
				}
				/**
				* ���´������󡣸��ݳ�������һ���ڴ棬����һ������
				*
				* @param len    ��ʾ��Ҫ������csf_csfstring����ĳ���
				*/
				inline csf_void reset(const csf_int32 len) {

					clear();
					set_buffer(new csf_uchar(len));
					set_size(len);
					set_is_free(csf_true);
				}

			private:
				/**
				 * ��ʾ�������ݵĻ����ַ
				 */
				csf_uchar* m_buffer = csf_nullptr;
				/**
				 * ��ʾ�������ݵĻ��泤��
				 */
				csf_uint32 m_size = 0;
				/**
				 * ��ʾ�Ƿ��ڶ�������ʱ���ͷ��ڴ档true��ʾ��Ҫ�ͷţ�false��ʾ����Ҫ�ͷţ�Ĭ��Ϊtrue����Ϊfalseʱע���������ط���ʾ�ͷţ������ڴ�й¶��
				 */
				csf_bool m_is_free = csf_true;

			};

		}

	}

}
#endif // !defined(CSF_MEMBLOCK_INCLUDED_)
