#include <iostream>
#include "TimeSlot.h"

using namespace std;

TimeSlot::TimeSlot(const std::string& time, int roomCount, int seatsPerRoom) {
    // TODO: 保存 time；循环 roomCount 次，向 rooms 加入机房
    // 提示：机房编号从 101 开始（101、102、...），每个机房 seatsPerRoom 个座位
    //      用 rooms.push_back(Room(机房编号, seatsPerRoom)) 依次加入
}

std::string TimeSlot::getTime() const {
    return time;
}

std::vector<Room>::iterator TimeSlot::findRoom(int roomId) {
    // TODO: 遍历 rooms，找到 id == roomId 的机房则返回对应迭代器；找不到返回 rooms.end()
    return rooms.end();  // 占位，实现时替换
}

void TimeSlot::showRoomStatus() const {
    // TODO: 遍历 rooms，输出每个机房的编号、已占用数（getOccupied()）、剩余数（getRest()）
}

std::vector<Room>& TimeSlot::getRooms() {
    return rooms;
}
