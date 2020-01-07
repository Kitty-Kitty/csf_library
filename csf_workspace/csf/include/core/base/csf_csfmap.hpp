/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_csfmap.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:38
*
*Description: Class(csf_csfmap)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CSFMAP_INCLUDED_)
#define CSF_CSFMAP_INCLUDED_

#include <functional>
#include "csf_stdcollector.hpp"
#include "csf_collector.hpp"
#include "csf_mutex.hpp"
#include "csf_csftype_template.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * ��ʾcsf��װ��map����
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6��-2018 17:28:38
			 */
			template <class Tkey, class Tvalue>
			class csf_csfmap : public csf::core::base::csf_collector
			{
				typedef	typename csf_map<Tkey, Tvalue>::iterator		_map_iterator;
				typedef	typename csf_map<Tkey, Tvalue>::value_type		_map_value_type;
			public:
				/**
				* ��ʾģ�������б���Ϣ
				* @author fz
				* @version 1.0
				* @updated 12-7��-2018 16:20:57
				*/
				typedef enum csfmap_operation_enum
				{
					/**
					* ��ʾcsfmapδ֪״̬
					*/
					csfmap_operation_none = 0x00000000,
					/**
					* ��ʾcsfmap�˳�ѭ��
					*/
					csfmap_operation_break = 0x01000000,
					/**
					* ��ʾcsfmap����ѭ��
					*/
					csfmap_operation_return = 0x02000000,
					/**
					* ��ʾcsfmapɾ���ڵ�
					*/
					csfmap_operation_remove = 0x03000000,
					/**
					* ��ʾcsfmap����ѭ��
					*/
					csfmap_operation_continue = 0x04000000,
				} csfmap_operation;
			public:
				inline explicit csf_csfmap() {

				}
				inline virtual ~csf_csfmap() {
					
				}

			public:
				/**
				* ��ʾ����һ������
				*
				* @param key    ��ʾmap��key
				* @param val    ��ʾmap��value
				*/
				inline void insert(Tkey key, Tvalue val) {

					csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					m_map.insert(_map_value_type(key, val));
				}
				/**
				* ��ʾ����һ�����ݶ���
				*
				* @param key    ��ʾmap��key
				*/
				csf_bool get(Tvalue &value, Tkey key) {

					csf_bool				tmp_ret = csf_false;

					tmp_ret = find(value, key);
					if (csf_true == tmp_ret) {
						erase(key);
						return tmp_ret;
					}
					return tmp_ret;
				}
				/**
				* ��ʾ��ѯһ�����ݶ���
				*
				* @param key    ��ʾmap��key
				*/
				csf_bool find(Tvalue &value, Tkey key) {

					_map_iterator			tmp_iter;
					csf_bool				tmp_ret = csf_false;

					csf_shared_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					tmp_iter = m_map.find(key);
					if (tmp_iter != m_map.end()) {
						value = tmp_iter->second;
						return csf_true;
					}

					return csf_false;
				}
				/**
				* ��ʾ��ѯһ�����ݶ����Ƿ���ڣ����ڷ���true�������ڷ���false
				*
				* @param key    ��ʾmap��key
				*/
				inline csf_bool have_key(Tkey key) {

					_map_iterator		tmp_iter;

					csf_shared_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					tmp_iter = m_map.find(key);
					if (tmp_iter != m_map.end()) {
						return csf_true;
					}
					else {
						return csf_false;
					}
				}
				/**
				* ��ʾѭ��������������ڵ�����
				*
				* @param key    ��ʾmap��key
				*/
				void for_each(std::function<csfmap_operation(_map_iterator)> func) {

					_map_iterator			tmp_iter;
					csfmap_operation		tmp_operation = csfmap_operation_none;


					csf_shared_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					for (tmp_iter = m_map.begin(); tmp_iter != m_map.end(); )
					{
						tmp_operation = func(tmp_iter);
						switch (tmp_operation)
						{
						case csfmap_operation_break:
						case csfmap_operation_return:
						{
							return;
						}
						case csfmap_operation_remove:
						{
							m_map.erase(tmp_iter++);
						}
						break;
						default:
						{
							tmp_iter++;
						}
						break;
						}
					}
				}
				/**
				* ��ʾ����map����������
				*
				* @param key    ��ʾmap��key
				*/
				inline int size() {

					csf_shared_lock<decltype(m_mutex)> tmp_lock(m_mutex);
					return m_map.size();
				}
				/**
				* ��ʾ�����������
				*
				* @param key    ��ʾmap��key
				*/
				inline bool clear() {

					csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);
					m_map.clear();

					return csf_true;
				}
				/**
				* ��ʾ���һ��ָ��������
				*
				* @param key    ��ʾmap��key
				*/
				inline void remove(Tkey key) {
					erase(key);
				}
				/**
				* ��ʾ���һ��ָ��������
				*
				* @param key    ��ʾmap��key
				*/
				inline void erase(Tkey key) {

					csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

					m_map.erase(key);
				}

			protected:
				/**
				* ��ʾ��׼map����
				*/
				csf_map<Tkey, Tvalue>		m_map;
				/**
				* ��ʾ�̰߳�ȫʹ�õĻ���������
				*/
				csf_shared_mutex			m_mutex;
			};
		}
	}
}
#endif // !defined(CSF_CSFMAP_INCLUDED_)
