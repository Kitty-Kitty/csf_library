#!/bin/sh

#主要功能是：使用软件的方式，简单实现一个crt功能。用于解决时间回到1970年的问题。

shell_path=$(cd `dirname $0`;pwd);
current_path=$pwd;
str_date=`date +"%Y-%m-%d %H:%M:%S"`;
date_file="${shell_path}/.datetime.txt";
log_file="${shell_path}/.datetime.log";
#表示日志文件的最大行数，大于最大行数时，要不断的回滚日志操作
log_max_lines=100;

#判断文件是否存在，不存在则要进行初始化处理;如果存在则使用;
if [ ! -f ${date_file} ]; then
	echo "${str_date}" > ${date_file};
else
	str_date=`cat ${date_file}`;
	date -s "${str_date}";
	echo "init system time[${str_date}]." >> ${log_file};
fi

#每10秒
while true
do
	sleep 10;
	str_date=`date +"%Y-%m-%d %H:%M:%S"`;
	echo "${str_date}" > ${date_file};
	echo "update time[${str_date}] init file[${date_file}]." >> ${log_file};

	#如果日志超过指定行数，则开始回滚日志
	tmp_log_lines=`wc -l ${log_file} | awk '{print $1}'`;
	while [ ${tmp_log_lines} -gt ${log_max_lines} ]
	do
		sed -i '1d' ${log_file};
		tmp_log_lines=`wc -l ${log_file} | awk '{print $1}'`;
	done
done

exit 0;