#pragma once

#include <string>
#include <vector>
#include "Room.h"

// 时间段类：管理自己这个时段下的所有机房
class TimeSlot {
private:
    std::string       time;   // 时间段字符串，如 "08:00-10:00"
    std::vector<Room> rooms;  // 该时段下的所有机房

public:
    TimeSlot(const std::string& time, int roomCount, int seatsPerRoom);  // 构造函数

    std::string getTime() const;                     // 获取时间段字符串
    std::vector<Room>::iterator findRoom(int roomId); // 按 id 查机房，找不到返回 rooms.end()
    void showRoomStatus() const;                     // 展示每个机房的已占用/剩余数量
    std::vector<Room>& getRooms();                   // 供上层用 rooms.end() 判断是否找到
};
