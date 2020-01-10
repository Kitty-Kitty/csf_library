#!/bin/sh

#��Ҫ�����ǣ�ʹ������ķ�ʽ����ʵ��һ��crt���ܡ����ڽ��ʱ��ص�1970������⡣

shell_path=$(cd `dirname $0`;pwd);
current_path=$pwd;
str_date=`date +"%Y-%m-%d %H:%M:%S"`;
date_file="${shell_path}/.datetime.txt";
log_file="${shell_path}/.datetime.log";
#��ʾ��־�ļ�����������������������ʱ��Ҫ���ϵĻع���־����
log_max_lines=100;

#�ж��ļ��Ƿ���ڣ���������Ҫ���г�ʼ������;���������ʹ��;
if [ ! -f ${date_file} ]; then
	echo "${str_date}" > ${date_file};
else
	str_date=`cat ${date_file}`;
	date -s "${str_date}";
	echo "init system time[${str_date}]." >> ${log_file};
fi

#ÿ10��
while true
do
	sleep 10;
	str_date=`date +"%Y-%m-%d %H:%M:%S"`;
	echo "${str_date}" > ${date_file};
	echo "update time[${str_date}] init file[${date_file}]." >> ${log_file};

	#�����־����ָ����������ʼ�ع���־
	tmp_log_lines=`wc -l ${log_file} | awk '{print $1}'`;
	while [ ${tmp_log_lines} -gt ${log_max_lines} ]
	do
		sed -i '1d' ${log_file};
		tmp_log_lines=`wc -l ${log_file} | awk '{print $1}'`;
	done
done

exit 0;