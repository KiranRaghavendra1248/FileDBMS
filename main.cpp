#include <iostream>
#include<cstdio>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class student
{
public:
    string name,id,address,mail_id,branch;
    student() { }
    void getData(); // get student data from user
    void displayData();
    void putData(int flag);
};
void student :: getData()
{
    cout<<"Enter student name: ";
    getline(cin,name);
    cout<<"Enter student ID: ";
    getline(cin,id);
    cout<<"Enter address: ";
    getline(cin,address);
    cout<<"Enter mail id: ";
    getline(cin,mail_id);
    cout<<"Enter branch: ";
    getline(cin,branch);
}
void student :: displayData()
{
    cout<<name<<"\t"<<id<<"\t"<<address<<"\t"<<mail_id<<"\t"<<branch<<"\t"<<endl;
}
// flag=0 while appending to database
// flag=1 when writing to database from scratch
void student :: putData(int flag)
{
    fstream fp;
    if(flag==0)
        fp.open("database.txt",ios::app);
    if(flag==1)
        fp.open("database.txt",ios::out);
    fp<<name<<endl;
    fp<<id<<endl;
    fp<<address<<endl;
    fp<<mail_id<<endl;
    fp<<branch<<endl;
    fp.close();
}
void insert_method()
{
    int n,i;
    cout<<" Enter number of students: ";
    cin>>n;
    cin.ignore();
    student s[n];
    for(i=0;i<n;i++)
    {
        s[i].getData();
    }
    cout<<"Writing to file..."<<endl;
    for( i=0;i<n;i++)
    {
        s[i].putData(0);
    }
}
void update_method()
{
    fstream f;
    f.open("database.txt",ios::in);
    int c=0,n,i;
    while(f)
    {
        char k=f.get();
        if (k=='\n')
            c++;
    }
    f.close();
    n=c/5;
    cout<<"Number of student details in file presently: "<<n<<endl;
    if(n==0)
    {
        cout<<"File Empty!!"<<endl;
        return;
    }
    student s[n];
    f.open("database.txt",ios::in);
    cout<<"Loading from file.."<<endl;
    for(i=0;i<n;i++)
    {
        getline(f,s[i].name);
        getline(f,s[i].id);
        getline(f,s[i].address);
        getline(f,s[i].mail_id);
        getline(f,s[i].branch);
    }
    f.close();
    string id_;
    cout<<"Enter ID of student whose data is to be modified: ";
    getline(cin,id_);
    for(i=0;i<n;i++)
    {
        if(id_==s[i].id)
            break;
    }
    if (i<n)
    {
       cout<<" Enter new details:"<<endl;
        cout<<"Enter student name: ";
        getline(cin,s[i].name);
        cout<<"Enter student ID: ";
        cin>>s[i].id;
        cin.ignore();
        cout<<"Enter address: ";
        getline(cin,s[i].address);
        cout<<"Enter mail id: ";
        cin>>s[i].mail_id;
        cin.ignore();
        cout<<"Enter branch: ";
        getline(cin,s[i].branch);
        s[0].putData(1);
        for(i=1;i<n;i++)
        {
            s[i].putData(0);
        }
    }
    else
        cout<<" The searched record doesn't exist"<<endl;

}
void delete_method()
{
    fstream f;
    f.open("database.txt",ios::in);
    int c=0,n,i,j;
    while(f)
    {
        char k=f.get();
        if (k=='\n')
            c++;
    }
    f.close();
    n=c/5;
    cout<<"Number of student details in file presently: "<<n<<endl;
    if(n==0)
    {
        cout<<"File Empty!!"<<endl;
        return;
    }
    student s[n];
    f.open("database.txt",ios::in);
    cout<<"Loading from file.."<<endl;
    for(i=0;i<n;i++)
    {
        getline(f,s[i].name);
        getline(f,s[i].id);
        getline(f,s[i].address);
        getline(f,s[i].mail_id);
        getline(f,s[i].branch);
    }
    string id_;
    f.close();
    cout<<"Enter ID of student to delete: ";
    getline(cin,id_);
    for(i=0;i<n;i++)
    {
        if(id_==s[i].id)
            break;
    }
    if (i<n)
    {
        cout<<" The searched record has been found and deleted"<<endl;
        if(n==1)
        {
            cout<<"File is empty now"<<endl;
            cout<<"Exiting the program.."<<endl;
            int t=remove("database.txt");
            return;
        }
        if(i==0) // First record must be deleted. So put second record in write mode and all other records in append mode. Hence 1st record is left out
        {
            s[1].putData(1);
            for(j=2;j<n;j++)
            {
                s[j].putData(0);
            }
        }
        else // Put 1st record in write mode and all other records in append mode if it is not the one to be deleted
        {
            s[0].putData(1);
            for(j=1;j<n;j++)
            {
                if (j!=i)
                    s[j].putData(0);
            }
        }

    }
    else
        cout<<" The record doesn't exist"<<endl;
}
void search_method()
{
    fstream f;
    f.open("database.txt",ios::in);
    int c=0,n,i;
    while(f)
    {
        char k=f.get();
        if (k=='\n')
            c++;
    }
    f.close();
    n=c/5;
    cout<<"Number of student details in file presently: "<<n<<endl;
    student s[n];
    if(n==0)
    {
        cout<<"File Empty!!"<<endl;
        return;
    }
    f.open("database.txt",ios::in);
    cout<<"Loading from file.."<<endl;
    for(i=0;i<n;i++)
    {
        getline(f,s[i].name);
        getline(f,s[i].id);
        getline(f,s[i].address);
        getline(f,s[i].mail_id);
        getline(f,s[i].branch);
    }
    f.close();
    string id_;
    cout<<"Enter ID of student to search: ";
    getline(cin,id_);
    for(i=0;i<n;i++)
    {
        if(id_==s[i].id)
            break;
    }
    if (i<n)
    {
        cout<<" The searched record has been found"<<endl;
        cout<<s[i].name<<"\t"<<s[i].id<<"\t"<<s[i].address<<"\t"<<s[i].mail_id<<"\t"<<s[i].branch<<endl;
    }
    else
        cout<<" The searched record doesn't exist"<<endl;
}
void display_method()
{
    fstream f;
    f.open("database.txt",ios::in);
    int c=0,n,i;
    while(f)
    {
        char k=f.get();
        if (k=='\n')
            c++;
    }
    f.close();
    n=c/5;
    cout<<"Number of student details in file presently: "<<n<<endl;
    student s[n];
    if(n==0)
    {
        cout<<"File Empty!!"<<endl;
        return;
    }
    f.open("database.txt",ios::in);
    cout<<"Loading from file.."<<endl;
    for(i=0;i<n;i++)
    {
        getline(f,s[i].name);
        getline(f,s[i].id);
        getline(f,s[i].address);
        getline(f,s[i].mail_id);
        getline(f,s[i].branch);
    }
    f.close();
    for(i=0;i<n;i++)
    {
        s[i].displayData();
    }
}
int main()
{
    while(true)
    {
        int input;
        cout<<"____________________________________________________________________________________________"<<endl;
        cout<<" 1 to insert record"<<endl;
        cout<<" 2 to delete record"<<endl;
        cout<<" 3 to update existing record"<<endl;
        cout<<" 4 to search existing records"<<endl;
        cout<<" 5 to display existing records"<<endl;
        cout<<" 0 to exit"<<endl;
        cin>>input;
        cin.ignore();
        int flag;
        switch(input)
        {
            case 1:
                insert_method();
                cout<<" Insertion successful"<<endl;
                break;
            case 2:
                delete_method();
                break;
            case 3:
                update_method();
                break;
            case 4:
                search_method();
                break;
            case 5:
                display_method();
                break;

            default:exit(1);
        }

    }
    return 0;
}


