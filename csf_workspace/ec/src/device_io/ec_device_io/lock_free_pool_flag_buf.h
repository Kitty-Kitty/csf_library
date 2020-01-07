


/**************************************************************************

Copyright:compony

Version:0.1.0.0

Author:fangzhenmu@compony.com.cn

Date:2015-05-25 16:04:45

Description:��Ҫʵ�ִ����ڴ�ص�flag_buf

**************************************************************************/




#ifndef	_LOCK_FREE_POOL_FLAG_BUFFER_INCLUDE_H_
#define _LOCK_FREE_POOL_FLAG_BUFFER_INCLUDE_H_





#include <stdio.h>
#include <boost/lockfree/queue.hpp>
#include "data_type.h"
#include "mutex.h"







class			lock_free_pool_manager_class;
class			lock_free_pool_flag_buffer_class;






typedef			lock_free_pool_manager_class						lock_free_pool_manager;
typedef			lock_free_pool_flag_buffer_class					lock_free_pool_flag_buf;






typedef			lock_free_pool_manager_class*					lock_free_pool_manager_p;
typedef			lock_free_pool_flag_buffer_class*				lock_free_pool_flag_buf_p;






#define			DEFAULT_PAGE_SIZE								4096
#define			lock_free_queue									boost::lockfree::queue





class lock_free_pool_manager_class
{
public:
	/******************************************************************************************************
	* ��Ȩ����:fz & compony
	* ��������:���ڴ�ع���
	* ��    ��:
	*			����Ǽ򵥵��ڴ����ģ��
	* ��    ��:
	*			1��int							size					[in]��ʾÿ���ڴ��Ĵ�С
	*			2��int							max_number				[in]��ʾ��󻺴���ڴ�����
	* �� �� ֵ:
	*			bool
	*			ȡֵ˵��:
	*					true : �ɹ�
	*					false: ʧ��
	* ��    ע:
	*
	* ��    ��:fz
	* ��������:fangzhenmu@compony.com.cn
	* ��������:2015-08-25 14:04:47
	******************************************************************************************************/
	lock_free_pool_manager_class(int size, int max_number)
		: m_size(size)
		, m_max_number(max_number)
		, m_current_number(0)
		, m_free_number(0)
		, m_lager_number(0)
		, m_free_buffer_queue(0)
	{

	}

	~lock_free_pool_manager_class()
	{
		clear();
	}

public:
	/******************************************************************************************************
	* ��Ȩ����:fz & compony
	* ��������:�ڴ�ط��亯��
	* ��    ��:
	*			���ݴ�С�������ڴ�
	* ��    ��:
	*			1��int							size						[in]��ʾ��Ҫ������ڴ��С
	*			2��int							&ret_size					[out]��ʾ���ص�ʵ�ʷ�����ڴ��С
	
	* �� �� ֵ:
	*			char*
	*			ȡֵ˵��:
	*					��NULL : �ɹ� 
	*					NULL: ʧ��
	* ��    ע:
	*			
	* ��    ��:fz
	* ��������:fangzhenmu@compony.com.cn
	* ��������:2015-08-25 15:20:33
	******************************************************************************************************/
	char*	pool_malloc(int size, int &ret_size)
	{
		char*					p = NULL;



		if (size <= 0)
		{
			ret_size = 0;
			return NULL;
		}

		if (size > m_size)
		{
			//����һ�����ڴ��
			p = (char*)malloc(size);
			if (!p)
			{
				ret_size = 0;
				return NULL;
			}
			else
			{
				ret_size = size;
				++m_lager_number;
				return p;
			}
		}
		else
		{
			//���С��Ĭ�ϵĴ�С,�����ӻ����л�ȡ
			if (m_free_buffer_queue.pop(p))
			{
				ret_size = m_size;
				--m_free_number;
				return p;
			}
			else
			{
				//��������б�û�У������·���һ���ڴ��
				p = (char*)malloc(m_size);
				if (!p)
				{
					ret_size = 0;
					return NULL;
				}
				else
				{
					++m_current_number;
					ret_size = m_size;
					return p;
				}
			}
		}
	}

	/******************************************************************************************************
	* ��Ȩ����:fz & compony
	* ��������:��������
	* ��    ��:
	*			���������Ĺ�����Ϣ
	* ��    ��:
	*			1��char*						p						[in]��ʾ��Ҫ���ͷŵ��ڴ�ָ��
	*			2��int							size					[in]��ʾ��ʱ��������ڴ��С
	
	* �� �� ֵ:
	*			bool
	*			ȡֵ˵��:
	*					true : �ɹ� 
	*					false: ʧ��
	* ��    ע:
	*			
	* ��    ��:fz
	* ��������:fangzhenmu@compony.com.cn
	* ��������:2015-08-25 15:29:56
	******************************************************************************************************/
	bool	pool_free(char* p, int size)
	{
		if (!p || size <= 0)
		{
			return false;
		}

		if (size > m_size)
		{
			free(p);
			--m_lager_number;
		}
		else
		{
			if (m_current_number > m_max_number && m_free_number > 0)
			{
				free(p);
				--m_current_number;
			}
			else
			{
				m_free_buffer_queue.push(p);
				++m_free_number;
			}
		}
				
		return true;
	}

	/******************************************************************************************************
	* ��Ȩ����:fz & compony
	* ��������:reset
	* ��    ��:
	*			���������ڴ��������С
	* ��    ��:
	*			1��int							size					[in]��ʾÿ���ڴ��Ĵ�С
	*			2��int							max_number				[in]��ʾ��󻺴���ڴ�����
	* �� �� ֵ:
	*			bool
	*			ȡֵ˵��:
	*					true : �ɹ� 
	*					false: ʧ��
	* ��    ע:
	*			�ú���Ϊ����ȫ������ֻ�Ƿ����ڴ�δʹ��ʱ�����������ò��������ڴ汻ʹ�ú����ý�ʧ�ܣ�
	*			������������ڴ�ص�ʹ�����̣�ֻ�Ƿ������ò������мɲ����ڴ�ر�ʹ�ú���ô˺���
	* ��    ��:fz
	* ��������:fangzhenmu@compony.com.cn
	* ��������:2015-08-25 15:35:35
	******************************************************************************************************/
	bool	reset(int size, int max_number)
	{
		if (m_current_number > 0)
		{
			return false;
		}
		else
		{
			m_size = size;
			m_current_number = 0;
		}

		return true;
	}

	/******************************************************************************************************
	* ��Ȩ����:fz & compony
	* ��������:clear
	* ��    ��:
	*			��������е�����
	* ��    ��:
	* �� �� ֵ:
	*			bool
	*			ȡֵ˵��:
	*					true : �ɹ� 
	*					false: ʧ��
	* ��    ע:
	*			
	* ��    ��:fz
	* ��������:fangzhenmu@compony.com.cn
	* ��������:2015-08-26 11:53:28
	******************************************************************************************************/
	bool	clear()
	{
		char*					p = NULL;
		int						i = 0;


		while (m_free_buffer_queue.pop(p))
		{
			if (p)
			{
				free(p);
			}

			--m_free_number;
			--m_current_number;
			--m_lager_number;
			p = NULL;
		}

		for (i = m_lager_number; i > 0; i--) {
			p = NULL;
			m_free_buffer_queue.pop(p);

			if (p)
			{
				free(p);
			}
		}

		return true;
	}
private:
	int													m_size;									//��ʾ��ǰ���õ��ڴ�ؿ�Ĵ�С
	int													m_max_number;							//��ʾ��󱣴���ڴ������
	atomic_int											m_current_number;						//��ǰ������ڴ������
	atomic_int											m_free_number;							//��ǰ����Ŀ��е��ڴ������
	atomic_int											m_lager_number;							//��ǰ����Ĵ���ڴ������
	boost::lockfree::queue<char*>						m_free_buffer_queue;					//���еĶ���
};



class lock_free_pool_flag_buffer_class
{
public:
	lock_free_pool_flag_buffer_class(lock_free_pool_manager_p lock_free_pool_manager_p, int len)
		: m_buf_p(NULL)
		, m_start_p(NULL)
		, m_pos_p(NULL)
		, m_last_p(NULL)
		, m_end_p(NULL)
		, m_lock_free_pool_manager_p(lock_free_pool_manager_p)
		, m_size(0)
	{
		int						ret_size = 0;



		m_buf_p = lock_free_pool_manager_p->pool_malloc(len, ret_size);
		if (!m_buf_p)
		{
			throw "pool malloc failed";
		}

		m_start_p = m_buf_p;
		m_pos_p = m_buf_p;
		m_last_p = m_buf_p;
		m_end_p = m_buf_p + ret_size;
		m_size = ret_size;
	}

	~lock_free_pool_flag_buffer_class()
	{
		m_lock_free_pool_manager_p->pool_free(m_buf_p, m_size);
	}

public:
	inline bool clear()
	{
		if (!m_buf_p)
		{
			return false;
		}

		m_start_p = m_buf_p;
		m_pos_p = m_buf_p;
		m_last_p = m_buf_p;

		return true;
	}

	inline int copy(char* p, int len)
	{
		if (!p || len <= 0 || !m_buf_p)
		{
			return 0;
		}

		if (len > m_size)
		{
			len = m_size;
		}

		memcpy(m_buf_p, p, len);
		m_pos_p = m_buf_p;
		m_last_p = m_buf_p + len;

		return len;
	}

	inline int cat(char* p, int len)
	{
		if (!p || len <= 0 || !m_buf_p)
		{
			return 0;
		}

		if (len > (m_end_p - m_last_p))
		{
			len = (m_end_p - m_last_p);
		}

		memcpy(m_last_p, p, len);
		m_last_p = m_last_p + len;

		return len;
	}

	inline int length()
	{
		return (m_last_p - m_pos_p);
	}

	inline int size()
	{
		return m_size;
	}

	inline int free_size()
	{
		return (m_end_p - m_last_p);
	}

	inline char* get_buf()
	{
		return m_pos_p;
	}

public:
	char*							m_buf_p;
	char*							m_start_p;
	char*							m_pos_p;
	char*							m_last_p;
	char*							m_end_p;
	lock_free_pool_manager_p		m_lock_free_pool_manager_p;
	int								m_size;
};


#endif


