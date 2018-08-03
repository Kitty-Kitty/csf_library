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
*Date: 29-7月-2018 15:13:18
*
*Description: Interface(csf_stream_connect_interface) 表示数据流的操作接口
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_STREAM_CONNECT_INTERFACE_INCLUDED_)
#define CSF_STREAM_CONNECT_INTERFACE_INCLUDED_

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
			 * @created 29-7月-2018 15:13:19
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
#endif // !defined(CSF_STREAM_CONNECT_INTERFACE_INCLUDED_)
