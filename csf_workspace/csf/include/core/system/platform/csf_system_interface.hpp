/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_system_interface.hpp
*
*Version: 1.0
*
*Date: 07-1月-2020 13:49:55
*
*Description: Interface(csf_system_interface) 表示系统的操作接口
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_SYSTEM_INTERFACE_H_INCLUDED_)
#define CSF_SYSTEM_INTERFACE_H_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace platform
			{
				/**
				 * 表示系统的操作接口
				 * @author f
				 * @version 1.0
				 * @created 07-1月-2020 13:49:56
				 */
				class csf_system_interface
				{

				public:
					csf_system_interface() {

					}

					virtual ~csf_system_interface() {

					}

				};

			}

		}

	}

}
#endif // !defined(CSF_SYSTEM_INTERFACE_H_INCLUDED_)
