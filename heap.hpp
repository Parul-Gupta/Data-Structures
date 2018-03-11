#ifndef HEAP_HPP
#define HEAP_HPP
#include<iostream>
using namespace std;
  template <typename E>
class node{
	private:
		E elem;
		node<E>* parent;
		node<E>* left;
		node<E>* right;
	public:
		node(const E& e);
        template <typename A,typename B>
        friend class Heap;
 };
  
  template <typename E>
node<E>::node(const E& e){
	elem=e;
	parent=NULL;
	left=NULL;
	right=NULL;
}

  template <typename E, typename C>			// element and comparator
  class Heap {					// priority-queue interface
  private:
  	node<E>* heap;           //root of the heap
  	node<E>* last;           //pointer to last inserted element
  	int s;                   //size of heap
  public:
    Heap();                            //Constructor
    int size() const;					// number of elements
    bool isEmpty() const;				// is the queue empty?
    void insert(const E& e);				// insert element
    const E& min() const;		// minimum element
    void removeMin();			// remove minimum
    void mergeHeaps(Heap<E,C> H);    //merges heap H with the given heap
    void buildHeap(E A[], int size);  //builds heap using the given array
    
	bool firstSmaller(E& e1,E& e2,C& isless);  //returns true if 1st elem is smaller
	void upheapify(node<E>* n);  
	void downheapify(node<E>* n);
	
	void preorder(node<E>* n,E* arr,int* f_i); //puts the nodes of the heap starting from node n in preorder into the array arr
	node<E>* getheap();              //returns the root of the heap
  };
  template <typename E,typename C>
Heap<E,C>::Heap(){
	heap=NULL;
	last=NULL;
	s=0;
}

template <typename E,typename C>
node<E>* Heap<E,C>::getheap(){
	return heap;
}

  template <typename E,typename C>
int Heap<E,C>::size() const{
	return s;	
}

  template <typename E,typename C>
bool Heap<E,C>::isEmpty() const{
	return (s==0);	
}

  template <typename E,typename C>
void Heap<E,C>::insert(const E& e){
	node<E>* temp=new node<E>(e);
	if(last==NULL){
		heap=last=temp;
		s++;
		return;
	}
	else if(last->parent==NULL){
		last->left=temp;
		temp->parent=last;
		last=temp;
		s++;
		upheapify(temp);
		return;
	}
	else if(last->parent->left==last){
		last->parent->right=temp;
		temp->parent=last->parent;
		last=temp;
		s++;
		upheapify(temp);
		return;
	}
	else{
		while(last!=heap){
	        if(last->parent->left!=last)last=last->parent;
	        else{
	            last=last->parent->right;
	        	break;
	        }	
		}
		while(last->left!=NULL)last=last->left;
		last->left=temp;
		temp->parent=last;
		last=temp;
		s++;
		upheapify(temp);
		return;
	}
}

  template <typename E,typename C>
const E& Heap<E,C>::min() const{
	if(s>0)return heap->elem;
	else cout<<"Heap is empty.\n";	
}

template <typename E,typename C>
void Heap<E,C>::removeMin(){
	if(s==1){
		node<E>* temp=heap;
		heap=last=NULL;
		delete temp;
		s--;	
	}
	else if(s>1){
		E temp=last->elem;
		last->elem=heap->elem;
		heap->elem=temp;
		node<E>* temp1=last;
		last=last->parent;
		if(temp1==last->right){
			last->right=NULL;
			delete temp1;
			s--;
			last=last->left;
		}
		else{
			last->left=NULL;
			delete temp1;
			s--;
			while(last!=heap){
				if(last->parent->right!=last)last=last->parent;
				else{
					last=last->parent->left;
					break;
				}
			}
			while(last->right!=NULL)last=last->right;
		}
		downheapify(heap);
	}
	else cout<<"Heap is empty.\n";
}

  template <typename E,typename C>
void Heap<E,C>::mergeHeaps(Heap<E,C> H){
	E* arr=new E[s+H.size()];
	int *i=new int;
	*i=0;
	preorder(heap,arr,i);
	preorder(H.getheap(),arr,i);
	buildHeap(arr,*i);
	delete i;
	//delete arr;	
}

template <typename E,typename C>
void Heap<E,C>::preorder(node<E>* n,E* arr,int* f_i){
	if(n!=NULL){
        arr[(*f_i)++]=n->elem;
    	preorder(n->left,arr,f_i);
    	preorder(n->right,arr,f_i);
    	return;
    }
    else return;
}

  template <typename E,typename C>
void Heap<E,C>::buildHeap(E A[], int size){
	node<E>* temp[size];
    for(int i=0;i<size;i++){
		temp[i]=new node<E>(A[i]);
	}
	for(int i=size/2-1;i>=0;i--){
		temp[i]->left=temp[2*i+1];
		temp[2*i+1]->parent=temp[i];
		if((2*i+2)<size){
			temp[i]->right=temp[2*i+2];
			temp[2*i+2]->parent=temp[i];
		}
		downheapify(temp[i]);
	}
	heap=temp[0];
	last=temp[size-1];	
	s=size;	
}

  template <typename E,typename C>
bool Heap<E,C>::firstSmaller(E& e1,E& e2,C& isless){
	return isless(e1,e2);	
}

template <typename E,typename C>
void Heap<E,C>::upheapify(node<E>* n){
	C isless;
	while(n->parent!=NULL && !firstSmaller(n->parent->elem,n->elem,isless)){
		E temp=n->elem;
		n->elem=n->parent->elem;
		n->parent->elem=temp;
		n=n->parent;
	}
}

  template <typename E,typename C>
void Heap<E,C>::downheapify(node<E>* n){
	if(n->left==NULL)return;
	else if(n->right==NULL){
		C isless;
		if(!firstSmaller(n->elem,n->left->elem,isless)){
			E temp=n->elem;
			n->elem=n->left->elem;
			n->left->elem=temp;
			return;
		}
		else return;
	}
	else{
		E temp1=n->left->elem;
		E temp2=n->right->elem;
		E temp=n->elem;
		C isless;
	    if(firstSmaller(temp1,temp,isless) && firstSmaller(temp1,temp2,isless)){
			n->left->elem=temp;
			n->elem=temp1;
			downheapify(n->left);
			return;
		}
        else if(firstSmaller(temp2,temp,isless) && firstSmaller(temp2,temp1,isless)){
			n->right->elem=temp;
			n->elem=temp2;
			downheapify(n->right);
			return;
		}
		else return;
	}
}

#endif




