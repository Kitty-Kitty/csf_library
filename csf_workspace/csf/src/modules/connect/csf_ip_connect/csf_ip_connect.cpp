/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_ip_connect.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 15:10:39
*
*Description: Class(csf_ip_connect)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_ip_connect.hpp"

using csf::modules::connect::csf_ip_connect;


csf_ip_connect::~csf_ip_connect() {

}


/**
* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_ip_connect::write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {

	//���ж����ݵĺϷ��ԣ�֮���ٴ���
	if (!buffer.is_valid()) {
		exception_callback(shared_from_this()
			, callback
			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
		return csf_failure;
	}

	//���buffer��д���ȴ�Сû�����ã�buffer.get_length()Ϊ0��������������Ŀռ��С�Զ���������
	//����������ҪΪ�����շ�����ʱ��ʹ�óɱ����û����üǵñ������buffer.set_length()���������ײ���Զ�����ͬʱ�����˳���Ĳ�ȷ���ԡ�
	//����Ĭ�ϳ���Ϊ�������������ݵĳ���
	//����Ĭ�ϳ���Ϊ���������п��пռ�ĳ���
	if (buffer.get_length() <= 0 && buffer.length() > 0) {
		buffer.set_length(buffer.length());
	}

	//����csf_connect_buffer�ı�־λ���ж��첽��ͬ��
	if (buffer.get_is_sync()) {
		//return sync_write(buffer.get_buffer(), buffer.get_length(), callback);
		return sync_write(buffer, callback);
	}
	else {
		//return async_write(buffer.get_buffer(), buffer.get_length(), callback);
		return async_write(buffer, callback);
	}
	return 0;
}


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
* @param callback    ��ʾ��ȡ�Ļص�����
*/
csf_int32 csf_ip_connect::read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {

	//���ж����ݵĺϷ��ԣ�֮���ٴ���
	if (!buffer.is_valid()) {
		exception_callback(shared_from_this()
			, callback
			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
				, "not enough storage available"));
		return csf_failure;
	}

	//������ճ���Ϊ�գ�buffer.get_length()Ϊ0�������ʾ�������������Ŀ��пռ��С��
	//����������ҪΪ�����շ�����ʱ��ʹ�óɱ����û����üǵñ������buffer.set_length()���������ײ���Զ�����ͬʱ�����˳���Ĳ�ȷ���ԡ�
	//����Ĭ�ϳ���Ϊ�������������ݵĳ���
	//����Ĭ�ϳ���Ϊ���������п��пռ�ĳ���
	if (buffer.get_length() <= 0 && buffer.avail() > 0) {
		buffer.set_length(buffer.avail());
	}

	//����filled��־λ
	set_is_filled(buffer.get_is_filled());

	//����csf_connect_buffer�ı�־λ�ͻص������Ƿ�Ϊ�����ж��첽��ͬ��
	if (buffer.get_is_sync() || csf_nullptr == callback) {
		//return sync_read(buffer.get_buffer(), buffer.get_length(), callback);
		return sync_read(buffer, callback);
	}
	else {
		//return async_read(buffer.get_buffer(), buffer.get_length(), callback);
		return async_read(buffer, callback);
	}
	return 0;
}


/**
* ��Ҫ�����ǣ������첽д����ص�����
* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
*
* @param buffer		 ��ʾ���ݵĻ���
* @param connect_ptr ��ʾ��ǰ���������Ӷ���
* @param callback    ��ʾ�쳣��������Ϣ
* @param error_code  ��ʾboost�Ĵ�����Ϣ
* @param length		��ʾ��ǰʵ��д�Ļ��泤��
*/
csf_bool csf_ip_connect::async_write_callback(csf_connect_buffer<csf_buffer>& buffer
	, csf_connect_ptr connect_ptr
	, const csf_connect_callback& callback
	, const boost::system::error_code& error_code
	, csf_uint32 length) {


	//�������������մ�����
	if (error_code) {
		exception_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
		return csf_false;
	}

	//����Ѿ���������������ݣ��������ص�����
	if (length >= buffer.get_length()) {
		async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
		return csf_true;
	}
	else {
		//���û�з�����ȫ�����в������ݣ�����»�����Ϣ��������
		buffer.get_container()->set_pos(buffer.get_container()->get_pos() + length);
		buffer.set_length(buffer.get_length() - length);

		async_write(std::ref(buffer), callback);
	}

	return csf_true;
}


/**
* ��Ҫ�����ǣ������첽������ص�����
* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
*
* @param buffer		 ��ʾ���ݵĻ���
* @param connect_ptr ��ʾ��ǰ���������Ӷ���
* @param callback    ��ʾ�쳣��������Ϣ
* @param error_code  ��ʾboost�Ĵ�����Ϣ
* @param length   ��ʾ��ǰʵ��д�Ļ��泤��
*/
csf_bool csf_ip_connect::async_read_callback(csf_connect_buffer<csf_buffer>& buffer
	, csf_connect_ptr connect_ptr
	, const csf_connect_callback& callback
	, const boost::system::error_code& error_code
	, csf_uint32 length) {

	//�������������մ�����
	if (error_code) {
		exception_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
		return csf_false;
	}

	if (length > 0) {
		//������յ����ݣ����ƶ�buffer�еĻ����α꣬������һ�ν���
		buffer.get_container()->set_last(buffer.get_container()->get_last() + length);
		buffer.set_length(buffer.get_length() - length);
	}

	//�����Ҫ�����������ݣ���������գ�ֱ������������ȫ
	if (csf_false == buffer.get_is_filled()) {
		async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
		return csf_true;
	}
	else {
		//����Ѿ���������������ݣ��������ص�����
		if (length >= buffer.get_length()) {
			async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
			return csf_true;
		}
		else {
			async_read(std::ref(buffer), callback);
		}
	}

	return csf_true;
}
