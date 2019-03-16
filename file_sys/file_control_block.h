#pragma once
#include<string>
#include "file_type.h"
#include "access.h"
#include "file_alloc_table.h"
#include <time.h>
using namespace std;

const int N = 4096;

class FCB {
public:
	string name;//�ļ�����    �ļ���.��չ��
	int nodeId;//�ļ���ʶ������ϵͳ�����ļ���Ψһ��ʶ��
	FileType type;//�ļ����ͣ�����չ��������
	string path;//�ļ�λ�ã��ļ�������豸�ľ���λ�á�
	int size;//�ļ���С�����ֽڻ��Ϊ��λ���ļ����ȡ�
	Access access;//�ļ��ı�����ʽ��ͨ���ж���д��ִ�еȡ�
	string modifyDate;// �ļ��Ĵ������޸����ڡ�
	FCB *index[N];//������
	FCB *father;//���ڵ�
	FCB();
	~FCB();
	string getTime();//��ȡϵͳʱ��
};