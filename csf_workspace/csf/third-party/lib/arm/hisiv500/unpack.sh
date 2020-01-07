#!/bin/sh

shell_path=$(cd `dirname $0`;pwd);
current_path=$pwd;
str_date=`date +"%Y%m%dT%H%M%S"`;
str_archive_type="tar.xz";

#进入库源目录
cd ${shell_path};

#开始解压安装库
library_list=`find ./ -mindepth 1 -maxdepth 1 -name "*${str_archive_type}" -type f -printf "%f "`;
process_count=0;

echo "";
echo "packages information";
echo "library_list[ ${#library_list[@]} ]:";
echo "--------------------------------------------";

for tmp_library in ${library_list[*]}
do
	process_count=$((${process_count}+1))
	echo "[ ${process_count}/${#library_list[@]} ] ${tmp_library}";
done

echo "--------------------------------------------";


echo "";
echo "begin unpack ...";
echo "";

echo "library_list[ ${#library_list[@]} ]:";
echo "--------------------------------------------";

process_count=0;
for tmp_library in ${library_list[*]}
do
	process_count=$((${process_count}+1))
	echo "[ ${process_count}/${#library_list[@]} ] ${tmp_library}";
	#tar -xvJf ${tmp_library};
	tar -xJf ${tmp_library};
done

echo "--------------------------------------------";

echo "";
echo "end unpack success!";

cd ${current_path};

exit 0;