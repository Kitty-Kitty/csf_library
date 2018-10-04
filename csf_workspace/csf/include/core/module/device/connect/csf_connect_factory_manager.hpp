/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_connect_factory_manager.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:37
*
*Description: Class(csf_connect_factory_manager) ��ʾ���ӹ���������
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_FACTORY_MANAGER_H_INCLUDED_)
#define CSF_CONNECT_FACTORY_MANAGER_H_INCLUDED_

#include "csf_connect.hpp"
#include "csf_connect_factory_manager_interface.hpp"
#include "csf_manager.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * ��ʾ���ӹ���������
				 * @author f
				 * @version 1.0
				 * @created 01-10��-2018 12:54:37
				 */
				class csf_connect_factory_manager : public csf::core::module::csf_manager
					, public csf::core::module::connect::csf_connect_factory_manager_interface
				{

				public:
					csf_connect_factory_manager();
					virtual ~csf_connect_factory_manager();

					/**
					 * ģ���ʼ��
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
					/**
					 * ģ������
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_nullptr);
					/**
					 * ģ��ֹͣ
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);
					/**
					* ��ʾ���ӹ�������������Ķ����б�
					*/
					inline csf_unordered_map<csf_string, csf_connect_factory_ptr>& get_factories() {

						return m_factories;
					}
					/**
					* ��ʾͨ�������ļ����������Ӷ��󱣴�Ķ����б�
					*/
					inline csf_unordered_map<csf_string, csf_connect_ptr>& get_connectes() {

						return m_connectes;
					}
				private:
					/**
					* ��ʾ���ӹ�������������Ķ����б�
					*/
					csf_unordered_map<csf_string, csf_connect_factory_ptr> m_factories;
					/**
					* ��ʾͨ�������ļ����������Ӷ��󱣴�Ķ����б�
					*/
					csf_unordered_map<csf_string, csf_connect_ptr> m_connectes;
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_FACTORY_MANAGER_H_INCLUDED_)
