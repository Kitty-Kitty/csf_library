/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_container_interface.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6��-2018 16:45:40
*
*Description: Interface(csf_container_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONTAINER_INTERFACE_INCLUDED_)
#define CSF_CONTAINER_INTERFACE_INCLUDED_

#include "csf_typedef.h"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * ��ʾ���з�collector��ĸ������Ĳ����ӿ�
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6��-2018 16:45:40
			 */
			class csf_container_interface
			{

			public:
				csf_container_interface() {

				}

				virtual ~csf_container_interface() {

				}

				/**
				 * ��ʾ�����Ƿ�Ϊ�գ�Ϊ�շ���true,���򷵻�false������Ϊ0��nullΪ�գ�����true��
				 */
				virtual csf_bool empty() =0;
				/**
				 * ��ʾ��ȡ������ʵ�����ݳ��ȣ�û������Ϊ0
				 */
				virtual csf_uint32 length() =0;
				/**
				 * ��ʾ��ȡ�����Ŀռ䳤�ȡ�û��Ԥ�����ڴ���࣬��size=length������csf_string��length=size����Ԥ�����ڴ���࣬size>=lengt
				 * h������csf_buffer��size>=length��
				 */
				virtual csf_uint32 size() =0;
				/**
				 * ��ʾ�����������Щ����Ҫ�ͷſռ䣨���磺csf_chain������Щ�ռ�����õ�������������(���磺csf_buffer)��
				 */
				virtual csf_void clear() =0;

			};

		}

	}

}
#endif // !defined(CSF_CONTAINER_INTERFACE_INCLUDED_)
