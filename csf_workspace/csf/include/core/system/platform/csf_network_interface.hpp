/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_network_interface.hpp
*
*Version: 1.0
*
*Date: 07-1月-2020 13:49:55
*
*Description: Interface(csf_network_interface) 表示网络的操作接口
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_NETWORK_INTERFACE_H_INCLUDED_)
#define CSF_NETWORK_INTERFACE_H_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace platform
			{
				/**
				 * 表示网络的操作接口
				 * @author f
				 * @version 1.0
				 * @created 07-1月-2020 13:49:55
				 */
				class csf_network_interface
				{

				public:
					csf_network_interface() {

					}

					virtual ~csf_network_interface() {

					}

				};

			}

		}

	}

}
#endif // !defined(CSF_NETWORK_INTERFACE_H_INCLUDED_)
