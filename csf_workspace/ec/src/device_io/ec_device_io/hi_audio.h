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





#define		HI_AUDIO_THREAD_JOIN_TIME_MS									5000					//��ʾ�߳��˳��ȴ�ʱ�䣬��λ��
#define		HI_AUDIO_LOCK_FREE_MAX_NUMBER								10						//��ʾý�����������е�������
#define		HI_AUDIO_LOCK_FREE_BUFFER_SIZE								10 * 1024				//��ʾ����bufferĬ�ϴ�С
#define		HI_AUDIO_DEFAULT_STACK_SIZE									50 * 1024				//��ʾĬ�ϵ��߳��ڿռ��С
#define		HI_AUDIO_DATA_QUEUE_MAX_SIZE									240						//��ʾ������Ƶ���ݻ�����еĳ��ȣ�ÿ��Լ24�����ݡ�240Լ10��;��Ҫ��ֹ����̫����ܵ����ڴ�й¶����



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
	* ��Ȩ����: fz & compony
	*
	* ��������: init
	*
	* ����ȫ��: hi_audio_class::init
	*
	* ��������: virtual public 
	*
	* ����˵��: hi audio�ĳ�ʼ��
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:24:53
	********************************************************************************/
	virtual bool init() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: start
	*
	* ����ȫ��: hi_audio_class::start
	*
	* ��������: virtual public 
	*
	* ����˵��: hi audio������
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:25:10
	********************************************************************************/
	virtual bool start() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: stop
	*
	* ����ȫ��: hi_audio_class::stop
	*
	* ��������: virtual public 
	*
	* ����˵��: hi audio��ֹͣ
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:25:26
	********************************************************************************/
	virtual bool stop() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: decode_data
	*
	* ����ȫ��: hi_audio_class::decode_data
	*
	* ��������: public 
	*
	* ����˵��: hi audio���벥������
	*
	* ��    ��: const char* buf						[in/out]����˵��
	* ��    ��: int len						[in/out]����˵��
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:25:41
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
	* ��Ȩ����: fz & compony
	*
	* ��������: get_encode_data
	*
	* ����ȫ��: hi_audio_class::get_encode_data
	*
	* ��������: public 
	*
	* ����˵��: hi audio��ȡ��������
	*
	*
	* �� �� ֵ: lock_free_pool_flag_buf_ptr
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:26:08
	********************************************************************************/
	inline lock_free_pool_flag_buf_ptr get_encode_data()
	{
		return m_audio_enc_ptr_queue.pop_front();
	}

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: enable_send
	*
	* ����ȫ��: hi_audio_class::enable_send
	*
	* ��������: public 
	*
	* ����˵��: �������ͣ����ǽ��б��벥�źͽ��벥��
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-5-25 16:14:19
	********************************************************************************/
	inline bool enable_send()
	{
		m_aenc_is_send = true;
		m_adec_is_send = true;
		return true;
	}

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: disable_send
	*
	* ����ȫ��: hi_audio_class::disable_send
	*
	* ��������: public 
	*
	* ����˵��: �رշ��ͣ����ǲ����б��벥�źͽ��벥��
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-5-25 16:15:36
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
	* ��Ȩ����: fz & compony
	*
	* ��������: sys_init
	*
	* ����ȫ��: hi_audio_class::sys_init
	*
	* ��������: virtual protected 
	*
	* ����˵��: hi audio��ϵͳ��ʼ��������ϵͳ��Դ
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:26:30
	********************************************************************************/
	virtual bool sys_init() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: sys_exit
	*
	* ����ȫ��: hi_audio_class::sys_exit
	*
	* ��������: virtual protected 
	*
	* ����˵��: hi audio��ϵͳ�˳������ո�����Դ
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:26:44
	********************************************************************************/
	virtual bool sys_exit() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: init_ai
	*
	* ����ȫ��: hi_audio_class::init_ai
	*
	* ��������: virtual protected 
	*
	* ����˵��: hi audio�ĳ�ʼ������ai�豸
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:28:49
	********************************************************************************/
	virtual bool init_ai() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: start_ai
	*
	* ����ȫ��: hi_audio_class::start_ai
	*
	* ��������: virtual protected 
	*
	* ����˵��: hi audio����������ai�豸
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:29:04
	********************************************************************************/
	virtual bool start_ai() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: stop_ai
	*
	* ����ȫ��: hi_audio_class::stop_ai
	*
	* ��������: virtual protected 
	*
	* ����˵��: hi audio��ֹͣ����ai�豸
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:29:21
	********************************************************************************/
	virtual bool stop_ai() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: init_ao
	*
	* ����ȫ��: hi_audio_class::init_ao
	*
	* ��������: virtual protected 
	*
	* ����˵��: hi audio�ĳ�ʼ�����ao�豸
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:29:35
	********************************************************************************/
	virtual bool init_ao() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: start_ao
	*
	* ����ȫ��: hi_audio_class::start_ao
	*
	* ��������: virtual protected 
	*
	* ����˵��: hi audio���������ao�豸
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:30:15
	********************************************************************************/
	virtual bool start_ao() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: stop_ao
	*
	* ����ȫ��: hi_audio_class::stop_ao
	*
	* ��������: virtual protected 
	*
	* ����˵��: hi audio��ֹͣ���ao�豸
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:30:39
	********************************************************************************/
	virtual bool stop_ao() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: init_aenc
	*
	* ����ȫ��: hi_audio_class::init_aenc
	*
	* ��������: virtual protected 
	*
	* ����˵��: hi audio�ĳ�ʼ�������豸
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:30:50
	********************************************************************************/
	virtual bool init_aenc() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: start_aenc
	*
	* ����ȫ��: hi_audio_class::start_aenc
	*
	* ��������: virtual protected 
	*
	* ����˵��: hi audio�����������豸
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:31:11
	********************************************************************************/
	virtual bool start_aenc() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: stop_aenc
	*
	* ����ȫ��: hi_audio_class::stop_aenc
	*
	* ��������: virtual protected 
	*
	* ����˵��: hi audio��ֹͣ�����豸
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:31:24
	********************************************************************************/
	virtual bool stop_aenc() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: init_adec
	*
	* ����ȫ��: hi_audio_class::init_adec
	*
	* ��������: virtual protected 
	*
	* ����˵��: hi audio�ĳ�ʼ�������豸
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:31:33
	********************************************************************************/
	virtual bool init_adec() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: start_adec
	*
	* ����ȫ��: hi_audio_class::start_adec
	*
	* ��������: virtual protected 
	*
	* ����˵��: hi audio�����������豸
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:31:46
	********************************************************************************/
	virtual bool start_adec() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: stop_adec
	*
	* ����ȫ��: hi_audio_class::stop_adec
	*
	* ��������: virtual protected 
	*
	* ����˵��: hi audio��ֹͣ�����豸
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:31:57
	********************************************************************************/
	virtual bool stop_adec() = 0;

	/*******************************************************************************
	* ��Ȩ����: fz & compony
	*
	* ��������: set_stop_thread_flag
	*
	* ����ȫ��: hi_audio_class::set_stop_thread_flag
	*
	* ��������: protected 
	*
	* ����˵��: hi audio�����߳�ֹͣ��ʶ
	*
	*
	* �� �� ֵ: bool
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@compony.com.cn
	* �������ڣ�2018-2-9 14:32:05
	********************************************************************************/
	inline bool set_stop_thread_flag()
	{
		m_aenc_is_start = false;
		m_adec_is_start = false;

		return true;
	}

protected:
	bool										m_aenc_is_start;						//��ʾ�����߳��Ƿ�����
	bool										m_adec_is_start;						//��ʾ�����߳��Ƿ�����
	bool										m_aenc_is_send;							//��ʾ�����߳��Ƿ�Ҫ���沢���ͱ�������
	bool										m_adec_is_send;							//��ʾ�����߳��Ƿ�Ҫ���沢���ͽ�������

	thread_group_ex							m_aenc_thread_group;					//��ʾ�����̹߳�����
	thread_group_ex							m_adec_thread_group;					//��ʾ�����̹߳�����

	lock_free_pool_manager					m_audio_enc_lock_free_pool_manager;		//��ʾ�����ڴ������
	lock_free_pool_manager					m_audio_dec_lock_free_pool_manager;		//��ʾ�����ڴ������

	lock_free_pool_flag_buf_ptr_queue		m_audio_enc_ptr_queue;					//��ʾ�������ݶ���
	lock_free_pool_flag_buf_ptr_queue		m_audio_dec_ptr_queue;					//��ʾ�������ݶ���

};


#endif //_HI_AUDIO_H_


