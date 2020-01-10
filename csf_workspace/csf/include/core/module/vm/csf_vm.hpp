/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: Administrator
*
*File name: csf_vm.hpp
*
*Version: 1.0
*
*Date: 10-1月-2020 14:50:43
*
*Description: Class(csf_vm) 表示csf的虚拟主机。
这是新引入的模块类型，主要处理app上一层次内容，充当一种容器角色。其目的是释放app概念，让app、device、device_io能够的用于业务处理。
csf_vm的处理逻辑相对固定，主要初始化环境操作，为系统运行搭建最基础的环境。例如：初始日志系统、解析配置文件等。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_VM_H_INCLUDED_)
#define CSF_VM_H_INCLUDED_

#include "csf_app.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			class csf_slave;
			/**
			 * 表示csf的虚拟主机。
			 * 这是新引入的模块类型，主要处理app上一层次内容，充当一种容器角色。其目的是释放app概念，让app、device、device_io能够的用于业务处理。
			 * csf_vm的处理逻辑相对固定，主要初始化环境操作，为系统运行搭建最基础的环境。例如：初始日志系统、解析配置文件等。
			 * @author Administrator
			 * @version 1.0
			 * @created 10-1月-2020 14:50:43
			 */
			class csf_vm : public csf::core::module::csf_app
			{

			public:
				csf_vm();
				virtual ~csf_vm();

				/**
				 * 功能：
				 *    模块初始化，进行模块启动前的准备工作。
				 * 返回：
				 *    0   ：表示成功
				 *    非0 ：表示失败
				 * 
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * 功能：
				 *    模块启动，进行模块启动工作。表示模块已经正常运行。
				 * 返回：
				 *    0   ：表示成功
				 *    非0 ：表示失败
				 * 
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * 功能：
				 *    模块停止，进行模块停止工作。释放模块初始化、运行时创建的资源。
				 * 返回：
				 *    0   ：表示成功
				 *    非0 ：表示失败
				 * 
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);

			private:
				/**
				 * 表示当前已经运行的客户进程
				 */
				csf_slave* m_slaves[64] = {csf_nullptr, };

			};

		}

	}

}
#endif // !defined(CSF_VM_H_INCLUDED_)
