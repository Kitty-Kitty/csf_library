/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_factory.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 01-7��-2018 18:45:44
*
*Description: Class(csf_module_factory)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MODULE_FACTORY_INCLUDED_)
#define CSF_MODULE_FACTORY_INCLUDED_

#include "csf_mutex.hpp"
#include "csf_module_factory_printf.h"
#include "csf_module_factory_interface.hpp"
#include "csf_atomic.h"

class csf_module_factory_manager;

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			* �����������������
			*/
			#define csf_module_factory_create_handle_name					"create"
			#define csf_module_factory_destroy_handle_name					"destroy"

			#ifdef WIN32
			//��ʾ������Ϣ����ռ��С
			#define CSF_MODULE_FACTORY_MAX_ERROR_STRING						1024
			#endif

			typedef	csf_module* (*csf_module_create_handle)(const csf_configure_manager* conf_mg);
			typedef csf_int32 (*csf_module_destroy_handle)(const csf_module *module);


			/**
			 * ��ʾģ�鴴������
			 * @author fz
			 * @version 1.0
			 * @created 01-7��-2018 18:45:44
			 */
			class csf_module_factory : public csf::core::module::csf_module_factory_interface
			{

			public:
				inline explicit csf_module_factory()
					: m_count(0)
					, m_name("")
					, m_symbol_path("")
					, m_create_handle(csf_nullptr)
					, m_destroy_handle(csf_nullptr)
					, m_symbol_handle(csf_nullptr)
					, m_module_factory_manager(csf_nullptr)
					, m_configure_manager(csf_nullptr)
					, m_type(csf_module::csf_module_type::csf_module_type_none) {

				}
				/**
				 * ����module_configure����һ������
				 *
				 * @param module_configure    ��ʾģ���������Ϣ
				 */
				inline explicit csf_module_factory(const csf_void* mfm
					, const csf_configure_manager* cm
					, const csf_module_configure& module_configure)

					: csf_module_factory(
						mfm,
						cm,
						((csf_module_configure&)module_configure).get_name(),
						((csf_module_configure&)module_configure).get_file()) {
				}
				/**
				 * ����ģ�����ƺ�ģ���ļ�·������һ������
				 *
				 * @param name    ��ʾģ�������
				 * @param path    ��ʾģ�鶯̬���ļ�·��
				 */
				inline explicit csf_module_factory(const csf_void* mfm
					, const csf_configure_manager* cm
					, const csf_char* name, const csf_char* path)

					: m_count(0)
					, m_name(name)
					, m_symbol_path(path)
					, m_create_handle(csf_nullptr)
					, m_destroy_handle(csf_nullptr)
					, m_symbol_handle(csf_nullptr)
					, m_module_factory_manager((csf_module_factory_manager*)mfm)
					, m_configure_manager((csf_configure_manager*)cm)
					, m_type(csf_module::csf_module_type::csf_module_type_none) {


				}
				/**
				 * ����ģ�����ƺ�ģ���ļ�·������һ������
				 *
				 * @param name    ��ʾģ�������
				 * @param path    ��ʾģ�鶯̬���ļ�·��
				 */
				inline explicit csf_module_factory(const csf_void* mfm
					, const csf_configure_manager* cm
					, const csf_string& name
					, const csf_string& path)

					: csf_module_factory(mfm, cm, name.c_str(), path.c_str()) {
				}

				inline virtual ~csf_module_factory() {
					clear();
				}
				/**
				 * ��ʾ���ù�����
				 */
				inline csf_configure_manager* get_configure_manager() {

					return m_configure_manager;
				}
				/**
				 * ģ���ʼ��
				 *
				 * @param conf_mg    ��ʾ�����ļ���Ϣ
				 */
				virtual csf::core::base::csf_int32 init(const csf_configure_manager* conf_mg = csf_null);
				/**
				 * ����ģ������� ���أ�0��ʾ��ȷ��<0��ʾ�����룻
				 *
				 * @param module    ��ʾ��Ҫ���ٵ�ģ���ַ
				 */
				inline virtual csf_int32 destory(const csf_module* module) {

					csf_int32					tmp_ret = 0;

					//�ж��Ƿ��Ѿ����أ����δ���������
					if (!is_load()) {
						csf_module_factory_log(error, csf_log_code_error,
							"symbol unload error.");
						return csf_failure;
					}

					//�ͷ�ģ����Դ
					tmp_ret = get_destroy_handle()(module);
					if (tmp_ret) {
						csf_module_factory_log(warning, csf_log_code_warning,
							"destroy module[%p] return[%d] warning.",
							module,
							tmp_ret);
					}
					//�ͷ������������1
					down_count();

					return tmp_ret;
				}
				/**
				 * ��ʾ���ù�����
				 *
				 * @param newVal    newVal
				 */
				inline csf::core::base::csf_void set_configure_manager(const csf_configure_manager* newVal) {

					m_configure_manager = (csf_configure_manager*)newVal;
				}
				/**
				 * ģ������
				 *
				 * @param conf_mg    ��ʾ�����ļ���Ϣ
				 */
				virtual csf::core::base::csf_int32 start(const csf_configure_manager* conf_mg = csf_null);
				/**
				 * ����ģ������� ���أ��ǿձ�ʾ������ģ���ַ���ձ�ʾ����
				 *
				 * @param conf_mg    ��ʾģ�����������Ϣ
				 */
				virtual csf_module * create(const csf_configure_manager* conf_mg);

				inline csf::core::base::csf_int32 get_count() {

					return m_count;
				}
				/**
				 * ģ��ֹͣ
				 *
				 * @param conf_mg    ��ʾ�����ļ���Ϣ
				 */
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager* conf_mg = csf_null);
				inline const csf_string& get_name() {

					return m_name;
				}
				/**
				 * ��ʾģ�鴴�����
				 */
				inline csf::core::module::csf_module_create_handle get_create_handle() {

					return m_create_handle;
				}
				/**
				 * ��ʾģ�����پ��
				 */
				inline csf::core::module::csf_module_destroy_handle get_destroy_handle() {

					return m_destroy_handle;
				}
				/**
				 * �򿪶�̬���ӿ�󷵻ص�ָ��
				 */
				inline csf_void* get_symbol_handle() {

					return m_symbol_handle;
				}
				/**
				* ģ������
				*/
				inline const csf::core::module::csf_module::csf_module_type& get_type() {

					return m_type;
				}
				/**
				* ��ʾģ�鹤�������Ĺ���������
				*/
				inline csf_module_factory_manager* get_module_factory_manager() {

					return m_module_factory_manager;
				}
				/**
				* ���ܣ�����ͷ�������Դ
				*/
				csf_void clear();
			protected:
				/**
				* ��ʾģ����ļ�Ŀ¼
				*/
				inline const csf_string& get_symbol_path() {

					return m_symbol_path;
				}
				/**
				*
				* @param newVal    newVal
				*/
				inline csf_void set_count(const csf_int32 newVal) {

					m_count = newVal;
				}
				/**
				*
				* @param newVal    newVal
				*/
				inline csf_void set_name(const csf_string& newVal) {

					m_name = newVal;
				}
				/**
				* ��ʾģ����ļ�Ŀ¼
				*
				* @param newVal    newVal
				*/
				inline csf_void set_symbol_path(const csf_string& newVal) {

					m_symbol_path = newVal;
				}
				/**
				* �豸ģ�������
				*
				* @param newVal    ��ʾģ�������
				*/
				inline csf_void set_name(const csf_char* newVal) {

					m_name = newVal;
				}
				/**
				* ��ʾģ����ļ�Ŀ¼
				*
				* @param newVal    ��ʾ���õ�ģ�鶯̬����ļ�·��
				*/
				inline csf_void set_symbol_path(const csf_char* newVal) {

					m_symbol_path = newVal;
				}
				/**
				* ��ʾģ�鴴�����
				*
				* @param newVal    newVal
				*/
				inline csf::core::base::csf_void set_create_handle(const csf::core::module::csf_module_create_handle newVal) {
					m_create_handle = newVal;
				}
				/**
				* ��ʾģ�����پ��
				*
				* @param newVal    newVal
				*/
				inline csf::core::base::csf_void set_destroy_handle(const csf::core::module::csf_module_destroy_handle newVal) {
					m_destroy_handle = newVal;
				}
				/**
				* �򿪶�̬���ӿ�󷵻ص�ָ��
				*
				* @param newVal    newVal
				*/
				inline csf::core::base::csf_void set_symbol_handle(const csf_void* newVal) {

					m_symbol_handle = (csf_void*)newVal;
				}
				/**
				* ��ʾ���ض�̬��ģ�顣 ���أ��ǿգ�csf_null����ʾ�ɹ�����(csf_null)��ʾ����
				*
				* @param path    ��ʾ����ģ����ļ�·��
				*/
				inline csf_void* load(const csf_string& path) {

					if (path.empty()) {
						return csf_nullptr;
					}

					return  load(path.c_str());
				}
				/**
				* ��ʾ���ض�̬��ģ�顣 ���أ��ǿգ�csf_null����ʾ�ɹ�����(csf_null)��ʾ����
				*
				* @param path    ��ʾ����ģ����ļ�·��
				*/
				csf_void* load(const csf_char* path);
				/**
				* ж��ģ����
				*
				* @param symbol_handle    ��ʾ��Ҫж�صĶ�̬����
				*/
				csf::core::base::csf_void unload(const csf_void* symbol_handle);
				/**
				* ��ʾģ���Ƿ��Ѿ������ء� ���أ�csf_true��ʾ�Ѿ����أ�csf_false��ʾ��û�м��ء�
				*/
				inline csf_bool is_load() {

					if (get_symbol_handle() && get_create_handle() && get_destroy_handle()) {
						return csf_true;
					}

					return csf_false;
				}
				/**
				* ���Ҷ�̬���еķ��ž��
				*
				* @param handle    ��ʾ��̬���ļ����
				* @param name    ��ʾ��Ҫ��ȡ�ķ�������
				*/
				csf_void* find_symbol(const csf_void* handle, const csf_char* name);
				/**
				* ���Ҷ�̬���еķ��ž��
				*
				* @param handle    ��ʾ��̬���ļ����
				* @param name    ��ʾ��Ҫ��ȡ�ķ�������
				*/
				inline csf_void* find_symbol(const csf_void* handle, const csf_string& name) {

					if (!handle || name.empty()) {
						return csf_nullptr;
					}

					return  find_symbol(handle, name.c_str());
				}
				/**
				* ��ʾ��ʼ��ģ��Ĵ��������پ���� ���أ�true��ʾ�ɹ���false��ʾ����
				*
				* @param path    ��ʾ����ģ����ļ�·��
				*/
				inline csf_bool init_handles(const csf_string& path) {

					if (path.empty()) {
						return csf_false;
					}

					return init_handles(path.c_str());
				}
				/**
				* ��ʾ��ʼ��ģ��Ĵ��������پ���� ���أ�true��ʾ�ɹ���false��ʾ����
				*
				* @param path    ��ʾ����ģ����ļ�·��
				*/
				csf_bool init_handles(const csf_char* path);
				/**
				* ��ʾ����һ��������ÿ�γɹ�����ģ�飬�����1��
				*/
				inline csf_void up_count() {
					++m_count;
				}
				/**
				* ��ʾ����һ��������ÿ������һ��ģ�飬�����1��
				*/
				inline csf_void down_count() {
					--m_count;
				}
				/**
				* ģ������
				*
				* @param newVal    ģ������
				*/
				inline csf_void set_type(const csf::core::module::csf_module::csf_module_type newVal) {

					m_type = newVal;
				}
				/**
				* ��ʾģ�鹤�������Ĺ���������
				*
				* @param newVal
				*/
				inline void set_module_factory_manager(csf_module_factory_manager* newVal) {

					m_module_factory_manager = newVal;
				}
			private:
				/**
				 * ��ʾģ�鴴��������
				 */
				csf::core::base::csf_atomic_uint32 m_count = 0;
				/**
				 * ��ʾģ�鹤����Ӧ��ģ������
				 */
				csf_string m_name = "";
				/**
				* ģ������
				*/
				csf::core::module::csf_module::csf_module_type m_type = csf_module::csf_module_type::csf_module_type_none;
				/**
				 * ��ʾģ����ļ�Ŀ¼
				 */
				csf_string m_symbol_path = "";
				/**
				* ��ʾ�̰߳�ȫʹ�õĻ���������
				*/
				csf_shared_mutex m_mutex;
				/**
				 * ��ʾģ�鴴�����
				 */
				csf::core::module::csf_module_create_handle m_create_handle = csf_nullptr;
				/**
				 * ��ʾģ�����پ��
				 */
				csf::core::module::csf_module_destroy_handle m_destroy_handle = csf_nullptr;
				/**
				 * �򿪶�̬���ӿ�󷵻ص�ָ��
				 */
				csf_void* m_symbol_handle = csf_nullptr;
				/**
				 * ��ʾģ�鹤�������Ĺ���������
				 */
				csf_module_factory_manager* m_module_factory_manager = csf_nullptr;
				/**
				 * ��ʾ�����ļ�������
				 */
				csf::core::system::csf_configure_manager* m_configure_manager = csf_nullptr;
			};

		}

	}

}
#endif // !defined(CSF_MODULE_FACTORY_INCLUDED_)
