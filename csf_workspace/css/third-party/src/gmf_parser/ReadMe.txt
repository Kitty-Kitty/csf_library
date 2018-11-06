编译方法:
	1、进入build 目录
	2、cmake ../			指令cmake 指令，要求cmake 版本大于2.5,成功后生成Makefile。 测试模式执行cmake -DDEBUG_MODE=ON ../即可
	3、make				编译程序，成功后生成可执行文件，debug模式目录:debug/gmf_parser。  release模式目录:release/gmf_parser
	
	可执行文件名:gmf_parser

使用方法：
	根据不同的编译模式，进入对应的目录：./gmf_parser