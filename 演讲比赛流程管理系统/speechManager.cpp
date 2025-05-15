#include"speechManager.h"

//构造函数
SpeechManager::SpeechManager()
{
	//初始化容器和属性
	this->initSpeech();
	//创建选手
	this->createSpeech();
	//加载往届记录
	this->loadRecord();
}

//菜单功能
void SpeechManager::show_menu()
{
	cout << "********************************************" << endl;
	cout << "************* 欢迎参加演讲比赛 *************" << endl;
	cout << "************* 1.开始演讲比赛   *************" << endl;
	cout << "************* 2.查看往届记录   *************" << endl;
	cout << "************* 3.清空比赛记录   *************" << endl;
	cout << "************* 0.退出比赛程序   *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//初始化容器和属性
void SpeechManager::initSpeech()
{
	//容器置空
	this->v1.clear();
	this->v2.clear();
	this->Victory.clear();
	this->m_speaker.clear();

	//初始化比赛轮次
	this->m_index = 1;

	//将记录的容器清空
	this->m_Record.clear();
}

//创建选手
void SpeechManager::createSpeech()
{
	string nameSpeed = "ABCDEFGHIJKL";
	for (int i = 0;i < 12;i++)
	{
		string name = "选手";
		name += nameSpeed[i];

		//创建具体选手 
		Speaker sp;
		sp.m_name = name;

		for (int j = 0;j < 2;j++)
		{
			sp.m_score[j] = 0;
		}

		//创建选手编号  并放到容器中
		this->v1.push_back(i + 10001);

		//选手编号以及对应选手放入 map容器中
		this->m_speaker.insert(make_pair(i + 10001, sp));
	}
}

//开始比赛  比赛完整流程控制函数
void SpeechManager::statrSpeech()
{
	//第一轮开始比赛

	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechContest();
	//3、显示晋级结果
	this->showScore();
	//第二轮开始比赛
	this->m_index++;
	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechContest();
	//3、显示最终结果
	this->showScore();
	//4、保存分数到文件中
	this->saveRecord();
	//初始化容器和属性
	this->initSpeech();
	//创建选手
	this->createSpeech();
	//加载往届记录
	this->loadRecord();
	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}

//抽签
void SpeechManager::speechDraw()
{
	cout << "第" << this->m_index << "轮比赛的选手正在抽签" << endl;
	cout << "------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->m_index == 1)
	{
		//第一轮比赛
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin();it != v1.end();it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//第二轮比赛
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

//比赛
void SpeechManager::speechContest()
{
	cout << "-----------第" << this->m_index << "次比赛正式开始-----------" << endl;

	//准备临时容器存放小组数据
	multimap<double, int,greater<double>> groupScore;

	int num = 0;

	//在场选手容器
	vector<int> v_src;
	if (this->m_index  == 1)
	{
		v_src = v1;
	}
	else
	{
		v_src = v2;
	}

	//遍历所有选手
	for (vector<int>::iterator it = v_src.begin();it != v_src.end();it++)
	{
		num++;
		//评委打分
		deque<double> d;
		for (int i = 0;i < 10;i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";  //查看每个人的每个得分
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>());  //排序
		d.pop_front();  //去掉最高分
		d.pop_back();  //去掉最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);  //总分
		double avg = sum / double(size(d));  //平均分

		//打印平均分
		//cout << "编号：" << *it << " 姓名：" << this->m_speaker[*it].m_name << " 平均分：" << avg << endl;
		
		this->m_speaker[*it].m_score[this->m_index - 1] = avg;

		//key 是分数  value 是选手编号
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin();mit != groupScore.end();mit++)
			{
				cout << "编号：" << mit->second << " 姓名：" << this->m_speaker[mit->second].m_name << " 成绩："
					<< mit->first << endl;
			}
			cout << endl;

			//取走前三名
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
			groupScore.clear();  //小组容器清空
		}
	}
	cout << "-----------第" << this->m_index << "轮比赛完毕-----------"<<endl;
	system("pause");
}

//显示得分
void SpeechManager::showScore()
{
	cout << "-----------第" << this->m_index << "轮晋级选手成员信息如下：-----------" << endl;

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
		cout << "选手编号：" << *it << " 姓名：" << this->m_speaker[*it].m_name
			<< " 分数" << this->m_speaker[*it].m_score[this->m_index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	show_menu();
}

//保存记录
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
	cout << "记录已经保存" << endl;
	this->fileIsEmpty = false;
}

//读取记录
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);

	//文件不存在的情况
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在!" << endl;
		ifs.close();
		return;
	}

	//文件为空的情况
	char ch;
	ifs >> ch ;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		//cout << "文件为空!" << endl;
		ifs.close();
		return;
	}

	//文件不为空的情况
	this->fileIsEmpty = false;
	int index = 0;

	string data;
	ifs.putback(ch);  //放回读取过的字符
	while (ifs >> data)
	{
		//cout << data << endl;
		int pos = -1;
		int start = 0;

		vector<string> v;  //存放6个字符串  3个编号  3个分数
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
		cout << it->first << "冠军编号 " << it->second[0] <<" 冠军得分："<<it->second[1] << endl;
	}*/
}

//显示往届记录
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在或者为空!" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size();i++)
		{
			cout << "第" << i + 1 << "届"
				<< "冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << " "
				<< "亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << " "
				<< "季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}

//清空文件
void SpeechManager::clearRecord()
{
	cout << "是否确定清空文件" << endl;
	cout << "1. 确认" << endl;
	cout << "2. 取消" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//确认清空
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化容器和属性
		this->initSpeech();
		//创建选手
		this->createSpeech();
		//加载往届记录
		this->loadRecord();

		cout << "清空成功!" << endl;
	}
	system("pause");
	system("cls");
}

//退出系统
void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//析构函数
SpeechManager::~SpeechManager()
{

}