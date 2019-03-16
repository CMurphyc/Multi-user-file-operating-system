//#include<bits/stdc++.h>
#include<algorithm>
#include<iostream>
#include<queue>
#include<iomanip>
#include<fstream>  
#include<direct.h>  
#include<io.h> 
#include"disk_manager.h"
#include"folder.h"
#include"file_type.h"
#include"access.h"
#include"file_alloc_table.h"
using namespace std;

const string ACCESS[] = { "只读","可修改","可执行" };
const string rootPath = "C:/Users/Murphyc/Desktop/操作系统/file_sys";

queue<FCB*> persistQueue;//队列
FAT fat;
string blocks[N];
ofstream *out = NULL;
ifstream *in = NULL;

void DiskMannger::DiskWrite(File * file)
{
	//文件输出流
	printf("%s\n", file->path.c_str());
	out = new ofstream(file->path.c_str());
	if (out->is_open()) out->close();
}

bool DiskMannger::DiskMkdir(string dirName)
{
	printf("%s\n", dirName.c_str());
	return _mkdir(dirName.c_str()) == 0;
}

bool DiskMannger::DiskRmdir(string dirName)
{
	return _rmdir(dirName.c_str()) == 0;
}

bool DiskMannger::DiskCkdir(string dirName)
{

	if (_access(dirName.c_str(), 0) == -1) return  _mkdir(dirName.c_str()) == 0;
	return false;
}

void DiskMannger::DiskRmdir(Folder *f)
{
	//删除所有节点
	for (int i = 0; i < (int)f->child.size(); i++) {
		if (f->child[i]->type == DOCUMENT) {
			printf("%s\n", f->child[i]->path.c_str());
			remove(f->child[i]->path.c_str());
		}
		else {
			this->DiskRmdir((Folder*)f->child[i]);
		}
	}
	printf("%s\n", f->path.c_str());
	this->DiskRmdir(f->path.c_str());
}

DiskMannger::DiskMannger()
{
	fat.init(blocks);//初始化文件分配表
	root = new Folder(rootPath, FileType::FOLDER);
	root->path = rootPath;//设置磁盘根为目录
	this->DiskMkdir(rootPath);//设置父节点的根节点
	root->father = root;
	string user;
	int power;
	cout << "请输入用户名与用户权限" << endl;
	cin >> user >> power;
	cout << "欢迎！！-----------您可输入help获得帮助------------" << endl << "\n[root@localhost " + rootPath + "]# ";
	string opear, op;
	while (cin >> op)
	{
		if (op == "format") this->format(blocks);
		else if (op == "mkdir"&&power) this->Mkdir();
		else if (op == "rmdir"&&power) this->Rmdir();
		else if (op == "open") this->open();
		else if (op == "close") this->close();
		else if (op == "create"&&power) this->create();
		else if (op == "rm"&&power) this->rm();
		else if (op == "ls") this->ls();
		else if (op == "cd") this->cd();
		else if (op == "exit") {
			printf("%s\n", "再见！");
			exit(0);
		}
		else if (op == "help") {
			cout << endl;
			cout << "* : format:对文件存储器进行格式化.\n" <<
				"① mkdir:用于创建子目录\n" <<
				"② rmdir : 用于删除子目录\n" <<
				"③ ls : 用于显示目录\n" <<
				"④ cd : 用于更改当前目录\n" <<
				"⑤ write : 用于写文件\n" <<
				"⑥ read : 用于读文件\n" <<
				"⑦ open : 用于打开文件\n" <<
				"⑧ close : 用于关闭文件\n" <<
				"⑨ create : 用于创建文件\n" <<
				"⑩ rm : 用于删除文件\n" <<
				"* : exit : 退出系统\n"
				<< endl;
		}
		else if (!power) cout << "你没有该权限！" << endl;
		else cout << "该指令不存在" << endl;
		cout << "\n[root@localhost " + this->root->path + " ]# ";

	}
}

DiskMannger::~DiskMannger()
{

}

void DiskMannger::format(string *blocks)
{
	fat.init(blocks);
	//回退到根目录
	while (root->father != root) this->root = (Folder*)(this->root->father);
	this->DiskRmdir(this->root);
	root->child.clear();
	printf("%s\n", "磁盘格式化成功！");
}

void DiskMannger::Mkdir()
{
	string name;
	cin >> name;
	Folder *childFile = new Folder(name, FileType::FOLDER);
	childFile->father = (this->root);//设置父节点
	childFile->path = this->root->path + name + "/";
	//判断是否文件重复
	//判断是否文件重复 
	if (this->root->count(childFile))cout << "创建文件夹失败，文件夹名出现重复" << endl;//文件重复报错
	else {
		cout << "创建文件夹成功" << endl;
		this->DiskMkdir(childFile->path);
		this->root->addChild(childFile);
	}
}

void DiskMannger::Rmdir()
{
	string name;
	cin >> name;
	Folder *childFile = new Folder(name, FOLDER);
	childFile = (Folder*) this->root->find(childFile);
	if (this->root->erase(childFile)) {
		//文件重复报错
		this->DiskRmdir(childFile);
		cout << "删除文件夹成功" << endl;
	}
	else cout << "无此文件夹 ，删除文件夹失败" << endl;
}

void DiskMannger::ls()
{
	cout << setw(10) << "访问权限"
		<< setw(20) << "文件大小"
		<< setw(35) << "修改日期"
		<< setw(20) << "文件名"
		<< endl;
	int size = this->root->size();
	for (int i = 0; i<size; i++) {
		cout << setw(10) << ACCESS[this->root->child[i]->access]
			<< setw(20) << (this->root->child[i]->type != FOLDER ? ((File*)this->root->child[i])->toString(blocks).size() : 4096)
			<< setw(35) << this->root->child[i]->modifyDate
			<< setw(20) << this->root->child[i]->name
			<< endl;
	}
}

void DiskMannger::cd()
{
	string name;
	cin >> name;
	if (name == "..") this->root = (Folder*)(this->root->father);
	else {
		if (this->root->count(new Folder(name, FOLDER))) {
			if (this->root->find(new Folder(name, FOLDER))->type != FOLDER) cout << "无此文件夹" << endl;
			else root = (Folder*)this->root->find(new Folder(name, FOLDER));
		}
		else cout << "无此文件夹 " << endl;
	}
}

void DiskMannger::create()
{
	string name;
	cin >> name;
	File *childFile = new File(name, DOCUMENT, fat);
	childFile->father = (this->root);//设置父节点
	childFile->path = this->root->path + name;
	//判断是否文件重复
	if (this->root->count(childFile)) {
		//文件重复报错
		cout << "创建文件失败，文件名出现重复！！" << endl;
	}
	else {
		cout << "创建文件成功！" << endl;
		this->root->addChild(childFile);
		this->DiskWrite(childFile);
	}
}

void DiskMannger::open()
{
	string name, cmd;
	cin >> name;
	File * file = (File*)this->root->find(new File(name, DOCUMENT, fat));
	if (file != NULL) {
		printf("%s\n", "文件读写流打开成功!");
		cout << "\n[root@localhost " + this->root->path + " ]# ";
		while (cin >> cmd) {
			cout << "\n[root@localhost " + this->root->path + " ]# ";
			if (cmd == "write") this->write(file->path.c_str(), file);
			else if (cmd == "read") this->read(file->path.c_str());
			else if (cmd == "close") {
				this->close();
				break;
			}
		}
	}
	else printf("%s\n", "无法打开文件读写流，无此文件！");
}

void DiskMannger::close()
{
	if (out == NULL || in == NULL) printf("%s\n", "无文件读写流需要关闭!");
	else {
		out->close();
		in->close();
		printf("%s\n", "文件读写流关闭成功!");
	}
}

void DiskMannger::write(const char *s, File* file)
{
	string content;
	cin >> content;
	if (in != NULL)in->close();
	file->addContent(content.c_str(), blocks, fat);//添加内容到文件中
	content = file->toString(blocks);
	out = new ofstream(s);
	if (out->is_open()) *out << content;
	out->close();
}

void DiskMannger::read(const char *s)
{
	char *content = new char[N];
	if (out != NULL)out->close();
	in = new ifstream(s);
	if (in->is_open()) *in >> content;
	in->close();
	cout << content;
}

void DiskMannger::rm()
{
	string name;
	cin >> name;
	File *childFile = new File(name, DOCUMENT, fat);
	if (this->root->count(childFile)) {
		//文件重复报错
		childFile = (File*) this->root->find(childFile);
		remove(childFile->path.c_str());
		childFile->release(fat, blocks);
		this->root->erase(childFile);
		cout << "删除文件成功！" << endl;
	}
	else cout << "无此文件 ，删除文件失败" << endl;
}