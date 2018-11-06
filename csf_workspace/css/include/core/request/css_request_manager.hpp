/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_request_manager.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:30
*
*Description: Class(css_request_manager) 表示请求管理器，主要处理各种请求内容
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_REQUEST_MANAGER_H_INCLUDED_)
#define CSS_REQUEST_MANAGER_H_INCLUDED_

#include "csf_manager.hpp"

namespace css
{
	namespace core
	{
		/**
		 * 表示请求管理器，主要处理各种请求内容
		 * @author f
		 * @version 1.0
		 * @created 07-10月-2018 16:50:30
		 */
		class css_request_manager : public csf::core::module::csf_manager
		{

		public:
			css_request_manager();
			virtual ~css_request_manager();

			/**
			 * 模块初始化
			 * 
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
			/**
			 * 模块启动
			 * 
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
			/**
			 * 模块停止
			 * 
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
			/**
			 * 表示请求队列
			 */
			inline csf_csfqueue<css_request> get_request_queue() {

				return m_request_queue;
			}
			/**
			 * 表示请求队列
			 * 
			 * @param newVal
			 */
			inline csf_void set_request_queue(const csf_csfqueue<css_request>& newVal) {

				m_request_queue = newVal;
			}
			/**
			 * 表示请求处理function列表
			 */
			inline csf_map<css_semh_command, css_semh_request_function> get_semh_request_function() {

				return m_semh_request_function;
			}
			/**
			 * 表示线程处理函数，主要从队列中获取请求进行处理
			 */
			csf_void process();
			/**
			 * 表示请求处理function列表
			 * 
			 * @param newVal
			 */
			inline csf_void set_semh_request_function(const csf_map<css_semh_command, css_semh_request_function> newVal) {

				m_semh_request_function = newVal;
			}

		private:
			/**
			 * 表示请求队列
			 */
			csf_csfqueue<css_request> m_request_queue;
			/**
			 * 表示请求处理function列表
			 */
			csf_map<css_semh_command, css_semh_request_function> m_semh_request_function;

		};

	}

}
#endif // !defined(CSS_REQUEST_MANAGER_H_INCLUDED_)
