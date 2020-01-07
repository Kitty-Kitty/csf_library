/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_manager_interface.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 06-7��-2018 19:09:43
*
*Description: Interface(csf_attribute_manager_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_MANAGER_INTERFACE_INCLUDED_)
#define CSF_ATTRIBUTE_MANAGER_INTERFACE_INCLUDED_

#include "csf_typedef.h"
#include "csf_attribute.hpp"

using namespace csf::core::base;
using namespace csf::core::system::attribute;

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/**
				 * �������Թ������Ĳ����ӿڣ���Ҫ������ɾ���顢�ĵȡ�
				 * @author fz
				 * @version 1.0
				 * @created 06-7��-2018 19:09:43
				 */
				class csf_attribute_manager_interface
				{

				public:
					csf_attribute_manager_interface() {

					}

					virtual ~csf_attribute_manager_interface() {

					}

					/**
					 * ��������Ϊ����attribute_manager�����һ�����ԡ�
					 * ע�⣺��ʾ��ӵ��������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ����������ʧ�ܡ�
					 * ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
					 * 
					 * @param name    ��ʾ��ӵ��������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ���
					 * @param attribute    ��ʾ��ӵ����Զ���
					 */
					virtual csf_bool add(const csf_string& name, csf_attribute& attribute) =0;
					/**
					 * ��������Ϊ����attribute_manager�����һ�����ԡ�
					 * ע�⣺��ʾ��ӵ��������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ����������ʧ�ܡ�
					 * ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
					 * 
					 * @param name    ��ʾ��ӵ��������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ���
					 * @param attribute    ��ʾ��ӵ����Զ���
					 */
					virtual csf_bool add(const csf_char* name, csf_attribute& attribute) =0;
					/**
					 * ��������Ϊ���������ƴ�attribute_manager��ɾ��һ�����ԡ�
					 * ���أ�true��ʾɾ���ɹ��������ڸ���������Ĭ�Ϸ��سɹ�����false��ʾʧ�ܡ�
					 * 
					 * @param name    ��ʾ��Ҫɾ������������
					 */
					virtual csf_bool del(const csf_string& name) =0;
					/**
					 * ��������Ϊ���������ƴ�attribute_manager��ɾ��һ�����ԡ�
					 * ���أ�true��ʾɾ���ɹ��������ڸ���������Ĭ�Ϸ��سɹ�����false��ʾʧ�ܡ�
					 * 
					 * @param name    ��ʾ��Ҫɾ������������
					 */
					virtual csf_bool del(const csf_char* name) =0;
					/**
					 * ��������Ϊ���������ƴ�attribute_manager�в�ѯһ�����ԡ�
					 * ���أ�һ�����Զ���
					 * 
					 * @param name    ��ʾ��������
					 */
					virtual const csf_attribute& find(const csf_string& name) =0;
					/**
					 * ��������Ϊ���������ƴ�attribute_manager�в�ѯһ�����ԡ�
					 * ���أ�һ�����Զ���
					 * 
					 * @param name    ��ʾ��Ҫ����������
					 */
					virtual const csf_attribute& find(const csf_char* name) =0;
					/**
					 * ��������Ϊ������attribute_manager��һ��������Ϣ��
					 * ���أ�true��ʾ�����Ҹ��³ɹ���false��ʾ�����ڻ�ʧ�ܡ�
					 * 
					 * @param name    ��ʾ�������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ���
					 * @param attribute    ��ʾ���Զ���
					 */
					virtual csf_bool update(const csf_string& name, csf_attribute& attribute) =0;
					/**
					 * ��������Ϊ������attribute_manager��һ��������Ϣ��
					 * ���أ�true��ʾ�����Ҹ��³ɹ���false��ʾ�����ڻ�ʧ�ܡ�
					 * 
					 * @param name    ��ʾ�������ƣ���һ��attribute_manager�б��뱣֤Ψһ���ظ���
					 * @param attribute    ��ʾ���Զ���
					 */
					virtual csf_bool update(const csf_char* name, csf_attribute& attribute) =0;

				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_MANAGER_INTERFACE_INCLUDED_)
