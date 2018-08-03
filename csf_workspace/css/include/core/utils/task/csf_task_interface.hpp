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
*Date: 19-7��-2018 20:11:51
*
*Description: Interface(csf_task_interface) ��ʾ����Ĳ����ӿ�
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_TASK_INTERFACE_INCLUDED_)
#define CSF_TASK_INTERFACE_INCLUDED_

#include "csf_typedef.h"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace task
			{
				/**
				 * ��ʾ����Ĳ����ӿ�
				 * @author f
				 * @version 1.0
				 * @created 19-7��-2018 20:11:51
				 */
				class csf_task_interface
				{

				public:
					csf_task_interface() {

					}

					virtual ~csf_task_interface() {

					}

					/**
					 * ��ʾ����ӿڣ���ֻ��is_process����true�����process��
					 */
					virtual csf_int32 process() =0;
					/**
					 * ��ʾ�Ƿ���д���,���is_process����true������ִ��process��
					 */
					virtual csf_bool is_process() =0;
					/**
					 * ��ʾ����ӿڣ���ֻ��is_delete����true�����process_delete��
					 */
					virtual csf_int32 process_delete() =0;
					/**
					 * �ж��Ƿ���Ҫɾ�������is_delete����true��ɾ��task��
					 */
					virtual csf_bool is_delete() =0;

				};

			}

		}

	}

}
#endif // !defined(CSF_TASK_INTERFACE_INCLUDED_)
