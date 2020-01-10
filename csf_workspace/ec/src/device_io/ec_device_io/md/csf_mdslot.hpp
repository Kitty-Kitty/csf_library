/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mdslot.hpp
*
*Version: 1.0
*
*Date: 30-11月-2019 16:44:05
*
*Description: Class(csf_mdslot) 表示媒体数据通道，能用于临时保存媒体数据。其中媒体数据生产端源源不断插入到媒体流数据通道中，同时媒体数据消费者源源不断从媒体流数据通道中取出。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MDSLOT_H_INCLUDED_)
#define CSF_MDSLOT_H_INCLUDED_

#include "csf_mdframe.hpp"
#include "csf_csfdeque.hpp"
#include "csf_stddef.h"

namespace ec
{
	namespace core
	{
		/**
		 * 表示媒体数据通道，能用于临时保存媒体数据。其中媒体数据生产端源源不断插入到媒体流数据通道中，同时媒体数据消费者源源不断从媒体流数据通道中取出。
		 * @author f
		 * @version 1.0
		 * @created 30-11月-2019 16:44:05
		 */
		class csf_mdslot
		{

		public:
			csf_mdslot();
			/**
			* 根据名称创建一个媒体流槽
			*
			* @param name    表示媒体流数据槽的名称
			*/
			inline explicit csf_mdslot(std::string name) {
				set_name(name);
			}
			virtual ~csf_mdslot();
			/**
			 * 表示通道的uuid，用于唯一标识一个通道
			 */
			inline std::string get_guid() {

				return m_guid;
			}
			/**
			 * 表示通道的名称，用于描述通道
			 */
			inline std::string get_name() {

				return m_name;
			}
			/**
			 * 表示通道的名称，用于描述通道
			 *
			 * @param newVal
			 */
			inline void set_name(std::string newVal) {

				csf_strncpy(m_name, newVal.c_str(), csf_sizeof(m_name) - 1);
			}
			/**
			 * 功能：清除内存管理器中的所有内存对象，释放内存管理器中保存的所有内存
			 * 返回：无
			 */
			inline void clear() {

				m_queue.clear();
			}
			/**
			* 功能：向通道中发送媒体数据帧
			* 返回：true表示发送成功；false表示发送失败；
			*
			* @param object    表示需要添加的媒体对象
			*/
			inline virtual bool push_frame(csf_mdobject* object) {

				//验证参数的合法性
				if (!object) {
					return false;
				}

				//将数据帧插入到队列中保存
				csf_mdframe_ptr tmp_mdframe(new csf_mdframe(object));
				get_queue().push_back(tmp_mdframe);

				return true;
			}
			/**
			 * 功能：获取当前数据帧
			 * 返回：返回数据帧对象，如果没有数据帧则返回null对象指针。
			 */
			inline virtual csf_mdframe_ptr pop_frame() {

				csf_mdframe_ptr tmp_ptr;

				get_queue().pop_front(tmp_ptr);

				return tmp_ptr;
			}
			/**
			* 主要功能：
			*    查询收集器的元素总个数。
			* 返回：
			*    >=0表示元素的总个数。
			*/
			inline virtual csf_int32 size() {
				return get_queue().size();
			}
		private:
			/**
			* 表示通道的uuid，用于唯一标识一个通道
			*/
			inline void set_guid();
		private:
			/**
			 * 表示通道的uuid，用于唯一标识一个通道
			 */
			char m_guid[128] = { 0, };
			/**
			 * 表示通道的名称，用于描述通道
			 */
			char m_name[128] = { 0, };
			/**
			 * 表示当前媒体帧对象指针
			 */
			csf_csfdeque<csf_mdframe_ptr> m_queue;
			/**
			 * 表示当前媒体帧对象指针
			 */
			inline csf_csfdeque<csf_mdframe_ptr>& get_queue() {

				return m_queue;
			}

		};

	}

}
#endif // !defined(CSF_MDSLOT_H_INCLUDED_)
