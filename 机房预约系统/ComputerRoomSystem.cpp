#include <iostream>
#include "ComputerRoomSystem.h"

using namespace std;

void ComputerRoomSystem::addTimeSlot(const TimeSlot& ts) {
    timeSlots.push_back(ts);
}

TimeSlot& ComputerRoomSystem::getTimeSlot(int index) {
    return timeSlots[index];
}

int ComputerRoomSystem::getTimeSlotCount() const {
    return timeSlots.size();
}

void ComputerRoomSystem::showTime() const {
    // TODO: 遍历 timeSlots，输出每个时间段（建议带从 1 开始的序号，方便选择）
    for(size_t i = 0; i < timeSlots.size(); ++i) {
        cout << (i + 1) << ". " << timeSlots[i].getTime() << endl;
    }
}
