/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mdframe.hpp
*
*Version: 1.0
*
*Date: 30-11月-2019 16:44:05
*
*Description: Class(csf_mdframe) 表示媒体帧数据。
插入csf_mdpipe中的每一个数据都是一个csf_mdframe，而从csf_mdpipe中读取的每一个数据都是一个csf_mdframe。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MDFRAME_H_INCLUDED_)
#define CSF_MDFRAME_H_INCLUDED_

#include <memory>
#include "csf_mdbuffer.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示媒体帧数据。
		 * 插入csf_mdpipe中的每一个数据都是一个csf_mdframe，而从csf_mdpipe中读取的每一个数据都是一个csf_mdframe。
		 * @author f
		 * @version 1.0
		 * @created 30-11月-2019 16:44:05
		 */
		class csf_mdframe : public std::enable_shared_from_this<csf_mdframe>
		{

		public:
			/**
			* 功能：根据csf_mdbuffer对象创建一个csf_mdframe对象
			* 返回：无
			*
			* @param newVal
			*/
			inline explicit csf_mdframe(csf_mdbuffer& newVal)
				: m_mdbuffer(newVal) {
			}
			virtual ~csf_mdframe() {
				get_mdbuffer().destroy();
			}

			/**
			 * 表示csf_mdframe所拥有的csf_buffer对象
			 */
			inline csf_mdbuffer& get_mdbuffer() {

				return m_mdbuffer;
			}
			/**
			 * 表示判断是否为空。
			 * 返回：true表示为空；false表示不为空。
			 */
			inline virtual bool is_null() {

				return m_mdbuffer.is_null();
			}
			/**
			 * 表示保存内容的缓存地址
			 */
			inline unsigned char* get_buffer() {

				return m_mdbuffer.get_buffer();
			}
			/**
			 * 表示当前实际已经使用的缓存的长度
			 */
			inline unsigned int length() {

				return m_mdbuffer.length();
			}

		private:
			/**
			 * 表示csf_mdframe所拥有的csf_buffer对象
			 */
			csf_mdbuffer m_mdbuffer;

			/**
			 * 表示csf_mdframe所拥有的csf_buffer对象
			 * 
			 * @param newVal
			 */
			inline void set_mdbuffer(csf_mdbuffer& newVal) {

				m_mdbuffer = newVal;
			}

		};
		//定义一个智能指针类型
		typedef	std::shared_ptr<csf_mdframe>	csf_mdframe_ptr;
	}

}
#endif // !defined(CSF_MDFRAME_H_INCLUDED_)
