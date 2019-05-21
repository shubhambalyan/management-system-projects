// Owner Tenant Management

#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
using namespace std;

class apartment
{
      int apartmentNumber;
      char ownerName[30];
      int type; 
      char ophone[30];
      char tenantName[30];
      int totalTenants;
      char tphone[30];
      float rent;
      float area;
    public:
      void accept();
      void show();
      void update();
      float compressData(float);
      int getApartmentNumber()
      {
          return apartmentNumber;
      }
      int getType()
      {
          return type;
      }
      float getRent()
      {
          return rent;
      }
      float getArea()
      {
          return area;
      }
}flat;

//Read new records
void apartment::accept()
{
        cout<<"\nApartment Number: ";
        cin>>apartmentNumber;
        cout<<"Owner Name: ";
        fflush(stdin);
		gets(ownerName);
        cout<<"Type (1/2/3 BHK): ";
		cin>>type;
		cout<<"Owner Phone Number: ";
		fflush(stdin);
		gets(ophone);
		cout<<"Tenant Name ('NA' instead): ";
		fflush(stdin);
		gets(tenantName);
		cout<<"Total Number of Tenants ('0' instead): ";
		cin>>totalTenants;
		cout<<"Tenant Phone Number ('NA' instead): ";
		fflush(stdin);
		gets(tphone);
		cout<<"Rent per month (ex: 25000, '0' instead): ";
		cin>>rent;
		rent=compressData(rent);
		cout<<"Flat Area (in sq. ft.): ";
		cin>>area;
}

//Compress rent data
float apartment::compressData(float rent)
{
	float compressedRent = rent/1000;
	return compressedRent;
}

//Display records
void apartment::show()
{
	    //system("CLS");
        cout<<endl<<"Apartment Number: ";
        cout<<apartmentNumber<<endl;
        cout<<"Owner Name: ";
        puts(ownerName);
        cout<<"Flat Type (1/2/3 BHK): ";
		cout<<type<<endl;
		cout<<"Owner Phone Number: ";
		puts(ophone);
		cout<<"Tenant Name: ";
		puts(tenantName);
		cout<<"Total Number of Tenants: ";
		cout<<totalTenants<<endl;
		cout<<"Tenant Phone Number: ";
		puts(tphone);
		cout<<"Rent (per month): Rs.";
		cout<<rent<<"k"<<endl;
		cout<<"Flat Area (in sq. ft.): ";
		cout<<area<<endl<<endl;
		system("PAUSE");
		//system("CLS");
}

//Update records with new values
void apartment::update()
{
	char tenantNewName[30], tphoneNew[30];
    float newRent;
    int newNumberOfTenants;
    cout<<"\nEnter the new Details...";
    cout<<"\nNew Tenant Name (Enter '1' to retain old one): ";
    fflush(stdin);   gets(tenantNewName);
    cout<<"\nNew Tenant Phone Number (Enter '1' to retain old one): ";
    fflush(stdin);   gets(tphoneNew);
	cout<<"\nNew Flat Rent/month (Enter 1 to retain old one, ex: 25000): ";
    cin>>newRent;
    newRent=compressData(newRent);
    cout<<"\nNew Number of Tenants (Enter 1 to retain old one): ";
    cin>>newNumberOfTenants;
	if(strcmp(tenantNewName,"1")!=0)
	   strcpy(tenantName,tenantNewName);
	if(strcmp(tphoneNew,"1")!=0)
	   strcpy(tphone,tphoneNew);
	if(newRent!=1)
	   rent=newRent;
	if(newNumberOfTenants!=1)
	   totalTenants=newNumberOfTenants;
}

//Search for records based on multiple conditions
void Search_condition()
{
    int stype;
    float srent;
    char found='n';
    ifstream file("apartment.dat",ios::in|ios::binary);    
    cout<<"\nEnter the values for the Search...\n";
    cout<<"\n1.Type (1/2/3 BHK, specify 1/2/3): ";
	cin>>stype;
    cout<<"\n2.Rent per month(for <=x, specify x like 25000): ";
	cin>>srent;
	srent=srent/1000;
    file.seekg(0,ios::beg);
    while(1)               
    {
            file.read((char*)&flat,sizeof(flat));
            if(!file)
               break;
            if(( flat.getType() == stype ) && ( flat.getRent() <= srent ))
            {
                  flat.show();
                  found='y';
            }
    }
    if(found=='n')
       cout<<"\nNO RECORD FOUND !!!\n\n";
    file.close();
    system("PAUSE");
}

//Search for record based on primary key (apartment number)
void Search_apartment()
{
	int apNumber;
	char found='n';
    ifstream file("apartment.dat",ios::in|ios::binary);    
    cout<<"\nEnter the apartment number to search: ";
    cin>>apNumber;
    file.seekg(0,ios::beg);
    while(1)               
    {
            file.read((char*)&flat,sizeof(flat));
            if(!file)
               break;
            if(apNumber == flat.getApartmentNumber())
            {
                  flat.show();
                  found='y';
            }
    }
    if(found=='n')
       cout<<"\nNO RECORD FOUND !!!\n";
    file.close();
    system("PAUSE"); 
}

//Read records from file
void Read_Records()
{ 
      ifstream f1("apartment.dat",ios::in|ios::binary);
      if(!f1)
      {
             cerr<<"\nFile Open Error !!!";
             return;
      }
      while(f1.read((char*)&flat,sizeof(flat)))
      {  
              flat.show(); 
      } 
      f1.close();
}

//Write record to file according to flat number
void Insert_record()
{
     ifstream fi("apartment.dat",ios::in|ios::binary);
     ofstream fo("temp.dat",ios::out|ios::binary);
     char last='y', duplicate='n';
     apartment snew;
	 cout<<"\nEnter the details of the new Record: \n";
	 snew.accept();
	 while(fi.read((char*)&flat,sizeof(flat)))
	 {	         
         if(snew.getApartmentNumber()==flat.getApartmentNumber())
		 {
		 	cout<<"\nApartment details for #"<<snew.getApartmentNumber()<<" ALREADY EXISTS\n\n";
		 	duplicate='y';
			goto label;		        	
		 }   
         if(snew.getApartmentNumber()<=flat.getApartmentNumber())
         {
             fo.write((char*)&snew,sizeof(snew));
             last='n';
             break;
         }
         else
         	 fo.write((char*)&flat,sizeof(flat));
     }
     if(last=='y')
         fo.write((char*)&snew,sizeof(snew));
     else if(!fi.eof())
     {
        while(1)
        {     
           if(!fi)
              break;
           fi.read((char*)&flat,sizeof(flat));              
           fo.write((char*)&flat,sizeof(flat));
           if(!fi)
              break;
        }
     }
     fi.close();
     fo.close();
     remove("apartment.dat");
     rename("temp.dat","apartment.dat");
     cout<<"\nApartment Added Successfully !!!\n";
     label:
     if(duplicate=='y')
     {
     	remove("temp.dat");
	 }
	 system("PAUSE");  
}     

//Delete a record given the apartment number
void Delete_record()
{
     ifstream fi("apartment.dat",ios::in|ios::binary); 
     ofstream fo("temp.dat",ios::out|ios::binary); 
     int aID=0;
     char found='f'; 
     cout<<"\nEnter the apartment number to be deleted: ";
	 cin>>aID;
     while(fi.read((char*)&flat,sizeof(flat))) 
     {              
              if(aID==flat.getApartmentNumber())
              { 
                   cout<<"\nDetails of the apartment to be deleted\n";
                   flat.show();
                   found='t'; 
                   continue; 
              } 
              else 
                   fo.write((char*)&flat,sizeof(flat));
              
      } 
      if(found=='f') 
        cout<<"\n\n\t\tRECORD NOT FOUND !!!\n\n";
      else
        cout<<"\n\n\t\tRecord Deleted Successfully !!!\n\n"; 
      fi.close(); 
      fo.close();       
      remove("apartment.dat"); 
      rename("temp.dat","apartment.dat");
      system("PAUSE");  
}

//Update the record given the updated values
void Update_record()
{
     fstream f1("apartment.dat",ios::in|ios::out|ios::binary); 
     int aID; 
     long pos; 
     char found='f'; 
     cout<<"\nEnter the apartment number to be Updated: ";
	 cin>>aID;
	 if(!f1)
	 {
		cout<<"File not Found";
		exit(0);
	 } 
	 else
	 {
		f1.read((char*)&flat, sizeof(flat));
		while(!f1.eof())
		{
			if(aID==flat.getApartmentNumber())
			{
				f1.seekg(0,ios::cur);
				flat.update();
				f1.seekp(f1.tellg() - sizeof(flat));
				f1.write((char*)&flat, sizeof(flat));
				found='t';
				cout<<"\n\n\t\tRECORD UPDATED !!!\n\n";
			}
			f1.read((char*)&flat, sizeof(flat));
		}
	 }

     if(found=='f') 
        cout<<"\n\n\t\tRECORD NOT FOUND !!!\n\n";
     f1.close();
     system("PAUSE"); 
}

//Calculate rent of the flat including per sq. ft. maintenance
void Calculate_rent()
{
	int aptNumber;
	float maintenanceAmount, rentPlusMaintenance=0.0;
	char found='n';
    ifstream file("apartment.dat",ios::in|ios::binary);    
    cout<<"\nEnter the maintenance amount for this month (amount in Rs. per sq. ft.): ";
    cin>>maintenanceAmount;
    cout<<"\nEnter the apartment number for which the rent is to be calculated: ";
    cin>>aptNumber;
    file.seekg(0,ios::beg);
    while(1)               
    {
            file.read((char*)&flat,sizeof(flat));
            if(!file)
               break;
            if(aptNumber == flat.getApartmentNumber())
            {
            	  rentPlusMaintenance = flat.getArea()*maintenanceAmount + flat.getRent()*1000;
            	  cout<<"\n\nThe total monthly rent to be paid: Rs. "<<rentPlusMaintenance<<endl<<endl;
                  found='y';
            }
    }
    if(found=='n')
       cout<<"\nNO RECORD FOUND !!!\n\n";
    file.close();
    system("PAUSE");
}

//Supported operations menu
void main_menu()
{
    int choice;
    system("CLS");
    cout<<"*******************************************************************************";
    cout<<"\n\t     \tApartment (Owner & Tenant) Management System\t\t      \n";
    cout<<"*******************************************************************************";
    cout<<"\n\n\t\t\t    <<<<<:: MENU ::>>>>>\n";
    cout<<"\n\t\t\t    1. Add Apartment";
    cout<<"\n\t\t\t    2. Delete Apartment";
    cout<<"\n\t\t\t    3. Update Apartment";
    cout<<"\n\t\t\t    4. Display All Apartments";
    cout<<"\n\t\t\t    5. Search Apartment (Based on apartment #)";
    cout<<"\n\t\t\t    6. Search Apartment (Based on conditions)";
    cout<<"\n\t\t\t    7. Calculate monthly rent (incl. maintenance)";
    cout<<"\n\t\t\t    8. Exit";
    cout<<"\n\t\t\t    Enter your choice: ";
    cin>>choice;
    switch(choice)
    {                   
           case 1: Insert_record();
                   break;
                   
           case 2: Delete_record();
                   break;
                   
           case 3: Update_record();
                   break;
                   
           case 4: Read_Records();
                   break;
                   
           case 5: Search_apartment();
                   break;
                   
           case 6: Search_condition();
                   break;
                   
           case 7: Calculate_rent();
		           break;
           
           case 8: break;
           
           default: cout<<"\nNo such option...\n\n";
                    system("PAUSE");
                    main_menu();
					break;
    } 
    if(choice!=8)
       main_menu();
}

int main()
{        
    main_menu();
    getch();
    return 0;
}
