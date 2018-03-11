#include"graph.hpp"
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

int main(){
	ifstream file;
	file.open("courses.txt",ios::in);
	string name;
	int due,n;
	graph G;
	int i=0;
	vertex v;
	while(file>>name>>due){
		name.erase(0,1);
		stringstream p(name);
		p>>n;
		v.set_data(n,due);
		G.addvertex(v);
	}
	file.close();
	file.open("dependencies.txt",ios::in);
	string sub1,sub2;
	while(file>>sub1>>sub2){
		sub1.erase(0,1);
		sub2.erase(0,1);
		stringstream p1(sub1);
		stringstream p2(sub2);
		int n1,n2;
		p1>>n1;
		p2>>n2;
		edge e(n2);
		G.add_edge(n1,e);
	}
	file.close();
	G.longestpath();
}
