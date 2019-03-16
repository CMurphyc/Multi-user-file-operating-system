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
	struct tm t;   //tm�ṹָ��
	time_t now;  //����time_t���ͱ���
	time(&now);      //��ȡϵͳ���ں�ʱ��
	localtime_s(&t, &now);
	string s = "";
	printf("%d �� %d �� %d �� %d ʱ %d �� %d ��\n", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,  t.tm_hour, t.tm_min, t.tm_sec);
	s += int_to_string(t.tm_year + 1900);
	s += "��";
	s += int_to_string(t.tm_mon + 1);
	s += "��";
	s += int_to_string(t.tm_mday);
	s += "��";
	s += int_to_string(t.tm_hour);
	s += "ʱ";
	s += int_to_string(t.tm_min);
	s += "��";
	s += int_to_string(t.tm_sec);
	s += "��";
	return s;
}