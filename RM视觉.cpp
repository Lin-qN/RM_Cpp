#include<iostream>
#include<fstream> 
#include<cstring>
#include<iomanip>
#include<cmath>
#include<vector>
using namespace std;
class Robot
{
	friend class team;
protected:
	int number;
	char team;
	int blood_vol;
	bool dead_flag;
	int heat;
	int cur_heat;
	char kind;
public:
	Robot(int n=0,char t='R',int b=100,int h=200,int ch=0,char k='B')
	{
		number=n;
		team=t;
		blood_vol=b;
		dead_flag=0;
		heat=h;
		cur_heat=ch;
		kind=k;

		cout<<"已创建";
		if(t=='R')
			cout<<"红方";
		else
			cout<<"蓝方";
		cout<<n<<"号";
		switch(k)
		{
			case 'B':
				cout<<"步兵";
				break;
			case 'S':
				cout<<"哨兵";
				break;
			case 'Y':
				cout<<"英雄";
				break;
			case 'G':
				cout<<"工程";
				break;
		}
		cout<<"机器人！\n";
	}
	void shoot(int n)
	{
		int cost,radius;
		if(kind=='B'||kind=='S')
		{
			cost=15;
			radius=17;
		}
		else if(kind=='Y')
		{
			cost=30;
			radius=42;
		}
		else
		{
			n=0;
			cost=0;
			radius=0;
			cout<<"非可发射弹丸机种！\n";
		}
		if(team=='R')
			cout<<"红方";
		else
			cout<<"蓝方";
		cout<<number<<"号";
		switch(kind)
		{
			case 'B':
				cout<<"步兵";
				break;
			case 'S':
				cout<<"哨兵";
				break;
			case 'Y':
				cout<<"英雄";
				break;
			case 'G':
				cout<<"工程";
				break;
		}
		cout<<"机器人发射"<<n<<"发"<<radius<<"mm弹丸！增加"<<n*cost<<"点热量。\n";

		cur_heat+=n*cost;
		if(cur_heat>heat)
		{
			cout<<"超出热量上限！"<<number<<"号哨兵机器人死亡。\n";
			blood_vol=0;
			die();
		}
	}
	void attacked(int injure)
	{
		cout<<number<<"号机器人受到"<<injure<<"点伤害！\n";
		blood_vol-=injure;
		if(blood_vol<=0)
		{
			cout<<"血量归0！"<<number<<"号机器人死亡。\n";
			blood_vol=0;
			die();
		}
	}
	void die()
	{
		cur_heat = 0;
		dead_flag=true;
	}
	void show()
	{

	}
};

//class B_robot:public Robot
//{
//public:
//	B_robot(int n=0,char t='R',int b=100,int h=200,int ch=0,char k='B'):Robot(n,t,b,h,ch,k){}
//	void shoot(int n)
//	{
//		if(team='R')
//			cout<<"红方";
//		else
//			cout<<"蓝方";
//		cout<<number<<"号步兵机器人发射"<<n<<"发17mm弹丸！增加"<<n*15<<"点热量。\n";
//
//		cur_heat+=n*15;
//		if(cur_heat>heat)
//		{
//			cout<<"超出热量上限！"<<number<<"号步兵机器人死亡。\n";
//			blood_vol=0;
//			die();
//		}
//	}
//};
//
//class S_robot:public Robot
//{
//public:
//	S_robot(int n=0,char t='R',int b=200,int h=300,int ch=0,char k='S'):Robot(n,t,b,h,ch,k){}
//	void shoot(int n)
//	{
//		if(team='R')
//			cout<<"红方";
//		else
//			cout<<"蓝方";
//		cout<<number<<"号哨兵机器人发射"<<n<<"发17mm弹丸！增加"<<n*15<<"点热量。\n";
//
//		cur_heat+=n*15;
//		if(cur_heat>heat)
//		{
//			cout<<"超出热量上限！"<<number<<"号哨兵机器人死亡。\n";
//			blood_vol=0;
//			die();
//		}
//	}
//};
//
//class Y_robot:public Robot
//{
//public:
//	Y_robot(int n=0,char t='R',int b=200,int h=300,int ch=0,char k='Y'):Robot(n,t,b,h,ch,k){}
//	void shoot(int n)
//	{
//		if(team='R')
//			cout<<"红方";
//		else
//			cout<<"蓝方";
//		cout<<number<<"号英雄机器人发射"<<n<<"发42mm弹丸！增加"<<n*30<<"点热量。\n";
//
//		cur_heat+=n*30;
//		if(cur_heat>heat)
//		{
//			cout<<"超出热量上限！"<<number<<"号英雄机器人死亡。\n";
//			blood_vol=0;
//			die();
//		}
//	}
//};
//
//class G_robot:public Robot
//{
//public:
//	G_robot(int n=0,char t='R',int b=200,int h=0,int ch=0,char k='G'):Robot(n,t,b,h,ch,k){}
//};

class team
{
protected:
	vector<Robot*> member;
public:
	void A(char team,char kind,unsigned int number)
	{
		int b,h;
		switch(kind)
		{
			case 'B':
				b=100;
				h=200;
				break;
			case 'S':
				b=200;
				h=300;
				break;
			case 'Y':
				b=200;
				h=300;
				break;
			case 'G':
				b=200;
				h=0;
				break;
		}
		Robot* p=new Robot(number,team,b,h,0,kind);
		member.push_back(p);
	}
	void F(char team,int number,int injure)
	{
		vector<Robot*>::iterator p=member.begin();
		for(;p!=member.end();p++)
			if((*p)->number==number)
			{
				(*p)->attacked(injure);
				break;
			}
	}
	void H(char team,int number,int n)
	{
		vector<Robot*>::iterator p=member.begin();
		for(;p!=member.end();p++)
			if((*p)->number==number)
			{
				//cout<<(*p)->kind<<endl;
				(*p)->shoot(n);
				break;
			}
	}
}B,R;
int main()
{
	ifstream infile;
	infile.open("data.txt");
	char order;
	char team;
	unsigned int number;
	int bullet;
	int injure;
	char kind;
	while(1)
	{
		while(!infile.eof())
		{
			infile>>order;
			if(order=='A')
			{
				infile>>team;
				if(team=='R')
				{
					infile>>kind>>number;
					R.A(team,kind,number);
				}
				else
				{
					infile>>kind>>number;
					B.A(team,kind,number);
				}
			}
			else if(order=='F')
			{
				infile>>team;
				if(team=='R')
				{
					infile>>number>>injure;
					R.F(team,number,injure);
				}
				else
				{
					infile>>number>>injure;
					B.F(team,number,injure);
				}
			}
			else if(order=='H')
			{
				infile>>team;
				if(team=='R')
				{
					infile>>number>>bullet;
					R.H(team,number,bullet);
				}
				else
				{
					infile>>number>>bullet;
					B.H(team,number,bullet);
				}
			}
			else
				return 0;
		}
	}

	return 0;
}
