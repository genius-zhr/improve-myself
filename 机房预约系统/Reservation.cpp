#include <iostream>
#include "Reservation.h"

using namespace std;

Reservation::Reservation() {
    currentTimeSlotIndex = 0;  // 默认选中第 1 个时间段，避免未初始化导致越界

    // TODO: 初始化固定数据
    // 提示：用 system.addTimeSlot(...) 依次加入 3 个时间段：
    //   "08:00-10:00"、"10:00-12:00"、"14:00-16:00"
    //   每个时间段 3 个机房、每机房 10 个座位
    system.addTimeSlot(TimeSlot("08:00-10:00", 3, 10));
    system.addTimeSlot(TimeSlot("10:00-12:00", 3, 10));
    system.addTimeSlot(TimeSlot("14:00-16:00", 3, 10));
}

void Reservation::selectTime() {
    // TODO:
    // 1. 显示所有时间段（可调用 system.showTime()）
    // 2. 读入用户选择（从 1 开始）
    // 3. 校验范围，把 currentTimeSlotIndex 设为对应下标（从 0 开始）
    system.showTime();
    int choice;
    cin >> choice;
    if (choice >= 1 && choice <= system.getTimeSlotCount()) {
        currentTimeSlotIndex = choice - 1;
    } else {
        cout << "Invalid choice. Please select a valid time slot." << endl;
    }
}

void Reservation::showTime() {
    // TODO: 调用 system.showTime()
    system.showTime();
}

void Reservation::showStatus() {
    // TODO: 调用 system.getTimeSlot(currentTimeSlotIndex).showRoomStatus()
    system.getTimeSlot(currentTimeSlotIndex).showRoomStatus();
}

std::vector<Room>::iterator Reservation::findRoom(int roomId) {
    // TODO: 取当前时段 system.getTimeSlot(currentTimeSlotIndex)，
    //       遍历其 rooms 找到 id == roomId 的机房；找不到返回对应 end()
    auto &currentTimeSlot = system.getTimeSlot(currentTimeSlotIndex);
    for (auto it = currentTimeSlot.getRooms().begin(); it != currentTimeSlot.getRooms().end(); ++it) {
        if (it->getId() == roomId) {
            return it;
        }
    }
    return currentTimeSlot.getRooms().end();  // 占位，实现时替换
}

std::vector<Seat>::iterator Reservation::findSeat(int roomId, int seatId) {
    // TODO: 全流程查找：当前时段 -> 机房(roomId) -> 座位(seatId)
    //       找到返回座位迭代器；找不到返回对应 end()
    auto roomIt = findRoom(roomId);
    if (roomIt != system.getTimeSlot(currentTimeSlotIndex).getRooms().end()) {
        return roomIt->searchSeat(seatId);
    }
    return {};  // 机房不存在：返回默认（无效）座位迭代器
}

void Reservation::reserve() {
    // TODO:
    // 1. 读入机房号、座位号
    // 2. findRoom(roomId) 找到机房（先判断机房是否存在）
    // 3. findSeat(roomId, seatId) 找到座位（判断座位是否存在）
    // 4. 座位未占用 -> setOccupied(true)，提示预约成功；已占用 -> 提示预约失败
    int roomId, seatId;
    cout << "Enter room ID: ";
    cin >> roomId;
    cout << "Enter seat ID: ";
    cin >> seatId;
    auto roomIt = findRoom(roomId);
    if (roomIt != system.getTimeSlot(currentTimeSlotIndex).getRooms().end()) {
        auto seatIt = roomIt->searchSeat(seatId);
        if (seatIt != roomIt->getSeats().end()) {
            if (!seatIt->getOccupied()) {
                seatIt->setOccupied(true);
                cout << "Reservation successful." << endl;
            } else {
                cout << "Seat is already occupied." << endl;
            }
        } else {
            cout << "Seat not found." << endl;
        }
    } else {
        cout << "Room not found." << endl;
    }
}

void Reservation::cancel() {
    // TODO:
    // 1. 读入机房号、座位号
    // 2. findRoom + findSeat 找到座位（判断机房/座位是否存在）
    // 3. 座位已占用 -> setOccupied(false)，提示取消成功；未占用 -> 提示取消失败
    int roomId, seatId;
    cout << "Enter room ID: ";
    cin >> roomId;
    cout << "Enter seat ID: ";
    cin >> seatId;
    auto roomIt = findRoom(roomId);
    if (roomIt != system.getTimeSlot(currentTimeSlotIndex).getRooms().end()) {
        auto seatIt = roomIt->searchSeat(seatId);
        if (seatIt != roomIt->getSeats().end()) {
            if (seatIt->getOccupied()) {
                seatIt->setOccupied(false);
                cout << "Cancellation successful." << endl;
            } else {
                cout << "Seat is not occupied." << endl;
            }
        } else {
            cout << "Seat not found." << endl;
        }
    } else {
        cout << "Room not found." << endl;
    }
}
