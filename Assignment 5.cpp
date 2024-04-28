#include<iostream>
using namespace std;

class gnode
{
	int id;
	string username;
	gnode *next;
	public:
	gnode()
	{
		id=0;
		username="\0";
		next=NULL;
	}
	friend class graph;
};
class stack
{
	int top;
	int stck[20];	
	public:
	stack();
	void push(int temp);
	int pop();
	void isfull();
	void isempty();
};

stack::stack()
{
	top=-1;
}
void stack::push(int temp)
{
	top++;
	stck[top]=temp;
}
int stack::pop()
{
	int temp=stck[top];
	top--;
	return temp;
}
void stack::isfull()
{
	if(top==19)
	{
		cout<<"\nStack is Full";
	}
}
void stack::isempty()
{
	if(top==-1)
	{
		cout<<"\n Stack is Empty";
	}
}
class graph
{
	int n;
	gnode *head[10];
	public:
	graph();
	void create();
	void display();
	void dfs();
	void dfs(int v,int visited[10]);
	void dfs_nr();
};

graph::graph()
{
	n=0;
	cout<<"\nEnter the number of vertices : \n";
	cin>>n;
	for(int i=0;i<n;i++)
	{
		head[i]=new gnode;
		head[i]->id=i;
		cout<<"\nEnter the Username : \n";
		cin>>head[i]->username;
	}
}

void graph::create()
{
	int v,ch;
	gnode *temp,*curr;
	for(int i=0;i<n;i++)
	{
		temp=head[i];
		do
		{
			cout<<"\nEnter the Adjacent vertex "<<i;
			cin>>v;
			if(v==i)
			{
				cout<<"\nSelf Loop are not allowed ";
			}
			else
			{
				curr=new gnode;
				curr->id=v;
				temp->next=curr;
				temp=temp->next;
			}
			cout<<"\nEnter 1 if you want to continue \n";
			cin>>ch;
		}while(ch==1);
	}
}
void graph::display()
{
	gnode *temp;
	for(int i=0;i<n;i++)
	{
		temp=head[i];
		while(temp!=NULL)
		{
			cout<<temp->username<<"\t"<<temp->id<<"\n";
			temp=temp->next;
		}
	}
}
void graph::dfs()
{
	int visited[10],v;
	for(int i=0;i<n;i++)
	{
		visited[i]=0;
	}
	cout<<"\nEnter the starting User id  of graph \n";
	cin>>v;
	dfs(v,visited);
}
void graph::dfs(int v, int visited[10])
{	
	cout<<head[v]->username<<"\t";
	gnode *temp;
	visited[v]=1;
	temp=head[v]->next;
	while(temp!=NULL)
	{
		if(!visited[temp->id])
		{
			dfs(temp->id,visited);
		}
		temp=temp->next;
	}
	
}
void graph::dfs_nr()
{
	int visited[10],v;
	gnode *temp;
	stack sc;
	cout<<"\nEnter the starting User id  of graph \n";
	cin>>v;
	for(int i=0;i<n;i++)
	{
		visited[i]=0;
	}
	sc.push(v);
	visited[v]=1;
		v=sc.pop();
		cout<<head[v]->username<<"\n";
		while(temp!=NULL)
		{
		if(!visited[temp->id])
		{
			sc.push(temp->id);
			visited[temp->id]=1;
		}
		}
}
int main()
{
	int choice,ch1;
	graph g;
	do
	{
		cout<<"\nChoose an Operation\n1.Create a Graph\n2.Display a Graph\n3.Depth First Traversal\n4.DFS without traversal\n";
		cin>>choice;
		switch(choice)
		{
			case 1:
			{
				g.create();
				break;
			}
			case 2:
			{
				g.display();
				break;
			}
			case 3:
			{
				g.dfs();
				break;
			}
			case 4:
			{
				g.dfs_nr();
				break;
			}
		}
		cout<<"\nIf you want to perform operations press 1.\n";
		cin>>ch1;
	}while(ch1==1);
}
