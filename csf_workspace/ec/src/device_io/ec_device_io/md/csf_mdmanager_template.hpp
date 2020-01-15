/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mdmanager_template.hpp
*
*Version: 1.0
*
*Date: 02-12月-2019 18:32:56
*
*Description: Class(csf_mdmanager_template) 表示媒体相关管理器模块
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MDMANAGER_TEMPLATE_H_INCLUDED_)
#define CSF_MDMANAGER_TEMPLATE_H_INCLUDED_

#include <iostream>
#include "csf_csfmap.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示媒体相关管理器模块
		 * @author f
		 * @version 1.0
		 * @created 02-12月-2019 18:32:56
		 */
		template<typename TypeName>
		class csf_mdmanager_template
		{

		public:
			csf_mdmanager_template() {

			}

			virtual ~csf_mdmanager_template() {

			}

			/**
			 * 功能：根据名称，将媒体通道添加到管理表中
			 * 返回：true表示成功；false表示失败；
			 * 
			 * @param name    表示当前媒体通道在通道管理器中对应的名称
			 * @param item    表示需要被添加的对象
			 */
			inline bool add(std::string name, TypeName* item) {
				get_items().insert(name, item);
				return true;
			}
			/**
			 * 功能：表示删除指定名称的媒体通道
			 * 返回：true表示成功；false表示失败；
			 * 
			 * @param name    表示需要被删除的媒体通道名称
			 */
			inline bool del(std::string name) {
				get_items().remove(name);
				return true;
			}
			/**
			 * 功能：表示需要查找的对象
			 * 返回：如果查找到，则返回对象指针；如果查找失败，则返回为空；
			 * 
			 * @param name    表示需要被删除的媒体通道名称
			 */
			inline TypeName* find(std::string name) {

				TypeName	*tmp_value = NULL;

				if (csf_true == get_items().find(tmp_value, name)) {
					return tmp_value;
				}

				return NULL;
			}

		private:
			/**
			 * 表示管理器中的各个对象
			 */
			csf_csfmap<std::string, TypeName*> m_items;

			/**
			 * 表示管理器中的各个对象
			 */
			csf_csfmap<std::string, TypeName*>& get_items() {
 
 				return m_items;
 			}

		};

	}

}

#endif // !defined(CSF_MDMANAGER_TEMPLATE_H_INCLUDED_)
