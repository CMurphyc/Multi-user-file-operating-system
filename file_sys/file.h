#pragma once
#include "file_control_block.h"
#include<string>

class File :public FCB
{
public:
	//���캯��
	File();
	File(string _name, FileType _type, FAT & fat);
	//��������
	~File();
	//���л�
	void Serialization();
	//�����л�
	void Deserialization();
	bool addContent(const char * content, string  blocks[], FAT & fat);
	//�ļ�����
	int index[N];
	//��һ���ļ���
	FCB* father;
	void release(FAT & fat, string* blocks);
	string toString(string blocks[]);
	//�ͷŴ��̿�
};