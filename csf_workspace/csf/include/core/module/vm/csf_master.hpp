/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: Administrator
*
*File name: csf_master.hpp
*
*Version: 1.0
*
*Date: 10-1月-2020 14:50:42
*
*Description: Class(csf_master) 表示csf的虚拟主机。
这是新引入的模块类型，主要处理app上一层次内容，充当一种容器角色。其目的是释放app概念，让app、device、device_io能够的用于业务处理。
csf_vm的处理逻辑相对固定，主要初始化环境操作，为系统运行搭建最基础的环境。例如：初始日志系统、解析配置文件等。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MASTER_H_INCLUDED_)
#define CSF_MASTER_H_INCLUDED_

#include "csf_typedef.h"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示csf的虚拟主机。
			 * 这是新引入的模块类型，主要处理app上一层次内容，充当一种容器角色。其目的是释放app概念，让app、device、device_io能够的用于业务处理。
			 * csf_vm的处理逻辑相对固定，主要初始化环境操作，为系统运行搭建最基础的环境。例如：初始日志系统、解析配置文件等。
			 * @author Administrator
			 * @version 1.0
			 * @created 10-1月-2020 14:50:42
			 */
			class csf_master
			{

			public:
				csf_master();
				virtual ~csf_master();
				/**
				 * 功能：
				 *    模块初始化，进行模块启动前的准备工作。
				 * 返回：
				 *    0   ：表示成功
				 *    非0 ：表示失败
				 * 
				 */
				virtual csf::core::base::csf_int32 init();
				/**
				 * 功能：
				 *    模块启动，进行模块启动工作。表示模块已经正常运行。
				 * 返回：
				 *    0   ：表示成功
				 *    非0 ：表示失败
				 * 
				 */
				virtual csf::core::base::csf_int32 start();
				/**
				 * 功能：
				 *    模块停止，进行模块停止工作。释放模块初始化、运行时创建的资源。
				 * 返回：
				 *    0   ：表示成功
				 *    非0 ：表示失败
				 * 
				 */
				virtual csf::core::base::csf_int32 stop();
				
			private:

			};

		}

	}

}
#endif // !defined(CSF_MASTER_H_INCLUDED_)
