/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_dgram_connect_interface.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:41
*
*Description: Interface(csf_dgram_connect_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_DGRAM_CONNECT_INTERFACE_INCLUDED_)
#define CSF_DGRAM_CONNECT_INTERFACE_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * 表示数据报文操作接口
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:41
				 */
				class csf_dgram_connect_interface
				{

				public:
					csf_dgram_connect_interface() {

					}

					virtual ~csf_dgram_connect_interface() {

					}

				};

			}

		}

	}

}
#endif // !defined(CSF_DGRAM_CONNECT_INTERFACE_INCLUDED_)
