#pragma once

#include <vector>
#include "Seat.h"

// 机房类：管理自己的所有座位
class Room {
private:
    int               id;     // 机房编号
    std::vector<Seat> seats;  // 该机房的所有座位

public:
    Room(int id, int seatCount);                         // 构造函数，生成 seatCount 个座位
    std::vector<Seat>::iterator searchSeat(int seatId);  // 按 id 查座位，找不到返回 seats.end()
    void showStatus() const;                             // 遍历展示每个座位的占用状态
    int  getOccupied() const;                            // 实时计算已占用数量
    int  getRest() const;                                // 实时计算剩余数量
    int  getId() const;                                  // 获取机房编号
    std::vector<Seat>& getSeats();                       // 供上层用 seats.end() 判断是否找到
};
