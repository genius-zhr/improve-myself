#include "workerManager.h"
#include "worker.h"
#include "Boss.h"
#include "Employee.h"
#include "Manager.h"
#include <fstream>
#define filename "empdata.txt"
WorkerManager::WorkerManager() {
	ifstream ifs;
	ifs.open(filename, ios::in);
	//判断文件是否打开成功
	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
		this->m_EmpNum = 0;
		this->array = NULL;
		this->isfile = true;
		ifs.close();
		return;
	}
	else {
		char ch;
		ifs >> ch;
		if (ifs.eof()) {
			cout << "文件为空" << endl;
			this->m_EmpNum = 0;
			this->array = NULL;
			this->isfile = true;
			ifs.close();
			return;
		}
		else {
			int num = this->getfilenum();
			cout << "职工人数为:" << num << endl;
			this->m_EmpNum = num;
			this->array = new Worker * [this->m_EmpNum];
			this->initemp();
		}
	}
}
WorkerManager::~WorkerManager() {
	for (int i = 0;i < this->m_EmpNum;i++) {
		delete this->array[i];
	}
	delete[] this->array;
}
void WorkerManager::showMenu() {
	cout << "*************************************" << endl;
	cout << "********欢迎使用职工管理系统!********" << endl;
	cout << "***********0.退出管理程序************" << endl;
	cout << "***********1.增加职工信息************" << endl;
	cout << "***********2.显示职工信息************" << endl;
	cout << "***********3.删除离职职工************" << endl;
	cout << "***********4.修改职工信息************" << endl;
	cout << "***********5.查找职工信息************" << endl;
	cout << "***********6.按照编号排序************" << endl;
	cout << "***********7.清空所有文档************" << endl;
	cout << "*************************************" << endl;
}
void WorkerManager::exitSystem() {
	cout << "欢迎下次使用!" << endl;
	exit(0);
}
void WorkerManager::save() {
	ofstream ofs;
	ofs.open(filename, ios::out);
	for (int i = 0;i < this->m_EmpNum;i++) {
		ofs << this->array[i]->m_id << "  "
			<< this->array[i]->m_name << "  "
			<< this->array[i]->m_Deptid << endl;
	}
	ofs.close();
}
int WorkerManager::getfilenum() {
	ifstream ifs;
	ifs.open(filename, ios::in);
	int id;
	string name;
	int dId;
	int a = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		a++;
	}
	return a;
}
void WorkerManager::addWorker() {
	cout << "请输入要添加的员工数量:" << endl;
	int addsize;
	cin >> addsize;
	if (addsize > 0) {
		int newsize = this->m_EmpNum + addsize;
		Worker** newarray = new Worker * [newsize];
		if (this->array != NULL) {
			for (int i = 0;i < m_EmpNum;i++){
				newarray[i] = array[i];
			}
		}
		for (int i = 0;i < addsize;i++) {
			int id;
			string name;
			int dselect;//部门选择
			cout << "请输入第" << i + 1 << "个职工编号:" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个职工姓名:" << endl;
			cin >> name;
			cout << "请选择该职工岗位" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dselect;
			Worker* new_worker = NULL;
			switch (dselect) {
			case 1:
				new_worker = new Employee(id, name, 1);
				break;
			case 2:
				new_worker = new Manager(id, name, 2);
				break;
			case 3:
				new_worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newarray[this->m_EmpNum + i] = new_worker;
		}
		delete[] this->array;
		this->array = newarray;
		this->m_EmpNum = newsize;
		this->isfile = false;
		cout << "成功添加!" << endl;
		//将信息保存到文件中
		this->save();
	}
	else {
		cout << "输入数据有误" << endl;
	}
	system("clear");
}
void WorkerManager::initemp() {
	ifstream ifs;
	ifs.open(filename, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker=NULL;
		if (dId == 1) {
			worker = new Employee(id,name,dId);
		}
		else if (dId == 2) {
			worker = new Manager(id, name, dId);
		}
		else if (dId == 3) {
			worker = new Boss(id, name, dId);
		}
		this->array[index] = worker;
		index++;
	}
	ifs.close();
}
int WorkerManager::nameSearch(){
	string name;
	cout << "输入要查找的职工姓名:" << endl;
	cin >> name;
	for (int i = 0;i < this->m_EmpNum;i++) {
		if (this->array[i]->m_name == name) {
			return i;
		}
		else {
			continue;
		}
	}
	string select;
	cout << "没有这位职工" << endl;
	cout << "选择是否重新查找yes/no" << endl;
	cin >> select;
	if (select == "yes") {
		return nameSearch();
	}
	else if(select=="no") {
		return -1;
	}
	return -1;
}
int WorkerManager::idSearch() {
	int id;
	cout << "输入要查找的职工编号:" << endl;
	cin >> id;
	for (int i = 0;i < this->m_EmpNum;i++) {
		if (this->array[i]->m_id == id) {
			return i;
		}
		else {
			continue;
		}
	}
	string select;
	cout << "没有这位职工" << endl;
	cout << "选择是否重新查找yes/no" << endl;
	cin >> select;
	if (select == "yes") {
		return idSearch();
	}
	else if (select == "no") {
		return -1;
	}
	return -1;
}
void WorkerManager::show_emp() {
	if (this->array == NULL) {
		cout << "当前没有职工记录" << endl;
		return;
	}
	else {
		for (int i = 0;i < this->m_EmpNum;i++) {
			this->array[i]->showInfo();
			}
		}
	system("clear");
}
void WorkerManager::deleteEmp() {
	cout << "请输入要删除的职工姓名:" << endl;
	string name;
	cin >> name;
	for (int i = 0;i < this->m_EmpNum;i++) {
		if (this->array[i]->m_name != name) {
			continue;
		}
		else {
			Worker* del = this->array[i];
			for (int j = i;j < this->m_EmpNum-1;j++) {
				this->array[j] = this->array[j + 1];
			}
			this->array[this->m_EmpNum-1] = NULL;
			this->m_EmpNum--;
			delete del;
			this->save();
			cout << "删除成功" << endl;
			system("clear");
			return;
		}
	}
	cout << "未找到该职工" << endl;
	system("clear");
}
void WorkerManager::modifyEmp() {
	cout << "请输入要修改的职工姓名:" << endl;
	string name1;
	cin >> name1;
	for (int i = 0;i < this->m_EmpNum;i++) {
		if (this->array[i]->m_name != name1) {
			continue;
		}
		else {
			delete this->array[i];
			int id;
			cout << "请输入新的职工编号" << endl;
			cin >> id;
			string name;
			cout << "请输入新的职工姓名" << endl;
			cin >> name;
			int dId;
			cout << "请输入新的职工部门编号" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dId;
			Worker* worker = NULL;
			if (dId == 1) {
				worker = new Employee(id, name, dId);
			}
			else if (dId == 2) {
				worker = new Manager(id, name, dId);
			}
			else if (dId == 3) {
				worker = new Boss(id, name, dId);
			}
			this->array[i] = worker;
			this->save();
			cout << "修改成功" << endl;
			system("clear");
			return;
		}
	}
	cout << "未找到该职工" << endl;
	system("clear");
}
void WorkerManager::searchEmp() {
	int select;
	cout << "请选择你要按什么方式查找" << endl;
	cout << "1.编号" << endl;
	cout << "2.姓名" << endl;
	cin >> select;
	if (select != 1&&select != 2) {
		cout << "请重新选择" << endl;
		searchEmp();
	}
	else {
		int idx;
		switch (select) {
		case 1:
			idx = idSearch();
			break;
		case 2:
			idx = nameSearch();
			break;
		}
		if (idx != -1) {
			this->array[idx]->showInfo();
		}
		else {
			cout << "已放弃查找" << endl;
		}
		system("clear");
	}
}
void WorkerManager::sortEmp() {
	if (this->m_EmpNum == 0) {
		cout << "当前没有职工记录" << endl;
		system("clear");
		return;
	}
	//冒泡排序，按编号升序排列
	for (int i = 0;i < this->m_EmpNum - 1;i++) {
		for (int j = 0;j < this->m_EmpNum - 1 - i;j++) {
			if (this->array[j]->m_id > this->array[j + 1]->m_id) {
				Worker* temp = this->array[j];
				this->array[j] = this->array[j + 1];
				this->array[j + 1] = temp;
			}
		}
	}
	this->save();
	cout << "排序完成!" << endl;
	system("clear");
}
void WorkerManager::cleanFile() {
	cout << "确定要清空所有数据吗?" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;
	int select;
	cin >> select;
	if (select == 1) {
		//释放所有职工对象
		for (int i = 0;i < this->m_EmpNum;i++) {
			delete this->array[i];
		}
		//释放指针数组
		delete[] this->array;
		this->array = NULL;
		this->m_EmpNum = 0;
		//清空文件内容
		ofstream ofs;
		ofs.open(filename, ios::out);
		ofs.close();
		cout << "已清空所有数据!" << endl;
	}
	else {
		cout << "已取消清空" << endl;
	}
	system("clear");
}