#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "Boss.h"
#include "Employee.h"
#include "Manager.h"
#include <fstream>
#include <string>
using namespace std;
int main() {
	WorkerManager wm;
	while (true) {
		wm.showMenu();
		int select;
		cout << "请输入你的选择:" << endl;
		cin >> select;
		switch (select) {
		case 0:
			wm.exitSystem();
			break;
		case 1:
			wm.addWorker();
			break;
		case 2:
			wm.show_emp();
			break;
		case 3:
			wm.deleteEmp();
			break;
		case 4:
			wm.modifyEmp();
			break;
		case 5:
			wm.searchEmp();
			break;
		case 6:
			wm.sortEmp();
			break;
		case 7:
			wm.cleanFile();
			break;
		default:
			system("clear");
			break;
		}
	}
	
	

	return 0;
}