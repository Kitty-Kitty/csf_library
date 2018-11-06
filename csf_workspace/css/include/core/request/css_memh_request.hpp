/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_memh_request.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:29
*
*Description: Class(css_memh_request) ��ʾmemh����������
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_MEMH_REQUEST_H_INCLUDED_)
#define CSS_MEMH_REQUEST_H_INCLUDED_

#include "css_request.hpp"

namespace css
{
	namespace core
	{
		/**
		 * ��ʾmemh����������
		 * @author f
		 * @version 1.0
		 * @created 07-10��-2018 16:50:29
		 */
		class css_memh_request : public css::core::css_request
		{

		public:
			css_memh_request();
			virtual ~css_memh_request();

			/**
			 * ��ʾmemh�ṹ������
			 */
			gmp_gmph_memh_t* get_memh();
			/**
			 * ��ʾmemh�ṹ������
			 * 
			 * @param newVal
			 */
			void set_memh(gmp_gmph_memh_t* newVal);

		private:
			/**
			 * ��ʾmemh�ṹ������
			 */
			gmp_gmph_memh_t* m_memh = csf_null;

		};

	}

}
#endif // !defined(CSS_MEMH_REQUEST_H_INCLUDED_)
