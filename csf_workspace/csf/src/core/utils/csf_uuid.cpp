/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_uuid.hpp
*
*Version: 1.0
*
*Date: 30-11月-2019 17:33:25
*
*Description: Class(csf_uuid)
*
*Others:
*
*History:
*
*******************************************************************************/

#ifdef WIN32
#include <objbase.h>
#else
#include <inttypes.h>
#include <sys/types.h>
#include <uuid/uuid.h>
#endif

// #include <boost/uuid/uuid.hpp>
// #include <boost/uuid/uuid_io.hpp>
// #include <boost/uuid/uuid_generators.hpp>
// #include "csf_stddef.h"
#include "csf_uuid.hpp"

using csf::core::utils::csf_uuid;


//表示生成的uuid字符串长度
#define	CSF_UUID_BUFFER_LEN			36

//表示生成uuid的格式
static const char *fmt_lower = "%08x%04x%04x%02x%02x%02x%02x%02x%02x%02x%02x";


csf_uuid::csf_uuid() {

}



csf_uuid::~csf_uuid() {

}





/**
 * 功能：创建32位的uuid字符串保存到目标内存位置
 * 返回：true表示创建成功；false表示创建失败；
 * 
 * @param dest    表示创建后的32位uuid保存的位置。该存储空间不能少于32字节。
 * @param len    表示dest内存长度
 */
bool csf_uuid::make32(char* dest, int len) {

	if (len < CSF_UUID_BUFFER_LEN) {
		return false;
	}

#ifdef WIN32
	GUID guid;
	CoCreateGuid(&guid);
	_snprintf_s(
		dest,
		len,
		len - 1,
		"%08x%04x%04x%02x%02x%02x%02x%02x%02x%02x%02x",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1],
		guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
#else

	uuid_t			uuid_out;

	uuid_generate(uuid_out);
	//uuid_unparse_x(uuid_out, dest, fmt_lower);
	uuid_unparse_upper(uuid_out, dest);
#endif

// 	boost::uuids::uuid a_uuid = boost::uuids::random_generator()();  //// 这里是两个() ，因为这里是调用的 () 的运算符重载
// 	const std::string tmp_uuid = boost::uuids::to_string(a_uuid);
// 	csf_strncpy(dest, tmp_uuid.c_str(), len);

	return true;
}