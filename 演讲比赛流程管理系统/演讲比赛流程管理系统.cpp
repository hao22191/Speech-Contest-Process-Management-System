#include<iostream>
using namespace std;
#include<string>
#include<ctime>
#include "speechManager.h"

int main()
{
	//随机数种子
	srand((unsigned int)time(NULL));

	//创建管理对象
	SpeechManager sm;

	//测试12名选手创建
	/*for (map<int, Speaker>::iterator it = sm.m_speaker.begin();it != sm.m_speaker.end();it++)
	{
		cout << "选手编号：" << it->first << " 选手姓名：" << it->second.m_name << " 选手得分：" << it->second.m_score[0] << endl;
	}*/

	//用于存储用户的输入
	int choice = 0;

	while (true)
	{
		sm.show_menu();

		cout << "请输入您的选择：" << endl;

		cin >> choice;

		switch (choice)
		{
		case 1:  //  开始比赛
			sm.statrSpeech();
			break;
		case 2:  //查看往届比赛记录
			sm.showRecord();
			break;
		case 3:  //清空比赛记录
			sm.clearRecord();
			break;
		case 0:  //退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");  //清屏
			break;
		}
	}


	system("pause");
	return 0;
}