/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_dgram_connect_interface.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:42
*
*Description: Interface(csf_dgram_connect_interface) 表示数据报文操作接口
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_DGRAM_CONNECT_INTERFACE_H_INCLUDED_)
#define CSF_DGRAM_CONNECT_INTERFACE_H_INCLUDED_

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
			 * @created 01-10月-2018 12:54:42
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
#endif // !defined(CSF_DGRAM_CONNECT_INTERFACE_H_INCLUDED_)
