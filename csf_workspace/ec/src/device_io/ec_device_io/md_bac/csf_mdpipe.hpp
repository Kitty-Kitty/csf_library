/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mdpipe.hpp
*
*Version: 1.0
*
*Date: 30-11月-2019 16:44:05
*
*Description: Class(csf_mdpipe) 表示媒体数据通道，能用于临时保存媒体数据。其中媒体数据生产端源源不断插入到媒体流数据通道中，同时媒体数据消费者源源不断从媒体流数据通道中取出。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MDPIPE_H_INCLUDED_)
#define CSF_MDPIPE_H_INCLUDED_

#include "csf_mdpipe_interface.hpp"
#include "csf_mdframe.hpp"
#include "csf_mdpool.hpp"
#include "csf_csfdeque.hpp"

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
		class csf_mdpipe : public ec::core::csf_mdpipe_interface
		{

		public:
			/**
			 *
			 * @param buffer_size
			 * 表示当前内存池正常的内存大小。其中小于等于该数值大小时，分配内存大小为buffer_size；如果超过该buffer_size则表示为超大内存；
			 *
			 * @param size    表示内存池保留的最多内存数量。
			 * 当内存块数量超过这个数量时，free的内存块将立即被释放；
			 * 当没有超过这个数量，free的内存块不将立即释放，用于下次malloc时分配
			 */
			inline explicit csf_mdpipe(unsigned int buffer_size, unsigned int size)
				: m_guid{ 0, }
				, m_name{ 0, }
				, m_mdpool(buffer_size, size) {

				//每一个通道都有一个唯一的标识id
				set_guid();
			}
			virtual ~csf_mdpipe() {

			}
			/**
			 * 表示通道的uuid，用于唯一标识一个通道
			 */
			inline std::string get_guid() {

				return m_guid;
			}
			/**
			 * 表示当前内存池正常的内存大小。其中小于等于该数值大小时，分配内存大小为buffer_size；如果超过该buffer_size则表示为超大内存；
			 */
			inline unsigned int get_buffer_size() {

				return get_mdpool().get_buffer_size();
			}
			/**
			 * 表示通道的名称，用于描述通道
			 */
			inline std::string get_name() {

				return m_name;
			}
			/**
			 * 表示当前内存池正常的内存大小。其中小于等于该数值大小时，分配内存大小为buffer_size；如果超过该buffer_size则表示为超大内存；
			 *
			 * @param newVal
			 */
			inline void set_buffer_size(unsigned int newVal) {

				get_mdpool().set_buffer_size(newVal);
			}
			/**
			 * 表示内存池保留的最多内存数量。
			 * 当内存块数量超过这个数量时，free的内存块将立即被释放；
			 * 当没有超过这个数量，free的内存块不将立即释放，用于下次malloc时分配
			 */
			inline unsigned int get_max_size() {

				return get_mdpool().get_max_size();
			}
			/**
			 * 表示通道的名称，用于描述通道
			 *
			 * @param newVal
			 */
			inline void set_name(std::string newVal) {

				if (newVal.length() > sizeof(m_name)) {
					csf_strncpy(m_name, newVal.c_str(), sizeof(m_name));
				}
				else {
					csf_strncpy(m_name, newVal.c_str(), newVal.length());
				}
			}
			/**
			 * 表示内存池保留的最多内存数量。
			 * 当内存块数量超过这个数量时，free的内存块将立即被释放；
			 * 当没有超过这个数量，free的内存块不将立即释放，用于下次malloc时分配
			 *
			 * @param newVal
			 */
			inline void set_max_size(unsigned int newVal) {

				m_mdpool.set_max_size(newVal);
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
			 * @param data    表示需要发送的媒体数据帧数据
			 * @param len    表示需要发送的数据长度
			 */
			bool push_frame(unsigned char* data, unsigned int len);
			/**
			 * 功能：获取当前数据帧
			 * 返回：返回数据帧对象，如果没有数据帧则返回null对象指针。
			 */
			csf_mdframe_ptr pop_frame() {

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
			 * 当前通道使用的内存池对象，媒体数据保存的内存就是由内存池分配的
			 */
			csf_mdpool m_mdpool;

			/**
			 * 表示当前媒体帧对象指针
			 */
			inline csf_csfdeque<csf_mdframe_ptr>& get_queue() {

				return m_queue;
			}
			/**
			 * 当前通道使用的内存池对象，媒体数据保存的内存就是由内存池分配的
			 */
			inline csf_mdpool& get_mdpool() {

				return m_mdpool;
			}

		};

	}

}
#endif // !defined(CSF_MDPIPE_H_INCLUDED_)
