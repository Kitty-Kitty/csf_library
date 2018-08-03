/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_device_io_interface.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:40
*
*Description: Interface(csf_device_io_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_DEVICE_IO_INTERFACE_INCLUDED_)
#define CSF_DEVICE_IO_INTERFACE_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device_io
			{
				/**
				 * 表示设备io操作的抽象
				 * @author fangzhenmu@aliyun.com
				 * @version 1.0
				 * @created 27-6月-2018 17:28:40
				 */
				class csf_device_io_interface
				{

				public:
					csf_device_io_interface() {

					}

					virtual ~csf_device_io_interface() {

					}

				};

			}

		}

	}

}
#endif // !defined(CSF_DEVICE_IO_INTERFACE_INCLUDED_)
