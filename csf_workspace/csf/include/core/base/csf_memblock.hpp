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
*Date: 27-6月-2018 16:53:41
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
			 * 表示csf使用的内存空间类
			 * @author f
			 * @version 1.0
			 * @created 27-6月-2018 16:53:41
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
				 * 根据缓存地址和长度创建对象
				 * 
				 * @param buf    表示根据缓存地址和长度创建一个csf_csfstring
				 * @param len    len
				 * @param is_free
				 * 表示是否在对象销毁时，释放内存。true表示需要释放；false表示不需要释放；默认为true，当为false时注意在其他地方显示释放，避免内存泄露。
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
				 * 根据长度申请一个内存，创建一个对象
				 * 
				 * @param len    表示需要创建的csf_csfstring缓存的长度
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
				 * 表示容器是否为空，为空返回true,否则返回false。长度为0或null为空，返回true。
				 */
				inline csf_bool empty() const {

					if (!m_buffer || size() <= 0) {
						return csf_true;
					}

					return csf_false;
				}
				/**
				 * 表示获取容器的实际内容长度，没有内容为0
				 */
				inline csf_uint32 length() const {

					return size();
				}
				/**
				 * 表示获取容器的空间长度。没有预分配内存的类，则size=length，例如csf_string中length=size。而预分配内存的类，size>=lengt
				 * h，例如csf_buffer中size>=length。
				 */
				inline csf_uint32 size() const {

					return m_size;
				}
				/**
				* 表示清空容器，有些类需要释放空间（例如：csf_chain），有些空间可重用的类则重置数据(例如：csf_buffer)。
				* 执行clear后，对象还是完整的，可以继续使用。而相对执行destroy函数后，部分资源将会被释放，可能导致对象不完整，不能继续正常使用。
				*/
				inline csf_void clear() {
					
				}
				/**
				 * 表示清空内存空间
				 */
				inline csf_void memzero() {

					if (m_buffer && size() > 0) {
						csf_memset(m_buffer, 0, size());
					}
				}
				/**
				 * 表示保存内容的缓存地址
				 */
				inline csf_uchar* get_buffer() const {

					return m_buffer;
				}
				/**
				* 根据缓存地址和长度配置一个对象，更新对象信息。
				* 返回:true表示成功；false表示失败。
				*
				* @param buf    表示根据缓存地址和长度创建一个csf_csfstring
				* @param len    len
				* @param is_free
				* 表示是否在对象销毁时，释放内存。true表示需要释放；false表示不需要释放；默认为true，当为false时注意在其他地方显示释放，避免内存泄露。
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
				* 表示保存内容的缓存长度
				*/
				inline csf_uint32 get_size() const {

					return m_size;
				}
				/**
				 * 表示是否在对象销毁时，释放内存。true表示需要释放；false表示不需要释放；默认为true，当为false时注意在其他地方显示释放，避免内存泄露。
				 */
				inline csf_bool get_is_free() const {

					return m_is_free;
				}
				/**
				 * 表示是否在对象销毁时，释放内存。true表示需要释放；false表示不需要释放；默认为true，当为false时注意在其他地方显示释放，避免内存泄露。
				 * 
				 * @param new_value
				 */
				inline csf_void set_is_free(const csf_bool new_value) {

					m_is_free = new_value;
				}

			protected:
				/**
				* 表示保存内容的缓存长度
				*
				* @param new_value
				*/
				inline csf_void set_size(const csf_uint32 new_value) {

					m_size = new_value;
				}
				/**
				* 表示保存内容的缓存地址
				*
				* @param new_value    new_value
				*/
				inline void set_buffer(const csf_uchar* new_value) {

					m_buffer = (csf_uchar*)new_value;
				}
				/**
				* 重新创建对象。根据长度申请一个内存，创建一个对象
				*
				* @param len    表示需要创建的csf_csfstring缓存的长度
				*/
				inline csf_void reset(const csf_int32 len) {

					destroy();
					set_buffer(new csf_uchar[len]);
					set_size(len);
					set_is_free(csf_true);
				}
				/**
				* 表示销毁容器，除了clear清空数据外，更增加了销毁内存的功能。
				* 执行clear后，对象还是完整的，可以继续使用。而相对执行destroy函数后，部分资源将会被释放，可能导致对象不完整，不能继续正常使用。
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
				 * 表示保存内容的缓存地址
				 */
				csf_uchar* m_buffer = csf_nullptr;
				/**
				 * 表示保存内容的缓存长度
				 */
				csf_uint32 m_size = 0;
				/**
				 * 表示是否在对象销毁时，释放内存。true表示需要释放；false表示不需要释放；默认为true，当为false时注意在其他地方显示释放，避免内存泄露。
				 */
				csf_bool m_is_free = csf_true;

			};

		}

	}

}
#endif // !defined(CSF_MEMBLOCK_INCLUDED_)
