#ifndef GRAPH_HPP
#define GRAPH_HPP
#include<iostream>
#include<vector>
#include<stack>
#include<limits.h>
using namespace std;

class edge{
	int out;
	public:
		edge(int o);
		friend class graph;
		friend class vertex;		
};

edge::edge(int o){
	out = o;
}

class vertex{
	int num;           //course name
	int duration;      //course duration
	vector<edge> adj;  //vector of edges connected to the vertex
	bool is_visited;
	public:
		vertex();
		void set_data(int n,int d);
		friend class graph;
};
vertex::vertex(){
	num=0;
	duration=0;
	is_visited=false;
}

void vertex::set_data(int n,int d){
	num=n;
	duration=d;
}

class graph{
	vector<vertex> g;
	public:
		void addvertex(vertex w);
		void top_sort(vertex& v,stack<int> &S);
		void longestpath();
		void add_edge(int i,edge e);
		bool isDCG(int v,bool* isvisited,bool* inStack);
};

void graph::add_edge(int i,edge e){
	g[i-1].adj.push_back(e);
}

void graph::addvertex(vertex w){
	g.push_back(w);
}

bool graph::isDCG(int v,bool* isvisited,bool* inStack){
	if(isvisited[v-1]==false){
		isvisited[v-1]=true;
		inStack[v-1]=true;
		vector<edge>:: iterator it;
		for(it=g[v-1].adj.begin();it!=g[v-1].adj.end();it++){
			if(!isvisited[(it->out)-1] && isDCG(it->out,isvisited,inStack))return true;
			else if (inStack[(it->out)-1]) return true;
		}
	}
	inStack[v-1]=false;
	return false;
}

void graph::top_sort(vertex& v,stack<int> &S){
	v.is_visited=true;
	vector<edge>:: iterator it;
	for(it=v.adj.begin();it!=v.adj.end();it++){
		edge l=*(it);
		if(g[l.out-1].is_visited==false){
			top_sort(g[l.out-1],S);
		}
	} 
	S.push(v.num);
}

void graph::longestpath(){
	bool* isvisited=new bool[g.size()];
	bool* inStack=new bool[g.size()];
	for(int i=0;i<g.size();i++){
		isvisited[i]=false;
		inStack[i]=false;
	}
	if(isDCG(1,isvisited,inStack)){
		cout<<"Not a DAG.\n";
		return;
	}
	stack<int> Stack;
	top_sort(g[0],Stack);
	int size=Stack.size();
	int arr[2][size];
	for(int i=0;i<size;i++){
		arr[0][i]=INT_MIN;
		arr[1][i]=0;
	}
	arr[0][0]=0;
	while(Stack.empty()==false){
		int u=Stack.top();
		Stack.pop();
		vector<edge>:: iterator it;
		if(arr[0][u-1]!=INT_MIN){
			for(it=g[u-1].adj.begin();it!=g[u-1].adj.end();it++){
			if(arr[0][(it->out)-1]<(arr[0][u-1]+g[(it->out)-1].duration)){
				arr[0][(it->out)-1]=(arr[0][u-1]+g[(it->out)-1].duration);
				arr[1][(it->out)-1]=u;	
			}
			}
		}
	}
	stack<int> S1;
	S1.push(size);
	int i=size;
	while(S1.top()!=1){
		i=arr[1][i-1];
		S1.push(i);
	}
	cout<<"The longest path is:"<<endl;
	while(!S1.empty()){
		cout<<"C"<<S1.top()<<"\t";
		S1.pop();
	}
	cout<<endl;
	cout<<"Total duration is "<<arr[0][size-1]+g[size-1].duration<<" months.\n";
}

#endif







