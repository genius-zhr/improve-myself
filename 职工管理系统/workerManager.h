#pragma once	
#include "worker.h"
#include <iostream>
using namespace std;
class WorkerManager {
public:
	WorkerManager();
	void showMenu();//展示功能菜单
	void exitSystem();//退出程序
	int m_EmpNum;
	Worker** array;
	void addWorker();
	~WorkerManager();
	bool isfile;
	void save();//将数据存在文件中
	int getfilenum();//统计文件内数据数量
	void initemp();
	void show_emp();//展示职工名单
	void deleteEmp();//删除职工
	void modifyEmp();//修改职工信息
	void searchEmp();//查找职工信息
	int nameSearch();//按姓名查，返回下标
	int idSearch();//按编号查，返回下标
	void sortEmp();//按照编号排序
	void cleanFile();//清空所有数据
};
void showMenu();
