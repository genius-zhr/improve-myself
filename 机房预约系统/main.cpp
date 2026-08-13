#include <iostream>
#include "Reservation.h"

using namespace std;

// 菜单循环：由我实现
int main() {
    Reservation reservation;

    int choice = -1;
    while (choice != 0) {
        cout << "\n========== 机房预约系统 ==========" << endl;
        cout << "1. 查看所有时间段" << endl;
        cout << "2. 选择时间段" << endl;
        cout << "3. 查看当前时段的机房/座位状态" << endl;
        cout << "4. 预约座位" << endl;
        cout << "5. 取消预约" << endl;
        cout << "0. 退出系统" << endl;
        cout << "请输入你的选择：";
        cin >> choice;

        switch (choice) {
        case 1:
            reservation.showTime();
            break;
        case 2:
            reservation.selectTime();
            break;
        case 3:
            reservation.showStatus();
            break;
        case 4:
            reservation.reserve();
            break;
        case 5:
            reservation.cancel();
            break;
        case 0:
            cout << "感谢使用，再见！" << endl;
            break;
        default:
            cout << "输入有误，请重新选择。" << endl;
            break;
        }
    }

    return 0;
}
