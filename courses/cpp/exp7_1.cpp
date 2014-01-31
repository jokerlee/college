/* 
1��	�绰��
    	��дC++����������¹��ܣ�
��1��	ʵ�ּ򵥵绰�����ܣ��������������绰���룻
��2��	�û�����������������Ҳ���������
��3��	�û�����ͨ�����룬��������͵绰���룻
��4��	�û�����ɾ�������͵绰���룻
��5��	�绰�����Ա�����ָ���ļ��У�
��6��	�绰�ɱ���ָ���ļ��ж��뵽�ڴ档
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
		string name;//���� 
		string phone;//���� 
	public:
		Record( string n="", string p="" );//���캯�� 
		void set_name( string n );//�������� 
		void set_phone( string p );//���ú��� 
		string show_name()const;//�������� 
		string show_phone()const;//���غ��� 
};


class Phonebook
{
	private:
		vector<Record> phonelist;
		int end;//���� 
	public:
		Phonebook();
		int tail()const;//���س��� 
		bool load();//���ļ�������Ϣ 
		bool update()const;//���仯���µ��ļ� 
		void add_record( const string n, const string p );//��Ӽ�¼ 
		void del_record( int n );//ɾ����¼ 
		void mod_record( const int m, const string n, const string p );//�޸ļ�¼ 
		int search_name( const string n );//��������ѯ 
		int search_phone( const string p );	//�������ѯ 
		void show_menu()const;//��ʾ�ɵ� 
		void show_book()const;//��ʾ�����绰�� 
		void show_record( int n )const;//��ʾһ����¼ 
		void clear();//��ռ�¼ 
};

/*=============Class Member Function Definition=============*/


/* Class Record */
Record::Record( string n, string p )
{
	name = n;
	phone = p;
}
//�޸ļ�¼���� 
void Record::set_name( string n )
{
	name = n;
}
//�޸ļ�¼���� 
void Record::set_phone( string p )
{
	phone = p;
}
//���ؼ�¼���� 
string Record::show_name()const
{
	return name;
}
//���ؼ�¼���� 
string Record::show_phone()const
{
	return phone;
}

/* Class Phonebook */
//���캯�� 
Phonebook::Phonebook()
{
	end = -1;
}
//���ص绰������ 
int Phonebook::tail()const
{
	return end;
}
//���ļ������¼ 
bool Phonebook::load()
{
	cout << "msg:����绰����..." << endl;
	ifstream fin( "records.txt" );
	if ( !fin )
	{
		cout << "msg:�绰���ļ���ʧ��" << endl;
		return 0;
	}
	string n, p;
	clear();
	//������ȡ����Ӽ�¼ 
	while ( getline( fin, n ) && getline( fin, p ) )
	{
		add_record( n, p );
	}
	fin.close();
	cout << "msg:�������,������" << tail()+1 << "����¼" << endl;
	return 1;
}
//���ļ������¼ 
bool Phonebook::update()const
{
	cout << "msg:����绰����..." << endl;
	ofstream fout( "records.txt", ios_base::out | ios_base::trunc );
	if ( !fout )
	{
		cout << "msg:�绰���ļ���ʧ��" << endl;
		return 0;
	}
	int i;
	for ( i=0; i<=tail(); i++ )
	{
		fout << phonelist[i].show_name() << endl << phonelist[i].show_phone() << endl;
	}
	fout.close();
	cout << "msg:������� " << i << endl;
	return 1;
}
//��绰����������Ӽ�¼ 
void Phonebook::add_record( const string n, const string p )
{
	Record tmp( n, p );
	phonelist.push_back( tmp );
	end ++;
}
//ɾ���绰���еļ�¼ 
void Phonebook::del_record( int n )
{
	if ( n-1<0 || n-1 >tail() )
	{
		cout << "��¼#" << n << "������" << endl;
		return;
	}
	vector <Record>::iterator I=phonelist.begin();
	while ( n-- ) I++;
	phonelist.erase( I );
	end --;
	
}
//���ĵ绰���еļ�¼ 
void Phonebook::mod_record( int m, const string n, const string p )
{
	if ( n != "0" )
		phonelist[m].set_name( n );
	if ( p != "0" )
		phonelist[m].set_phone( p );
}
//������������¼ 
int Phonebook::search_name( const string n )
{
	for ( int i=0; i<=tail(); i++ )
		if ( phonelist[i].show_name() == n )
			return i;
	return -1;
}
//������������¼ 
int Phonebook::search_phone( const string p )
{
	for ( int i=0; i<=tail(); i++ )
		if ( phonelist[i].show_phone() == p )
			return i;
	return -1;
}
//��ӡ�����绰�� 
void Phonebook::show_book()const
{
    if ( end == -1 )
    {
        cout << "�޼�¼" << endl;
		return;
	}
	
    cout << setw(4) << "���" << ":" << setw(20) << "����" 
	     << setw(20) << "�绰����" << endl;
	for ( int i=0; i<=tail(); i++ )
		cout << setw(4) << i+1 << ":" << setw(20) << phonelist[i].show_name()
		     << setw(20) << phonelist[i].show_phone() << endl;
}
//��ʾһ����¼ 
void Phonebook::show_record( const int n )const
{
	cout << setw(4) << "���" << ":" << setw(20) << "����" 
	     << setw(20) << "�绰����" << endl;
	cout << setw(4) << n+1 << ":" << setw(20) << phonelist[n].show_name()
	     << setw(20) << phonelist[n].show_phone() << endl;
}


void Phonebook::show_menu()const
{
	cout << "**** 1.��Ӽ�¼    ****" << endl
		 << "**** 2.ɾ����¼    ****" << endl
		 << "**** 3.�޸ļ�¼    ****" << endl
		 << "**** 4.��ѯ��¼    ****" << endl
		 << "**** 5.��ʾһ����¼****" << endl
		 << "**** 6.��ʾȫ����¼****" << endl
		 << "**** 7.��ʾ�˵�    ****" << endl
		 << "**** 8.�����޸�    ****" << endl
		 << "**** 9.��������    ****" << endl
		 << "**** 0.�˳�        ****" << endl;
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
	cout << "=======��ӭʹ�õ绰������=======" << endl;

	/* Load data from record file */
	pb.load();
		
	/* show menu & wait for command */
	pb.show_menu();
	while (1)
	{
		cout << "================================================" << endl; //�ָ��� 
		cout << "cmd>";
		cin.clear();
		//��������� 
		while ( !(cin >> cmd) )
		{
			cout << "msg:�������,����������" << endl;
			cin.clear(); 
			cin.sync();
			cout << "cmd>";		
		}
		switch (cmd)
		{
			case 1:
				cout << "������Ҫ��ӵ�����(0ȡ��):" << endl;
				cin.get();
				getline( cin, n );
				if ( n != "0" )
				{
					cout << "������Ҫ��ӵĺ���:" << endl;
					getline( cin, p );
				}
				else
					break;
				pb.add_record( n, p );
				break;
			case 2:
				cout << "������Ҫɾ����¼�ı��(0ȡ��):" << endl;
				cin >> m;
				if ( m == 0 )
					break;
				else
					pb.del_record( m );
				break;
			case 3:
				cout << "������Ҫ�޸ļ�¼�ı��(0ȡ��):" << endl;
				cin >> m;
				if ( m==0 )
					break;
				cout << "�������µ�����(0����):" << endl;
				cin.get();
				getline( cin, n );				
				cout << "�������µĺ���(0����):" << endl;
				getline( cin, p );
				pb.mod_record( m-1, n, p );
				break;
			case 4:
				cout << "1.��������ѯ" << endl
					 << "2.�������ѯ" << endl
					 << "0.ȡ��" << endl;
				cin >> cmd;
				switch (cmd)
				{
					case 0: break;
					case 1:
						cout << "������Ҫ���ҵ�����:" << endl;
						cin.get();						
						getline( cin, n );
						m = pb.search_name(n);
						if ( m == -1 )
							cout << "msg:����" << n << "������" << endl;
						else
							pb.show_record( m );
						break;
					case 2:
						cout << "������Ҫ���ҵĺ���:" << endl;
						cin.get();			
						getline( cin, p );
						m = pb.search_phone(p);
						if ( m == -1 )
							cout << "msg:����" << p << "������" << endl;
						else
							pb.show_record( m );
						break;
					default:
						cout << "msg:�������,����������" << endl;
						cin.clear(); 
						cin.sync();
						break;
				}
				break;
			case 5:
				cout << "������Ҫ��ʾ��¼�ı��:" << endl;
				cin >> m;
				if ( m-1 > pb.tail() || m-1<0 )
					cout << "msg:��¼������" << endl;
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
				cout << "==============ллʹ��==============" << endl;
				system( "pause" );
				return 0;
			default:
				cout << "msg:�������,����������" << endl;
                cin.clear(); 
				cin.sync();
				break;
		}
	}
}
