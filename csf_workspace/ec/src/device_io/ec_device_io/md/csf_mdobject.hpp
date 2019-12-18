/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mdobject.hpp
*
*Version: 1.0
*
*Date: 02-12月-2019 12:20:34
*
*Description: Interface(csf_mdobject) 表示保存数据的媒体源数据对象
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MDOBJECT_H_INCLUDED_)
#define CSF_MDOBJECT_H_INCLUDED_

#include <stdio.h>
#include "csf_mdobject_interface.hpp"

namespace ec
{
	namespace core
	{
		class csf_mdpool;
		/**
		 * 表示媒体帧数据内容对象。
		 * @author f
		 * @version 1.0
		 * @updated 02-12月-2019 14:08:03
		 */
		class csf_mdobject : public ec::core::csf_mdobject_interface
		{
		public:
			csf_mdobject()
				: m_mdpool(NULL) {

			}
			/**
			* 功能：
			*    根据对象缓存池创建对象
			*
			* @param pool
			*/
			inline explicit csf_mdobject(csf_mdpool* pool)
				: m_mdpool(pool) {

			}

			virtual ~csf_mdobject() {

			}

			/**
			 * 功能：表示媒体数据对象销毁接口
			 * 返回：无
			 */
			virtual void destroy() = 0;
			/**
			 * 功能：重新初始化媒体数据对象
			 * 返回：无
			 */
			virtual void reset() = 0;
			/**
			 * 表示对象所属的对象池指针
			 */
			inline csf_mdpool* get_mdpool() {

				return m_mdpool;
			}
			/**
			 * 表示对象所属的对象池指针
			 *
			 * @param newVal
			 */
			inline void set_mdpool(csf_mdpool* newVal) {

				m_mdpool = newVal;
			}
		private:
			/**
			* 表示对象所属的对象池指针
			*/
			csf_mdpool* m_mdpool = NULL;

		};

	}

}
#endif // !defined(CSF_MDOBJECT_H_INCLUDED_)
