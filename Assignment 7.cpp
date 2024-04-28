#include<iostream>
#include<string>
#define max 10
using namespace std;


class student {
    int rollno;
    string name;
    int grade;
    public:
    student();
    friend class Hash;
}s;

student::student(){
    rollno=-1;
    name=" ";
    grade=' ';
}

class Hash{
    student hashtable[max];
    public:
    Hash();
    void insert_wr();
    void display();
};

Hash::Hash(){
    for(int i=0;i<max;i++){
    hashtable[i].rollno=-1;
    }
}



void Hash::insert_wr(){
    int ch;
    do{
        int i,loc;
        cout<<"Enter the roll number"<<endl;
        cin>>s.rollno;
        cout<<"Enter the name"<<endl;
        cin>>s.name;
        loc=s.rollno%max;
        if(hashtable[loc].rollno==-1){
            hashtable[loc]=s;
        } 
        else{
            i=(loc+1)%max;
            while(i!=loc){
                if(hashtable[i].rollno==-1){
                    hashtable[i]=s;
                    break;
                }
                i=(i+1)%max;
            }
        }
        cout<<"Press 1 to add more numbers?"<<endl;
        cin>>ch;
        if(i==loc){
            cout<<"Hash is full"<<endl;
            break;
        }

    }while(ch==1);
}

void Hash::display(){
    cout<<"loc"<<" "<<"RollNo"<<" "<<"name"<<endl;
    for(int i=0;i<max;i++){
        cout<<i<<"  "<<hashtable[i].rollno<<"  "<<hashtable[i].name<<endl;
    }
}

int main(){
    Hash h;
    h.insert_wr();
    h.display();
    return 0;
}
