#include "speaker.h"

// 这里的每个方法都很简单，主要是"赋值"和"取值"。
// 构造函数记得把成员初始化好：编号 0、姓名为空、两轮成绩都是 0。

Speaker::Speaker() {
    // TODO: 初始化成员变量（编号、姓名、两轮成绩）
    m_id=0;
    m_name="";
    m_round1=0;
    m_round2=0;
}

void Speaker::setId(int id) {
    // TODO: m_id = id;
    m_id=id;
}

int Speaker::getId() const {
    // TODO: 返回 m_id
    return m_id;
}

void Speaker::setName(const std::string& name) {
    // TODO: m_name = name;
    m_name=name;
}
std::string Speaker::getName() const {
    // TODO: 返回 m_name
    return m_name;
}

void Speaker::setRound1(double score) {
    // TODO: m_round1 = score;
    m_round1=score;
}

double Speaker::getRound1() const {
    // TODO: 返回 m_round1
    return m_round1;
}

void Speaker::setRound2(double score) {
    // TODO: m_round2 = score;
    m_round2=score;
}

double Speaker::getRound2() const {
    // TODO: 返回 m_round2
    return m_round2;
}
