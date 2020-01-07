/*******************************************************************************
*
*Copyright:compony
*
*File name: hi_audio.cpp
*
*Author:fangzhenmu@compony.com.cn
*
*Version: 1.0
*
*Date:2018/02/09
*
*Description: create (hi_audio.cpp)
*
*Others:
*
*History:
*******************************************************************************/
#include "hi_audio.h"


#if 0

hi_audio_class::hi_audio_class()
	: m_aenc_is_start(false)
	, m_adec_is_start(false)
	, m_audio_enc_lock_free_pool_manager(HI_AUDIO_LOCK_FREE_BUFFER_SIZE, HI_AUDIO_LOCK_FREE_MAX_NUMBER)
	, m_audio_enc_ptr_queue(m_null_lock_free_pool_flag_buf_ptr)
	, m_audio_dec_ptr_queue(m_null_lock_free_pool_flag_buf_ptr)
{
}
hi_audio_class::~hi_audio_class()
{
}

bool hi_audio_class::push_front(lock_free_pool_flag_buf_ptr lfpf_ptr)
{

	return true;
}

lock_free_pool_flag_buf_ptr hi_audio_class::pop_front()
{
	return m_null_lock_free_pool_flag_buf_ptr;
}

#endif



