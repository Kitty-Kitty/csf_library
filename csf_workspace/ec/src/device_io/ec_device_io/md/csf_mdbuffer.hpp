/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mdbuffer.hpp
*
*Version: 1.0
*
*Date: 02-12月-2019 14:12:48
*
*Description: Class(csf_mdbuffer) 表示媒体帧数据内容。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MDBUFFER_H_INCLUDED_)
#define CSF_MDBUFFER_H_INCLUDED_

#include "csf_mdobject.hpp"
#include "csf_buffer.hpp"

using namespace csf::core::base;

namespace ec
{
	namespace core
	{
		/**
		 * 表示媒体帧数据内容。
		 * @author f
		 * @version 1.0
		 * @created 02-12月-2019 14:12:48
		 */
		class csf_mdbuffer : public ec::core::csf_mdobject
		{

		public:
			csf_mdbuffer();
			virtual ~csf_mdbuffer();

			/**
			* 构造一个指定长度的buffer
			*
			* @param len    表示buffer缓存的长度
			*/
			inline explicit csf_mdbuffer(const unsigned int len)
				: m_buffer(len) {

			}
			/**
			* 功能：
			*    根据对象池和大小创建一个存储对象
			*
			* @param pool    表示当前对象所属的对象池
			* @param len    表示buffer缓存的长度
			*/
			inline explicit csf_mdbuffer(csf_mdpool* pool, const unsigned int len)
				: csf_mdobject(pool)
				, m_buffer(len) {

			}
			/**
			*
			* @param buf    表示根据缓存空间来创建buffer
			* @param len    表示缓存的长度
			*/
			inline explicit csf_mdbuffer(const unsigned char* buf, const unsigned int len)
				: m_buffer(buf, len) {

			}

			/**
			 * 功能：根据csf_mdbuffer对象创建一个csf_mdframe对象
			 * 返回：无
			 *
			 * @param newVal
			 */
			inline explicit csf_mdbuffer(csf_buffer& newVal) {

				m_buffer = newVal;
			}

			/**
			* 表示csf_mdframe所拥有的csf_buffer对象
			*/
			inline unsigned char* get_buffer() {

				return  m_buffer.get_buffer();
			}

			/**
			* 表示当前实际已经使用的缓存的长度
			*/
			inline csf_uint32 length() {

				return m_buffer.length();
			}

			/**
			 * 表示判断是否为空。
			 * 返回：true表示为空；false表示不为空。
			 */
			inline virtual csf_bool is_null() {

				return m_buffer.is_null();
			}

			/**
			 * 功能：重新初始化媒体数据对象
			 * 返回：无
			 */
			virtual void reset() {
				m_buffer.reset();
			}

			/**
			* 功能：表示媒体数据对象销毁接口
			* 返回：无
			*/
			virtual void destroy() {
				m_buffer.clear();
			}
			/**
			* 功能：
			*    获取当前csf_buffer缓存的大小
			* 返回：
			*    缓存空间的大小
			*/
			inline csf_uint32 size() {

				return m_buffer.size();
			}
		protected:
			/**
			* 表示csf_mdframe所拥有的csf_buffer对象
			*/
			inline csf_buffer& get_native_buffer() {

				return  m_buffer;
			}
		private:
			/**
			 * 表示csf_mdframe所拥有的csf_buffer对象
			 */
			csf_buffer m_buffer;

			/**
			 * 表示csf_mdframe所拥有的csf_buffer对象
			 *
			 * @param newVal
			 */
			inline void set_buffer(csf_buffer& newVal) {

				m_buffer = newVal;
			}

		};

	}

}
#endif // !defined(CSF_MDBUFFER_H_INCLUDED_)
