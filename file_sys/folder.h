#pragma once
#include"file_control_block.h"
#include"file.h"
#include<vector>

class Folder :public FCB
{
public:
	vector<FCB * >child;
	void addChild(FCB* file);
	Folder(string _name, FileType _type);
	bool count(FCB *file);
	FCB* find(FCB *file);
	bool erase(FCB* file);
	int size();
private:
	int childSize;
};