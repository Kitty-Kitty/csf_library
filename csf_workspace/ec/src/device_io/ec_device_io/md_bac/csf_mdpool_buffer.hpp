/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mdpool_buffer.hpp
*
*Version: 1.0
*
*Date: 28-11月-2019 21:21:53
*
*Description: Class(csf_mdpool_buffer) 表示无锁对列实现的适合媒体流处理使用的内存池管理
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MDPOOL_BUFFER_H_INCLUDED_)
#define CSF_MDPOOL_BUFFER_H_INCLUDED_

#include <stdio.h>
#include <boost/lockfree/queue.hpp>
#include "csf_mdbuffer.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示无锁对列实现的适合媒体流处理使用的内存池管理
		 * @author f
		 * @version 1.0
		 * @updated 28-11月-2019 21:40:36
		 */
		class csf_mdpool_buffer
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
			inline explicit csf_mdpool_buffer(int buffer_size, int size)
				: m_buffer_size(0)
				, m_max_size(0)
				, m_used_count(0)
				, m_lager_count(0) {

			}

			virtual ~csf_mdpool_buffer() {

			}

			/**
			 * 表示当前内存池正常的内存大小。其中小于等于该数值大小时，分配内存大小为buffer_size；如果超过该buffer_size则表示为超大内存；
			 */
			inline unsigned int get_buffer_size() {

				return m_buffer_size;
			}
			/**
			 * 表示当前内存池正常的内存大小。其中小于等于该数值大小时，分配内存大小为buffer_size；如果超过该buffer_size则表示为超大内存；
			 *
			 * @param newVal
			 */
			inline void set_buffer_size(unsigned int newVal) {

				m_buffer_size = newVal;
			}
			/**
			* 表示内存池保留的最多内存数量。
			* 当内存块数量超过这个数量时，free的内存块将立即被释放；
			* 当没有超过这个数量，free的内存块不将立即释放，用于下次malloc时分配
			*/
			inline unsigned int get_max_size() {

				return m_max_size;
			}
			/**
			* 表示内存池保留的最多内存数量。
			* 当内存块数量超过这个数量时，free的内存块将立即被释放；
			* 当没有超过这个数量，free的内存块不将立即释放，用于下次malloc时分配
			*
			* @param newVal
			*/
			inline void set_max_size(unsigned int newVal) {

				m_max_size = newVal;
			}
			/**
			 * 表示内存池中正常大小的内存块数量计数
			 */
			inline int get_used_count() {

				return m_used_count;
			}
			/**
			 * 表示内存池中超大的内存块数量计数
			 */
			inline int get_lager_count() {

				return m_lager_count;
			}
			/**
			 * 功能：分配指定大小的内存块
			 * 返回：csf_mdbuffer 对象，描述该内存信息
			 *
			 * @param size    表示需要用于分配的内存大小
			 */
			csf_mdbuffer* mdalloc(unsigned int size);
			/**
			* 功能：释放之前分配的资源
			* 返回：无
			*
			* @param mdbuffer    表示需要被释放的mdbuffer对象
			*/
			void mdfree(csf_mdbuffer* mdbuffer);
			/**
			 * 功能：清除内存管理器中的所有内存对象，释放内存管理器中保存的所有内存
			 * 返回：无
			 */
			void clear();
		private:
			/**
			* 表示内存池中超大的内存块数量计数
			*
			* @param newVal
			*/
			inline void set_lager_count(int newVal) {

				m_lager_count = newVal;
			}
			/**
			* 表示内存池中正常大小的内存块数量计数
			*
			* @param newVal
			*/
			inline void set_used_count(int newVal) {

				m_used_count = newVal;
			}
			/**
			* 功能：销毁对象
			* 返回：无
			*
			* @param mdbuffer    表示需要被释放的mdbuffer对象
			*/
			inline void destroy(csf_mdbuffer* mdbuffer) {
				if (!mdbuffer) {
					return;
				}

				free(mdbuffer->get_buffer());
				delete mdbuffer;
			}
		private:
			/**
			 * 表示一个boost::lockfree::queue对象，用于保存已经分配的内存
			 */
			boost::lockfree::queue<csf_mdbuffer*> m_queue;
			/**
			 * 表示当前内存池正常的内存大小。其中小于等于该数值大小时，分配内存大小为buffer_size；如果超过该buffer_size则表示为超大内存；
			 */
			unsigned int m_buffer_size = 0;
			/**
			 * 表示内存池保留的最多内存数量。
			 * 当内存块数量超过这个数量时，free的内存块将立即被释放；
			 * 当没有超过这个数量，free的内存块不将立即释放，用于下次malloc时分配
			 */
			unsigned int m_max_size = 0;
			/**
			 * 表示内存池中正常大小的内存块数量计数
			 */
			std::atomic<int> m_used_count = 0;
			/**
			 * 表示内存池中超大的内存块数量计数
			 */
			std::atomic<int> m_lager_count = 0;

		};

	}

}
#endif // !defined(CSF_MDPOOL_BUFFER_H_INCLUDED_)
