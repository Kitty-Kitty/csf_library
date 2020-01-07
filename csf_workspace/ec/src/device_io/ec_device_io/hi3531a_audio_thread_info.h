/*******************************************************************************
*
*Copyright:compony
*
*File name: hi3531a_audio_thread_info.h
*
*Author:fangzhenmu@compony.com.cn
*
*Version: 1.0
*
*Date:2018/02/08
*
*Description: create (hi3531a_audio_thread_info.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _HI3531A_AUDIO_THREAD_INFO_H_
#define _HI3531A_AUDIO_THREAD_INFO_H_




#include "hi_include.h"




class hi3531a_audio_thread_info_class;




typedef	 class hi3531a_audio_thread_info_class						hi3531a_audio_thread_info;




class hi3531a_audio_thread_info_class
{
public:
	hi3531a_audio_thread_info_class()
		: m_fd(0)
		, m_audio_dev(0)
		, m_audio_channel(0)
		, m_audio_process_channel(0)
		, m_thread_p(NULL)
	{

	}

	~hi3531a_audio_thread_info_class()
	{

	}

public:
	bool	set_fd(int fd)
	{
		m_fd = fd;
	}

	bool set_channel_info(int audio_dev, int audio_channel, int audio_process_channel)
	{
		m_audio_dev = audio_dev;
		m_audio_channel = audio_channel;
		m_audio_process_channel = audio_process_channel;
	}

public:
	int					m_fd;										//��ʾ��Ƶ���豸������
	int					m_audio_dev;								//��ʾ��Ƶ�豸
	int					m_audio_channel;							//��ʾ��Ƶ�豸ͨ��
	int					m_audio_process_channel;					//��ʾ��Ƶ�����
	thread_p				m_thread_p;									//��ʾ�������߳�
};




#endif //_HI3531A_AUDIO_THREAD_INFO_H_


