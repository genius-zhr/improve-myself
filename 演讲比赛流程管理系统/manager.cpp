#include "manager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <random>
#include <deque>
using namespace std;

// ==================================================================
// 下面每个方法都写明了"该做什么"，由你来实现。
// 这是本项目的核心，尤其是 score / promoteTop / 文件读写。
// 需要额外头文件时自己加 include。
// ==================================================================

// 构造函数：程序启动时自动调用，做两件事
SpeechManager::SpeechManager() {
    // TODO:
    //  1. loadRecord()   —— 检查 record.txt 存在吗？为空吗？设置 m_fileIsEmpty
    //  2. initSpeakers() —— 准备 12 名选手名单
    loadRecord();
    initSpeakers();
}
        


SpeechManager::~SpeechManager() {
    // 没有需要手动释放的资源，保持空即可
}
void SpeechManager::initSpeakers(){
        ifstream file;
        file.open("speaker.txt",ios::in);
        if(!file.is_open()||file.peek()==EOF){
            for(int i=0;i<12;i++){
                Speaker s;
                s.setId(i+10001);
                s.setName("选手"+to_string(i+1));
                m_speakers.insert(make_pair(s.getId(),s));
            }
            }else{
            int id;
            string name;
            double round1,round2;
            while(file>>id&&file>>name&&file>>round1&&file>>round2){
            Speaker s;
            s.setId(id);
            s.setName(name);
            s.setRound1(round1);
            s.setRound2(round2);
            m_speakers.insert(make_pair(s.getId(),s));
            }
            }
    }

// 开始比赛：跑完整两轮
void SpeechManager::startSpeech() {
    // TODO:
    //  第一轮：
    //    m_round = 1
    //    drawOrder();      // 12 人抽签，决定出场顺序
    //    contest();        // 分两组比赛，各组前 3 名晋级（共 6 人）
    //    saveRecord();     // 把本轮成绩保存到 speaker.txt
    //    showScore(1);     // 显示第一轮结果
    //  第二轮：
    //    m_round = 2
    //    drawOrder();      // 晋级的 6 人重新抽签
    //    contest();        // 单场决赛，取前 3 名 = 冠亚季军
    //    saveResult();     // 追加一届结果到 record.txt
    //    saveRecord();     // 更新 speaker.txt
    //    showScore(2);     // 显示最终结果
    m_round=1;
    drawOrder();
    contest();
    saveRecord();
    showScore(1);
    m_round=2;
    drawOrder();
    contest();
    saveResult();
    saveRecord();
    showScore(2);
}

// 抽签：把当前参赛选手的编号打乱，存进 m_order
void SpeechManager::drawOrder() {
    // TODO:
    //  m_order 里放的是"这轮要比赛的人"的编号
    //  第一轮是 12 人，第二轮是晋级的 6 人
    //  用 std::shuffle 打乱顺序（参考随机数种子怎么写）
    m_order.clear();
    if(m_round==1){
        for(auto it=m_speakers.begin();it!=m_speakers.end();it++){
            m_order.push_back(it->first);
        }
    }else if(m_round==2){
        m_order=m_promoted;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_order.begin(), m_order.end(), g);
}

// 进行一轮比赛：按当前轮次决定分组和晋级方式
void SpeechManager::contest() {
    // TODO:
    //  第一轮（m_round == 1）：
    //    把 m_order 前 6 个放进 m_group1，后 6 个放进 m_group2
    //    对每一组：
    //      score(1, 该组);      // 打分 + 去最高最低取平均
    //      promoteTop(3, 该组); // 组内前 3 名加入 m_promoted
    //  第二轮（m_round == 2）：
    //    score(2, m_order);     // 6 人打分
    //    promoteTop(3, m_order);// 前 3 名 = 最终名次（存进 m_promoted）
    //
    //  打分来源：可以用随机数模拟评委，也可以手动输入，你来定。
    m_group1.clear();
    m_group2.clear();
    if(m_round==1){
        for(int i=0;i<6;i++){
            m_group1.push_back(m_order[i]);
        }
        for(int i=6;i<12;i++){
            m_group2.push_back(m_order[i]);
        }
        score(1,m_group1);
        promoteTop(3,m_group1);
        score(1,m_group2);
        promoteTop(3,m_group2);
    }else if(m_round==2){
        score(2,m_order);
        promoteTop(3,m_order);
    }
}

// 计分：给一组选手算成绩
// round: 1 或 2，决定把结果写到第一轮还是第二轮成绩
void SpeechManager::score(int round, vector<int>& contestants) {
    // TODO:
    //  对 contestants 里的每位选手：
    //    1. 收齐 10 位评委的打分（随机 or 输入），存到一个容器
    //    2. 去掉一个最高分、一个最低分
    //    3. 剩下 8 个求和取平均
    //    4. 把平均分写入该选手对应轮次的成绩（setRound1 / setRound2）
    //  提示：去最高最低可以 sort 后掐头去尾，也可以用 max_element/min_element
    deque<double> scores;
    for(auto id : contestants){
        scores.clear();
        for(int i=0;i<10;i++){
            double score;
            cout<< "请输入选手 " << m_speakers[id].getName() << " 的第 " << i+1 << " 位评委打分：";
            cin>>score;
            scores.push_back(score);
        }
        sort(scores.begin(),scores.end());
        scores.pop_front();
        scores.pop_back();
        double sum=accumulate(scores.begin(),scores.end(),0.0);
        double avg=sum/scores.size();
        if(round==1){
            m_speakers[id].setRound1(avg);
        }else if(round==2){
            m_speakers[id].setRound2(avg);
        }
    }
}

// 晋级：把一组里成绩前 n 名的选手编号，追加进 m_promoted
void SpeechManager::promoteTop(int n, vector<int>& group) {
    // TODO:
    //  1. 按成绩从高到低给 group 排序（分数相同怎么排？规则你来定）
    //     —— 这就是练 sort + 自定义比较器的地方
    //  2. 取前 n 个编号，push_back 进 m_promoted
    // 自定义比较器：按当前轮次成绩从高到低排，同分按编号小在前
    sort(group.begin(), group.end(), [this](int a, int b) {
        // m_round 决定比哪一轮的成绩
        double sa = (m_round == 1) ? m_speakers[a].getRound1() : m_speakers[a].getRound2();
        double sb = (m_round == 1) ? m_speakers[b].getRound1() : m_speakers[b].getRound2();
        if (sa != sb) return sa > sb;   // 成绩高的排前面
        return a < b;                    // 同分：编号小的排前面
    });
    for(int i=0;i<n;i++){
        m_promoted.push_back(group[i]);
    }
}

// 显示本轮成绩
void SpeechManager::showScore(int round) {
    // TODO:
    //  第一轮：显示每组选手的成绩和组内名次
    //  第二轮：显示最终排名（冠军 / 亚军 / 季军）
    //  遍历对应容器，从 m_speakers 里取出选手信息打印
}

// 保存当前名单 + 两轮成绩 到 speaker.txt
void SpeechManager::saveRecord() {
    // TODO:
    //  每行一个选手，格式建议：编号 姓名 第一轮成绩 第二轮成绩（空格分隔）
    //  遍历 m_speakers 写入文件
    ofstream file;
    file.open("speaker.txt",ios::out);
    for(auto it=m_speakers.begin();it!=m_speakers.end();it++){
        file<<it->second.getId()<<" "<<it->second.getName()<<" "<<it->second.getRound1()<<" "<<it->second.getRound2()<<endl;
    }
    file.close();
}

// 追加本届冠亚季军 到 record.txt
void SpeechManager::saveResult() {
    // TODO:
    //  每届一行，格式建议：届次 冠军编号 亚军编号 季军编号
    //  m_promoted[0] 冠军，m_promoted[1] 亚军，m_promoted[2] 季军
    //  用"追加"方式打开文件（别把上一届覆盖掉）
    ofstream file;
    file.open("record.txt",ios::app);
    int roundNum=0;
    ifstream infile("record.txt");
    string line;
    while (getline(infile, line)) {
        if (!line.empty()) {
            roundNum++;
        }
    }
    file<<roundNum+1<<" "<<m_promoted[0]<<" "<<m_promoted[1]<<" "<<m_promoted[2]<<endl;
    file.close();
}

// 加载历史记录：检查 record.txt 是否存在、是否为空
void SpeechManager::loadRecord() {
    // TODO:
    //  1. 尝试打开 record.txt
    //  2. 判断：文件不存在 or 空文件 -> m_fileIsEmpty = true
    //  3. 文件有内容 -> m_fileIsEmpty = false
    ifstream file;
    file.open("record.txt",ios::in);
    if(!file.is_open()||file.peek()==EOF){
        m_fileIsEmpty=true;
    }else{
        m_fileIsEmpty=false;
    }
}

// 查看往届记录
void SpeechManager::showRecord() {
    // TODO:
    //  如果 m_fileIsEmpty 为 true：提示"记录为空"，直接返回
    //  否则：
    //    读 record.txt 的每一行，解析出 届次 冠军 亚军 季军 的编号
    //    用编号在 m_speakers 里找到名字，打印出来
    //  提示：文件末尾可能有空行，解析时要能跳过，别崩
    if(m_fileIsEmpty){
        cout<<"记录为空"<<endl;
        return;
    }else{
        ifstream file;
        file.open("record.txt",ios::in);
        string line;
        while(getline(file,line)){
            if(line.empty()){
                continue;
            }
            istringstream iss(line);
            int roundNum,championId,runnerUpId,thirdPlaceId;
            iss>>roundNum>>championId>>runnerUpId>>thirdPlaceId;
            cout<<"第"<<roundNum<<"届比赛结果："<<endl;
            cout<<"冠军："<<m_speakers.find(championId)->second.getName()<<"（编号："<<championId<<"）"<<endl;
            cout<<"亚军："<<m_speakers.find(runnerUpId)->second.getName()<<"（编号："<<runnerUpId<<"）"<<endl;
            cout<<"季军："<<m_speakers.find(thirdPlaceId)->second.getName()<<"（编号："<<thirdPlaceId<<"）"<<endl;

        }
    }
}

// 清空往届记录
void SpeechManager::clearRecord() {
    // TODO:
    //  确认后再清空 record.txt（把文件内容清空 or 直接 remove 文件）
    //  记得把 m_fileIsEmpty 改成 true
    //  提示：清空前要不要问一下用户确认？建议要
    ofstream file;
    file.open("record.txt",ios::out|ios::trunc);
    file.close();
    m_fileIsEmpty=true;
}
