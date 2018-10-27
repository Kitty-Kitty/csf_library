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
*Date: 27-6月-2018 17:28:35
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
			 * 表示链表结构数据
			 * @author f
			 * @version 1.0
			 * @created 27-6月-2018 17:28:35
			 */
			class csf_chain : public csf::core::base::csf_container
			{

			public:
				inline explicit csf_chain()
					: m_length(0) {

				}
				/**
				*
				* @param len    表示需要创建的chain的长度
				*/
				inline explicit csf_chain(const csf_uint32 len)
					: m_length(0) {

				}
				virtual ~csf_chain() {
					clear();
				}
				/**
				* 表示判断是否为空。
				* 返回：true表示为空；false表示不为空。
				*/
				inline csf_bool is_null() const {

					return empty();
				}
				/**
				* 表示判断是否不为空。
				* 返回：true表示不为空；false表示为空。
				*/
				inline csf_bool not_null() const {

					return !empty();
				}
				/**
				 * 表示容器是否为空，为空返回true,否则返回false。长度为0或null都为空，返回true。
				 */
				inline csf_bool empty() const {

					if (length() <= 0) {
						return csf_true;
					}
					return csf_false;
				}
				/**
				 * 表示获取容器的实际内容长度，没有内容为0
				 */
				inline csf_uint32 length() const {

					return m_length;
				}
				/**
				 * 表示获取容器的空间长度。没有预分配内存的类，则size=length，例如csf_string中length=size。而预分配内存的类，size>=lengt
				 * h，例如csf_buffer中size>=length。
				 */
				inline csf_uint32 size() const {

					return length();
				}
				/**
				 * 表示添加一个csf_buffer到chain中。
				 * 返回：0表示成功；<0表示错误。
				 * 
				 * @param buffer    表示需要添加的csf_buffer地址
				 */
				inline csf_int32 add(csf_buffer* buffer) {

					if (!buffer) {
						return csf_failure;
					}

					return add(*buffer);
				}
				/**
				 * 表示添加一个csf_buffer到chain中。
				 * 返回：0表示成功；<0表示错误。
				 * 
				 * @param buffer    表示需要添加的csf_buffer
				 */
				inline csf_int32 add(csf_buffer& buffer) {

					csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					m_chain.push_back(new csf_buffer(buffer));

					return csf_success;
				}
				/**
				* 表示从chain中删除一个csf_buffer。
				* 返回：0表示成功；<0表示错误。
				*
				* @param buffer    表示需要删除的csf_buffer地址
				*/
				inline csf_int32 del(csf_buffer* buffer) {

					if (!buffer) {
						return csf_failure;
					}

					return del(*buffer);
				}
				/**
				* 表示从chain中删除一个csf_buffer,其中chain的查找根据所有属性相同。
				* 返回：0表示成功；<0表示错误。
				*
				* @param buffer    表示需要添加的csf_buffer
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
				 * 清空chain,并释放chain中的所有缓存空间。
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
				 * 表示将chain转换为csf_buffer
				 * 返回：>=0表示实际数据的长度；<0表示错误；
				 * 
				 * @param buffer    表示需要被保存的csf_buffer对象
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
				 * 表示将chain转换为csf_csfstring
				 * 返回：>=0表示实际数据的长度；<0表示错误；
				 * 
				 * @param csfstr    表示需要被保存的csf_csfstringr对象
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
				 * 表示将chain转换到指定的内存中
				 * 返回：>=0表示实际数据的长度；<0表示错误；
				 * 
				 * @param buf    表示需要被保存的内存地址
				 * @param len    表示内存缓存buf的长度
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
				 * 表示添加一个csf_csfstring到chain中。
				 * 返回：0表示成功；<0表示错误。
				 * 
				 * @param csfstr    表示需要添加的csf_csfstring
				 */
				inline csf_int32 add(csf_csfstring& csfstr) {

					if (csfstr.size() <= 0) {
						return csf_failure;
					}

					return add(new csf_buffer(csfstr.get_buffer(), csfstr.length()));
				}
				/**
				 * 表示添加一个内存数据到chain中。
				 * 返回：0表示成功；<0表示错误。
				 * 
				 * @param buf    表示需要添加的内存数据地址
				 * @param len    表示需要添加的内存数据长度
				 */
				inline csf_int32 add(const csf_uchar* buf, const csf_uint32 len) {

					if (!buf || len <= 0) {
						return csf_failure;
					}

					return add(new csf_buffer(buf, len));
				}

			private:
				/**
				 * 表示数据的实际长度
				 */
				csf::core::base::csf_atomic_uint32 m_length = 0;
				/**
				 * 表示缓存链表数据，保存所有buffer
				 */
				csf_list<csf_buffer*> m_chain;
				/**
				* 表示线程安全使用的互斥锁内容
				*/
				csf_shared_mutex	 m_mutex;
				/**
				 * 表示缓存链表数据，保存所有buffer
				 */
				inline csf_list<csf_buffer*>& get_chain() {

					return m_chain;
				}
				/**
				 * 表示缓存链表数据，保存所有buffer
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
