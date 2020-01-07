/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_socket.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:49
*
*Description: Class(csf_socket)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_SOCKET_INCLUDED_)
#define CSF_SOCKET_INCLUDED_

#include "csf_connect.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * ��ʾsocket����ͨ�ſ�����
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 27-6��-2018 17:28:49
			 */
			class csf_socket : public csf::core::module::device::csf_connect
			{

			public:
				csf_socket();
				virtual ~csf_socket();

				cf_int32 init();
				cf_int32 start();
				cf_int32 stop();

			};

		}

	}

}
#endif // !defined(CSF_SOCKET_INCLUDED_)
