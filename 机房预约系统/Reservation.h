#pragma once

#include <vector>
#include "ComputerRoomSystem.h"

// 预约业务类：负责初始化数据 + 预约/取消操作
class Reservation {
private:
    ComputerRoomSystem system;  // 持有系统对象
    int  currentTimeSlotIndex;  // 当前选中的时间段下标（从 0 开始）

public:
    Reservation();  // 构造函数，初始化固定时间段/机房/座位

    void selectTime();  // 选择时间段，设置 currentTimeSlotIndex
    void showTime();    // 显示所有时间段（委托给 system）
    void showStatus();  // 显示当前时段的机房/座位状态（委托给 system）

    std::vector<Room>::iterator findRoom(int roomId);              // 在当前时段找机房
    std::vector<Seat>::iterator findSeat(int roomId, int seatId);  // 全流程查找座位

    void reserve();  // 预约座位
    void cancel();   // 取消预约
};
