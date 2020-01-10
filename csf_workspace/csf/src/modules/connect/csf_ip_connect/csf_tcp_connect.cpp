/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_tcp_connect.hpp
*
*Version: 1.0
*
*Date: 02-10ÔÂ-2018 14:18:00
*
*Description: Class(csf_tcp_connect)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_tcp_connect.hpp"

using csf::modules::connect::csf_tcp_connect;


csf_tcp_connect::~csf_tcp_connect() {

	close_socket();
}




/**
* Ä£¿é³õÊ¼»¯
*
* @param conf_mg    ±íÊ¾ÅäÖÃÎÄ¼þÐÅÏ¢
*/
csf::core::base::csf_int32 csf_tcp_connect::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* ±íÊ¾´ò¿ªÁ¬½ÓÐÅÏ¢.
* ·µ»Ø£º0±íÊ¾³É¹¦£»·Ç0±íÊ¾Ê§°Ü£»
*
* @param url    ±íÊ¾Á¬½ÓµØÖ·
*/
csf_int32 csf_tcp_connect::open(const csf_url& url) {

	return 0;
}


/**
* ±íÊ¾¹Ø±ÕÁ¬½Ó.
* ·µ»Ø£º0±íÊ¾³É¹¦£»·Ç0±íÊ¾Ê§°Ü£»
*/
csf_int32 csf_tcp_connect::close() {

	close_socket();

	return csf_connect::close();
}


/**
* Ä£¿éÆô¶¯
*
* @param conf_mg    ±íÊ¾ÅäÖÃÎÄ¼þÐÅÏ¢
*/
csf::core::base::csf_int32 csf_tcp_connect::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* ±íÊ¾ÉèÖÃÁ¬½ÓµÄÊôÐÔÏîÄ¿ÐÅÏ¢¡£
* ·µ»Ø£º0±íÊ¾³É¹¦£»·Ç0±íÊ¾Ê§°Ü¡£
*/
csf_int32 csf_tcp_connect::set_option() {

	return 0;
}


/**
* Ä£¿éÍ£Ö¹
*
* @param conf_mg    ±íÊ¾ÅäÖÃÎÄ¼þÐÅÏ¢
*/
csf::core::base::csf_int32 csf_tcp_connect::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* Ö÷Òª¹¦ÄÜÊÇ£º´ò¿ªÒ»¸ö¼àÌýµØÖ·¡£
* ·µ»Ø£º0±íÊ¾³É¹¦£»·Ç0±íÊ¾Ê§°Ü£»
*
* @param url    ±íÊ¾ÐèÒª¼àÌýµÄµØÖ·
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
csf_int32 csf_tcp_connect::listen(const csf_url& url, const csf_connect_callback& callback) {

	csf::modules::connect::csf_ip_url  tmp_ip_url;


	//¶ÔurlÄÚÈÝ½øÐÐºÏ·¨ÐÔ´¦Àí£¬±ÜÃâ³öÏÖ´¦ÀíÒì³£
	if (csf_ip_url::is_valid_type(url)) {
		tmp_ip_url = (csf::modules::connect::csf_ip_url&)url;
	}
	else {
		if (csf_failure == tmp_ip_url.parse(url.get_url())) {
			csf_log_ex(error, csf_log_code_error
				, "listen[url:%s] failed! url format failed!"
				, url.get_url().c_str());
			return csf_failure;
		}
	}

	try {
		//Èç¹ûÒÑ¾­¼àÌýÁË£¬Ôò·µ»ØÊ§°Ü
		if (csf_nullptr != get_acceptor()) {

			csf_log_ex(error, csf_log_code_error
				, "listen[url:%s] failed! connect is listening."
				, tmp_ip_url.get_url().c_str());

			exception_callback(shared_from_this()
				, callback
				, csf_ip_connect_error(
					csf_connect_error::csf_connect_code::csf_connect_code_listen
					, "is listening"));

			return csf_failure;
		}

		//´´½¨Ò»¸öacceptor£¬ÓÃÓÚÊµÏÖtcp¼àÌý
		set_acceptor(new boost::asio::ip::tcp::acceptor(
			get_socket().get_io_service()
			, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(tmp_ip_url.get_ip())
				, tmp_ip_url.get_port())));

		async_accept(callback);
	}
	catch (boost::exception& e) {

		csf_log_ex(error, csf_log_code_error
			, "listen [url:%s] failed! reason:[%s -- %s]."
			, tmp_ip_url.get_url().c_str()
			, boost::current_exception_diagnostic_information().c_str()
			, boost::diagnostic_information(e).c_str());

		exception_callback(shared_from_this()
			, callback
			, csf_ip_connect_error(
				csf_connect_error::csf_connect_code::csf_connect_code_listen
				, boost::diagnostic_information(e)));

		return csf_failure;
	}

	return csf_succeed;
}


/**
* Ö÷Òª¹¦ÄÜÊÇ£ºÐèÒªÁ¬½ÓÒ»¸öµØÖ·¡£
* ·µ»Ø£º0±íÊ¾³É¹¦£»·Ç0±íÊ¾Ê§°Ü£»
*
* @param url    ±íÊ¾ÐèÒª¼àÌýµÄµØÖ·
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
csf_int32 csf_tcp_connect::connect(const csf_url& url, const csf_connect_callback& callback) {

	csf::modules::connect::csf_ip_url  tmp_ip_url;


	//¶ÔurlÄÚÈÝ½øÐÐºÏ·¨ÐÔ´¦Àí£¬±ÜÃâ³öÏÖ´¦ÀíÒì³£
	if (csf_ip_url::is_valid_type(url)) {
		tmp_ip_url = (csf::modules::connect::csf_ip_url&)url;
	}
	else {
		if (csf_failure == tmp_ip_url.parse(url.get_url())) {
			csf_log_ex(error, csf_log_code_error
				, "connect[url:%s] failed! url format failed!"
				, url.get_url().c_str());
			return csf_failure;
		}
	}

	//µØÖ·ÑéÖ¤³É¹¦£¬ÔòÏÈ¸üÐÂµØÖ·ÐÅÏ¢
	set_remote_url(tmp_ip_url);

	//¸ù¾ÝÊÇ·ñ´æÔÚ»Øµ÷º¯ÊýÀ´ÅÐ¶ÏÊ¹ÓÃÍ¬²½·½Ê½»¹ÊÇÒì²½·½Ê½
	boost::asio::ip::tcp::endpoint tmp_remote_endpoint(
		boost::asio::ip::address::from_string(tmp_ip_url.get_ip()), tmp_ip_url.get_port());
	if (csf_nullptr != callback) {
		get_socket().async_connect(tmp_remote_endpoint
			, boost::bind(&csf_ip_connect::async_connect_callback
				, this
				, shared_from_this()
				, callback
				, boost::asio::placeholders::error));
		return csf_succeed;
	}
	else {
		boost::system::error_code	tmp_error;

		get_socket().connect(tmp_remote_endpoint, tmp_error);
		if (tmp_error) {
			set_error(csf_connect_error(tmp_error.value()
				, boost::system::system_error(tmp_error).what()));

			csf_log_ex(error, csf_log_code_error
				, "connect[url:%s] failed! %s."
				, tmp_ip_url.get_url().c_str()
				, get_error().to_string().c_str());
			return csf_failure;
		}
		else {
			//¸üÐÂÒ»ÏÂ±¾µØµÄµØÖ·ÐÅÏ¢
			get_local_url();

			csf_log_ex(notice, csf_log_code_notice
				, "connect[url:%s] succeed! %s"
				, tmp_ip_url.get_url().c_str()
				, to_string().c_str());
			return csf_succeed;
		}
	}

	return csf_failure;
}


/**
* Ö÷Òª¹¦ÄÜÊÇ£ºÐ´ÈëÖ¸¶¨»º´æµÄÄÚÈÝ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦Ð´ÈëµÄÊý¾Ý³¤¶È£»
*
* @param buf    ±íÊ¾ÄÚÈÝµÄ»º´æµØÖ·
* @param len    ±íÊ¾ÄÚÈÝ»º´æµÄ³¤¶È
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	//ÕâÀï¿ÉÒÔ²»½øÐÐÊý¾ÝµÄÐ£Ñé´¦Àí£¬ÕâÑù»á¼õÉÙÊý¾Ý¶ÁÈ¡µÄÐ§ÂÊ
// 	if (csf_nullptr == buf
// 		|| len <= 0) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes
// 				, "data is null"));
// 		return csf_failure;
// 	}
// 
// 	//¸ù¾ÝÊÇ·ñÓÐ»Øµ÷º¯Êý£¬À´ÅÐ¶ÏÊ¹ÓÃÒì²½»¹ÊÇÍ¬²½
// 	if (csf_nullptr == callback) {
// 		return sync_write(buf, len, callback);
// 	}
// 	else {
// 		return async_write(buf, len, callback);
// 	}
// 	return 0;
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£ºÐ´Èëcsf_bufferÄÚÈÝ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦Ð´ÈëµÄÊý¾Ý³¤¶È£»
*
* @param buffer    ±íÊ¾ÐèÒªÐ´ÈëµÄcsf_bufferÄÚÈÝ
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::write(csf_buffer& buffer, const csf_connect_callback& callback) {
// 
// 	return write(buffer.get_buffer(), buffer.length(), callback);
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£º·¢ËÍcsf_csfstringÄÚÈÝ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦Ð´ÈëµÄÊý¾Ý³¤¶È£»
*
* @param csfstr    ±íÊ¾csf_csfstringµÄÄÚÈÝ
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::write(csf_csfstring& csfstr, const csf_connect_callback& callback) {
// 
// 	return write(csfstr.get_buffer(), csfstr.length(), callback);
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£º·¢ËÍcsf_csfstringÄÚÈÝ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦Ð´ÈëµÄÊý¾Ý³¤¶È£»
*
* @param chain    ±íÊ¾csf_chainµÄÄÚÈÝ
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::write(csf_chain& chain, const csf_connect_callback& callback) {
// 
// 	csf_buffer				tmp_buffer(chain.length());
// 
// 	chain.convert(tmp_buffer);
// 
// 	return write(tmp_buffer, callback);
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£ºÐ´ÈëÖ¸¶¨»º´æµÄÄÚÈÝ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦Ð´ÈëµÄÊý¾Ý³¤¶È£»
*
* @param buffer    ±íÊ¾ÐèÒª·¢ËÍµÄÄÚÈÝ»º´æ
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback) {
// 
// 	//ÏÈÅÐ¶ÏÊý¾ÝµÄºÏ·¨ÐÔ£¬Ö®ºóÔÙ´¦Àí
// 	if (!buffer.is_valid()) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
// 		return csf_failure;
// 	}
// 
// 	//¸ù¾Ýcsf_connect_bufferµÄ±êÖ¾Î»À´ÅÐ¶ÏÒì²½ÓëÍ¬²½
// 	if (buffer.get_is_sync()) {
// 		return sync_write(buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	else {
// 		return async_write(buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	return 0;
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£ºÐ´Èëcsf_bufferÄÚÈÝ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦Ð´ÈëµÄÊý¾Ý³¤¶È£»
*
* @param buffer    ±íÊ¾ÐèÒª·¢ËÍµÄÄÚÈÝ»º´æ
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
//  csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {
//  
//  	//ÏÈÅÐ¶ÏÊý¾ÝµÄºÏ·¨ÐÔ£¬Ö®ºóÔÙ´¦Àí
//  	if (!buffer.is_valid()) {
//  		exception_callback(shared_from_this()
//  			, callback
//  			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
//  		return csf_failure;
//  	}
//  
//  	//Èç¹ûbufferÖÐÐ´³¤¶È´óÐ¡Ã»ÓÐÉèÖÃ£¨buffer.get_length()Îª0£©£¬Ôò¸ù¾ÝËÞÖ÷µÄ¿Õ¼ä´óÐ¡×Ô¶¯ÉèÖÃÊý¾Ý
//  	//ÕâÑù´¦ÀíÖ÷ÒªÎª¼õÉÙÊÕ·¢²Ù×÷Ê±µÄÊ¹ÓÃ³É±¾£¬ÓÃ»§²»ÓÃ¼ÇµÃ±ØÐëµ÷ÓÃbuffer.set_length()º¯Êý¡£µ«µ×²ãµÄ×Ô¶¯´¦Àí£¬Í¬Ê±ÒýÈëÁË³ÌÐòµÄ²»È·¶¨ÐÔ¡£
//  	//·¢ËÍÄ¬ÈÏ³¤¶ÈÎªËÞÖ÷ÈÝÆ÷ÖÐÊý¾ÝµÄ³¤¶È
//  	//½ÓÊÕÄ¬ÈÏ³¤¶ÈÎªËÞÖ÷ÈÝÆ÷ÖÐ¿ÕÏÐ¿Õ¼äµÄ³¤¶È
//  	if (buffer.get_length() <= 0 && buffer.length() > 0) {
//  		buffer.set_length(buffer.length());
//  	}
//  
//  	//¸ù¾Ýcsf_connect_bufferµÄ±êÖ¾Î»À´ÅÐ¶ÏÒì²½ÓëÍ¬²½
//  	if (buffer.get_is_sync()) {
//  		//return sync_write(buffer.get_buffer(), buffer.get_length(), callback);
//  		return sync_write(buffer, callback);
//  	}
//  	else {
//  		//return async_write(buffer.get_buffer(), buffer.get_length(), callback);
//  		return async_write(buffer, callback);
//  	}
//  	return 0;
//  }


/**
* Ö÷Òª¹¦ÄÜÊÇ£º·¢ËÍcsf_csfstringÄÚÈÝ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦Ð´ÈëµÄÊý¾Ý³¤¶È£»
*
* @param buffer    ±íÊ¾ÐèÒª·¢ËÍµÄÄÚÈÝ»º´æ
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback) {
// 
// 	//ÏÈÅÐ¶ÏÊý¾ÝµÄºÏ·¨ÐÔ£¬Ö®ºóÔÙ´¦Àí
// 	if (!buffer.is_valid()) {
// 		return exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
// 	}
// 
// 	//¸ù¾Ýcsf_connect_bufferµÄ±êÖ¾Î»À´ÅÐ¶ÏÒì²½ÓëÍ¬²½
// 	if (buffer.get_is_sync()) {
// 		return sync_write(buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	else {
// 		return async_write(buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	return 0;
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£º·¢ËÍcsf_csfstringÄÚÈÝ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦Ð´ÈëµÄÊý¾Ý³¤¶È£»
*
* @param buffer    ±íÊ¾ÐèÒª·¢ËÍµÄÄÚÈÝ»º´æ
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback) {
// 
// 	//ÏÈÅÐ¶ÏÊý¾ÝµÄºÏ·¨ÐÔ£¬Ö®ºóÔÙ´¦Àí
// 	if (!buffer.is_valid()) {
// 		return exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
// 	}
// 
// 	//ÏÈ½«chain×ª»¯Îªbuffer£¬³ÉÎªÒ»¸öÁ¬ÐøµÄÄÚ´æ¿Õ¼äºó´¦Àí
// 	csf_buffer				tmp_buffer(buffer.length());
// 
// 	buffer.get_container()->convert(tmp_buffer);
// 
// 	//¸ù¾Ýcsf_connect_bufferµÄ±êÖ¾Î»À´ÅÐ¶ÏÒì²½ÓëÍ¬²½
// 	if (buffer.get_is_sync()) {
// 		return sync_write(tmp_buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	else {
// 		return async_write(tmp_buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	return 0;
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£º¶ÁÈ¡Êý¾Ý²¢´æÔÚÖ¸¶¨»º´æÎ»ÖÃ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦¶ÁÈ¡µÄÊý¾Ý³¤¶È£»
*
* @param buf    ±íÊ¾¶ÁÈ¡Êý¾Ý´æÔÚµÄÖ¸¶¨»º´æµØÖ·
*
* @param len    ±íÊ¾¶ÁÈ¡Êý¾Ý´æÔÚµÄÖ¸¶¨»º´æ³¤¶È
* @param callback    ±íÊ¾¶ÁÈ¡µÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::read(csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	//ÏÈÅÐ¶ÏÊý¾ÝµÄºÏ·¨ÐÔ£¬Ö®ºóÔÙ´¦Àí
// 	if (csf_nullptr == buf
// 		|| len <= 0) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
// 		return csf_failure;
// 	}
// 
// 	//¸ù¾Ýcsf_connect_bufferµÄ±êÖ¾Î»À´ÅÐ¶ÏÒì²½ÓëÍ¬²½
// 	if (csf_nullptr == callback) {
// 		return sync_read(buf, len, callback);
// 	}
// 	else {
// 		return async_read(buf, len, callback);
// 	}
// 	return 0;
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£º¶ÁÈ¡Êý¾Ý²¢´æÔÚÖ¸¶¨»º´æÎ»ÖÃ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦¶ÁÈ¡µÄÊý¾Ý³¤¶È£»
*
* @param buffer    ±íÊ¾¶ÁÈ¡Êý¾Ý´æÔÚµÄcsf_buffer
* @param len    ±íÊ¾¶ÁÈ¡Êý¾Ý´æÔÚµÄÖ¸¶¨»º´æ³¤¶È
* @param callback    ±íÊ¾¶ÁÈ¡µÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::read(csf_buffer& buffer, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	//Ê£Óà¿Õ¼ä³ä×ãÊ±£¬ÔòÖ±½Ó´¦Àí
// 	if (buffer.avail() >= len) {
// 		return read(buffer.get_buffer(), len, callback);
// 	}
// 	else {
// 		//Èç¹ûÊ£ÓàµÄ¿Õ¼ä²»×ã£¬Ôò±¨³öÒì³£
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
// 				, "not enough storage available"));
// 		return csf_failure;
// 	}
// 
// 	return 0;
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£º¶ÁÈ¡Êý¾Ý²¢´æÔÚÖ¸¶¨»º´æÎ»ÖÃ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦¶ÁÈ¡µÄÊý¾Ý³¤¶È£»
*
* @param csfstr    ±íÊ¾¶ÁÈ¡Êý¾Ý´æÔÚµÄcsf_csfstring
* @param len    ±íÊ¾¶ÁÈ¡Êý¾Ý´æÔÚµÄÖ¸¶¨»º´æ³¤¶È
* @param callback    ±íÊ¾¶ÁÈ¡µÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::read(csf_csfstring& csfstr, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	//Ê£Óà¿Õ¼ä³ä×ãÊ±£¬ÔòÖ±½Ó´¦Àí
// 	if (csfstr.length() >= len) {
// 		return read(csfstr.get_buffer(), len, callback);
// 	}
// 	else {
// 		//Èç¹ûÊ£ÓàµÄ¿Õ¼ä²»×ã£¬Ôò±¨³öÒì³£
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
// 				, "not enough storage available"));
// 		return csf_failure;
// 	}
// 
// 	return 0;
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£º¶ÁÈ¡Êý¾Ý²¢´æÔÚÖ¸¶¨»º´æÁ´±íÖÐ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦¶ÁÈ¡µÄÊý¾Ý³¤¶È£»
*
* @param chain    ±íÊ¾¶ÁÈ¡Êý¾Ý´æÔÚµÄcsf_csfstring
* @param len    ±íÊ¾¶ÁÈ¡Êý¾Ý´æÔÚµÄÖ¸¶¨»º´æ³¤¶È
* @param callback    ±íÊ¾¶ÁÈ¡µÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::read(csf_chain& chain, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	//ÏÈÅÐ¶ÏÊý¾ÝµÄºÏ·¨ÐÔ£¬Ö®ºóÔÙ´¦Àí
// 	if (len <= 0) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
// 				, "not enough storage available"));
// 		return csf_failure;
// 	}
// 
// 	csf_int32		tmp_length = 0;
// 	csf_buffer		tmp_buffer(len);
// 
// 	//chainÖ»ÄÜ½øÐÐÍ¬²½½ÓÊÕºÍ±£´æ´¦Àí
// 	tmp_length = read(tmp_buffer, len, csf_nullptr);
// 	if (tmp_length >= (csf_int32)len) {
// 		chain.add(tmp_buffer);
// 		async_callback(shared_from_this(), callback, csf_ip_connect_error());
// 		return csf_succeed;
// 	}
// 	else {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_operation_error, "read data error"));
// 
// 		return csf_failure;
// 	}
// 
// 	return 0;
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£º¶ÁÈ¡Êý¾Ý²¢´æÔÚÖ¸¶¨»º´æÎ»ÖÃ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦¶ÁÈ¡µÄÊý¾Ý³¤¶È£»
*
* @param buffer    ±íÊ¾¶ÁÈ¡Êý¾Ý´æ·ÅµÄ»º´æ¶ÔÏó
*
* @param callback    ±íÊ¾¶ÁÈ¡µÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback) {
// 
// 	//ÏÈÅÐ¶ÏÊý¾ÝµÄºÏ·¨ÐÔ£¬Ö®ºóÔÙ´¦Àí
// 	if (!buffer.is_valid()) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
// 				, "not enough storage available"));
// 		return csf_failure;
// 	}
// 	//¸üÐÂfilled±êÖ¾Î»
// 	set_is_filled(buffer.get_is_filled());
// 
// 	//¸ù¾Ýcsf_connect_bufferµÄ±êÖ¾Î»À´ÅÐ¶ÏÒì²½ÓëÍ¬²½
// 	if (buffer.get_is_sync()) {
// 		return sync_read(buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	else {
// 		return async_read(buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 
// 	return csf_succeed;
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£º¶ÁÈ¡Êý¾Ý²¢´æÔÚÖ¸¶¨»º´æÎ»ÖÃ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦¶ÁÈ¡µÄÊý¾Ý³¤¶È£»
*
* @param buffer    ±íÊ¾¶ÁÈ¡Êý¾Ý´æÔÚµÄ»º´æ¶ÔÏó
* @param callback    ±íÊ¾¶ÁÈ¡µÄ»Øµ÷º¯Êý
*/
//  csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {
//  
//  	//ÏÈÅÐ¶ÏÊý¾ÝµÄºÏ·¨ÐÔ£¬Ö®ºóÔÙ´¦Àí
//  	if (!buffer.is_valid()) {
//  		exception_callback(shared_from_this()
//  			, callback
//  			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
//  				, "not enough storage available"));
//  		return csf_failure;
//  	}
//  
//  	//Èç¹û½ÓÊÕ³¤¶ÈÎª¿Õ£¨buffer.get_length()Îª0£©£¬Ôò±íÊ¾²ÉÓÃËÞÖ÷ÈÝÆ÷µÄ¿ÕÏÐ¿Õ¼ä´óÐ¡¡£
//  	//ÕâÑù´¦ÀíÖ÷ÒªÎª¼õÉÙÊÕ·¢²Ù×÷Ê±µÄÊ¹ÓÃ³É±¾£¬ÓÃ»§²»ÓÃ¼ÇµÃ±ØÐëµ÷ÓÃbuffer.set_length()º¯Êý¡£µ«µ×²ãµÄ×Ô¶¯´¦Àí£¬Í¬Ê±ÒýÈëÁË³ÌÐòµÄ²»È·¶¨ÐÔ¡£
//  	//·¢ËÍÄ¬ÈÏ³¤¶ÈÎªËÞÖ÷ÈÝÆ÷ÖÐÊý¾ÝµÄ³¤¶È
//  	//½ÓÊÕÄ¬ÈÏ³¤¶ÈÎªËÞÖ÷ÈÝÆ÷ÖÐ¿ÕÏÐ¿Õ¼äµÄ³¤¶È
//  	if (buffer.get_length() <= 0 && buffer.avail() > 0) {
//  		buffer.set_length(buffer.avail());
//  	}
//  
//  	//¸üÐÂfilled±êÖ¾Î»
//  	set_is_filled(buffer.get_is_filled());
//  
//  	//¸ù¾Ýcsf_connect_bufferµÄ±êÖ¾Î»À´ÅÐ¶ÏÒì²½ÓëÍ¬²½
//  	if (buffer.get_is_sync()) {
//  		//return sync_read(buffer.get_buffer(), buffer.get_length(), callback);
//  		return sync_read(buffer, callback);
//  	}
//  	else {
//  		//return async_read(buffer.get_buffer(), buffer.get_length(), callback);
//  		return async_read(buffer, callback);
//  	}
//  	return 0;
//  }


/**
* Ö÷Òª¹¦ÄÜÊÇ£º¶ÁÈ¡Êý¾Ý²¢´æÔÚÖ¸¶¨»º´æÎ»ÖÃ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦¶ÁÈ¡µÄÊý¾Ý³¤¶È£»
*
* @param buffer    ±íÊ¾¶ÁÈ¡Êý¾Ý´æÔÚµÄ»º´æ¶ÔÏó
* @param callback    ±íÊ¾¶ÁÈ¡µÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback) {
// 
// 	//ÏÈÅÐ¶ÏÊý¾ÝµÄºÏ·¨ÐÔ£¬Ö®ºóÔÙ´¦Àí
// 	if (!buffer.is_valid()) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
// 				, "not enough storage available"));
// 		return csf_failure;
// 	}
// 	//¸üÐÂfilled±êÖ¾Î»
// 	set_is_filled(buffer.get_is_filled());
// 
// 	//¸ù¾Ýcsf_connect_bufferµÄ±êÖ¾Î»À´ÅÐ¶ÏÒì²½ÓëÍ¬²½
// 	if (buffer.get_is_sync()) {
// 		return sync_read(buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	else {
// 		return async_read(buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	return 0;
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£º¶ÁÈ¡Êý¾Ý²¢´æÔÚÖ¸¶¨»º´æÁ´±íÖÐ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦¶ÁÈ¡µÄÊý¾Ý³¤¶È£»
*
* @param buffer    ±íÊ¾¶ÁÈ¡Êý¾Ý´æÔÚµÄ»º´æ¶ÔÏó
* @param callback    ±íÊ¾¶ÁÈ¡µÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback) {
// 
// 	//ÏÈÅÐ¶ÏÊý¾ÝµÄºÏ·¨ÐÔ£¬Ö®ºóÔÙ´¦Àí
// 	if (!buffer.is_valid()) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
// 				, "not enough storage available"));
// 
// 		return csf_failure;
// 	}
// 
// 	return read(*(buffer.get_buffer()), buffer.get_length(), callback);
// }


/**
* ±íÊ¾Ð´ÈëÖ¸¶¨»º´æµÄÄÚÈÝ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦Ð´ÈëµÄÊý¾Ý³¤¶È£»
*
* @param buf    ±íÊ¾ÄÚÈÝµÄ»º´æµØÖ·
* @param len    ±íÊ¾ÄÚÈÝ»º´æµÄ³¤¶È
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::sync_write(const csf_uchar* buf
// 	, const csf_uint32 len
// 	, const csf_connect_callback& callback) {
// 
// 	csf_int32						tmp_length = 0;
// 	csf_int32						tmp_send_length = 0;
// 	boost::system::error_code		tmp_error_code;
// 
// 
// 	get_write_timeout().flush_time();
// 
// 	//Ñ­»··¢ËÍÊý¾ÝÄÚÈÝ£¬Ö±µ½Êý¾Ý·¢ËÍÍê³ÉÎªÖ¹
// 	while (tmp_send_length < (csf_int32)len)
// 	{
// 		tmp_length = get_socket().send(
// 			boost::asio::buffer(buf + tmp_send_length, len - tmp_send_length)
// 			, 0
// 			, tmp_error_code);
// 		if (tmp_length <= 0 || tmp_error_code) {
// 
// 			exception_callback(shared_from_this(), callback, csf_ip_connect_error(tmp_error_code));
// 
// 			return csf_failure;
// 		}
// 		tmp_send_length += tmp_length;
// 	}
// 
// 	exception_callback(shared_from_this(), callback, csf_ip_connect_error());
// 
// 	return len;
// }


/**
* ±íÊ¾Ð´ÈëÖ¸¶¨»º´æµÄÄÚÈÝ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦Ð´ÈëµÄÊý¾Ý³¤¶È£»
*
* @param buf    ±íÊ¾ÄÚÈÝµÄ»º´æµØÖ·
* @param len    ±íÊ¾ÄÚÈÝ»º´æµÄ³¤¶È
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::async_write(const csf_uchar* buf
// 	, const csf_uint32 len
// 	, const csf_connect_callback& callback) {
// 
// 	get_write_timeout().flush_time();
// 
// 	//ÕâÀïÖ÷ÒªÊÇÊý¾ÝÁ¿Ò»´ó£¬¾Í·¢ËÍ²»ÍêÈ«ÁË¡£ÓÈÆäÔÚlinuxÆ½Ì¨ÏÂ¸üÈÝÒ×³öÏÖÕâ¸öÎÊÌâ
// 	get_socket().async_write_some(boost::asio::buffer(buf, len)
// 		, boost::bind(&csf_tcp_connect::async_write_callback
// 			, this
// 			, buf
// 			, len
// 			, callback
// 			, boost::asio::placeholders::error
// 			, boost::asio::placeholders::bytes_transferred));
// 
// 	return len;
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£º´¦ÀíÒì²½Ð´´¦Àí»Øµ÷º¯Êý
* ·µ»Ø£º0±íÊ¾´¦Àí³É¹¦£»·Ç0±íÊ¾´¦ÀíÊ§°Ü
*
* @param buf		 ±íÊ¾ÄÚÈÝµÄ»º´æµØÖ·
* @param src_len	 ±íÊ¾ÐèÒª±»´¦ÀíµÄÔ´ÄÚÈÝ»º´æµÄ³¤¶È
* @param callback    ±íÊ¾Òì³£´¦Àí¾ä±úÐÅÏ¢
* @param error_code  ±íÊ¾boostµÄ´íÎóÐÅÏ¢
* @param write_len   ±íÊ¾µ±Ç°Êµ¼ÊÐ´µÄ»º´æ³¤¶È
*/
// csf_bool csf_tcp_connect::async_write_callback(const csf_uchar* buf
// 	, const csf_uint32 src_len
// 	, const csf_connect_callback& callback
// 	, const boost::system::error_code& error_code
// 	, csf_uint32 write_len) {
// 
// 	//Èç¹û´¦Àí´íÎó£¬Ôò°´ÕÕ´íÎó´¦Àí
// 	if (error_code) {
// 		exception_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
// 		return csf_false;
// 	}
// 	//Èç¹ûÒÑ¾­·¢ËÍÍê³ÉËùÓÐÊý¾Ý£¬ÔòÕý³£»Øµ÷·µ»Ø
// 	if (write_len >= src_len) {
// 		async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
// 		return csf_true;
// 	}
// 	else {
// 		//Èç¹ûÃ»ÓÐ·¢ËÍÍêÈ«£¬»¹ÓÐ²¿·ÖÊý¾Ý£¬Ôò¼ÌÐø·¢ËÍ
// 		async_write(buf + write_len, src_len - write_len, callback);
// 	}
// 
// 	return csf_true;
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£ºÍ¬²½¶ÁÈ¡Êý¾Ý£¬²¢·ÅÈëÖ¸¶¨»º´æ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦¶ÁÈëµÄÊý¾Ý³¤¶È£»
*
* @param buf    ±íÊ¾ÄÚÈÝµÄ»º´æµØÖ·
* @param len    ±íÊ¾ÄÚÈÝ»º´æµÄ³¤¶È
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::sync_read(csf_uchar* buf
// 	, const csf_uint32 len
// 	, const csf_connect_callback& callback) {
// 
// 	csf_int32						tmp_length = 0;
// 	csf_int32						tmp_receive_length = 0;
// 	boost::system::error_code		tmp_error_code;
// 
// 
// 	 do {
// 
// 		get_read_timeout().flush_time();
// 
// 		//½ÓÊÕÊý¾Ý
// 		tmp_length = get_socket().receive(boost::asio::buffer(buf + tmp_receive_length, len - tmp_receive_length)
// 			, 0
// 			, tmp_error_code);
// 		if (tmp_error_code) {
// 			//Èç¹û³öÏÖÍ¨ÐÅ´íÎó£¬Ôò´íÎó´¦Àí
// 			exception_callback(shared_from_this(), callback, csf_ip_connect_error(tmp_error_code));
// 			return csf_failure;
// 		}
// 		else if (tmp_receive_length <= 0) {
// 			//Èç¹û³öÏÖÊý¾ÝÄÚÈÝ´íÎó£¬ÔòÁíÍâ´¦Àí
// 			csf_ip_connect_error			tmp_error;
// 
// 			tmp_error.set_error(csf_connect_error::csf_connect_code_operation_error
// 				,"receive data length[ %d <=0 ]"
// 				, tmp_length);
// 			exception_callback(shared_from_this(), callback, tmp_error);
// 			return csf_failure;
// 		}
// 		else {
// 			//ÀÛ¼ÓÊý¾Ý³¤¶È
// 			tmp_receive_length += tmp_length;
// 		}
// 
// 	} while ((csf_int32)len > tmp_receive_length && csf_true == get_is_filled());		//ÅÐ¶ÏÊÇ·ñÌî³äÂú£¬Èç¹ûÐèÒªÔòÑ­»·´¦ÀíÖ±µ½Ìî³äÂú
// 
// 	return tmp_receive_length;
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£ºÒì²½¶ÁÈ¡Êý¾Ý£¬²¢·ÅÈëÖ¸¶¨»º´æ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦¶ÁÈëµÄÊý¾Ý³¤¶È£»
*
* @param buf    ±íÊ¾ÄÚÈÝµÄ»º´æµØÖ·
* @param len    ±íÊ¾ÄÚÈÝ»º´æµÄ³¤¶È
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
// csf_int32 csf_tcp_connect::async_read(csf_uchar* buf
// 	, const csf_uint32 len
// 	, const csf_connect_callback& callback) {
// 
// 	get_read_timeout().flush_time();
// 
// 	get_socket().async_receive(boost::asio::buffer(buf, len)
// 		, boost::bind(&csf_tcp_connect::async_read_callback
// 			, this
// 			, buf
// 			, len
// 			, callback
// 			, boost::asio::placeholders::error
// 			, boost::asio::placeholders::bytes_transferred));
// 
// 	return 0;
// }


/**
* Ö÷Òª¹¦ÄÜÊÇ£º´¦ÀíÒì²½¶Á´¦Àí»Øµ÷º¯Êý
* ·µ»Ø£º0±íÊ¾´¦Àí³É¹¦£»·Ç0±íÊ¾´¦ÀíÊ§°Ü
*
* @param buf		 ±íÊ¾ÄÚÈÝµÄ»º´æµØÖ·
* @param buf_len	 ±íÊ¾ÐèÒª±»´¦ÀíµÄÔ´ÄÚÈÝ»º´æµÄ³¤¶È
* @param callback    ±íÊ¾Òì³£´¦Àí¾ä±úÐÅÏ¢
* @param error_code  ±íÊ¾boostµÄ´íÎóÐÅÏ¢
* @param read_len   ±íÊ¾µ±Ç°Êµ¼ÊÐ´µÄ»º´æ³¤¶È
*/
// csf_bool csf_tcp_connect::async_read_callback(csf_uchar* buf
// 	, const csf_uint32 buf_len
// 	, const csf_connect_callback& callback
// 	, const boost::system::error_code& error_code
// 	, csf_uint32 read_len) {
// 
// 	//Èç¹û´¦Àí´íÎó£¬Ôò°´ÕÕ´íÎó´¦Àí
// 	if (error_code) {
// 		exception_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
// 		return csf_false;
// 	}
// 
// 	//Èç¹ûÐèÒª½ÓÊÕËùÓÐÊý¾Ý£¬Ôò¼ÌÐø½ÓÊÕ£¬Ö±µ½ÍêÕû½ÓÊÕÍêÈ«
// 	if (csf_false == get_is_filled()) {
// 		async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
// 		return csf_true;
// 	}
// 	else {
// 		//Èç¹ûÒÑ¾­·¢ËÍÍê³ÉËùÓÐÊý¾Ý£¬ÔòÕý³£»Øµ÷·µ»Ø
// 		if (read_len >= buf_len) {
// 			async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
// 			return csf_true;
// 		}
// 		else {
// 			//Èç¹ûÃ»ÓÐ·¢ËÍÍêÈ«£¬»¹ÓÐ²¿·ÖÊý¾Ý£¬Ôò¼ÌÐø·¢ËÍ
// 			async_read(buf + read_len, buf_len - read_len, callback);
// 		}
// 	}
// 
// 	return csf_true;
// }




/**
* ±íÊ¾Ð´ÈëÖ¸¶¨»º´æµÄÄÚÈÝ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦Ð´ÈëµÄÊý¾Ý³¤¶È£»
*
* @param buffer    ±íÊ¾ÄÚÈÝµÄ»º´æµØÖ·
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
csf_int32 csf_tcp_connect::sync_write(csf_connect_buffer<csf_buffer>& buffer
	, const csf_connect_callback& callback) {

	csf_uchar						*tmp_buf = buffer.get_buffer();
	csf_int32						tmp_total_length = buffer.get_length();
	csf_int32						tmp_length = 0;
	csf_int32						tmp_send_length = 0;
	boost::system::error_code		tmp_error_code;


	get_write_timeout().flush_time();

	//Ñ­»··¢ËÍÊý¾ÝÄÚÈÝ£¬Ö±µ½Êý¾Ý·¢ËÍÍê³ÉÎªÖ¹
	while (tmp_send_length < (csf_int32)tmp_total_length)
	{
		tmp_length = get_socket().send(
			boost::asio::buffer(tmp_buf + tmp_send_length, tmp_total_length - tmp_send_length)
			, 0
			, tmp_error_code);
		if (tmp_length <= 0 || tmp_error_code) {

			exception_callback(shared_from_this(), callback, csf_ip_connect_error(tmp_error_code));

			return csf_failure;
		}
		tmp_send_length += tmp_length;
	}

	exception_callback(shared_from_this(), callback, csf_ip_connect_error());

	return tmp_total_length;
}


/**
* ±íÊ¾Ð´ÈëÖ¸¶¨»º´æµÄÄÚÈÝ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦Ð´ÈëµÄÊý¾Ý³¤¶È£»
*
* @param buffer    ±íÊ¾ÄÚÈÝµÄ»º´æµØÖ·
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
csf_int32 csf_tcp_connect::async_write(csf_connect_buffer<csf_buffer>& buffer
	, const csf_connect_callback& callback) {

	get_write_timeout().flush_time();

	//ÕâÀïÖ÷ÒªÊÇÊý¾ÝÁ¿Ò»´ó£¬¾Í·¢ËÍ²»ÍêÈ«ÁË¡£ÓÈÆäÔÚlinuxÆ½Ì¨ÏÂ¸üÈÝÒ×³öÏÖÕâ¸öÎÊÌâ
	get_socket().async_write_some(boost::asio::buffer(buffer.get_buffer()
		, buffer.get_length())
		, boost::bind(&csf_tcp_connect::async_write_callback
			, this
			, std::ref(buffer)
			, shared_from_this()
			, callback
			, boost::asio::placeholders::error
			, boost::asio::placeholders::bytes_transferred));

	return buffer.get_length();
}


/**
* Ö÷Òª¹¦ÄÜÊÇ£ºÍ¬²½¶ÁÈ¡Êý¾Ý£¬²¢·ÅÈëÖ¸¶¨»º´æ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦¶ÁÈëµÄÊý¾Ý³¤¶È£»
*
* @param buffer    ±íÊ¾ÄÚÈÝµÄ»º´æµØÖ·
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
csf_int32 csf_tcp_connect::sync_read(csf_connect_buffer<csf_buffer>& buffer
	, const csf_connect_callback& callback) {

	csf_uchar						*tmp_buf = buffer.get_buffer();
	csf_int32						tmp_total_length = buffer.get_length();
	csf_int32						tmp_length = 0;
	csf_int32						tmp_receive_length = 0;
	boost::system::error_code		tmp_error_code;


	do {

		get_read_timeout().flush_time();

		//½ÓÊÕÊý¾Ý
		tmp_length = get_socket().receive(boost::asio::buffer(tmp_buf + tmp_receive_length
			, tmp_total_length - tmp_receive_length)
			, 0
			, tmp_error_code);
		if (tmp_error_code) {
			//Èç¹û³öÏÖÍ¨ÐÅ´íÎó£¬Ôò´íÎó´¦Àí
			exception_callback(shared_from_this(), callback, csf_ip_connect_error(tmp_error_code));
			return csf_failure;
		}
		else if (tmp_length <= 0) {
			//Èç¹û³öÏÖÊý¾ÝÄÚÈÝ´íÎó£¬ÔòÁíÍâ´¦Àí
			csf_ip_connect_error			tmp_error;

			tmp_error.set_error(csf_connect_error::csf_connect_code_operation_error
				, "receive data length[ %d <= 0 ]"
				, tmp_length);
			exception_callback(shared_from_this(), callback, tmp_error);
			return csf_failure;
		}
		else {
			//ÀÛ¼ÓÊý¾Ý³¤¶È
			tmp_receive_length += tmp_length;
		}

	} while ((csf_int32)tmp_total_length > tmp_receive_length
		&& csf_true == buffer.get_is_filled());		//ÅÐ¶ÏÊÇ·ñÌî³äÂú£¬Èç¹ûÐèÒªÔòÑ­»·´¦ÀíÖ±µ½Ìî³äÂú

	return tmp_receive_length;
}


/**
* Ö÷Òª¹¦ÄÜÊÇ£ºÒì²½¶ÁÈ¡Êý¾Ý£¬²¢·ÅÈëÖ¸¶¨»º´æ¡£
* ·µ»Ø£ºÐ¡ÓÚµÈÓÚ0±íÊ¾Ê§°Ü£»´óÓÚ0±íÊ¾³É¹¦¶ÁÈëµÄÊý¾Ý³¤¶È£»
*
* @param buffer    ±íÊ¾ÄÚÈÝµÄ»º´æµØÖ·
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
csf_int32 csf_tcp_connect::async_read(csf_connect_buffer<csf_buffer>& buffer
	, const csf_connect_callback& callback) {

	get_read_timeout().flush_time();

	get_socket().async_receive(boost::asio::buffer(buffer.get_buffer(), buffer.get_length())
		, boost::bind(&csf_tcp_connect::async_read_callback
			, this
			, std::ref(buffer)
			, shared_from_this()
			, callback
			, boost::asio::placeholders::error
			, boost::asio::placeholders::bytes_transferred));

	return 0;
}


/**
* ±íÊ¾Ô¶³ÌµÄÖ÷»úµØÖ·
*/
const csf_url& csf_tcp_connect::get_remote_url() const {

	//ÅÐ¶ÏÏÖÔÚµÄµØÖ·ÊÇ·ñ´æÔÚ£¬´æÔÚÔòÖ±½Ó·µ»Ø
	if (csf_ip_connect::get_remote_url().get_url().empty()
		&& get_socket().is_open()) {

		((csf_ip_url&)csf_ip_connect::get_remote_url()).set_url(
			get_socket().remote_endpoint().address().to_string()
			, get_socket().remote_endpoint().port());
	}

	return csf_ip_connect::get_remote_url();
}


/**
* ±íÊ¾±¾µØµÄÖ÷»úµØÖ·
*/
const csf_url& csf_tcp_connect::get_local_url() const {

	//ÅÐ¶ÏÏÖÔÚµÄµØÖ·ÊÇ·ñ´æÔÚ£¬´æÔÚÔòÖ±½Ó·µ»Ø
	if (csf_ip_connect::get_local_url().get_url().empty()
		&& get_socket().is_open()) {

		((csf_ip_url&)csf_ip_connect::get_local_url()).set_url(
			get_socket().local_endpoint().address().to_string()
			, get_socket().local_endpoint().port());
	}

	return csf_ip_connect::get_local_url();
}


/**
* Ö÷Òª¹¦ÄÜÊÇ£ºÒì²½tcp¼àÌýµÄaccept´¦Àíº¯Êý¡£
* ·µ»Ø£º0±íÊ¾³É¹¦£»·Ç0±íÊ¾Ê§°Ü£»
*
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
*/
csf::core::base::csf_int32 csf_tcp_connect::async_accept(const csf_connect_callback callback) {

	csf_tcp_connect		*tmp_connect = csf_nullptr;


	while (csf_true) {
		try {
			//ÕâÀïÖ÷Òª½â¾öÓÐÐ©Ê±ºònewÊ§°ÜµÄÎÊÌâ
			tmp_connect = new csf_tcp_connect(this);
			if (tmp_connect) {
				break;
			}
			else {
				csf_log_ex(error
					, csf_log_code_error
					, "create csf_tcp_connect() instance failed!");
			}
		}
		catch (boost::exception& e) {

			csf_log_ex(error, csf_log_code_error
				, "create csf_tcp_connect() instance exception! reason:[%s -- %s]."
				, boost::current_exception_diagnostic_information().c_str()
				, boost::diagnostic_information(e).c_str());

			continue;
		}
	}

	//ÎªÃ¿¸öÁ¬½ÓÌí¼ÓÒ»¸öÊ±¼ä´Á£¬Ö÷ÒªÎªÁË·½±ã³¬Ê±¡¢¿ÕÁ¬½ÓµÈ´¦Àí
	get_acceptor()->async_accept(
		tmp_connect->get_socket()
		, boost::bind(&csf_tcp_connect::accept_handle
			, this
			, csf_tcp_connect_ptr(tmp_connect)
			, callback
			, _1));

	return csf_succeed;
}


/**
* Ö÷Òª¹¦ÄÜÊÇ£ºÒì²½tcp¼àÌýµÄaccept»Øµ÷´¦Àíº¯Êý¡£
* ·µ»Ø£ºÎÞ
*
* @param connect_ptr    ±íÊ¾µ±Ç°ÍøÂçÍ¨ÐÅÁ¬½Ó¶ÔÏó
* @param callback    ±íÊ¾ÐèÒª·µ»ØµÄ»Øµ÷º¯Êý
* @param ec    ±íÊ¾µ±Ç°µÄ´íÎóÐÅÏ¢
*/
csf_void csf_tcp_connect::accept_handle(csf_tcp_connect_ptr connect_ptr
	, const csf_connect_callback callback
	, boost::system::error_code ec) {

	if (ec) {

		csf_log_ex(error
			, csf_log_code_error
			, "accept connect failed! reason:[%d] %s"
			, ec.value()
			, boost::system::system_error(ec).what());

		return;
	}

	//¼ÌÐøµÈ´ýÏÂÒ»¸ötcpÁ¬½ÓÇëÇó
	async_accept(callback);

	//ÉèÖÃ¿ÕÁ¬½Ó³¬Ê±´¦Àí¡£Èç¹û³¬¹ý¸ÃÊ±¼ä£¬Ôò±íÊ¾¿ÕÁ¬½Ó£¬ÐèÒª¹Ø±Õ´¦Àí¡£
	if (get_factory()) {

		if (csf_failure == ((csf_ip_connect_factory*)get_factory())->insert((csf_connect_ptr)connect_ptr)) {
			csf_log_ex(warning
				, csf_log_code_warning
				, "accept [%d/%d] %s over load warning. connect limit[%d]."
				, get_factory()->get_connect_collector().size()
				, ((csf_ip_connect_factory*)get_factory())->get_connect_limit()
				, connect_ptr->to_string().c_str()
				, ((csf_ip_connect_factory*)get_factory())->get_connect_limit());
			return;
		}
		connect_ptr->set_read_timeout(
			((csf_ip_connect_factory*)get_factory())->get_connect_timeout(), csf_nullptr);

		csf_log_ex(notice
			, csf_log_code_notice
			, "accept [%d/%d] %s succeed!"
			, get_factory()->get_connect_collector().size()
			, ((csf_ip_connect_factory*)get_factory())->get_connect_limit()
			, connect_ptr->to_string().c_str());
	}
	else {
		connect_ptr->set_read_timeout(csf_connect_timeout_default_ms, csf_nullptr);

		csf_log_ex(notice
			, csf_log_code_notice
			, "accept %s succeed!"
			, connect_ptr->to_string().c_str());
	}

	// 	csf_log_ex(info
	// 		, csf_log_code_info
	// 		, "accept %s."
	// 		, connect_ptr->to_string().c_str());

	//µ÷ÓÃ»Øµ÷º¯ÊýÍ¨Öª½ÓÊÕÊý¾ÝµÈ¸÷ÖÖ´¦Àí
	async_callback((csf_connect_ptr&)connect_ptr, callback, csf_ip_connect_error());
}


/**
* Ö÷Òª¹¦ÄÜ£º
*    ±íÊ¾socketÁ¬½Ó¶ÔÏó
* ·µ»Ø£º
*    0£º±íÊ¾³É¹¦£»
*    ·Ç0£º±íÊ¾Ê§°Ü£»
*/
csf_int32 csf_tcp_connect::close_socket() {

	if (get_socket().is_open()) {

		try {
			int									tmp_ret_int = 0;
			struct linger						tmp_linger = { 0, 0 };
			boost::system::error_code			tmp_error_code;


#if 0  //Ö÷ÒªÊÇboost_1_69_0ÖÐÃ»ÓÐget_socket().native() º¯Êý
			//ÉèÖÃÎªÁ¢¼´¹Ø±Õ´¦Àí£¬±ÜÃâ³öÏÖÑÓÊ±¹Ø±ÕµÄÎÊÌâ
			tmp_ret_int = setsockopt(get_socket().native()
				, SOL_SOCKET
				, SO_LINGER
				, (char*)(&tmp_linger)
				, sizeof(struct linger));
#endif

			//È¡ÏûËùÓÐ´¦Àí£¬¹Ø±ÕÊÕ·¢£¬¹Ø±ÕÁ¬½Ó¶ÔÏó
			get_socket().cancel();
			get_socket().shutdown(boost::asio::socket_base::shutdown_both, tmp_error_code);
			get_socket().close();
		}
		catch (boost::exception& e) {
			csf_log_ex(error
				, csf_log_code_error
				, "close %s failed! reason:[%s -- %s]."
				, to_string().c_str()
				, boost::current_exception_diagnostic_information().c_str()
				, boost::diagnostic_information(e).c_str());

			return csf_failure;
		}
	}

	return csf_succeed;
}