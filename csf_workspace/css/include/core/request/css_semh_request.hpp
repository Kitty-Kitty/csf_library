/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_semh_request.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:31
*
*Description: Class(css_semh_request) ��ʾsemh����ṹ��
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_SEMH_REQUEST_H_INCLUDED_)
#define CSS_SEMH_REQUEST_H_INCLUDED_

#include "css_request.hpp"
#include "prot_gmp_core.h"

namespace css
{
	namespace core
	{
		/**
		 * ��ʾsemh����ṹ��
		 * @author f
		 * @version 1.0
		 * @created 07-10��-2018 16:50:31
		 */
		class css_semh_request : public css::core::css_request
		{

		public:
			css_semh_request();
			virtual ~css_semh_request();

			/**
			 * ��ʾsemh�ṹ������
			 */
			gmp_gmph_semh_t* get_semh();
			/**
			 * ��ʾsemh�ṹ������
			 * 
			 * @param newVal
			 */
			void set_semh(gmp_gmph_semh_t* newVal);
			/**
			 * ��ʾgmf�ṹ������
			 */
			gmp_gmf_t* get_gmf();
			/**
			 * ��ʾgmf�ṹ������
			 * 
			 * @param newVal
			 */
			void set_gmf(gmp_gmf_t* newVal);

		private:
			/**
			 * ��ʾsemh�ṹ������
			 */
			gmp_gmph_semh_t* m_semh = csf_null;
			/**
			 * ��ʾgmf�ṹ������
			 */
			gmp_gmf_t* m_gmf = csf_null;

		};

	}

}
#endif // !defined(CSS_SEMH_REQUEST_H_INCLUDED_)
