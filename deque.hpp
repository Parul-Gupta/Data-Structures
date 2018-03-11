#ifndef DEQUE_HPP
#define DEQUE_HPP
#include<iostream>
#include"cStack.hpp"
using namespace std;
template <typename E>  
class Deque {				// deque as doubly linked list
  private:
  	cStack<E> deque;
  public:
    Deque();				// constructor
    int size() const;				// number of items in the deque
    bool empty() const;				// is the deque empty?
    const E& front() const; // the first element
    const E& back() const;	// the last element
    void insertFront(const E& e);		// insert new first element
    void insertBack(const E& e);		// insert new last element
    void removeFront();	// remove first element
    void removeBack();	// remove last element
  };
  
template <typename E>
Deque<E>::Deque(){
	
}

template <typename E>
int Deque<E>::size() const{
	int x=deque.redsize() + deque.bluesize();
	return x;
}

template <typename E>
bool Deque<E>::empty() const{
	return(deque.redempty() && deque.blueempty());
}

template <typename E>
const E& Deque<E>::front() const{
	if(deque.redempty() && !deque.blueempty())return deque.bluetop();
	else if(deque.redempty() && deque.blueempty())cout<<"Deque is empty.\n";
	else return deque.redtop();
}

template <typename E>
const E& Deque<E>::back() const{
	if(deque.blueempty() && !deque.redempty())return deque.redtop();
	else if(deque.redempty() && deque.blueempty())cout<<"Deque is empty.\n";
	else return deque.bluetop();
}

template <typename E>
void Deque<E>::insertFront(const E& e){
	if(!deque.redempty() && deque.blueempty()){
		deque.bluepush(deque.redtop());
		deque.redpop();
	}
	deque.redpush(e);
}

template <typename E>
void Deque<E>::insertBack(const E& e){
	if(!deque.blueempty() && deque.redempty()){
		deque.redpush(deque.bluetop());
		deque.bluepop();
	}
	deque.bluepush(e);
}

template <typename E>
void Deque<E>::removeFront(){
	if(deque.redempty() && !deque.blueempty())deque.bluepop();
	else if(!deque.redempty()){
		deque.redpop();
		if(deque.redempty()){
			cStack<E> aux;
			for(int i=0;i<deque.bluesize()/2;i++){
				aux.redpush(deque.bluetop());
				deque.bluepop();
			}
			while(!deque.blueempty()){
				deque.redpush(deque.bluetop());
				deque.bluepop();
			}
			while(!aux.redempty()){
				deque.bluepush(aux.redtop());
				aux.redpop();
			}
		}
	}
	else cout<<"Deque is empty.\n";
}

template <typename E>
void Deque<E>::removeBack(){
	if(deque.blueempty() && !deque.redempty())deque.redpop();
	else if(!deque.blueempty()){
		deque.bluepop();
		if(deque.blueempty()){
			cStack<E> aux;
			for(int i=0;i<deque.redsize()/2;i++){
				aux.bluepush(deque.redtop());
				deque.redpop();
			}
			while(!deque.redempty()){
				deque.bluepush(deque.redtop());
				deque.redpop();
			}
			while(!aux.blueempty()){
				deque.redpush(aux.bluetop());
				aux.bluepop();
			}
		}
	}
	else cout<<"Deque is empty.\n";
}

#endif
