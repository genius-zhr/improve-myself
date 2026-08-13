#include "Seat.h"

using namespace std;

Seat::Seat(int id) {
    // TODO: 保存 id，并把 isOccupied 初始化为 false
    // 提示：参数名和成员名都是 id，用 this->id 区分，或用初始化列表
}

void Seat::setOccupied(bool status) {
    isOccupied = status;
}

int Seat::getId() const {
    return id;
}

bool Seat::getOccupied() const {
    return isOccupied;
}
