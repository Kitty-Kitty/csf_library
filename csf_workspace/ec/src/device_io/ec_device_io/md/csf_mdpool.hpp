/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mdpool.hpp
*
*Version: 1.0
*
*Date: 02-12月-2019 12:20:35
*
*Description: Class(csf_mdpool) 表示媒体池处理类型
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MDPOOL_H_INCLUDED_)
#define CSF_MDPOOL_H_INCLUDED_

#include <stdio.h>
#include <atomic>
#include <boost/lockfree/queue.hpp>


#include "csf_mdpool_interface.hpp"
#include "csf_mdobject.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示媒体池处理类型
		 * @author f
		 * @version 1.0
		 * @created 02-12月-2019 12:20:35
		 */
		class csf_mdpool : public ec::core::csf_mdpool_interface
		{

		public:
			/**
			 *
			 * @param size    表示内存池保留的最多内存数量。
			 * 当内存块数量超过这个数量时，free的内存块将立即被释放；
			 * 当没有超过这个数量，free的内存块不将立即释放，用于下次malloc时分配
			 */
			inline explicit csf_mdpool(unsigned int size)
				: m_queue(0)
				, m_max_size(size)
				, m_used_count(0)
				, m_lager_count(0) {

			}
			virtual ~csf_mdpool() {

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
			 * 功能：创建一个资源对象
			 * 返回：一个资源对象
			 */
			virtual csf_mdobject* create();
			/**
			 * 功能：释放资源对象
			 * 返回：无
			 *
			 * @param mdobject    表示需要被释放的MDObjectTyper对象
			 */
			virtual void destroy(csf_mdobject* mdobject);
			/**
			 * 功能：清除内存管理器中的所有内存对象，释放内存管理器中保存的所有内存
			 * 返回：无
			 */
			void clear();
		protected:
			/**
			* 功能：创建一个资源对象
			* 返回：成功则一个资源对象指针；失败则返回空
			*/
			virtual csf_mdobject* create_object() { return NULL; }
			/**
			* 功能：销毁一个资源对象
			* 返回：无
			*
			* @param mdobject
			*/
			virtual void destroy_object(csf_mdobject* mdobject) {}
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
			* 表示一个boost::lockfree::queue对象，用于保存已经分配的内存
			*/
			inline boost::lockfree::queue<csf_mdobject*>& get_queue() {

				return m_queue;
			}
		private:
			/**
			 * 表示一个boost::lockfree::queue对象，用于保存已经分配的内存
			 */
			boost::lockfree::queue<csf_mdobject*> m_queue;
			/**
			 * 表示内存池保留的最多内存数量。
			 * 当内存块数量超过这个数量时，free的内存块将立即被释放；
			 * 当没有超过这个数量，free的内存块不将立即释放，用于下次malloc时分配
			 */
			unsigned int m_max_size = 0;
			/**
			 * 表示内存池中正常大小的内存块数量计数
			 */
			std::atomic<int> m_used_count{ 0 };
			/**
			 * 表示内存池中超大的内存块数量计数
			 */
			std::atomic<int> m_lager_count{ 0 };
		};
	}

}
#endif // !defined(CSF_MDPOOL_H_INCLUDED_)
