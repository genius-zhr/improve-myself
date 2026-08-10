#pragma once
#include <map>
#include <vector>
#include "speaker.h"

// ==================================================================
// 演讲比赛流程管理类：整个系统的核心，负责调度一场比赛的全过程
//   - 初始化 12 名选手
//   - 两轮比赛：抽签 -> 分组 -> 打分 -> 计分 -> 晋级
//   - 文件读写：保存当前名单/成绩、追加往届记录、清空记录
//
// 你要实现的是「私有方法」的代码体。
// 私有方法的拆分只是"建议方案"，实现时你可以按自己的思路调整。
// ==================================================================
class SpeechManager {
public:
    SpeechManager();             // 构造：检查历史记录 + 准备选手名单
    ~SpeechManager();            // 析构：目前不需要额外清理

    void startSpeech();          // 开始比赛（跑完整两轮）
    void showRecord();           // 查看往届比赛记录
    void clearRecord();          // 清空往届比赛记录

private:
    // ---------- 初始化 ----------
    void initSpeakers();         // 准备 12 名选手（文件里有就读，没有就生成）

    // ---------- 一轮比赛的步骤 ----------
    void drawOrder();            // 抽签：打乱当前参赛者的出场顺序
    void contest();              // 进行一轮：按轮次决定分组与晋级方式
    void score(int round, std::vector<int>& contestants);  // 计分：去最高最低取平均
    void promoteTop(int n, std::vector<int>& group);       // 晋级：把组内前 n 名加入晋级名单
    void showScore(int round);   // 显示本轮成绩

    // ---------- 文件操作 ----------
    void saveRecord();           // 保存当前名单 + 两轮成绩 -> speaker.txt
    void saveResult();           // 追加本届冠亚季军 -> record.txt
    void loadRecord();           // 读 record.txt，判断历史文件是否为空

    // ---------- 成员变量 ----------
    std::map<int, Speaker> m_speakers;   // 所有选手：编号 -> 选手
    std::vector<int> m_order;            // 抽签后的出场顺序（只存编号）
    std::vector<int> m_group1;           // 第一组选手编号（第一轮用）
    std::vector<int> m_group2;           // 第二组选手编号（第一轮用）
    std::vector<int> m_promoted;         // 晋级名单（第一轮后 6 人；第二轮后存最终名次）
    int  m_round;                        // 当前轮次：1 或 2
    bool m_fileIsEmpty;                  // record.txt 是否为空 / 不存在
};
