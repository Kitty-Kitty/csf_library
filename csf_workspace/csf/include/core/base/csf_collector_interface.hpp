/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_collector_interface.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:35
*
*Description: Interface(csf_collector_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_COLLECTOR_INTERFACE_INCLUDED_)
#define CSF_COLLECTOR_INTERFACE_INCLUDED_

#include "csf_typedef.h"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * ��ʾ�ռ��������ӿ�
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6��-2018 17:28:35
			 */
			class csf_collector_interface
			{

			public:
				csf_collector_interface() {

				}

				virtual ~csf_collector_interface() {

				}

				/**
				 * ��ѯ�ռ�����Ԫ���ܸ�����
				 * ���أ�>=0��ʾԪ�ص��ܸ�����
				 */
				virtual csf_int32 size() const =0;
				/**
				 * ��ʾ����ռ����е�����Ԫ��
				 */
				virtual csf_bool clear() =0;

			};

		}

	}

}
#endif // !defined(CSF_COLLECTOR_INTERFACE_INCLUDED_)
