#include "file_control_block.h"
#include<stdlib.h>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

FCB::FCB()
{
	this->access = Write;
	this->modifyDate = getTime();
	this->size = N;
}

FCB::~FCB()
{

}

string int_to_string(int x)
{
	string s = "";
	while (x)
	{
		int lef = x % 10;
		s += '0' + lef;
		x /= 10;
	}
	reverse(s.begin(), s.end());
	return s;
}
string FCB::getTime()
{
	struct tm t;   //tm结构指针
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&t, &now);
	string s = "";
	printf("%d 年 %d 月 %d 日 %d 时 %d 分 %d 秒\n", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,  t.tm_hour, t.tm_min, t.tm_sec);
	s += int_to_string(t.tm_year + 1900);
	s += "年";
	s += int_to_string(t.tm_mon + 1);
	s += "月";
	s += int_to_string(t.tm_mday);
	s += "日";
	s += int_to_string(t.tm_hour);
	s += "时";
	s += int_to_string(t.tm_min);
	s += "分";
	s += int_to_string(t.tm_sec);
	s += "秒";
	return s;
}