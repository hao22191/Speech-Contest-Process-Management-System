#pragma once
#include<iostream>
using namespace std;
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<deque>
#include<functional>
#include<algorithm>
#include<numeric>
#include"speaker.h"

class SpeechManager
{
public:
	//构造函数
	SpeechManager();

	//菜单功能
	void show_menu();

	//退出系统
	void exitSystem();

	//初始化容器和属性
	void initSpeech();

	//创建选手
	void createSpeech();

	//开始比赛  比赛完整流程控制函数
	void statrSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示得分
	void showScore();

	//保存记录
	void saveRecord();

	//读取记录
	void loadRecord();

	//显示往届记录
	void showRecord();

	//清空文件
	void clearRecord();

	//析构函数
	~SpeechManager();

	//成员属性
	//保存第一轮比赛选手编号容器
	vector<int> v1;

	//保存第二轮比赛选手编号容器
	vector<int> v2;

	//胜出的前三名选手编号容器
	vector<int> Victory;

	//存放编号以及对应的选手容器
	map<int, Speaker> m_speaker;

	//判断文件是否为空
	bool fileIsEmpty;

	//记录比赛轮次
	int m_index;

	//存放往届记录的容器
	map<int, vector<string>> m_Record;
};