#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
#define peoplesize 1000
typedef struct {
	string name;
	int gender;//1男2女
	int age;
	string phone;
	string address;
}person;
typedef struct {
	person personarray[peoplesize];
	int size;
}addressbooks;
//封装函数显示界面,void showMenu(),在main函数中调用封装好的函数
void showMenu() {
	cout << "==========================" << endl;
	cout << "=====  1.添加联系人  =====" << endl;
	cout << "=====  2.显示联系人  =====" << endl;
	cout << "=====  3.删除联系人  =====" << endl;
	cout << "=====  4.查找联系人  =====" << endl;
	cout << "=====  5.修改联系人  =====" << endl;
	cout << "=====  6.清空联系人  =====" << endl;
	cout << "=====  0.退出通讯录  =====" << endl;
	cout << "==========================" << endl;
}
void addPerson(addressbooks* abs) {
	if (abs->size == peoplesize) {
		cout << "通讯录已满" << endl;
		return;
	}
	else {
		cout << "请输入联系人姓名:" << endl;
		cin >> abs->personarray[abs->size].name;
		cout << "请输入联系人性别1--男，2--女:" << endl;
		int gender = 0;
		while (1) {
			cin >> gender;
			if (gender == 1 || gender == 2) {
				abs->personarray[abs->size].gender = gender;
				break;
			}
			else {
				cout << "输入不合法，请重新输入!!!" << endl;
			}
		}
		cout << "请输入联系人年龄:" << endl;
		cin >> abs->personarray[abs->size].address;
		cout << "请输入联系人电话号:" << endl;
		cin >> abs->personarray[abs->size].phone;
		cout << "请输入联系人住址:" << endl;
		cin >> abs->personarray[abs->size].address;
		abs->size++;
		cout << "添加成功" << endl;
		system("pause");
		system("cls");
	}
	return;
}
void showPerson(addressbooks *abs) {
	if (abs->size == 0) {
		cout << "暂无联系人" << endl;
	}
	else {
		for (int i = 0;i < abs->size;i++) {
			cout << "====================" << endl;
			cout << "联系人" << i+1 << "的姓名:" << abs->personarray[i].name << "   ";
			if (abs->personarray[i].gender == 1) {
				cout << "性别:男" << "   ";
			}
			else {
				cout << "性别:女" << "   ";
			}
			cout << "年龄:" << abs->personarray[i].age << "   " << "电话号:" << abs->personarray[i].phone << "   " << "住址:" << abs->personarray[i].address << endl;
			cout << "====================" << endl;
		}
	}
	cout << "显示完毕" << endl;
	system("pause");
	system("cls");
	return;
}
int isExist(addressbooks* abs, string name) {
	for (int i = 0;i < abs->size;i++) {
		if (abs->personarray[i].name == name)
			return i;//找到并返回目标联系人下标
	}
	return -1;//遍历一圈没找到目标联系人
}
void deletePerson(addressbooks* abs,int deleteidx) {
	for (int i = deleteidx;i < abs->size-1;i++) {
		abs->personarray[i] = abs->personarray[i + 1];
	}
	abs->size--;
	memset(&abs->personarray[abs->size], 0, sizeof(person));
	cout << "删除成功" << endl;
	system("pause");
	system("cls");
	return;
}
void findPerson(addressbooks* abs, int findidx) {
	cout << "姓名:" << abs->personarray[findidx].name << endl;
	cout << "年龄:" << abs->personarray[findidx].age << endl;
	cout << "性别:" << abs->personarray[findidx].gender << endl;
	cout << "电话:" << abs->personarray[findidx].phone << endl;
	cout << "住址:" << abs->personarray[findidx].address << endl;
	cout << "查找成功" << endl;
	system("pause");
	system("cls");
	return;
}
void modifyPerson(addressbooks* abs, int modifyidx) {
	cout << "请输入联系人姓名:" << endl;
	cin >> abs->personarray[modifyidx].name;
	cout << "请输入联系人性别1--男，2--女:" << endl;
	int gender = 0;
	while (1) {
		cin >> gender;
		if (gender == 1 || gender == 2) {
			abs->personarray[modifyidx].gender = gender;
			break;
		}
		else {
			cout << "输入不合法，请重新输入!!!" << endl;
		}
	}
	cout << "请输入联系人年龄:" << endl;
	cin >> abs->personarray[modifyidx].address;
	cout << "请输入联系人电话号:" << endl;
	cin >> abs->personarray[modifyidx].phone;
	cout << "请输入联系人住址:" << endl;
	cin >> abs->personarray[modifyidx].address;
	cout << "修改成功" << endl;
	system("pause");
	system("cls");
}
void cleanPerson(addressbooks* abs) {
	memset(&abs, 0, sizeof(addressbooks));
	cout << "已清除" << endl;
	abs->size = 0;
	system("pause");
	system("cls");
}
int main() {
	SetConsoleOutputCP(CP_UTF8); // 设置控制台输出为 UTF-8，解决中文乱码
	int select = 0;
	addressbooks abs;
	abs.size = 0;
	while (1) {
		showMenu();
		cin >> select;
		switch (select) {
		case 1://1.添加联系人
			addPerson(&abs);
			break;
		case 2://2.显示联系人
			showPerson(&abs);
			break;
		case 3://3.删除联系人
		{
			cout << "请输入删除联系人姓名:" << endl;
			string name;
			cin >> name;
			if (isExist(&abs, name) == -1) {
				cout << "未找到该联系人" << endl;
				system("pause");
				system("cls");
			}
			else {
				int idx = isExist(&abs, name);
				deletePerson(&abs, idx);
			}
		}
			break;
		case 4://4.查找联系人
		{
			cout << "请输入查找联系人姓名:" << endl;
			string name;
			cin >> name;
			if (isExist(&abs, name) == -1) {
				cout << "未找到该联系人" << endl;
				system("pause");
				system("cls");
			}
			else {
				int idx = isExist(&abs, name);
				findPerson(&abs, idx);
			}
		}
			break;
		case 5://5.修改联系人
		{
			cout << "请输入要修改联系人姓名:" << endl;
			string name;
			cin >> name;
			if (isExist(&abs, name) == -1) {
				cout << "未找到该联系人" << endl;
			}
			else {
				int idx = isExist(&abs, name);
				modifyPerson(&abs, idx);
			}
		}
			break;
		case 6://6.清空联系人
		{
			if (abs.size == 0) {
				cout << "通讯录为空" << endl;
			}
			else {
				cleanPerson(&abs);
			}
		}
			break;
		case 0://0.退出通讯录
			cout << "欢迎下次使用!" << endl;
		default:
			cout << "重新选择功能" << endl;
			break;
			system("pause");
			return 0;
		}

	}
	system("pause");
	return 0;
}