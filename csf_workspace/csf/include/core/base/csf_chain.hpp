/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_chain.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:35
*
*Description: Class(csf_chain)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CHAIN_INCLUDED_)
#define CSF_CHAIN_INCLUDED_


#include <list>

#include "csf_atomic.h"
#include "csf_container.hpp"
#include "csf_buffer.hpp"
#include "csf_csfstring.hpp"
#include "csf_default.h"
#include "csf_mutex.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * ��ʾ����ṹ����
			 * @author f
			 * @version 1.0
			 * @created 27-6��-2018 17:28:35
			 */
			class csf_chain : public csf::core::base::csf_container
			{

			public:
				inline explicit csf_chain()
					: m_length(0) {

				}
				/**
				*
				* @param len    ��ʾ��Ҫ������chain�ĳ���
				*/
				inline explicit csf_chain(const csf_uint32 len)
					: m_length(0) {

				}
				virtual ~csf_chain() {
					clear();
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
				 * ��ʾ�����Ƿ�Ϊ�գ�Ϊ�շ���true,���򷵻�false������Ϊ0��null��Ϊ�գ�����true��
				 */
				inline csf_bool empty() const {

					if (length() <= 0) {
						return csf_true;
					}
					return csf_false;
				}
				/**
				 * ��ʾ��ȡ������ʵ�����ݳ��ȣ�û������Ϊ0
				 */
				inline csf_uint32 length() const {

					return m_length;
				}
				/**
				 * ��ʾ��ȡ�����Ŀռ䳤�ȡ�û��Ԥ�����ڴ���࣬��size=length������csf_string��length=size����Ԥ�����ڴ���࣬size>=lengt
				 * h������csf_buffer��size>=length��
				 */
				inline csf_uint32 size() const {

					return length();
				}
				/**
				 * ��ʾ���һ��csf_buffer��chain�С�
				 * ���أ�0��ʾ�ɹ���<0��ʾ����
				 * 
				 * @param buffer    ��ʾ��Ҫ��ӵ�csf_buffer��ַ
				 */
				inline csf_int32 add(csf_buffer* buffer) {

					if (!buffer) {
						return csf_failure;
					}

					return add(*buffer);
				}
				/**
				 * ��ʾ���һ��csf_buffer��chain�С�
				 * ���أ�0��ʾ�ɹ���<0��ʾ����
				 * 
				 * @param buffer    ��ʾ��Ҫ��ӵ�csf_buffer
				 */
				inline csf_int32 add(csf_buffer& buffer) {

					csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					m_chain.push_back(new csf_buffer(buffer));

					return csf_success;
				}
				/**
				* ��ʾ��chain��ɾ��һ��csf_buffer��
				* ���أ�0��ʾ�ɹ���<0��ʾ����
				*
				* @param buffer    ��ʾ��Ҫɾ����csf_buffer��ַ
				*/
				inline csf_int32 del(csf_buffer* buffer) {

					if (!buffer) {
						return csf_failure;
					}

					return del(*buffer);
				}
				/**
				* ��ʾ��chain��ɾ��һ��csf_buffer,����chain�Ĳ��Ҹ�������������ͬ��
				* ���أ�0��ʾ�ɹ���<0��ʾ����
				*
				* @param buffer    ��ʾ��Ҫ��ӵ�csf_buffer
				*/
				inline csf_int32 del(csf_buffer& buffer) {

					csf_list<csf_buffer*>::iterator			tmp_iter;
					csf_int32								tmp_int_ret = csf_failure;


					csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					for (tmp_iter = m_chain.begin(); tmp_iter != m_chain.end(); tmp_iter++) {
						if (*(*tmp_iter) == buffer) {
							m_chain.erase(tmp_iter);
							tmp_int_ret = csf_success;
						}
					}

					return tmp_int_ret;
				}
				/**
				 * ���chain,���ͷ�chain�е����л���ռ䡣
				 */
				inline csf_void clear() {

					csf_list<csf_buffer*>::iterator			tmp_iter;

					csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					for (tmp_iter = m_chain.begin(); tmp_iter != m_chain.end(); tmp_iter++) {
						delete *tmp_iter;
					}
					m_chain.clear();
				}
				/**
				 * ��ʾ��chainת��Ϊcsf_buffer
				 * ���أ�>=0��ʾʵ�����ݵĳ��ȣ�<0��ʾ����
				 * 
				 * @param buffer    ��ʾ��Ҫ�������csf_buffer����
				 */
				inline csf_int32 convert(csf_buffer& buffer) {

					csf_list<csf_buffer*>::iterator			tmp_iter;

					
					csf_shared_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					for (tmp_iter = m_chain.begin(); tmp_iter != m_chain.end(); tmp_iter++) {
						buffer.cat(**tmp_iter);
					}

					buffer.length();
				}
				/**
				 * ��ʾ��chainת��Ϊcsf_csfstring
				 * ���أ�>=0��ʾʵ�����ݵĳ��ȣ�<0��ʾ����
				 * 
				 * @param csfstr    ��ʾ��Ҫ�������csf_csfstringr����
				 */
				inline csf_int32 convert(csf_csfstring& csfstr) {

					csf_list<csf_buffer*>::iterator			tmp_iter;

					
					csf_shared_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					for (tmp_iter = m_chain.begin(); tmp_iter != m_chain.end(); tmp_iter++) {
						csfstr.cat((*tmp_iter)->get_pos(), (*tmp_iter)->length());
					}

					csfstr.length();
				}
				/**
				 * ��ʾ��chainת����ָ�����ڴ���
				 * ���أ�>=0��ʾʵ�����ݵĳ��ȣ�<0��ʾ����
				 * 
				 * @param buf    ��ʾ��Ҫ��������ڴ��ַ
				 * @param len    ��ʾ�ڴ滺��buf�ĳ���
				 */
				inline csf_int32 convert(const csf_uchar* buf, const csf_uint32 len) {

					csf_uchar								*tmp_buf = (csf_uchar *)buf;
					csf_int32								tmp_int_ret = 0;
					csf_list<csf_buffer*>::iterator			tmp_iter;


					if (!buf || len < length()) {
						return csf_failure;
					}

					csf_shared_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					for (tmp_iter = m_chain.begin(); tmp_iter != m_chain.end(); tmp_iter++) {
						csf_memcpy(tmp_buf, (*tmp_iter)->get_pos(), (*tmp_iter)->length());
						tmp_buf += (*tmp_iter)->length();
					}
					tmp_int_ret = length();

					return tmp_int_ret;
				}
				/**
				 * ��ʾ���һ��csf_csfstring��chain�С�
				 * ���أ�0��ʾ�ɹ���<0��ʾ����
				 * 
				 * @param csfstr    ��ʾ��Ҫ��ӵ�csf_csfstring
				 */
				inline csf_int32 add(csf_csfstring& csfstr) {

					if (csfstr.size() <= 0) {
						return csf_failure;
					}

					return add(new csf_buffer(csfstr.get_buffer(), csfstr.length()));
				}
				/**
				 * ��ʾ���һ���ڴ����ݵ�chain�С�
				 * ���أ�0��ʾ�ɹ���<0��ʾ����
				 * 
				 * @param buf    ��ʾ��Ҫ��ӵ��ڴ����ݵ�ַ
				 * @param len    ��ʾ��Ҫ��ӵ��ڴ����ݳ���
				 */
				inline csf_int32 add(const csf_uchar* buf, const csf_uint32 len) {

					if (!buf || len <= 0) {
						return csf_failure;
					}

					return add(new csf_buffer(buf, len));
				}

			private:
				/**
				 * ��ʾ���ݵ�ʵ�ʳ���
				 */
				csf::core::base::csf_atomic_uint32 m_length = 0;
				/**
				 * ��ʾ�����������ݣ���������buffer
				 */
				csf_list<csf_buffer*> m_chain;
				/**
				* ��ʾ�̰߳�ȫʹ�õĻ���������
				*/
				csf_shared_mutex	 m_mutex;
				/**
				 * ��ʾ�����������ݣ���������buffer
				 */
				inline csf_list<csf_buffer*>& get_chain() {

					return m_chain;
				}
				/**
				 * ��ʾ�����������ݣ���������buffer
				 * 
				 * @param new_value
				 */
				inline csf_bool set_chain(const csf_list<csf_buffer*>& new_value) {

					m_chain = new_value;
				}

			};

		}

	}

}
#endif // !defined(CSF_CHAIN_INCLUDED_)
