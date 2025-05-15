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
	//���캯��
	SpeechManager();

	//�˵�����
	void show_menu();

	//�˳�ϵͳ
	void exitSystem();

	//��ʼ������������
	void initSpeech();

	//����ѡ��
	void createSpeech();

	//��ʼ����  �����������̿��ƺ���
	void statrSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�÷�
	void showScore();

	//�����¼
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//��ʾ�����¼
	void showRecord();

	//����ļ�
	void clearRecord();

	//��������
	~SpeechManager();

	//��Ա����
	//�����һ�ֱ���ѡ�ֱ������
	vector<int> v1;

	//����ڶ��ֱ���ѡ�ֱ������
	vector<int> v2;

	//ʤ����ǰ����ѡ�ֱ������
	vector<int> Victory;

	//��ű���Լ���Ӧ��ѡ������
	map<int, Speaker> m_speaker;

	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	//��¼�����ִ�
	int m_index;

	//��������¼������
	map<int, vector<string>> m_Record;
};