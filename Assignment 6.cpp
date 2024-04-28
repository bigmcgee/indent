#include <iostream>
using namespace std;

class graph{
		int cost[10][10];
		int tcities;
public:
		graph();
		void create();
		void display();
		void prims();
};

graph::graph(){
	tcities = 0;
	cout<< "Enter Total number of Cities: ";
	cin>> tcities;
	for(int i = 0; i < tcities; i++){
		for(int j = 0; j < tcities; j++){
			cost[i][j] = 0;
			}
		}
}

void graph::create(){
	char ch;
	for(int i = 0; i < tcities; i++){
		for(int j = i + 1; j< tcities; j++){
			cout<<"\nIs there a connection between "<<i+1<<" & "<<j+1<<"(y or n)";
			cin>>ch;
			if(ch == 'y'){
			cout<< "Enter cost of edge " <<i+1<<" & "<<j+1<<": ";
			cin>>cost[i][j];
			cost[j][i] = cost[i][j];
				}
			}
		}
	}

void graph::display(){
	for(int i = 0; i < tcities;i++){
		for(int j = 0; j < tcities; j++){
			cout<<cost[i][j]<<"\t";
		}
	cout<<"\n";
	}
}

void graph::prims(){
    int st[tcities][2];
    int r = 0, stv, min, i, j, k;
    int final = 0; 
    cout<<"Enter the Starting Vertex: ";
    cin>>stv;
    int nearest[tcities];
    nearest[stv] = -1;
    
    for(int i = 0; i < tcities; i++) {
        if(i != stv) {
            nearest[i] = stv;
        }
    }
    
    for(int i = 1; i < tcities; i++) {
        min = 999;
        for(int k = 0; k < tcities; k++) {
            if(nearest[k] != -1 && cost[k][nearest[k]] < min) {
                j = k;
                min = cost[k][nearest[k]];
            }
        }
        st[r][0] = j;
        st[r][1] = nearest[j];
        r++;
        final += min;
        nearest[j] = -1;
        for(int k = 0; k < tcities; k++) {
            if(nearest[k] != -1 && cost[k][nearest[k]] > cost[k][j]) {
                nearest[k] = j;
            }
        }
    }
    
    cout<<"\nThe spanning tree is as follows: \n";
    for(int i = 0; i < tcities - 1; i++) {
        for(int j = 0; j < 2; j++) {
            cout<<st[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"\nThe total cost is :"<<final<<endl;
}



int main()
{ 
    int ch,c;
    graph g;
    do
    {
    cout<<"1.Create graph \n2.Display graph\n3.Prim's Algorithm\n";
    cout<<"Enter your choice to do operation :";
    cin>>ch;
   switch(ch)
   {
    case 1:
       cout<<"================Create Graph============="<<endl;
       g.create();
       break;

    case 2:
       cout<<"================Display Graph============="<<endl;
       g.display();
       break;
    case 3:
    	 cout<<"================Prim's Algorithm============="<<endl;
    	 g.prims();
       break;
    default:
       cout<<"Invalid Choice"<<endl;
       break;
    }
    cout << "\nDo you want to perform more operations on Graph?\nEnter your Choice\n1.Yes\n2.No: ";
    cin >> c;
   }while (c==1);
    return 0;
}
