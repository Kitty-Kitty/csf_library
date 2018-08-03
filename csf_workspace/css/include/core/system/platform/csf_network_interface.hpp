/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_network_interface.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:47
*
*Description: Interface(csf_network_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_NETWORK_INTERFACE_INCLUDED_)
#define CSF_NETWORK_INTERFACE_INCLUDED_

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
				 * @created 27-6月-2018 17:28:47
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
#endif // !defined(CSF_NETWORK_INTERFACE_INCLUDED_)
