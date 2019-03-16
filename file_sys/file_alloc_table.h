#pragma once
#include<stack>
#include<algorithm>
using namespace std;

const static int BLOCK_SIZE = 4*1024 / sizeof(bool);

class FAT {
public:
	stack<int>freeDiskBlock;//空磁盘块栈
	stack<int>fullDiskBlock;//占用磁盘块
	void init(string  blocks[]);
	int  getBlock();
	void addBlock(int block, string  blocks[]);//获取一个空的磁盘块

};