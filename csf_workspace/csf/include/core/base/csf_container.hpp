/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_container.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6��-2018 17:01:18
*
*Description: Class(csf_container)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONTAINER_INCLUDED_)
#define CSF_CONTAINER_INCLUDED_

#include "csf_container_interface.hpp"
#include "csf_csftype_template.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * ��ʾ���з�collector��ĸ������
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6��-2018 17:01:18
			 */
			class csf_container : public csf::core::base::csf_container_interface
				, public csf::core::base::csf_csftype_template<csf_container>
			{

			public:
				csf_container() {

				}
				virtual ~csf_container() {

				}

				/**
				 * ��ʾ�����Ƿ�Ϊ�գ�Ϊ�շ���true,���򷵻�false������Ϊ0��nullΪ�գ�����true��
				 */
				inline virtual csf_bool empty() const {

					return csf_true;
				}
				/**
				 * ��ʾ��ȡ������ʵ�����ݳ��ȣ�û������Ϊ0
				 */
				inline virtual csf_uint32 length() const {

					return 0;
				}
				/**
				 * ��ʾ��ȡ�����Ŀռ䳤�ȡ�û��Ԥ�����ڴ���࣬��size=length������csf_string��length=size����Ԥ�����ڴ���࣬size>=lengt
				 * h������csf_buffer��size>=length��
				 */
				inline virtual csf_uint32 size() const {

					return 0;
				}
				/**
				 * ��ʾ�����������Щ����Ҫ�ͷſռ䣨���磺csf_chain������Щ�ռ�����õ�������������(���磺csf_buffer)��
				 */
				inline virtual csf_void clear() {

				}
				/**
				* ��ʾ�ж��Ƿ�Ϊ�ա�
				* ���أ�true��ʾΪ�գ�false��ʾ��Ϊ�ա�
				*/
				inline virtual csf_bool is_null() const {

					return csf_true;
				}
				/**
				* ��ʾ�ж��Ƿ�Ϊ�ա�
				* ���أ�true��ʾ��Ϊ�գ�false��ʾΪ�ա�
				*/
				inline virtual csf_bool not_null() const {

					return csf_true;
				}
			};

		}

	}

}
#endif // !defined(CSF_CONTAINER_INCLUDED_)
