/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fz
*
*File name: csf_hichannel_interface.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:50:14
*
*Description: Interface(csf_hichannel_interface) 表示海思处理作接口
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_HICHANNEL_INTERFACE_H_INCLUDED_)
#define CSF_HICHANNEL_INTERFACE_H_INCLUDED_

#include <iostream>

namespace ec
{
	namespace core
	{
		class csf_hiprocessor;
		class hichannel_conf;
		/**
		 * 表示海思处理作接口
		 * @author fz
		 * @version 1.0
		 * @created 03-12月-2019 13:50:14
		 */
		class csf_hichannel_interface
		{

		public:
			csf_hichannel_interface() {

			}

			virtual ~csf_hichannel_interface() {

			}

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
			virtual int init(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) =0;
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
			virtual int start(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) =0;
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
			virtual int stop(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) =0;

		};

	}

}
#endif // !defined(CSF_HICHANNEL_INTERFACE_H_INCLUDED_)
