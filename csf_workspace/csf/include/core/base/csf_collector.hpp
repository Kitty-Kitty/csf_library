/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_collector.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:35
*
*Description: Class(csf_collector)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_COLLECTOR_INCLUDED_)
#define CSF_COLLECTOR_INCLUDED_

#include "csf_collector_interface.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * ��ʾ�ռ���������
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6��-2018 17:28:35
			 */
			class csf_collector : public csf::core::base::csf_collector_interface
			{

			public:
				csf_collector() {

				}

				virtual ~csf_collector() {

				}

				/**
				 * ��ѯ�ռ�����Ԫ���ܸ�����
				 * ���أ�>=0��ʾԪ�ص��ܸ�����
				 */
				virtual csf_int32 size() const {

					return 0;
				}
				/**
				 * ��ʾ����ռ����е�����Ԫ��
				 */
				virtual csf_bool clear() {

					return csf_true;
				}

			};

		}

	}

}
#endif // !defined(CSF_COLLECTOR_INCLUDED_)
