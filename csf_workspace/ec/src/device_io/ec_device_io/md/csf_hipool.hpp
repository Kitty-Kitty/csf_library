/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_hipool.hpp
*
*Version: 1.0
*
*Date: 02-12月-2019 14:31:29
*
*Description: Class(csf_hipool) 表示海思音视频处理使用的对象池
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_HIPOOL_H_INCLUDED_)
#define CSF_HIPOOL_H_INCLUDED_

#include "csf_mdpool.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示海思音视频处理使用的对象池
		 * @author f
		 * @version 1.0
		 * @created 02-12月-2019 14:31:29
		 */
		class csf_hipool : public ec::core::csf_mdpool
		{

		public:
			/**
			* 指定参数创建对象池
			*
			* @param size    表示内存池保留的最多内存数量。
			* 当内存块数量超过这个数量时，free的内存块将立即被释放；
			* 当没有超过这个数量，free的内存块不将立即释放，用于下次malloc时分配
			* @param buffer_size    表示当前默认的内存大小
			*/
			inline explicit csf_hipool(unsigned int size, unsigned int buffer_size)
				: csf_mdpool(size)
				, m_buffer_size(buffer_size) {

			}

			virtual ~csf_hipool() {

			}

			/**
			* 功能：创建一个资源对象
			* 返回：一个资源对象
			*
			* @param buffer_size    表示需要创建内存空间大小
			*/
			virtual csf_mdobject* create(unsigned int buffer_size);
			/**
			* 功能：释放资源对象
			* 返回：无
			*
			* @param mdobject    表示需要被释放的MDObjectTyper对象
			*/
			virtual void destroy(csf_mdobject* mdobject);

			/**
			* 表示默认的内存空间大小
			*/
			inline unsigned int get_buffer_size() {

				return m_buffer_size;
			}
			/**
			* 表示默认的内存空间大小
			*
			* @param newVal
			*/
			inline void set_buffer_size(unsigned int newVal) {

				m_buffer_size = newVal;
			}

		protected:
			/**
			* 功能：创建一个资源对象
			* 返回：成功则一个资源对象指针；失败则返回空
			*
			* @param size    表示当前帧数据长度
			*/
			virtual csf_mdobject* create_object(unsigned int size);
			/**
			 * 功能：销毁一个资源对象
			 * 返回：无
			 *
			 * @param mdobject
			 */
			virtual void destroy_object(csf_mdobject* mdobject);
		private:
			/**
			* 功能：
			*    校验mdobject对象是否合法，满足需求。其中合法的标准为：内存大小是否大于需求大小。如果大于需求大小，则表示合法；其他为不合法；
			* 返回：
			*    true：表示满足需求，合法
			*    false：表示不满足需求，不合法
			*
			* @param mdobject    表示需要被释放的MDObjectTyper对象
			* @param size
			*/
			bool check_valid(csf_mdobject* mdobject, unsigned int size);
		private:
			/**
			* 表示默认的内存空间大小
			*/
			unsigned int m_buffer_size = 0;
		};

	}

}
#endif // !defined(CSF_HIPOOL_H_INCLUDED_)
