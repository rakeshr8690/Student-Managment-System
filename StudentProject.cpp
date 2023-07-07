//Classes and Objects in C++ | Practical
#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
using namespace std; 

void heading();
void addRecord();		//Fx to write data to file from memory
void showAll();			//Fx to read data from file to memory
void searchByRollNo();	//Fx to display data on query from file to memory
void deleteRecord();	//Fx to delete data from file
void viewDeleted();		//Fx to display deleted data 
void restoreRecord();	//Fx to restore the data from file to file
void modifyRecord();	//Fx to modify the data in file

class Student{
	private:
		int rollno;
		char name[20];		
		char gender;
		int age;
		int std;
		float marks; 
	public:
		char *getName()
		{
			return name;
		}
		int getRollNo()
		{
			return rollno;
		}
		Student()		//Default Constructor	Manager Functions
		{
			rollno=0;
			strcpy(name,"NONAME");
			gender='-';
			age=0;
			marks=0;
			std=1;
			cout<<"Default Constructor Invoked.....\n";
		}	
		Student(int rn, char nm[20], char g, int a, int s)
		{
			rollno=rn;
			strcpy(name,nm);
			gender=g;
			age=a;
			std=s;
			cout<<"Parameterized Constructor Invoked.....\n";			
		}
		
		void modifyData()	//Member Functions	Mutator Functions
		{
			cout<<"Roll No.: "<<rollno<<endl;
			cout<<"Enter Student Details\n";
			cout<<"Name    : ";
			cin>>name;
			cout<<"Gender  : ";
			cin>>gender;
			cout<<"Age     : ";
			cin>>age;
			cout<<"Standard: ";
			cin>>std;
		}

		
		void getData()	//Member Functions	Mutator Functions
		{
			cout<<"Enter Student Details\n";
			cout<<"Roll No.: ";
			cin>>rollno;
			cout<<"Name    : ";
			cin>>name;
			cout<<"Gender  : ";
			cin>>gender;
			cout<<"Age     : ";
			cin>>age;
			cout<<"Standard: ";
			cin>>std;
		}
		void showData()	//Member Functions	Accessor Functions
		{
			cout<<"Student Details\n";
			cout<<"Roll No.: "<<rollno<<endl;
			cout<<"Name    : "<<name<<endl;
			cout<<"Gender  : "<<gender<<endl;
			cout<<"Age     : "<<age<<endl;
			cout<<"Standard: "<<std<<endl;
		}
		void listData()
		{
			cout.setf(ios::left);
			cout<<setw(10)<<rollno;
			cout<<setw(20)<<name;
			cout<<setw(10)<<gender;
			cout<<setw(5)<<age;
			cout<<setw(5)<<std;
			cout<<endl;
		}	
}s;

void menu()
{
	cout<<"STUDENT RECORDS\n";
	cout<<"================\n";
	cout<<"0. Exit\n";
	cout<<"1. Register New Student\n";
	cout<<"2. Show All Students\n";
	cout<<"3. Search by Roll No\n";
	cout<<"4. Delete Record\n";
	cout<<"5. View Deleted Records\n";
	cout<<"6. Restore Deleted Record\n";
	cout<<"7. Modify Record\n";
	cout<<"Enter your choice: ";
}


void addRecord()
{
	ofstream fout;
	fout.open("stuData.json",ios::out|ios::app|ios::binary);
	s.getData();
	fout.write((char*)&s,sizeof(Student));
	fout.close();
	cout<<"\nData Saved to file....\n";
}

void showAll()
{
	ifstream fin;
	fin.open("stuData.json",ios::in|ios::binary);
	heading();
	while(fin.read((char*)&s,sizeof(s)))
	{
		//s.showData();
		s.listData();
	}
	fin.close();
}

void viewDeleted()
{
	ifstream fin;
	fin.open("trashes.json",ios::in|ios::binary);
	cout<<".....TRASH FILE DATA.....\n\n";
	heading();
	while(fin.read((char*)&s,sizeof(s)))
	{
		//s.showData();
		s.listData();
	}
	fin.close();
}

void deleteRecord()
{
	ifstream fin;
	fin.open("stuData.json",ios::in|ios::binary);
	ofstream fout1("temp.json");
	ofstream fout2("trashes.json",ios::app);
	int rn,flag=0;
	cout<<"Enter Roll No. to be deleted: ";
	cin>>rn;
	
	while(fin.read((char*)&s,sizeof(s)))
	{
		if(rn==s.getRollNo())
		{
			cout<<"Following records has been moved to trash.\n";
			s.showData();
			flag++;
			fout2.write((char*)&s,sizeof(s));
		}
		else
		{
			fout1.write((char*)&s,sizeof(s));
		}
	}
	fin.close();
	fout1.close();
	fout2.close();
	if (flag==0)
		cout<<"No such roll number in file...\n";
	remove("stuData.json");
	rename("temp.json","stuData.json");
}

void restoreRecord()
{
	ifstream fin;
	fin.open("trashes.json",ios::in|ios::binary);
	ofstream fout1("temp.json");
	ofstream fout2("stuData.json",ios::app);
	int rn,flag=0;
	cout<<"Enter Roll No. to be restored: ";
	cin>>rn;
	
	while(fin.read((char*)&s,sizeof(s)))
	{
		if(rn==s.getRollNo())
		{
			cout<<"Following record have been restored.\n";
			s.showData();
			flag++;
			fout2.write((char*)&s,sizeof(s));
		}
		else
		{
			fout1.write((char*)&s,sizeof(s));
		}
	}
	fin.close();
	fout1.close();
	fout2.close();
	if (flag==0)
		cout<<"No such roll number in file...\n";
	remove("trashes.json");
	rename("temp.json","trashes.json");
}

void modifyRecord()
{
	fstream fio;
	fio.open("stuData.json",ios::in|ios::out|ios::binary);
	int rn,flag=0, pos;
	cout<<"Enter Roll No. to be modified: ";
	cin>>rn;
	
	while(fio.read((char*)&s,sizeof(s)))
	{
		if(rn==s.getRollNo())
		{
			pos=fio.tellg();	//return the current position of cursor
			cout<<"Following record found to be modified....\n";
			s.showData();
			
			cout<<"\nEnter new record details\n";
			fio.seekg(pos-sizeof(s));//shift the cursor to its parameterized position
			s.getData();	//new data to memory
			fio.write((char*)&s,sizeof(s));
			flag++;
		}
	}
	fio.close();
	if (flag==0)
		cout<<"No such roll number in file...\n";	
}

void searchByRollNo()
{
	ifstream fin;
	fin.open("stuData.json",ios::in|ios::binary);
	int rn,flag=0;
	cout<<"Enter Roll No. to be search: ";
	cin>>rn;
	
	while(fin.read((char*)&s,sizeof(s)))
	{
		if(rn==s.getRollNo())
		{
			s.showData();
			flag++;
		}
	}
	fin.close();
	if (flag==0)
		cout<<"No such roll number in file...\n";
}

void heading()
{
	cout.setf(ios::left);
	cout<<setw(10)<<"Roll No.";
	cout<<setw(20)<<"Name";
	cout<<setw(10)<<"Gender";
	cout<<setw(5)<<"Age";
	cout<<setw(5)<<"Std";
	cout<<endl;
}

int main()
{
	int n=0, ch, rn, i, flag=0, pos;
	Student s[10];
	do
	{
		system("cls");
		menu();
		cin>>ch;
		switch(ch)
		{
			case 1: addRecord();break;
			case 2: showAll(); break;
			case 3: searchByRollNo(); break;		
			case 4: deleteRecord(); break;
			case 5: viewDeleted(); break;
			case 6: viewDeleted(); 
			        restoreRecord(); break;
			case 7: modifyRecord();
		}
		system("pause");
	}while(ch);
	return 0;
}
