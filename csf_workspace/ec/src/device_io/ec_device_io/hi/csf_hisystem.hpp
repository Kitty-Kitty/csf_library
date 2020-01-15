/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_hisystem.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 20:29:46
*
*Description: Class(csf_hisystem) 表示海思系统处理类
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_HISYSTEM_H_INCLUDED_)
#define CSF_HISYSTEM_H_INCLUDED_

#include "hisys_conf.hpp"

namespace ec
{
	namespace core
	{
		class csf_hiprocessor;
		/**
		 * 表示海思系统处理类
		 * @author f
		 * @version 1.0
		 * @created 03-12月-2019 20:29:46
		 */
		class csf_hisystem
		{

		public:
			csf_hisystem();
			virtual ~csf_hisystem();

			/**
			 * 功能：
			 *    初始化通道
			 * 返回：
			 *    0   ：表示成功
			 *    非0 ：表示失败
			 * 
			 * @param hiproc    表示海思处理模块对象
			 * @param hiconf    表示海思通道配置信息
			 */
			virtual int init(csf_hiprocessor* hiproc, const hisys_conf* hiconf);
			/**
			 * 功能：
			 *    启动通道
			 * 返回：
			 *    0   ：表示成功
			 *    非0 ：表示失败
			 * 
			 * @param hiproc    表示海思处理模块对象
			 * @param hiconf    表示海思通道配置信息
			 */
			virtual int start(csf_hiprocessor* hiproc, const hisys_conf* hiconf);
			/**
			 * 功能：
			 *    停止通道
			 * 返回：
			 *    0   ：表示成功
			 *    非0 ：表示失败
			 * 
			 * @param hiproc    表示海思处理模块对象
			 * @param hiconf    表示海思通道配置信息
			 */
			virtual int stop(csf_hiprocessor* hiproc, const hisys_conf* hiconf);

		protected:
			/**
			 * 功能：
			 *    初始化系统
			 * 返回：
			 *    0   ：表示成功
			 *    非0 ：表示失败
			 * 
			 * @param hiproc    表示海思处理模块对象
			 * @param hiconf    表示海思通道配置信息
			 */
			virtual int init_system(csf_hiprocessor* hiproc, const hisys_conf* hiconf);
			/**
			 * 功能：
			 *    退出系统
			 * 返回：
			 *    0   ：表示成功
			 *    非0 ：表示失败
			 * 
			 * @param hiproc    表示海思处理模块对象
			 * @param hiconf    表示海思通道配置信息
			 */
			virtual int exit_system(csf_hiprocessor* hiproc, const hisys_conf* hiconf);
			/**
			* 功能：
			*    打印系统信息
			* 返回：
			*    0   ：表示成功
			*    非0 ：表示失败
			*
			* @param hiproc    表示海思处理模块对象
			* @param hiconf    表示海思系统配置信息
			*/
			virtual void print_system(csf_hiprocessor* hiproc, const hisys_conf* hiconf);
			/**
			* 功能：
			*    判断系统是否已经在线
			* 返回：
			*    true ：表示在线
			*    false：表示离线
			*/
			virtual bool is_system_online();
			/**
			* 功能：
			*    初始化 MPP 的时间戳基准
			*/
			virtual void init_pts_base();
			/**
			* 功能：
			*    设置系统的配置类型
			* 返回：
			*    0   ：表示成功
			*    非0 ：表示失败
			*
			* @param hiproc    表示海思处理模块对象
			* @param hiconf    表示海思系统配置信息
			*/
			virtual int set_profile(csf_hiprocessor* hiproc, const hisys_conf* hiconf);
		};

	}

}
#endif // !defined(CSF_HISYSTEM_H_INCLUDED_)
