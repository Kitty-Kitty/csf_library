/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_mdbuffer.hpp
*
*Version: 1.0
*
*Date: 28-11月-2019 21:23:03
*
*Description: Class(csf_mdbuffer)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_mdbuffer.hpp"
#include "csf_mdpool.hpp"

using ec::core::csf_mdbuffer;

/**
* 表示销毁容器，除了clear清空数据外，更增加了销毁内存的功能。
* 执行clear后，对象还是完整的，可以继续使用。而相对执行destroy函数后，部分资源将会被释放，可能导致对象不完整，不能继续正常使用。
*/
void csf_mdbuffer::destroy() {

	if (NULL != get_mdpool()) {
		get_mdpool()->mdfree(*this);
	}
}