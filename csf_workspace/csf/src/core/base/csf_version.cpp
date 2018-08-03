/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_version.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 28-6ÔÂ-2018 21:08:20
*
*Description: Class(csf_version)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_version.hpp"

using csf::core::base::csf_version;


csf_version::csf_version()
	: m_version(CSF_VERSION)
	, m_strver(CSF_STRVER)
	, m_compile("")
	, m_build("")
	, m_description(CSF_VER) {

	m_build = __DATE__ "T" __TIME__;

#ifdef WIN32
	switch (_MSC_VER)
	{
	case 1800:
		m_compile = "Visual Studio 2013";
		break;
	case 1700:
		m_compile = "Visual Studio 2012";
		break;
	case 1600:
		m_compile = "Visual Studio 2010";
		break;
	case 1500:
		m_compile = "Visual Studio 2008";
		break;
	case 1400:
		m_compile = "Visual Studio 2005";
		break;
	case 1310:
		m_compile = "Visual Studio 2003";
		break;
	default:
		m_compile = "unknow compiler[MSC_VER=]";
		break;
	}
#else
	m_compile = __VERSION__;
#endif
}



csf_version::~csf_version() {

}