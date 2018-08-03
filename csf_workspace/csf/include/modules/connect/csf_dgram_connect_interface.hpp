/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: f
*
*Author: fz
*
*Version: 1.0
*
*Date: 29-7月-2018 15:13:08
*
*Description: Interface(csf_dgram_connect_interface) 表示数据报文操作接口
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_DGRAM_CONNECT_INTERFACE_INCLUDED_)
#define CSF_DGRAM_CONNECT_INTERFACE_INCLUDED_

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * 表示数据报文操作接口
			 * @author f
			 * @version 1.0
			 * @created 29-7月-2018 15:13:08
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
#endif // !defined(CSF_DGRAM_CONNECT_INTERFACE_INCLUDED_)
