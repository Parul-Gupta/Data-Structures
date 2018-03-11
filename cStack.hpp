#ifndef CSTACK_HPP
#define CSTACK_HPP
#include<iostream>
using namespace std;
  template <typename E>
  class cStack {			// an interface for a stack
  private:
    E* arr;
    int size;           //max capacity of the cStack
    int red_top;        //index of the top elem of red_stack
    int blue_top;       //index of the top elem of blue_stack
  public:
    cStack(int cap=100);		// constructor from capacity
    int redsize() const;		// number of items in stack
    bool redempty() const;		// is the stack empty?
    const E& redtop() const;	      		// the top element
    void redpush(const E& e); 		// push x onto the stack
    void redpop();		      	// remove the top element
    int bluesize() const;               // number of items in stack
    bool blueempty() const;             // is the stack empty?
    const E& bluetop() const;           // the top element
    void bluepush(const E& e);          // push x onto the stack
    void bluepop();                     // remove the top element 
 };
 
template <typename E>
cStack<E>::cStack(int cap){
	arr=new E[cap];
	red_top=-1;
	size=blue_top=cap;
}

template <typename E>
int cStack<E>::redsize() const{
	return red_top+1;
}

template <typename E>
bool cStack<E>::redempty() const{
	return (red_top<0);
}

template <typename E>
const E& cStack<E>::redtop()const{
	return arr[red_top];
}

template <typename E>
void cStack<E>::redpush(const E& e){
	if(blue_top-red_top<=1){
		cout<<"Stack overflow.\n";
	}
	else{
		arr[++red_top]=e;
	}
}

template <typename E>
void cStack<E>::redpop(){
	if(red_top<0){
		cout<<"Stack underflow.\n";
	}
	else{
		red_top--;		
	}
}

template <typename E>
int cStack<E>::bluesize() const{
	int x=size-blue_top;
	return x;
}

template <typename E>
bool cStack<E>::blueempty() const{
	return (blue_top>=size);
}

template <typename E>
const E& cStack<E>::bluetop()const{
	return arr[blue_top];
}

template <typename E>
void cStack<E>::bluepush(const E& e){
	if(blue_top-red_top<=1){
		cout<<"Stack overflow.\n";
	}
	else{
		arr[--blue_top]=e;
	}
}

template <typename E>
void cStack<E>::bluepop(){
	if(blue_top>=size){
		cout<<"Stack underflow.\n";
	}
	else{
		blue_top++;
	}	
}

#endif
