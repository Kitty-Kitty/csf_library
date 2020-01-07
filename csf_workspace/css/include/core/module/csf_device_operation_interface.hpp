/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_device_operation_interface.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:40
*
*Description: Interface(csf_device_operation_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_DEVICE_OPERATION_INTERFACE_INCLUDED_)
#define CSF_DEVICE_OPERATION_INTERFACE_INCLUDED_

#include "csf_typedef.h"
#include "csf_stdbind.hpp"
#include "csf_element.hpp"

using namespace csf::core::base;
using namespace csf::core::system;

namespace csf
{
	namespace core
	{
		namespace module
		{
			//��ʾ�쳣����ص�����
			typedef csf_function<csf_int32(csf_element& element)>	csf_device_operation_callback;
			/**
			 * ��ʾ�豸�����ӿ�
			 * @author f
			 * @version 1.0
			 * @created 27-6��-2018 17:28:40
			 */
			class csf_device_operation_interface
			{

			public:
				csf_device_operation_interface() {

				}

				virtual ~csf_device_operation_interface() {

				}

				/**
				 * ��ʾ�豸����Ӳ���
				 * 
				 * @param element    ��ʾ�豸��Ӳ���
				 * @param callback    ��ʾ�豸�����Ļص�����
				 */
				virtual csf_int32 del(const csf_element& element, const csf_device_operation_callback callback) =0;
				/**
				 * ��ʾ�豸����Ӳ���
				 * 
				 * @param element    ��ʾ�豸��Ӳ���
				 * @param callback    ��ʾ�豸�����Ļص�����
				 */
				virtual csf_int32 ctrl(const csf_element& element, const csf_device_operation_callback callback) =0;
				/**
				 * ��ʾ�豸����Ӳ���
				 * 
				 * @param element    ��ʾ�豸��Ӳ���
				 * @param callback    ��ʾ�豸�����Ļص�����
				 */
				virtual csf_int32 update(const csf_element& element, const csf_device_operation_callback callback) =0;
				/**
				 * ��ʾ�豸����Ӳ���
				 * 
				 * @param element    ��ʾ�豸��Ӳ���
				 * @param callback    ��ʾ�豸�����Ļص�����
				 */
				virtual csf_int32 add(const csf_element& element, const csf_device_operation_callback callback) =0;

			};

		}

	}

}
#endif // !defined(CSF_DEVICE_OPERATION_INTERFACE_INCLUDED_)
