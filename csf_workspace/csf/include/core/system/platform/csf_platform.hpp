/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_platform.hpp
*
*Version: 1.0
*
*Date: 07-1月-2020 13:49:55
*
*Description: Class(csf_platform) 描述系统信息类，主要获取系统相关的信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_PLATFORM_H_INCLUDED_)
#define CSF_PLATFORM_H_INCLUDED_

#include "csf_typedef.h"
#include "csf_system_interface.hpp"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace platform
			{
				/**
				 * 描述系统信息类，主要获取系统相关的信息
				 * @author f
				 * @version 1.0
				 * @updated 07-1月-2020 14:14:17
				 */
				class csf_platform : public csf::core::system::platform::csf_system_interface
				{

				public:
					csf_platform();
					virtual ~csf_platform();
					/**
					 * 功能：
					 *    使用程序文件所在的目录作为工作目录，设置程序运行的工作目录
					 * 返回：
					 *    0   ：表示成功；
					 *    非0 ：表示失败；
					 */
					static csf_int32 set_work_directory() {
						return set_work_directory(current_path());
					}
					/**
					 * 功能：
					 *    设置程序运行的工作目录
					 * 返回：
					 *    0   ：表示成功；
					 *    非0 ：表示失败；
					 * 
					 * @param newVal    表示工作目录地址
					 */
					static csf_int32 set_work_directory(csf_string newVal);
					/**
					 * 功能：
					 *    获取当前程序所在的目录地址
					 * 返回：
					 *    当前程序存放目录地址字符串，如果获取失败，则目录地址字符串为空。
					 */
					static csf_string current_path();
					/**
					 * 功能：
					 *    获取当前进程的PID数值，用于记录使用
					 * 返回：
					 *    返回当前进程的PID数值，成功则返回非0；失败则返回0；
					 */
					static csf_uint32 get_pid();
					/**
					 * 功能：
					 *    保存pid等信息到文件中
					 * 返回：
					 *    csf_true  ：  表示保存pid信息成功；
					 *    csf_false ：  表示保存pid信息失败；
					 *
					 * @param file    表示需要将信息保存的目的文件地址
					 */
					static csf_bool save_pid(csf_string file);
				};

			}

		}

	}

}
#endif // !defined(CSF_PLATFORM_H_INCLUDED_)
