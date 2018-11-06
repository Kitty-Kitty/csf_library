/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fz
*
*File name: device_io_media_channel.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:34
*
*Description: Class(device_io_media_channel) 表示媒体通道信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(DEVICE_IO_MEDIA_CHANNEL_H_INCLUDED_)
#define DEVICE_IO_MEDIA_CHANNEL_H_INCLUDED_

#include "css_device_io.hpp"

namespace css
{
	namespace modules
	{
		namespace media_server
		{
			namespace device_io_media_channel
			{
				/**
				 * 表示媒体通道信息
				 * @author fz
				 * @version 1.0
				 * @created 07-10月-2018 16:50:34
				 */
				class device_io_media_channel : public css::core::css_device_io
				{

				public:
					device_io_media_channel();
					virtual ~device_io_media_channel();

					cf_int32 init();
					cf_int32 start();
					cf_int32 stop();

				};

			}

		}

	}

}
#endif // !defined(DEVICE_IO_MEDIA_CHANNEL_H_INCLUDED_)
