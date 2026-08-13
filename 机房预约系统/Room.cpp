#include <iostream>
#include "Room.h"

using namespace std;

Room::Room(int id, int seatCount) {
    // TODO: 保存 id；循环 seatCount 次，向 seats 加入座位（编号 1 ~ seatCount）
    // 提示：用 seats.push_back(Seat(编号)) 依次加入
    this->id=id;
    for (int i = 1; i <= seatCount; i++) {
        seats.push_back(Seat(i));
    }
}

std::vector<Seat>::iterator Room::searchSeat(int seatId) {
    // TODO: 遍历 seats，找到 id == seatId 的座位则返回对应迭代器；找不到返回 seats.end()
    for (auto it = seats.begin(); it != seats.end(); ++it) {
        if (it->getId() == seatId) {
            return it;
        }
    }
    return seats.end();  // 占位，实现时替换
}

void Room::showStatus() const {
    // TODO: 遍历 seats，输出每个座位的编号和占用状态
    for (const auto& seat : seats) {
        cout << "Seat ID: " << seat.getId() << ", Occupied: " << (seat.getOccupied() ? "Yes" : "No") << endl;
    }
}

int Room::getOccupied() const {
    // TODO: 遍历统计 isOccupied == true 的数量并返回
    int count = 0;
    for (const auto& seat : seats) {
        if (seat.getOccupied()) {
            count++;
        }
    }
    return count;  // 占位，实现时替换
}

int Room::getRest() const {
    // TODO: 返回“座位总数 - 已占用数”（可以调用 getOccupied()）
    return seats.size() - getOccupied();  // 占位，实现时替换
}

int Room::getId() const {
    return id;
}

std::vector<Seat>& Room::getSeats() {
    return seats;
}
