#pragma once
#include<stack>
#include<algorithm>
using namespace std;

const static int BLOCK_SIZE = 4*1024 / sizeof(bool);

class FAT {
public:
	stack<int>freeDiskBlock;//�մ��̿�ջ
	stack<int>fullDiskBlock;//ռ�ô��̿�
	void init(string  blocks[]);
	int  getBlock();
	void addBlock(int block, string  blocks[]);//��ȡһ���յĴ��̿�

};