/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mdslot_cover.hpp
*
*Version: 1.0
*
*Date: 04-12月-2019 15:30:32
*
*Description: Class(csf_mdslot_cover) 表示支持覆盖的媒体数据槽。该槽主要特点是存在一个最大数量字。当槽中数据对象个数超过这个数字时，需要删除所有已经存在的对象。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MDSLOT_COVER_H_INCLUDED_)
#define CSF_MDSLOT_COVER_H_INCLUDED_

#include "csf_mdslot.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示支持覆盖的媒体数据槽。该槽主要特点是存在一个最大数量字。当槽中数据对象个数超过这个数字时，需要删除所有已经存在的对象。
		 * @author f
		 * @version 1.0
		 * @created 04-12月-2019 15:30:32
		 */
		class csf_mdslot_cover : public ec::core::csf_mdslot
		{

		public:
			csf_mdslot_cover();
			virtual ~csf_mdslot_cover();

			/**
			 * 根据名称创建一个媒体流槽
			 * 
			 * @param name    表示媒体流数据槽的名称
			 * @param max    表示媒体数据槽中的最大对象数量
			 */
			inline explicit csf_mdslot_cover(std::string name, unsigned int max = 64)
				: csf_mdslot(name)
				, m_max_size(max) {

			}
			/**
			 * 表示当前媒体槽中最多允许保存的对象数量
			 */
			inline unsigned int get_max_size() {

				return m_max_size;
			}
			/**
			 * 表示当前媒体槽中最多允许保存的对象数量
			 * 
			 * @param newVal
			 */
			inline void set_max_size(unsigned int newVal) {

				m_max_size = newVal;
			}
			/**
			 * 功能：向通道中发送媒体数据帧
			 * 返回：true表示发送成功；false表示发送失败；
			 * 
			 * @param object    表示需要添加的媒体对象
			 */
			inline virtual bool push_frame(csf_mdobject* object) {

				if (isfull()) {
					clear();
				}

				return csf_mdslot::push_frame(object);
			}
			/**
			* 功能：
			*    判断是否已经达到最大数量
			* 返回：
			*    true ： 表示已经达到最大数量，已经满了
			*    false： 表示还没有达到最大数量，还可以插入
			*/
			inline bool isfull() {
				if (size() >= (int)get_max_size()) {
					return true;
				}
				return false;
			}
		private:
			/**
			 * 表示当前媒体槽中最多允许保存的对象数量
			 */
			unsigned int m_max_size = 64;

		};

	}

}
#endif // !defined(CSF_MDSLOT_COVER_H_INCLUDED_)
