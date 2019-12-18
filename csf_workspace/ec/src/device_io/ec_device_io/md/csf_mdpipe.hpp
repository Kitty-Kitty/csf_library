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
*Date: 02-12月-2019 18:01:26
*
*Description: Class(csf_mdpipe) 表示媒体数据处理通道
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MDPIPE_H_INCLUDED_)
#define CSF_MDPIPE_H_INCLUDED_

#include "csf_mdslot.hpp"
#include "csf_mdpool.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示媒体数据处理通道
		 * @author f
		 * @version 1.0
		 * @created 02-12月-2019 18:01:26
		 */
		class csf_mdpipe
		{

		public:
			inline explicit csf_mdpipe()
				: csf_mdpipe(NULL, NULL) {

			}
			/**
			* 功能：
			*    根据数据槽类型和对象池创建通道
			*
			* @param mdslot    表示数据槽对象
			* @param mdpool    表示对象池对象
			*/
			inline explicit csf_mdpipe(csf_mdslot* mdslot, csf_mdpool* mdpool)
				: m_mdslot(m_mdslot)
				, m_mdpool(mdpool) {

			}
			virtual ~csf_mdpipe() {
				if (m_mdslot) {
					delete m_mdslot;
					m_mdslot = NULL;
				}
				if (m_mdpool) {
					delete m_mdpool;
					m_mdpool = NULL;
				}
			}

			/**
			* 表示当前媒体通道所包含的媒体处理槽
			*/
			inline csf_mdslot* get_mdslot() {

				return m_mdslot;
			}
			/**
			 * 表示当前媒体通道所包含的内存池
			 */
			inline csf_mdpool* get_mdpool() {

				return m_mdpool;
			}
			/**
			 * 表示当前媒体通道所包含的内存池
			 *
			 * @param newVal
			 */
			inline void set_mdpool(csf_mdpool* newVal) {

				m_mdpool = newVal;
			}
			/**
			* 表示当前媒体通道所包含的媒体处理槽
			*
			* @param newVal
			*/
			inline void set_mdslot(csf_mdslot* newVal) {

				m_mdslot = newVal;
			}
		private:
			/**
			* 表示当前媒体通道所包含的媒体处理槽
			*/
			csf_mdslot* m_mdslot = NULL;
			/**
			 * 表示当前媒体通道所包含的内存池
			 */
			csf_mdpool* m_mdpool = NULL;

		};

	}

}
#endif // !defined(CSF_MDPIPE_H_INCLUDED_)
