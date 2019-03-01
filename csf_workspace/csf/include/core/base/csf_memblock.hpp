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
					destroy();
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
				inline explicit csf_memblock(const csf_uchar* buf
					, const csf_int32 len
					, const csf_bool is_free = csf_true)
					: m_buffer(csf_nullptr)
					, m_size(len)
					, m_is_free(is_free) {
					if (len < 0) {
						throw csf_nullptr;
					}

					reset(len);
					memzero();
					csf_memcpy(get_buffer(), buf, len);

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
						memzero();
					}
				}
				/**
				* ��ʾ�ж��Ƿ�Ϊ�ա�
				* ���أ�true��ʾΪ�գ�false��ʾ��Ϊ�ա�
				*/
				inline csf_bool is_null() const {

					return empty();
				}
				/**
				* ��ʾ�ж��Ƿ�Ϊ�ա�
				* ���أ�true��ʾ��Ϊ�գ�false��ʾΪ�ա�
				*/
				inline csf_bool not_null() const {

					return !empty();
				}
				/**
				 * ��ʾ�����Ƿ�Ϊ�գ�Ϊ�շ���true,���򷵻�false������Ϊ0��nullΪ�գ�����true��
				 */
				inline csf_bool empty() const {

					if (!m_buffer || size() <= 0) {
						return csf_true;
					}

					return csf_false;
				}
				/**
				 * ��ʾ��ȡ������ʵ�����ݳ��ȣ�û������Ϊ0
				 */
				inline csf_uint32 length() const {

					return size();
				}
				/**
				 * ��ʾ��ȡ�����Ŀռ䳤�ȡ�û��Ԥ�����ڴ���࣬��size=length������csf_string��length=size����Ԥ�����ڴ���࣬size>=lengt
				 * h������csf_buffer��size>=length��
				 */
				inline csf_uint32 size() const {

					return m_size;
				}
				/**
				* ��ʾ�����������Щ����Ҫ�ͷſռ䣨���磺csf_chain������Щ�ռ�����õ�������������(���磺csf_buffer)��
				* ִ��clear�󣬶����������ģ����Լ���ʹ�á������ִ��destroy�����󣬲�����Դ���ᱻ�ͷţ����ܵ��¶������������ܼ�������ʹ�á�
				*/
				inline csf_void clear() {
					
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
				inline csf_uchar* get_buffer() const {

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
				inline csf_uint32 get_size() const {

					return m_size;
				}
				/**
				 * ��ʾ�Ƿ��ڶ�������ʱ���ͷ��ڴ档true��ʾ��Ҫ�ͷţ�false��ʾ����Ҫ�ͷţ�Ĭ��Ϊtrue����Ϊfalseʱע���������ط���ʾ�ͷţ������ڴ�й¶��
				 */
				inline csf_bool get_is_free() const {

					return m_is_free;
				}
				/**
				 * ��ʾ�Ƿ��ڶ�������ʱ���ͷ��ڴ档true��ʾ��Ҫ�ͷţ�false��ʾ����Ҫ�ͷţ�Ĭ��Ϊtrue����Ϊfalseʱע���������ط���ʾ�ͷţ������ڴ�й¶��
				 * 
				 * @param new_value
				 */
				inline csf_void set_is_free(const csf_bool new_value) {

					m_is_free = new_value;
				}

			protected:
				/**
				* ��ʾ�������ݵĻ��泤��
				*
				* @param new_value
				*/
				inline csf_void set_size(const csf_uint32 new_value) {

					m_size = new_value;
				}
				/**
				* ��ʾ�������ݵĻ����ַ
				*
				* @param new_value    new_value
				*/
				inline void set_buffer(const csf_uchar* new_value) {

					m_buffer = (csf_uchar*)new_value;
				}
				/**
				* ���´������󡣸��ݳ�������һ���ڴ棬����һ������
				*
				* @param len    ��ʾ��Ҫ������csf_csfstring����ĳ���
				*/
				inline csf_void reset(const csf_int32 len) {

					destroy();
					set_buffer(new csf_uchar[len]);
					set_size(len);
					set_is_free(csf_true);
				}
				/**
				* ��ʾ��������������clear��������⣬�������������ڴ�Ĺ��ܡ�
				* ִ��clear�󣬶����������ģ����Լ���ʹ�á������ִ��destroy�����󣬲�����Դ���ᱻ�ͷţ����ܵ��¶������������ܼ�������ʹ�á�
				*/
				inline virtual csf_void destroy() {

					if (m_buffer && get_is_free()) {
						delete[] m_buffer;
					}

					set_buffer(csf_nullptr);
					m_size = 0;
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
