/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_stream_connect_interface.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:53
*
*Description: Interface(csf_stream_connect_interface) 表示数据流的操作接口
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_STREAM_CONNECT_INTERFACE_H_INCLUDED_)
#define CSF_STREAM_CONNECT_INTERFACE_H_INCLUDED_

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * 表示数据流的操作接口
			 * @author f
			 * @version 1.0
			 * @created 01-10月-2018 12:54:53
			 */
			class csf_stream_connect_interface
			{

			public:
				csf_stream_connect_interface() {

				}

				virtual ~csf_stream_connect_interface() {

				}

			};

		}

	}

}
#endif // !defined(CSF_STREAM_CONNECT_INTERFACE_H_INCLUDED_)
