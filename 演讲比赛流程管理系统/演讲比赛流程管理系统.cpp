#include<iostream>
using namespace std;
#include<string>
#include<ctime>
#include "speechManager.h"

int main()
{
	//���������
	srand((unsigned int)time(NULL));

	//�����������
	SpeechManager sm;

	//����12��ѡ�ִ���
	/*for (map<int, Speaker>::iterator it = sm.m_speaker.begin();it != sm.m_speaker.end();it++)
	{
		cout << "ѡ�ֱ�ţ�" << it->first << " ѡ��������" << it->second.m_name << " ѡ�ֵ÷֣�" << it->second.m_score[0] << endl;
	}*/

	//���ڴ洢�û�������
	int choice = 0;

	while (true)
	{
		sm.show_menu();

		cout << "����������ѡ��" << endl;

		cin >> choice;

		switch (choice)
		{
		case 1:  //  ��ʼ����
			sm.statrSpeech();
			break;
		case 2:  //�鿴���������¼
			sm.showRecord();
			break;
		case 3:  //��ձ�����¼
			sm.clearRecord();
			break;
		case 0:  //�˳�ϵͳ
			sm.exitSystem();
			break;
		default:
			system("cls");  //����
			break;
		}
	}


	system("pause");
	return 0;
}