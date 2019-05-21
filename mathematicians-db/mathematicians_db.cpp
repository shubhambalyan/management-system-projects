#include<fstream>
#include<iostream>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<process.h>
#include<time.h>
using namespace std;

class math
{
	int ssn;
	char name[50];
	char company[25];
	int age;
	char qual[50];
public:
	math()
	{
		ssn=0;
		strcpy(name,"NULL");
		strcpy(company,"NULL");
		age=0;
		strcpy(qual,"NULL");
	}
	void getdata()
	{
		cout<<"Enter the ssn no.: ";
		cin>>ssn;
		cout<<"Enter the name of the mathematician\n: ";
		fflush(stdin);
		gets(name);
		cout<<"Enter the name of the company:\n ";
		fflush(stdin);
		gets(company);
		cout<<"Enter the age: \n";
		cin>>age;
		cout<<"Enter the qualifications of the mathematician:\n ";
		fflush(stdin);
		gets(qual);
		cout<<endl;
	}
	void display()
	{
		cout<<"SSN no.: "<<ssn;
		cout<<"\nName: ";
		puts(name);
		cout<<"\nCompany: ";
        puts(company);
		cout<<"Age "<<age<<endl;
		cout<<"Qualifications: ";
		puts(qual);
		cout<<endl;
	}
	int return_age()
	{
		return age;
	}
	int return_qual(char p[50])
	{
		if(strcmpi(p,qual)==0)
			return 1;
		else
			return 0;
	}
	int return_ssn()
	{
		return ssn;
	}
};

void insert()
{
    math s;
	ofstream of1("maths.dat",ios::binary|ios::app);
	cout<<"Enter the record to be inserted:\n";
	s.getdata();
    of1.write((char*)&s,sizeof(s));
	of1.close();
}

void delet()
{
	math s;
	int sno=0,flag=0;
	ifstream if1("maths.dat",ios::binary);
	ofstream of1("temp.dat",ios::binary|ios::out);
	cout<<"\nEnter the ssn no. to be deleted: ";
	cin>>sno;
	while(if1.read((char*)&s,sizeof(s)))
	{
		if(sno==s.return_ssn())
		{
			flag=1;
			continue;
		}
		else
		{
			of1.write((char*)&s,sizeof(s));
		}
	}
	if(flag==1)
		cout<<"\nThe record is successfully deleted!!!\n";
	else
		cerr<<"Record not found!!\n";
	if1.close();
	of1.close();
	remove("maths.dat");
	rename("temp.dat","maths.dat");
}

void update()
{
    math s;
	int sno,flag=0;
	long pos;
	fstream f1("maths.dat",ios::binary|ios::in|ios::out);
	cout<<"Enter the ssn no. to be updated: ";
	cin>>sno;
	while(f1.read((char*)&s,sizeof(s)))
	{
		pos=f1.tellg();
		if(sno==s.return_ssn())
		{
			pos-=sizeof(s);
			flag=1;
			f1.seekp(pos);
			s.getdata();
			f1.write((char*)&s,sizeof(s));
			cout<<"The record has been updated successfully!!\n";
			break;
		}
	}
	if (flag==0)
		cerr<<"Record not found!!\n";
	f1.close();
}

void Display()
{
     math s;
	ifstream if1("maths.dat",ios::binary|ios::in);
	while(if1.read((char*)&s,sizeof(s)))
	{
		s.display();
		cout<<endl;
	}
	if1.close();
}

void Display1()
{
	math s;
	char ql[25];
	int flag=0;
	ifstream if1("maths.dat",ios::binary|ios::in);
	if(!if1)
		cerr<<"File open error!!\n";
	else
	{
		cout<<"Enter the qualifications: ";
		fflush(stdin);
		gets(ql);
		while(if1.read((char*)&s,sizeof(s)))
		{
			if(s.return_qual(ql)==1)
			{
				flag=1;
				s.display();
			}
			else
				continue;
		}
	}
	if1.close();
	if(flag==0)
		cerr<<"\nqualification not found!!.\n";
}

void Display2()
{
	math s;
	int flag=0;
	ifstream if1("maths.dat",ios::binary|ios::in);
	if(!if1)
		cerr<<"File open error!!!\n";
	else
	{
		while(if1.read((char*)&s,sizeof(s)))
		{
			if(s.return_age()>40)
			{
				flag=1;
				s.display();
			}
			else
				continue;
		}
	}
	if1.close();
	if(flag==0)
		cerr<<"There is no such record!!!\n";
}

int main()
{
	math s;
	int i,ch;
    char ans;
	ofstream of1("maths.dat",ios::binary|ios::out);
	cout<<"Enter the initial 5 records:\n";
	for(i=0;i<2;i++)
	{
		cout<<"Record "<<i+1<<":\n";
		s.getdata();
		of1.write((char*)&s,sizeof(s));
	}
	of1.close();
	do
	{
		system("cls");
		cout<<"1. Insert a record.\n";
		cout<<"2. Delete a record.\n";
		cout<<"3. Update a record.\n";
		cout<<"4. Display all records.\n";
		cout<<"5. Display the records for a given qualifications.\n";
		cout<<"6. Display the records if the age is greater than 40.\n";
	    cout<<"7. Exit.\n";
		cout<<"\nChoose: ";
		cin>>ch;
		switch(ch)
		{
		case 1: insert();
			break;
		case 2: delet();
			break;
		case 3: update();
			break;
		case 4: Display();
			break;
		case 5: Display1();
			break;
		case 6: Display2();
			break;
		case 7: exit(0);
			break;
		default: cout<<"\nInvalid Option!!!!\n";
		}
		cout<<"Do you wish to continue?(Y/N)";
		ans=getch();
	}while(ans=='y'||ans=='Y');
	system("pause");
}
