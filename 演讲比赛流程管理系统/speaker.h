#pragma once
#include <string>

// ==================================================================
// 选手类：纯数据类，一个选手 = 编号 + 姓名 + 两轮成绩
// 它不参与比赛流程，只负责"装自己的数据"
// ==================================================================
class Speaker {
public:
    Speaker();   // 构造函数：默认把成员初始化为 0 / 空

    // 编号（从 10001 开始）
    void setId(int id);
    int  getId() const;

    // 姓名
    void setName(const std::string& name);
    std::string getName() const;

    // 第一轮成绩（未比赛时为 0）
    void setRound1(double score);
    double getRound1() const;

    // 第二轮成绩（未比赛时为 0）
    void setRound2(double score);
    double getRound2() const;

private:
    int         m_id;      // 选手编号
    std::string m_name;    // 选手姓名
    double      m_round1;  // 第一轮成绩
    double      m_round2;  // 第二轮成绩
};
