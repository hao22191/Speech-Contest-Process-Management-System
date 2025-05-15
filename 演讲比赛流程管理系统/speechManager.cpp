#include"speechManager.h"

//���캯��
SpeechManager::SpeechManager()
{
	//��ʼ������������
	this->initSpeech();
	//����ѡ��
	this->createSpeech();
	//���������¼
	this->loadRecord();
}

//�˵�����
void SpeechManager::show_menu()
{
	cout << "********************************************" << endl;
	cout << "************* ��ӭ�μ��ݽ����� *************" << endl;
	cout << "************* 1.��ʼ�ݽ�����   *************" << endl;
	cout << "************* 2.�鿴�����¼   *************" << endl;
	cout << "************* 3.��ձ�����¼   *************" << endl;
	cout << "************* 0.�˳���������   *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//��ʼ������������
void SpeechManager::initSpeech()
{
	//�����ÿ�
	this->v1.clear();
	this->v2.clear();
	this->Victory.clear();
	this->m_speaker.clear();

	//��ʼ�������ִ�
	this->m_index = 1;

	//����¼���������
	this->m_Record.clear();
}

//����ѡ��
void SpeechManager::createSpeech()
{
	string nameSpeed = "ABCDEFGHIJKL";
	for (int i = 0;i < 12;i++)
	{
		string name = "ѡ��";
		name += nameSpeed[i];

		//��������ѡ�� 
		Speaker sp;
		sp.m_name = name;

		for (int j = 0;j < 2;j++)
		{
			sp.m_score[j] = 0;
		}

		//����ѡ�ֱ��  ���ŵ�������
		this->v1.push_back(i + 10001);

		//ѡ�ֱ���Լ���Ӧѡ�ַ��� map������
		this->m_speaker.insert(make_pair(i + 10001, sp));
	}
}

//��ʼ����  �����������̿��ƺ���
void SpeechManager::statrSpeech()
{
	//��һ�ֿ�ʼ����

	//1����ǩ
	this->speechDraw();
	//2������
	this->speechContest();
	//3����ʾ�������
	this->showScore();
	//�ڶ��ֿ�ʼ����
	this->m_index++;
	//1����ǩ
	this->speechDraw();
	//2������
	this->speechContest();
	//3����ʾ���ս��
	this->showScore();
	//4������������ļ���
	this->saveRecord();
	//��ʼ������������
	this->initSpeech();
	//����ѡ��
	this->createSpeech();
	//���������¼
	this->loadRecord();
	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}

//��ǩ
void SpeechManager::speechDraw()
{
	cout << "��" << this->m_index << "�ֱ�����ѡ�����ڳ�ǩ" << endl;
	cout << "------------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->m_index == 1)
	{
		//��һ�ֱ���
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin();it != v1.end();it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//�ڶ��ֱ���
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin();it != v2.end();it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "------------------------------" << endl;
	system("pause");
	cout << endl;
}

//����
void SpeechManager::speechContest()
{
	cout << "-----------��" << this->m_index << "�α�����ʽ��ʼ-----------" << endl;

	//׼����ʱ�������С������
	multimap<double, int,greater<double>> groupScore;

	int num = 0;

	//�ڳ�ѡ������
	vector<int> v_src;
	if (this->m_index  == 1)
	{
		v_src = v1;
	}
	else
	{
		v_src = v2;
	}

	//��������ѡ��
	for (vector<int>::iterator it = v_src.begin();it != v_src.end();it++)
	{
		num++;
		//��ί���
		deque<double> d;
		for (int i = 0;i < 10;i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";  //�鿴ÿ���˵�ÿ���÷�
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>());  //����
		d.pop_front();  //ȥ����߷�
		d.pop_back();  //ȥ����ͷ�

		double sum = accumulate(d.begin(), d.end(), 0.0f);  //�ܷ�
		double avg = sum / double(size(d));  //ƽ����

		//��ӡƽ����
		//cout << "��ţ�" << *it << " ������" << this->m_speaker[*it].m_name << " ƽ���֣�" << avg << endl;
		
		this->m_speaker[*it].m_score[this->m_index - 1] = avg;

		//key �Ƿ���  value ��ѡ�ֱ��
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin();mit != groupScore.end();mit++)
			{
				cout << "��ţ�" << mit->second << " ������" << this->m_speaker[mit->second].m_name << " �ɼ���"
					<< mit->first << endl;
			}
			cout << endl;

			//ȡ��ǰ����
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin();mit != groupScore.end() && count<3;mit++,count++)
			{
				if (this->m_index == 1)
				{
					v2.push_back(mit->second);
				}
				else
				{
					Victory.push_back(mit->second);
				}
			}
			//
			groupScore.clear();  //С���������
		}
	}
	cout << "-----------��" << this->m_index << "�ֱ������-----------"<<endl;
	system("pause");
}

//��ʾ�÷�
void SpeechManager::showScore()
{
	cout << "-----------��" << this->m_index << "�ֽ���ѡ�ֳ�Ա��Ϣ���£�-----------" << endl;

	vector<int> v;

	if (this->m_index == 1)
	{
		v = v2;
	}
	else
	{
		v = Victory;
	}

	for (vector<int>::iterator it = v.begin();it != v.end();it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << " ������" << this->m_speaker[*it].m_name
			<< " ����" << this->m_speaker[*it].m_score[this->m_index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	show_menu();
}

//�����¼
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = Victory.begin();it != Victory.end();it++)
	{
		ofs << *it << "," << this->m_speaker[*it].m_score[1] << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "��¼�Ѿ�����" << endl;
	this->fileIsEmpty = false;
}

//��ȡ��¼
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);

	//�ļ������ڵ����
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�������!" << endl;
		ifs.close();
		return;
	}

	//�ļ�Ϊ�յ����
	char ch;
	ifs >> ch ;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�Ϊ��!" << endl;
		ifs.close();
		return;
	}

	//�ļ���Ϊ�յ����
	this->fileIsEmpty = false;
	int index = 0;

	string data;
	ifs.putback(ch);  //�Żض�ȡ�����ַ�
	while (ifs >> data)
	{
		//cout << data << endl;
		int pos = -1;
		int start = 0;

		vector<string> v;  //���6���ַ���  3�����  3������
		while (true)
		{
			pos = data.find(",", start);

			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
	/*for (map<int, vector<string>>::iterator it = m_Record.begin();it != m_Record.end();it++)
	{
		cout << it->first << "�ھ���� " << it->second[0] <<" �ھ��÷֣�"<<it->second[1] << endl;
	}*/
}

//��ʾ�����¼
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ��!" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size();i++)
		{
			cout << "��" << i + 1 << "��"
				<< "�ھ���ţ�" << this->m_Record[i][0] << " �÷֣�" << this->m_Record[i][1] << " "
				<< "�Ǿ���ţ�" << this->m_Record[i][2] << " �÷֣�" << this->m_Record[i][3] << " "
				<< "������ţ�" << this->m_Record[i][4] << " �÷֣�" << this->m_Record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}

//����ļ�
void SpeechManager::clearRecord()
{
	cout << "�Ƿ�ȷ������ļ�" << endl;
	cout << "1. ȷ��" << endl;
	cout << "2. ȡ��" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//ȷ�����
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//��ʼ������������
		this->initSpeech();
		//����ѡ��
		this->createSpeech();
		//���������¼
		this->loadRecord();

		cout << "��ճɹ�!" << endl;
	}
	system("pause");
	system("cls");
}

//�˳�ϵͳ
void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//��������
SpeechManager::~SpeechManager()
{

}