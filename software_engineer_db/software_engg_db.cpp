// OOPs Assignment

// Software Engineer Database

#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
using namespace std;

class software_engg
{
      int emp_ID;
      char name[30];
      int age; 
      char city[30];
      char firm[30];
      int work_exp;
      char desig[30];
      float salary;
      char qual[30];
    public:
      void accept();
      void show();
      void update();
      int getEmp_ID()
      {
          return emp_ID;
      }
      int getAge()
      {
          return age;
      }
      int getWork_exp()
      {
          return work_exp;
      }
      char *getFirm()
      {
          return firm;
      }
}soft;

void software_engg::accept()
{
        cout<<"\nEmp. ID: ";
        cin>>emp_ID;
        cout<<"\nName: ";
        fflush(stdin);
		gets(name);
        cout<<"\nAge: ";
		cin>>age;
		cout<<"\nCity: ";
		fflush(stdin);
		gets(city);
		cout<<"\nFirm: ";
		fflush(stdin);
		gets(firm);
		cout<<"\nWork Experience: ";
		cin>>work_exp;
		cout<<"\nDesignation: ";
		fflush(stdin);
		gets(desig);
		cout<<"\nSalary(per month): ";
		cin>>salary;
		cout<<"\nEducational Qualifications: ";
		fflush(stdin);
		gets(qual);
}

void software_engg::show()
{
        cout<<endl<<"Emp ID: ";
        cout<<emp_ID<<endl;
        cout<<endl<<"Name: ";
        puts(name);
        cout<<endl<<"Age: ";
		cout<<age<<endl;
		cout<<endl<<"City: ";
		puts(city);
		cout<<endl<<"Firm: ";
		puts(firm);
		cout<<endl<<"Work Experience: ";
		cout<<work_exp<<endl;
		cout<<endl<<"Designation: ";
		puts(desig);
		cout<<endl<<"Salary(per month): Rs.";
		cout<<salary<<endl;
		cout<<endl<<"Educational Qualifications: ";
		cout<<qual<<endl;
}

void software_engg::update()
{
	char company[30], post[30];
    float income;
    cout<<"\nEnter the new Details...";
    cout<<"\nNew Firm/Company(Enter '1' to retain old one): ";
    fflush(stdin);   gets(company);
    cout<<"\nNew Designation(Enter '1' to retain old one): ";
    fflush(stdin);   gets(post);
	cout<<"\nNew Salary(Enter 1 to retain old one): ";
    cin>>income;
	if(strcmp(company,"1")!=0)
	   strcpy(firm,company);
	if(strcmp(post,"1")!=0)
	   strcpy(desig,post);
	if(income!=1)
	   salary=income;
}

void Search()
{
    int age1,work_exp1;
    char firm1[30],found='n';
    ifstream file("engineer.dat",ios::in|ios::binary);    
    cout<<"\nEnter the values for the Search...";
    cout<<"\n1.Age(for <x, specify x): "; cin>>age1;
    cout<<"\n2.Work Experience(for >x, specify x): "; cin>>work_exp1;
    cout<<"\n3.Firm(Company's name): "; fflush(stdin); gets(firm1);
    cout<<"\nResults of the Search: \n";
    file.seekg(0,ios::beg);
    while(1)               
    {
            file.read((char*)&soft,sizeof(soft));
            if(!file)
               break;
            if((soft.getAge()<age1)&&(soft.getWork_exp()>work_exp1)&&(strcmp(soft.getFirm(),firm1)==0))
            {
                  soft.show();
                  found='y';
            }
    }
    if(found=='n')
       cout<<"\nNO RECORD FOUND !!!";
    file.close();
}

void Write_Records()
{
      ofstream f1("Engineer.dat",ios::out|ios::binary); 
      if(!f1)
      {
             cerr<<"\nFile Open Error !!!";
             return;
      }
      for(int i=0;i<5;i++)
      {
        cout<<"\nENGINEER #"<<i+1<<": \n";
        soft.accept(); 
        f1.write((char*)&soft,sizeof(soft)); 
      } 
      f1.close();
}

void Read_Records()
{ 
      int i=1;
      ifstream f1("Engineer.dat",ios::in|ios::binary);
      if(!f1)
      {
             cerr<<"\nFile Open Error !!!";
             return;
      }
      while(f1.read((char*)&soft,sizeof(soft))) 
      {  
              cout<<"\n-------------------------------------------------------------------------------";
              cout<<"\n\t\t\t\tENGINEER #"<<i;
              cout<<"\n-------------------------------------------------------------------------------\n";
              i++;
              soft.show(); 
      } 
      f1.close();
}

void Insert_record()
{
     ifstream fi("Engineer.dat",ios::in|ios::binary);
     ofstream fo("temp.dat",ios::out|ios::binary);
     char last='y';
     software_engg snew;
	 cout<<"\nEnter the details of the new Record: \n";
	 snew.accept();
	 while(fi.read((char*)&soft,sizeof(soft)))
	 {	             
	             if(snew.getEmp_ID()<=soft.getEmp_ID())
	             {
	                         fo.write((char*)&snew,sizeof(snew));
	                         last='n';
	                         break;
	             }
	             else
                 	 fo.write((char*)&soft,sizeof(soft));
     }
     if(last=='y')
         fo.write((char*)&snew,sizeof(snew));
     else if(!fi.eof())
     {
            while(1)
            {     
                   if(!fi)
                      break;
                   fi.read((char*)&soft,sizeof(soft));              
                   fo.write((char*)&soft,sizeof(soft));
                   if(!fi)
                      break;
            }
     }
     fi.close();
     fo.close();     
     remove("Engineer.dat");
     rename("temp.dat","Engineer.dat");
}     

void Delete_record()
{
     ifstream fi("Engineer.dat",ios::in|ios::binary); 
     ofstream fo("temp.dat",ios::out|ios::binary); 
     int eID=0;
     char found='f'; 
     cout<<"\nEnter the ID of the employee whose record is to be Deleted: ";
	 cin>>eID;
     while(fi.read((char*)&soft,sizeof(soft))) 
     {              
              if(eID==soft.getEmp_ID())
              { 
                   soft.show();
                   found='t'; 
                   continue; 
               } 
              else 
                   fo.write((char*)&soft,sizeof(soft));
              
      } 
      if(found=='f') 
        cout<<"\n\n\t\tRECORD NOT FOUND !!!\n\n";
      else
        cout<<"\n\n\t\tRecord Deleted Successfully !!!\n\n"; 
      fi.close(); 
      fo.close();       
      remove("Engineer.dat"); 
      rename("temp.dat","Engineer.dat");
}

void Update_record()
{
     fstream f1("Engineer.dat",ios::in|ios::out|ios::binary); 
     int eID; 
     long pos; 
     char found='f'; 
     cout<<"\nEnter the ID of the employee whose record is to be Updated: ";
	 cin>>eID;
     while(f1.read((char*)&soft,sizeof(soft))) 
     { 
          pos=f1.tellg();          
                      if(eID==soft.getEmp_ID())
                      { 
                           f1.seekg(pos);
                           soft.update();                            
                           f1.write((char*)&soft,sizeof(soft));
                           cout<<"\n\n\t\tRECORD UPDATED !!!\n\n"; 
                           found='t'; 
                           break; 
                      } 
     } 
     if(found=='f') 
        cout<<"\n\n\t\tRECORD NOT FOUND !!!\n\n";
     f1.close();
}

void main_menu()
{
    int choice;
    cout<<"\n\n\t\t\t    <<<<<:: MENU ::>>>>>\n";
    cout<<"\n\t\t\t    1. Write Records";
    cout<<"\n\t\t\t    2. Insert a Record";
    cout<<"\n\t\t\t    3. Delete a Record";
    cout<<"\n\t\t\t    4. Update a Record";
    cout<<"\n\t\t\t    5. Display all engineer";
    cout<<"\n\t\t\t    6. Perform Searching";
    cout<<"\n\t\t\t    7. Exit";
    cout<<"\n\t\t\t    Choice: ";
    cin>>choice;
    switch(choice)
    {                   
           case 1: Write_Records();
                   break;
                   
           case 2: Insert_record();
                   break;
                   
           case 3: Delete_record();
                   break;
                   
           case 4: Update_record();
                   break;
                   
           case 5: Read_Records();
                   break;
                   
           case 6: Search();
                   break;
                   
           case 7: break;
           
           default: cout<<"\nNo such option...";
                    main_menu();  break;
    } 
    if(choice!=7)
       main_menu();
}

int main()
{        
    cout<<"*******************************************************************************";
    cout<<"\n#\t     \tINTERNATIONAL UNION OF SOFTWARE ENGINEERS\t\t      #\n";
    cout<<"*******************************************************************************";
    main_menu();
    getch();
    return 0;
}
