// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <boost/process.hpp>
#include <boost/process/child.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

#define		csf_vm_version				1000000
#define		CSF_VM_VERSION				"V1.0.0"
#define		CSF_VM_VAR					"test_vm"
#define		CSF_VM_VER					CSF_VM_VAR "/" CSF_VM_VERSION


boost::process::child  *child = nullptr;
//表示执行指令
std::string  command = "";
boost::asio::io_context io_context;
/**
* 表示需要处理的进程信号
*/
boost::asio::signal_set signals(io_context);

void start_child();
void stop_child();
bool start_signals_process();

void signal_handler(boost::system::error_code ec, int signal) {

#ifdef __linux__
	printf("get signal[%d : %s] error_code[%d : %s].\r\n"
		, signal
		, strsignal(signal)
		, ec.value()
		, boost::system::system_error(ec).what()
	);
#else
	printf("get signal[%d] error_code[%d : %s].\r\n"
		, signal
		, ec.value()
		, boost::system::system_error(ec).what()
	);
#endif

	//stop_child();
}


void exit_handler(int signal, const std::error_code& ec) {

#ifdef __linux__
	printf("process exit warning. signal[%d : %s] error_code[%d : %s] .\r\n"
		, signal
		, strsignal(signal)
		, ec.value()
		, ec.message().c_str()
	);
#else
	printf("process exit warning. signal[%d] error_code[%d : %s] .\r\n"
		, signal
		, ec.value()
		, ec.message().c_str()
	);
#endif

	//stop_child();
	//start_child();
	stop_child();
}

void deamon_task() {
	while (true)
	{
		start_child();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		// do stuff
		std::cout << "deamon_task!" << std::endl;
	}
}


void io_context_task() {
	while (true)
	{
		io_context.reset();
		signals.async_wait(signal_handler);
		io_context.run();

		std::this_thread::sleep_for(std::chrono::seconds(1));
		// do stuff
		std::cout << "io_context_task!" << std::endl;
	}
}


bool start_signals_process() {

	// Construct a signal set registered for process termination.
	signals.add(SIGSEGV);
	signals.add(SIGINT);
	signals.add(SIGTERM);
	signals.add(SIGABRT);
#ifdef __linux__
	signals.add(SIGQUIT);
	signals.add(SIGILL);
	signals.add(SIGTRAP);
	//signals.add(SIGKILL);
	signals.add(SIGIOT);
	signals.add(SIGBUS);
	signals.add(SIGFPE);
	signals.add(SIGCHLD);

#endif

	// Start an asynchronous wait for one of the signals to occur.
	signals.async_wait(signal_handler);

	return true;
}

void start_child() {

	if (!child) {
  		child = new boost::process::child(
  			command,
  			io_context,
  			boost::process::on_exit(exit_handler)
  		);
		
#if 0
 		boost::process::child  c(
 			command,
 			io_context,
 			boost::process::on_exit(exit_handler)
 		);
		std::error_code ec;
		
		c.wait(ec);
		printf("start child[%p]. error_code[%d : %s]\r\n"
			, child
			, ec.value()
			, ec.message().c_str()
		);
#endif

		printf("start child[%p]. \r\n"
			, child
		);
	}
}

void stop_child() {

	if (child) {
		//child->wait();

		delete child;
		
		printf("delete child[%p]\r\n", child);
		child = nullptr;
	}
}


int main(int argc, char ** argv)
{
	char	tmp_buf[512] = { 0, };


	if (argc < 2) {
		printf("usage: app  path\r\n");
		return 0;
	}

    {
        

		memset(tmp_buf, 0, sizeof(tmp_buf));
#ifdef WIN32
		sprintf(tmp_buf, "%s  -f E:\project_work\arm_project\kitty\project\trunk\csf_library\csf_workspace\ec\config\csf_configs.xml  -t xml", argv[1]);
#else
		sprintf(tmp_buf, "%s  -f config/csf_configs.xml  -t xml", argv[1]);
#endif
		command = std::string(tmp_buf);

		start_signals_process();

		boost::thread deamon_thread(deamon_task);
		boost::thread io_context_thread(io_context_task);
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::seconds(10));
		}
    }
}
