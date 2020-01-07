


/**************************************************************************

Copyright:compony

Version:0.1.0.0

Author:fangzhenmu@compony.com.cn

Date:2015-05-25 16:04:45

Description:主要实现带有内存池的flag_buf

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
	* 版权所有:fz & compony
	* 方法名称:简单内存池管理
	* 功    能:
	*			这个是简单的内存管理模块
	* 参    数:
	*			1、int							size					[in]表示每个内存块的大小
	*			2、int							max_number				[in]表示最大缓存的内存数量
	* 返 回 值:
	*			bool
	*			取值说明:
	*					true : 成功
	*					false: 失败
	* 备    注:
	*
	* 作    者:fz
	* 电子邮箱:fangzhenmu@compony.com.cn
	* 创建日期:2015-08-25 14:04:47
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
	* 版权所有:fz & compony
	* 方法名称:内存池分配函数
	* 功    能:
	*			根据大小来分配内存
	* 参    数:
	*			1、int							size						[in]表示需要分配的内存大小
	*			2、int							&ret_size					[out]表示返回的实际分配的内存大小
	
	* 返 回 值:
	*			char*
	*			取值说明:
	*					非NULL : 成功 
	*					NULL: 失败
	* 备    注:
	*			
	* 作    者:fz
	* 电子邮箱:fangzhenmu@compony.com.cn
	* 创建日期:2015-08-25 15:20:33
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
			//分配一个大内存块
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
			//如果小于默认的大小,则尽量从缓存中获取
			if (m_free_buffer_queue.pop(p))
			{
				ret_size = m_size;
				--m_free_number;
				return p;
			}
			else
			{
				//如果空闲列表没有，则重新分配一个内存块
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
	* 版权所有:fz & compony
	* 方法名称:方法名称
	* 功    能:
	*			描述方法的功能信息
	* 参    数:
	*			1、char*						p						[in]表示需要被释放的内存指针
	*			2、int							size					[in]表示当时被申请的内存大小
	
	* 返 回 值:
	*			bool
	*			取值说明:
	*					true : 成功 
	*					false: 失败
	* 备    注:
	*			
	* 作    者:fz
	* 电子邮箱:fangzhenmu@compony.com.cn
	* 创建日期:2015-08-25 15:29:56
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
	* 版权所有:fz & compony
	* 方法名称:reset
	* 功    能:
	*			重新设置内存管理器大小
	* 参    数:
	*			1、int							size					[in]表示每个内存块的大小
	*			2、int							max_number				[in]表示最大缓存的内存数量
	* 返 回 值:
	*			bool
	*			取值说明:
	*					true : 成功 
	*					false: 失败
	* 备    注:
	*			该函数为不安全函数，只是方便内存未使用时进行重新设置操作。当内存被使用后设置将失败；
	*			函数本身有悖内存池的使用流程，只是方便重置操作；切忌不在内存池被使用后调用此函数
	* 作    者:fz
	* 电子邮箱:fangzhenmu@compony.com.cn
	* 创建日期:2015-08-25 15:35:35
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
	* 版权所有:fz & compony
	* 方法名称:clear
	* 功    能:
	*			清除缓存中的内容
	* 参    数:
	* 返 回 值:
	*			bool
	*			取值说明:
	*					true : 成功 
	*					false: 失败
	* 备    注:
	*			
	* 作    者:fz
	* 电子邮箱:fangzhenmu@compony.com.cn
	* 创建日期:2015-08-26 11:53:28
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
	int													m_size;									//表示当前设置的内存池块的大小
	int													m_max_number;							//表示最大保存的内存块数量
	atomic_int											m_current_number;						//当前保存的内存块数量
	atomic_int											m_free_number;							//当前保存的空闲的内存块数量
	atomic_int											m_lager_number;							//当前保存的大的内存块数量
	boost::lockfree::queue<char*>						m_free_buffer_queue;					//空闲的队列
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


