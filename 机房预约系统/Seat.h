#pragma once

// 座位类：只负责管理自己的状态，不关心其他座位
class Seat {
private:
    int  id;          // 座位编号
    bool isOccupied;  // 是否被占用

public:
    Seat(int id);                   // 构造函数，isOccupied 初始化为 false
    void setOccupied(bool status);  // 设置占用状态
    int  getId() const;             // 获取座位编号
    bool getOccupied() const;       // 获取占用状态
};
