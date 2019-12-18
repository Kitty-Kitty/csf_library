/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mdobject_interface.hpp
*
*Version: 1.0
*
*Date: 02-12月-2019 14:07:53
*
*Description: Interface(csf_mdobject_interface) 表示保存数据的媒体源数据对象操作接口
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MDOBJECT_INTERFACE_H_INCLUDED_)
#define CSF_MDOBJECT_INTERFACE_H_INCLUDED_

namespace ec
{
	namespace core
	{
		/**
		 * 表示保存数据的媒体源数据对象操作接口
		 * @author f
		 * @version 1.0
		 * @created 02-12月-2019 14:07:53
		 */
		class csf_mdobject_interface
		{

		public:
			csf_mdobject_interface() {

			}

			virtual ~csf_mdobject_interface() {

			}

			/**
			 * 功能：表示媒体数据对象销毁接口
			 * 返回：无
			 */
			virtual void destroy() =0;
			/**
			 * 功能：重新初始化媒体数据对象
			 * 返回：无
			 */
			virtual void reset() =0;

		};

	}

}
#endif // !defined(CSF_MDOBJECT_INTERFACE_H_INCLUDED_)
