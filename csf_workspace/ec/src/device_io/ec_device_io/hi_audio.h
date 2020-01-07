/*******************************************************************************
*
*Copyright:compony
*
*File name: hi_audio.h
*
*Author:fangzhenmu@compony.com.cn
*
*Version: 1.0
*
*Date:2018/02/08
*
*Description: create (hi_audio.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _HI_AUDIO_H_
#define _HI_AUDIO_H_




#include "hi_include.h"
#include "thread_group_ex.h"
#include "lock_free_pool_flag_buf.h"




class hi_audio_class;



	
typedef	 class hi_audio_class											hi_audio;
typedef	 shared_ptr<lock_free_pool_flag_buf>							lock_free_pool_flag_buf_ptr;
typedef	 queue_class<lock_free_pool_flag_buf_ptr>						lock_free_pool_flag_buf_ptr_queue;





#define		HI_AUDIO_THREAD_JOIN_TIME_MS									5000					//表示线程退出等待时间，单位秒
#define		HI_AUDIO_LOCK_FREE_MAX_NUMBER								10						//表示媒体流无锁队列的最大个数
#define		HI_AUDIO_LOCK_FREE_BUFFER_SIZE								10 * 1024				//表示单个buffer默认大小
#define		HI_AUDIO_DEFAULT_STACK_SIZE									50 * 1024				//表示默认的线程在空间大小
#define		HI_AUDIO_DATA_QUEUE_MAX_SIZE									240						//表示限制音频数据缓存队列的长度，每秒约24个数据。240约10秒;主要防止缓存太大可能导致内存泄露问题



static lock_free_pool_flag_buf_ptr										m_null_lock_free_pool_flag_buf_ptr;


class hi_audio_class
{
public:
	hi_audio_class()
		: m_aenc_is_start(false)
		, m_adec_is_start(false)
		, m_aenc_is_send(false)
		, m_adec_is_send(false)
		, m_audio_enc_lock_free_pool_manager(HI_AUDIO_LOCK_FREE_BUFFER_SIZE, HI_AUDIO_LOCK_FREE_MAX_NUMBER)
		, m_audio_dec_lock_free_pool_manager(HI_AUDIO_LOCK_FREE_BUFFER_SIZE, HI_AUDIO_LOCK_FREE_MAX_NUMBER)
		, m_audio_enc_ptr_queue(m_null_lock_free_pool_flag_buf_ptr)
		, m_audio_dec_ptr_queue(m_null_lock_free_pool_flag_buf_ptr)
	{

	}

	~hi_audio_class()
	{

	}

public:
	
	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: init
	*
	* 函数全名: hi_audio_class::init
	*
	* 函数访问: virtual public 
	*
	* 函数说明: hi audio的初始化
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:24:53
	********************************************************************************/
	virtual bool init() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: start
	*
	* 函数全名: hi_audio_class::start
	*
	* 函数访问: virtual public 
	*
	* 函数说明: hi audio的启动
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:25:10
	********************************************************************************/
	virtual bool start() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: stop
	*
	* 函数全名: hi_audio_class::stop
	*
	* 函数访问: virtual public 
	*
	* 函数说明: hi audio的停止
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:25:26
	********************************************************************************/
	virtual bool stop() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: decode_data
	*
	* 函数全名: hi_audio_class::decode_data
	*
	* 函数访问: public 
	*
	* 函数说明: hi audio解码播放数据
	*
	* 参    数: const char* buf						[in/out]参数说明
	* 参    数: int len						[in/out]参数说明
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:25:41
	********************************************************************************/
	inline bool decode_data(const char* buf, int len)
	{
		lock_free_pool_flag_buf_p					lfpfb_p = NULL;


		if (m_audio_dec_ptr_queue.size() >= HI_AUDIO_DATA_QUEUE_MAX_SIZE) {
			return false;
		}

		lfpfb_p = new lock_free_pool_flag_buf(&m_audio_dec_lock_free_pool_manager, len);
		if (!lfpfb_p) {
			return false;
		}

		lfpfb_p->copy(buf, len);
		m_audio_dec_ptr_queue.push_back(lock_free_pool_flag_buf_ptr(lfpfb_p));
		return true;
	}

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: get_encode_data
	*
	* 函数全名: hi_audio_class::get_encode_data
	*
	* 函数访问: public 
	*
	* 函数说明: hi audio获取编码数据
	*
	*
	* 返 回 值: lock_free_pool_flag_buf_ptr
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:26:08
	********************************************************************************/
	inline lock_free_pool_flag_buf_ptr get_encode_data()
	{
		return m_audio_enc_ptr_queue.pop_front();
	}

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: enable_send
	*
	* 函数全名: hi_audio_class::enable_send
	*
	* 函数访问: public 
	*
	* 函数说明: 开启发送，就是进行编码播放和解码播放
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-5-25 16:14:19
	********************************************************************************/
	inline bool enable_send()
	{
		m_aenc_is_send = true;
		m_adec_is_send = true;
		return true;
	}

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: disable_send
	*
	* 函数全名: hi_audio_class::disable_send
	*
	* 函数访问: public 
	*
	* 函数说明: 关闭发送，就是不进行编码播放和解码播放
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-5-25 16:15:36
	********************************************************************************/
	inline bool disable_send()
	{
		m_aenc_is_send = false;
		m_adec_is_send = false;
		m_audio_enc_ptr_queue.clear();
		m_audio_dec_ptr_queue.clear();
		return true;
	}

protected:
	
	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: sys_init
	*
	* 函数全名: hi_audio_class::sys_init
	*
	* 函数访问: virtual protected 
	*
	* 函数说明: hi audio的系统初始化，配置系统资源
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:26:30
	********************************************************************************/
	virtual bool sys_init() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: sys_exit
	*
	* 函数全名: hi_audio_class::sys_exit
	*
	* 函数访问: virtual protected 
	*
	* 函数说明: hi audio的系统退出，回收各种资源
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:26:44
	********************************************************************************/
	virtual bool sys_exit() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: init_ai
	*
	* 函数全名: hi_audio_class::init_ai
	*
	* 函数访问: virtual protected 
	*
	* 函数说明: hi audio的初始化输入ai设备
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:28:49
	********************************************************************************/
	virtual bool init_ai() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: start_ai
	*
	* 函数全名: hi_audio_class::start_ai
	*
	* 函数访问: virtual protected 
	*
	* 函数说明: hi audio的启动输入ai设备
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:29:04
	********************************************************************************/
	virtual bool start_ai() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: stop_ai
	*
	* 函数全名: hi_audio_class::stop_ai
	*
	* 函数访问: virtual protected 
	*
	* 函数说明: hi audio的停止输入ai设备
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:29:21
	********************************************************************************/
	virtual bool stop_ai() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: init_ao
	*
	* 函数全名: hi_audio_class::init_ao
	*
	* 函数访问: virtual protected 
	*
	* 函数说明: hi audio的初始化输出ao设备
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:29:35
	********************************************************************************/
	virtual bool init_ao() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: start_ao
	*
	* 函数全名: hi_audio_class::start_ao
	*
	* 函数访问: virtual protected 
	*
	* 函数说明: hi audio的启动输出ao设备
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:30:15
	********************************************************************************/
	virtual bool start_ao() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: stop_ao
	*
	* 函数全名: hi_audio_class::stop_ao
	*
	* 函数访问: virtual protected 
	*
	* 函数说明: hi audio的停止输出ao设备
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:30:39
	********************************************************************************/
	virtual bool stop_ao() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: init_aenc
	*
	* 函数全名: hi_audio_class::init_aenc
	*
	* 函数访问: virtual protected 
	*
	* 函数说明: hi audio的初始化编码设备
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:30:50
	********************************************************************************/
	virtual bool init_aenc() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: start_aenc
	*
	* 函数全名: hi_audio_class::start_aenc
	*
	* 函数访问: virtual protected 
	*
	* 函数说明: hi audio的启动编码设备
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:31:11
	********************************************************************************/
	virtual bool start_aenc() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: stop_aenc
	*
	* 函数全名: hi_audio_class::stop_aenc
	*
	* 函数访问: virtual protected 
	*
	* 函数说明: hi audio的停止编码设备
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:31:24
	********************************************************************************/
	virtual bool stop_aenc() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: init_adec
	*
	* 函数全名: hi_audio_class::init_adec
	*
	* 函数访问: virtual protected 
	*
	* 函数说明: hi audio的初始化解码设备
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:31:33
	********************************************************************************/
	virtual bool init_adec() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: start_adec
	*
	* 函数全名: hi_audio_class::start_adec
	*
	* 函数访问: virtual protected 
	*
	* 函数说明: hi audio的启动解码设备
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:31:46
	********************************************************************************/
	virtual bool start_adec() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: stop_adec
	*
	* 函数全名: hi_audio_class::stop_adec
	*
	* 函数访问: virtual protected 
	*
	* 函数说明: hi audio的停止解码设备
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:31:57
	********************************************************************************/
	virtual bool stop_adec() = 0;

	/*******************************************************************************
	* 版权所有: fz & compony
	*
	* 函数名称: set_stop_thread_flag
	*
	* 函数全名: hi_audio_class::set_stop_thread_flag
	*
	* 函数访问: protected 
	*
	* 函数说明: hi audio设置线程停止标识
	*
	*
	* 返 回 值: bool
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@compony.com.cn
	* 创建日期：2018-2-9 14:32:05
	********************************************************************************/
	inline bool set_stop_thread_flag()
	{
		m_aenc_is_start = false;
		m_adec_is_start = false;

		return true;
	}

protected:
	bool										m_aenc_is_start;						//表示编码线程是否启动
	bool										m_adec_is_start;						//表示解码线程是否启动
	bool										m_aenc_is_send;							//表示编码线程是否要保存并发送编码数据
	bool										m_adec_is_send;							//表示解码线程是否要保存并发送解码数据

	thread_group_ex							m_aenc_thread_group;					//表示编码线程管理组
	thread_group_ex							m_adec_thread_group;					//表示解码线程管理组

	lock_free_pool_manager					m_audio_enc_lock_free_pool_manager;		//表示编码内存管理组
	lock_free_pool_manager					m_audio_dec_lock_free_pool_manager;		//表示解码内存管理组

	lock_free_pool_flag_buf_ptr_queue		m_audio_enc_ptr_queue;					//表示编码数据队列
	lock_free_pool_flag_buf_ptr_queue		m_audio_dec_ptr_queue;					//表示解码数据队列

};


#endif //_HI_AUDIO_H_


