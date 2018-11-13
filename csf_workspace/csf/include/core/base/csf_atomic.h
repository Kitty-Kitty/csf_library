/*******************************************************************************
*
*Copyright:fz
*
*File name: csf_atomic.h
*
*Author:armuxinxian@aliyun.com
*
*Version: 1.0
*
*Date:2018/06/28
*
*Description: create (csf_atomic.h)
*
*Others:
*
*History:
*******************************************************************************/
#ifdef __linux__
#pragma GCC diagnostic error "-std=c++11"
#endif

#if !defined(_CSF_ATOMIC_H_)
#define _CSF_ATOMIC_H_



#ifdef __cplusplus
#include <cstdint>
#include <atomic>
#endif


#ifdef __cplusplus
namespace csf
{
	namespace core
	{
		namespace base
		{
#endif

			typedef std::atomic<bool>							csf_atomic_bool;
			typedef	std::atomic<char>							csf_atomic_char;
			typedef std::atomic<short>							csf_atomic_short;
			typedef std::atomic<int>							csf_atomic_int;
			typedef	std::atomic<long>							csf_atomic_long;


			typedef std::atomic<unsigned char>					csf_atomic_uchar;
			typedef std::atomic<unsigned short>					csf_atomic_ushort;
			typedef std::atomic<unsigned int>					csf_atomic_uint;
			typedef	std::atomic<unsigned long>					csf_atomic_ulong;


			typedef std::atomic<std::int8_t>					csf_atomic_int8;
			typedef std::atomic<std::int16_t>					csf_atomic_int16;
			typedef std::atomic<std::int32_t>					csf_atomic_int32;
			typedef	std::atomic<std::int64_t>					csf_atomic_int64;


			typedef std::atomic<std::uint8_t>					csf_atomic_uint8;
			typedef std::atomic<std::uint16_t>					csf_atomic_uint16;
			typedef std::atomic<std::uint32_t>					csf_atomic_uint32;
			typedef	std::atomic<std::uint64_t>					csf_atomic_uint64;


#ifdef __cplusplus
		}
	}
}
#endif

#endif //_CSF_ATOMIC_H_


