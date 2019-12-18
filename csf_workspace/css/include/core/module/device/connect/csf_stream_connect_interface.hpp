/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_stream_connect_interface.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:49
*
*Description: Interface(csf_stream_connect_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_STREAM_CONNECT_INTERFACE_INCLUDED_)
#define CSF_STREAM_CONNECT_INTERFACE_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * 表示数据流的操作接口
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:50
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

}
#endif // !defined(CSF_STREAM_CONNECT_INTERFACE_INCLUDED_)
