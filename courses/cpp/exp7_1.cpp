/* 
1、	电话本
    	编写C++程序完成以下功能：
（1）	实现简单电话本功能，用姓名来搜索电话号码；
（2）	用户输入姓名，程序查找并输出结果；
（3）	用户可以通过输入，添加姓名和电话号码；
（4）	用户可以删除姓名和电话号码；
（5）	电话本可以保存在指定文件中；
（6）	电话可被从指定文件中读入到内存。
*/ 

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

/*====================Class Declaration==================*/
class Record
{
	private:
		string name;//姓名 
		string phone;//号码 
	public:
		Record( string n="", string p="" );//构造函数 
		void set_name( string n );//设置姓名 
		void set_phone( string p );//设置号码 
		string show_name()const;//返回姓名 
		string show_phone()const;//返回号码 
};


class Phonebook
{
	private:
		vector<Record> phonelist;
		int end;//长度 
	public:
		Phonebook();
		int tail()const;//返回长度 
		bool load();//从文件载入信息 
		bool update()const;//将变化更新到文件 
		void add_record( const string n, const string p );//添加记录 
		void del_record( int n );//删除记录 
		void mod_record( const int m, const string n, const string p );//修改记录 
		int search_name( const string n );//按姓名查询 
		int search_phone( const string p );	//按号码查询 
		void show_menu()const;//显示采单 
		void show_book()const;//显示整个电话簿 
		void show_record( int n )const;//显示一条记录 
		void clear();//清空记录 
};

/*=============Class Member Function Definition=============*/


/* Class Record */
Record::Record( string n, string p )
{
	name = n;
	phone = p;
}
//修改记录姓名 
void Record::set_name( string n )
{
	name = n;
}
//修改记录号码 
void Record::set_phone( string p )
{
	phone = p;
}
//返回记录姓名 
string Record::show_name()const
{
	return name;
}
//返回记录号码 
string Record::show_phone()const
{
	return phone;
}

/* Class Phonebook */
//构造函数 
Phonebook::Phonebook()
{
	end = -1;
}
//返回电话本长度 
int Phonebook::tail()const
{
	return end;
}
//从文件读入记录 
bool Phonebook::load()
{
	cout << "msg:载入电话簿中..." << endl;
	ifstream fin( "records.txt" );
	if ( !fin )
	{
		cout << "msg:电话簿文件打开失败" << endl;
		return 0;
	}
	string n, p;
	clear();
	//逐条读取并添加记录 
	while ( getline( fin, n ) && getline( fin, p ) )
	{
		add_record( n, p );
	}
	fin.close();
	cout << "msg:载入完毕,共载入" << tail()+1 << "条记录" << endl;
	return 1;
}
//从文件读入记录 
bool Phonebook::update()const
{
	cout << "msg:保存电话簿中..." << endl;
	ofstream fout( "records.txt", ios_base::out | ios_base::trunc );
	if ( !fout )
	{
		cout << "msg:电话簿文件打开失败" << endl;
		return 0;
	}
	int i;
	for ( i=0; i<=tail(); i++ )
	{
		fout << phonelist[i].show_name() << endl << phonelist[i].show_phone() << endl;
	}
	fout.close();
	cout << "msg:更新完毕 " << i << endl;
	return 1;
}
//向电话本对象中添加记录 
void Phonebook::add_record( const string n, const string p )
{
	Record tmp( n, p );
	phonelist.push_back( tmp );
	end ++;
}
//删除电话本中的记录 
void Phonebook::del_record( int n )
{
	if ( n-1<0 || n-1 >tail() )
	{
		cout << "记录#" << n << "不存在" << endl;
		return;
	}
	vector <Record>::iterator I=phonelist.begin();
	while ( n-- ) I++;
	phonelist.erase( I );
	end --;
	
}
//更改电话本中的记录 
void Phonebook::mod_record( int m, const string n, const string p )
{
	if ( n != "0" )
		phonelist[m].set_name( n );
	if ( p != "0" )
		phonelist[m].set_phone( p );
}
//按姓名搜索记录 
int Phonebook::search_name( const string n )
{
	for ( int i=0; i<=tail(); i++ )
		if ( phonelist[i].show_name() == n )
			return i;
	return -1;
}
//按号码搜索记录 
int Phonebook::search_phone( const string p )
{
	for ( int i=0; i<=tail(); i++ )
		if ( phonelist[i].show_phone() == p )
			return i;
	return -1;
}
//打印整个电话本 
void Phonebook::show_book()const
{
    if ( end == -1 )
    {
        cout << "无记录" << endl;
		return;
	}
	
    cout << setw(4) << "编号" << ":" << setw(20) << "姓名" 
	     << setw(20) << "电话号码" << endl;
	for ( int i=0; i<=tail(); i++ )
		cout << setw(4) << i+1 << ":" << setw(20) << phonelist[i].show_name()
		     << setw(20) << phonelist[i].show_phone() << endl;
}
//显示一条记录 
void Phonebook::show_record( const int n )const
{
	cout << setw(4) << "编号" << ":" << setw(20) << "姓名" 
	     << setw(20) << "电话号码" << endl;
	cout << setw(4) << n+1 << ":" << setw(20) << phonelist[n].show_name()
	     << setw(20) << phonelist[n].show_phone() << endl;
}


void Phonebook::show_menu()const
{
	cout << "**** 1.添加记录    ****" << endl
		 << "**** 2.删除记录    ****" << endl
		 << "**** 3.修改记录    ****" << endl
		 << "**** 4.查询记录    ****" << endl
		 << "**** 5.显示一条记录****" << endl
		 << "**** 6.显示全部记录****" << endl
		 << "**** 7.显示菜单    ****" << endl
		 << "**** 8.保存修改    ****" << endl
		 << "**** 9.重新载入    ****" << endl
		 << "**** 0.退出        ****" << endl;
}


void Phonebook::clear()
{
	phonelist.clear();
	end = -1;
}

/*===============================================================*/

int main()
{
	Phonebook pb;
	int cmd, m;
	string n, p;
	cout << "=======欢迎使用电话簿程序=======" << endl;

	/* Load data from record file */
	pb.load();
		
	/* show menu & wait for command */
	pb.show_menu();
	while (1)
	{
		cout << "================================================" << endl; //分隔符 
		cout << "cmd>";
		cin.clear();
		//输入错误处理 
		while ( !(cin >> cmd) )
		{
			cout << "msg:输入错误,请重新输入" << endl;
			cin.clear(); 
			cin.sync();
			cout << "cmd>";		
		}
		switch (cmd)
		{
			case 1:
				cout << "请输入要添加的姓名(0取消):" << endl;
				cin.get();
				getline( cin, n );
				if ( n != "0" )
				{
					cout << "请输入要添加的号码:" << endl;
					getline( cin, p );
				}
				else
					break;
				pb.add_record( n, p );
				break;
			case 2:
				cout << "请输入要删除记录的编号(0取消):" << endl;
				cin >> m;
				if ( m == 0 )
					break;
				else
					pb.del_record( m );
				break;
			case 3:
				cout << "请输入要修改记录的编号(0取消):" << endl;
				cin >> m;
				if ( m==0 )
					break;
				cout << "请输入新的姓名(0不变):" << endl;
				cin.get();
				getline( cin, n );				
				cout << "请输入新的号码(0不变):" << endl;
				getline( cin, p );
				pb.mod_record( m-1, n, p );
				break;
			case 4:
				cout << "1.按姓名查询" << endl
					 << "2.按号码查询" << endl
					 << "0.取消" << endl;
				cin >> cmd;
				switch (cmd)
				{
					case 0: break;
					case 1:
						cout << "请输入要查找的姓名:" << endl;
						cin.get();						
						getline( cin, n );
						m = pb.search_name(n);
						if ( m == -1 )
							cout << "msg:姓名" << n << "不存在" << endl;
						else
							pb.show_record( m );
						break;
					case 2:
						cout << "请输入要查找的号码:" << endl;
						cin.get();			
						getline( cin, p );
						m = pb.search_phone(p);
						if ( m == -1 )
							cout << "msg:号码" << p << "不存在" << endl;
						else
							pb.show_record( m );
						break;
					default:
						cout << "msg:输入错误,请重新输入" << endl;
						cin.clear(); 
						cin.sync();
						break;
				}
				break;
			case 5:
				cout << "请输入要显示记录的编号:" << endl;
				cin >> m;
				if ( m-1 > pb.tail() || m-1<0 )
					cout << "msg:记录不存在" << endl;
				else
					pb.show_record( m-1 );
				break;
			case 6:
				pb.show_book();
				break;
			case 7:
				pb.show_menu();
				break;
			case 8:
				pb.update();
				break;
			case 9:
				pb.load();
				break;
			case 0:
				cout << "==============谢谢使用==============" << endl;
				system( "pause" );
				return 0;
			default:
				cout << "msg:输入错误,请重新输入" << endl;
                cin.clear(); 
				cin.sync();
				break;
		}
	}
}
