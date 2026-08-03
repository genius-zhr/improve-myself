#pragma once
#include <iostream>
#include <string>
using namespace std;
class Worker {
public:
	virtual ~Worker() {}
	virtual void showInfo() = 0;
	virtual string getDeptName() = 0;
	string m_name;//职工姓名
	int m_id;//职工编号
	int m_Deptid;//部门编号
};