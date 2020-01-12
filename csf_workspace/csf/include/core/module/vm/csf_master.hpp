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
#include "csf_default.h"
#include "csf_shared_memory.hpp"
#include "csf_vm.hpp"

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
				/**
				 *
				 * @param argc    表示当前程序的运行参数个数
				 *
				 * @param argv    表示当前运行参数数值内容
				 */
				explicit csf_master(int argc, char** argv)
					: m_argc(argc)
					, m_argv(argv) {

				}
				virtual ~csf_master() {

				}
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
			protected:

				/**
				 * 表示当前程序的运行参数个数
				 */
				inline int get_argc() {

					return m_argc;
				}


				/**
				 * 表示当前程序的运行参数个数
				 *
				 * @param newVal
				 */
				inline void set_argc(int newVal) {

					m_argc = newVal;
				}


				inline char** get_argv() {

					return m_argv;
				}


				/**
				 *
				 * @param newVal
				 */
				inline void set_argv(char** newVal) {

					m_argv = newVal;
				}
				/**
				 * 表示主机包含的虚拟机对象
				 */
				inline csf_vm* get_vm() {

					return m_vm;
				}
				/**
				 * 表示主机包含的虚拟机对象
				 *
				 * @param newVal
				 */
				inline void set_vm(csf_vm* newVal) {

					m_vm = newVal;
				}
				/**
				 * 功能：
				 *    处理当前进程的输入参数信息。
				 * 返回：
				 *    0   ：表示成功；
				 *    非0 ：表示失败；
				 */
				csf::core::base::csf_int32 process_option();
				/**
				 * 功能：
				 *    初始化共享内存资源
				 * 返回：
				 *    true  :  表示成功；
				 *    false :  表示失败；
				 */
				csf_bool init_shared_memory();
			private:
				/**
				 * 表示当前vm对象使用的共享内存
				 */
				inline csf_shared_memory& get_sm() {

					return m_sm;
				}
				/**
				 * 表示当前主机的名称
				 */
				inline csf_string get_name() {

					return m_name;
				}
				/**
				 * 表示当前主机的名称
				 *
				 * @param newVal
				 */
				inline void set_name(csf_string newVal) {

					m_name = newVal;
				}
			private:
				/**
				 * 表示当前vm对象使用的共享内存
				 */
				csf::core::module::csf_shared_memory m_sm;
				/**
				 * 表示当前程序的运行参数个数
				 */
				int m_argc = 0;
				/**
				 * 表示当前运行参数数值内容
				 */
				char** m_argv = nullptr;
				/**
				 * 表示主机包含的虚拟机对象
				 */
				csf_vm* m_vm = csf_nullptr;
				/**
				 * 表示当前主机的名称
				 */
				csf_string m_name = "";

			};

		}

	}

}
#endif // !defined(CSF_MASTER_H_INCLUDED_)
