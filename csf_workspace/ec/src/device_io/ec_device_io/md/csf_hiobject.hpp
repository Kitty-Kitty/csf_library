/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_hiobject.hpp
*
*Version: 1.0
*
*Date: 02-12月-2019 15:29:39
*
*Description: Class(csf_hiobject) 表示海思视频数据对象
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_HIOBJECT_H_INCLUDED_)
#define CSF_HIOBJECT_H_INCLUDED_

#include "csf_mdbuffer.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示海思视频数据对象
		 * @author f
		 * @version 1.0
		 * @created 02-12月-2019 15:29:39
		 */
		class csf_hiobject : public ec::core::csf_mdbuffer
		{

		public:
			csf_hiobject()
				: m_pts(0)
				, m_seq(0) {

			}
			/**
			* 功能：
			*    根据对象池和大小创建一个存储对象
			*
			* @param pool    表示当前对象所属的对象池
			* @param len    表示buffer缓存的长度
			*/
			inline explicit csf_hiobject(csf_mdpool* pool, const unsigned int len)
				: csf_mdbuffer(pool, len)
				, m_pts(0)
				, m_seq(0) {

			}
			/**
			* 构造一个指定长度的buffer
			*
			* @param len    表示buffer缓存的长度
			*/
			explicit csf_hiobject(const unsigned int len) 
				: csf_mdbuffer(len)
				, m_pts(0)
				, m_seq(0) {

			}
			virtual ~csf_hiobject() {

			}


			/**
			 * 功能：表示媒体数据对象销毁接口
			 */
			virtual void destroy();
			/**
			 * 功能：重新初始化媒体数据对象
			 * 返回：无
			 */
			virtual void reset();
			/**
			 * 表示当前媒体数据的时间戳
			 */
			inline csf_uint64 get_pts() {

				return m_pts;
			}
			/**
			 * 表示当前媒体数据的时间戳
			 *
			 * @param newVal
			 */
			inline void set_pts(csf_uint64 newVal) {

				m_pts = newVal;
			}
			/**
			* 功能：
			*    添加需要帧数据和时间戳。主要是将输入的数据复制一份，并且设置时间戳
			* 返回：
			*    被添加的数据长度
			*
			* @param buf    表示需要被添加的数据地址
			* @param len    需要被添加的数据长度
			* @param pts    表示当前数据帧的时间戳
			*/
			inline csf_uint32 cat(csf_uchar* buf, csf_uint32 len, csf_uint64 pts) {
				//get_native_buffer().reset();
				set_pts(pts);
				return get_native_buffer().cat(buf, len);
			}
			/**
			* 功能：
			*    添加需要帧数据和时间戳。主要是将输入的数据复制一份，并且设置时间戳
			* 返回：
			*    被添加的数据长度
			*
			* @param buf    表示需要被添加的数据地址
			* @param len    需要被添加的数据长度
			* @param pts    表示当前数据帧的时间戳
			* @param seq    表示数据帧的序号，如果为0，表示非法帧数据
			*
			*/
			inline csf_uint32 cat(csf_uchar* buf, csf_uint32 len, csf_uint64 pts, csf_uint32 seq) {
				set_seq(seq);
				return cat(buf, len, pts);
			}
			/**
			* 表示数据帧的序号，如果为0，表示非法帧数据
			*/
			inline csf_uint32 get_seq() {

				return m_seq;
			}
			/**
			* 表示数据帧的序号，如果为0，表示非法帧数据
			*
			* @param newVal
			*/
			inline void set_seq(csf_uint32 newVal) {

				m_seq = newVal;
			}
		private:
			/**
			 * 表示当前媒体数据的时间戳
			 */
			csf_uint64 m_pts = 0;
			/**
			* 表示数据帧的序号，如果为0，表示非法帧数据
			*/
			csf_uint32 m_seq = 0;
		};

	}

}
#endif // !defined(CSF_HIOBJECT_H_INCLUDED_)
