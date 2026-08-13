#pragma once

#include <vector>
#include "TimeSlot.h"

// 系统类：管理所有固定时间段
class ComputerRoomSystem {
private:
    std::vector<TimeSlot> timeSlots;  // 所有固定时间段

public:
    void addTimeSlot(const TimeSlot& ts);  // 添加一个时间段
    TimeSlot& getTimeSlot(int index);      // 获取指定下标的时间段
    int  getTimeSlotCount() const;         // 返回时间段数量
    void showTime() const;                 // 输出所有时间段
};
