#include <iostream>
#include "manager.h"

using namespace std;

// 菜单：显示功能选项
void showMenu() {
    cout << "========================================" << endl;
    cout << "         演讲比赛流程管理系统" << endl;
    cout << "           1. 开始比赛" << endl;
    cout << "           2. 查看往届记录" << endl;
    cout << "           3. 清空比赛记录" << endl;
    cout << "           0. 退出系统" << endl;
    cout << "========================================" << endl;
}

int main() {
    SpeechManager manager;   // 构造时会自动加载历史记录、准备名单

    int choice = 0;
    while (true) {
        showMenu();
        cout << "请输入您的选择：";
        cin >> choice;

        switch (choice) {
            case 1:  // 开始比赛
                manager.startSpeech();
                break;
            case 2:  // 查看往届记录
                manager.showRecord();
                break;
            case 3:  // 清空比赛记录
                manager.clearRecord();
                break;
            case 0:  // 退出系统
                cout << "欢迎下次使用！" << endl;
                return 0;
            default:
                cout << "输入有误，请重新输入！" << endl;
                break;
        }
        cout << endl;
    }
    return 0;
}
