/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_process_interface.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:47
*
*Description: Interface(csf_process_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_PROCESS_INTERFACE_INCLUDED_)
#define CSF_PROCESS_INTERFACE_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * 表示进程操作接口对象
				 * @author fangzhenmu@aliyun.com
				 * @version 1.0
				 * @created 27-6月-2018 17:28:47
				 */
				class csf_process_interface
				{

				public:
					csf_process_interface() {

					}

					virtual ~csf_process_interface() {

					}

				};

			}

		}

	}

}
#endif // !defined(CSF_PROCESS_INTERFACE_INCLUDED_)
