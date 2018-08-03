/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_csftype.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 30-6��-2018 10:06:03
*
*Description: Class(csf_csftype)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CSFTYPE_INCLUDED_)
#define CSF_CSFTYPE_INCLUDED_

#include "csf_null_interface.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * ��ʾcsf����Ļ����������͡�
			 * @author f
			 * @version 1.0
			 * @created 30-6��-2018 10:06:03
			 */
			class csf_csftype : public csf::core::base::csf_null_interface
			{

			public:
				csf_csftype();
				virtual ~csf_csftype();

				/**
				 * ��ʾ�ж��Ƿ�Ϊ�ա�
				 * ���أ�true��ʾΪ�գ�false��ʾ��Ϊ�ա�
				 */
				inline virtual csf_bool is_null() {

					return csf_true;
				}
				/**
				 * ��ʾ�ж��Ƿ�Ϊ�ա�
				 * ���أ�true��ʾ��Ϊ�գ�false��ʾΪ�ա�
				 */
				inline virtual csf_bool not_null() {

					return csf_true;
				}

			};

		}

	}

}
#endif // !defined(CSF_CSFTYPE_INCLUDED_)
