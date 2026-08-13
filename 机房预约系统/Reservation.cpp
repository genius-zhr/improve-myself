#include <iostream>
#include "Reservation.h"

using namespace std;

Reservation::Reservation() {
    // TODO: 初始化固定数据
    // 提示：用 system.addTimeSlot(...) 依次加入 3 个时间段：
    //   "08:00-10:00"、"10:00-12:00"、"14:00-16:00"
    //   每个时间段 3 个机房、每机房 10 个座位
}

void Reservation::selectTime() {
    // TODO:
    // 1. 显示所有时间段（可调用 system.showTime()）
    // 2. 读入用户选择（从 1 开始）
    // 3. 校验范围，把 currentTimeSlotIndex 设为对应下标（从 0 开始）
}

void Reservation::showTime() {
    // TODO: 调用 system.showTime()
}

void Reservation::showStatus() {
    // TODO: 调用 system.getTimeSlot(currentTimeSlotIndex).showRoomStatus()
}

std::vector<Room>::iterator Reservation::findRoom(int roomId) {
    // TODO: 取当前时段 system.getTimeSlot(currentTimeSlotIndex)，
    //       遍历其 rooms 找到 id == roomId 的机房；找不到返回对应 end()
    return {};  // 占位，实现时替换
}

std::vector<Seat>::iterator Reservation::findSeat(int roomId, int seatId) {
    // TODO: 全流程查找：当前时段 -> 机房(roomId) -> 座位(seatId)
    //       找到返回座位迭代器；找不到返回对应 end()
    return {};  // 占位，实现时替换
}

void Reservation::reserve() {
    // TODO:
    // 1. 读入机房号、座位号
    // 2. findRoom(roomId) 找到机房（先判断机房是否存在）
    // 3. findSeat(roomId, seatId) 找到座位（判断座位是否存在）
    // 4. 座位未占用 -> setOccupied(true)，提示预约成功；已占用 -> 提示预约失败
}

void Reservation::cancel() {
    // TODO:
    // 1. 读入机房号、座位号
    // 2. findRoom + findSeat 找到座位（判断机房/座位是否存在）
    // 3. 座位已占用 -> setOccupied(false)，提示取消成功；未占用 -> 提示取消失败
}
