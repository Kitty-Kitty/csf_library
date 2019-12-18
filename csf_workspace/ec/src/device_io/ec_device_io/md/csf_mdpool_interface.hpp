/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mdpool_interface.hpp
*
*Version: 1.0
*
*Date: 02-12月-2019 12:20:35
*
*Description: Interface(csf_mdpool_interface) 表示csf_mdpool操作接口
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MDPOOL_INTERFACE_H_INCLUDED_)
#define CSF_MDPOOL_INTERFACE_H_INCLUDED_

namespace ec
{
	namespace core
	{
		class csf_mdobject;
		/**
		 * 表示csf_mdpool操作接口
		 * @author f
		 * @version 1.0
		 * @created 02-12月-2019 12:20:35
		 */
		class csf_mdpool_interface
		{

		public:
			csf_mdpool_interface() {

			}

			virtual ~csf_mdpool_interface() {

			}

			/**
			 * 功能：清空csf_mdpool的所有资源
			 * 返回：无
			 */
			virtual void clear() = 0;
		protected:
			/**
			* 功能：创建一个资源对象
			* 返回：成功则一个资源对象指针；失败则返回空
			*/
			virtual csf_mdobject* create_object() = 0;
			/**
			* 功能：销毁一个资源对象
			* 返回：无
			*
			* @param mdobject
			*/
			virtual void destroy_object(csf_mdobject* mdobject) = 0;
		};

	}

}
#endif // !defined(CSF_MDPOOL_INTERFACE_H_INCLUDED_)
