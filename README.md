# Data-Structures
Implementing various modified versions of data structures, like double-ended queue using a special "Cstack" (coloured-stack), modified AVL Tree having option of deletion based on the order of insertion, Heap,etc.

In order to compile and run the graph, type on the console:
	g++ graph.cpp -std=c++11 -o b
	./b

For the graph:
To get the longest path (or maximum duration of courses),first I check whether the graph is a DAG and then we perform topological sorting on the graph starting from the source vertex ,i.e. vertex corresponding to C1. (I have assumed that the courses given in the file courses.txt are in counting order,i.e C1,C2,C3....and so on).This gives us a Stack.

After this I initialise row 0 of a 2-D array (no. of columns equal to the number of vertices and 2 rows, row 0 stores the longest distance from source vertex and row 1, the vertex preceding the given vertex in the longest path) with -inf and the column 0 (corresponding to the source vertex) with zero.

Now for every index of the array (in order of the vertices presnt in the stack), I go to its adjacent vertices and update their distances if the sum of durations of the course and its adjacent course is more than the number already stored at that index.Whenever I update a distance, I store the vertex updating it in the second row.

This will give us (the maximum duration-duration of the last course) in the last index of the array using which we can get the max duration. The second row of the array helps us get the order of vertices.

To check whether a graph is a DAG, I check whether I reach an ancestor while doing its DFS. 

Orders:
addvertex--------------O(1)
top_sort---------------O(n) [n=no. of courses]
longestpath------------O(n) [n=no. of courses]
add_edge---------------O(1)
isDCG------------------O(n) [n=no. of courses]

*********cStack.hpp************
This structure has an array, of which the left side acts as the red stack and the right side as the blue stack.
It has the following functions:
    Name                 Description                                 Time Complexity
	redsize();   ------> returns the size of the red stack               O(1)
	bluesize();   ------> returns the size of the blue stack             O(1)
	redempty();   ------> returns true if the red stack is empty         O(1)
	blueempty();   ------> returns true if the blue stack is empty       O(1)
	redtop();       -->     returns top element of the redstack          O(1)
	           (if red stack stack is empty it will print error and terminate the code) 
	bluetop();       -->     returns top element of the bluestack        O(1)
	           (if blue stack stack is empty it will print error and terminate the code)
	redpush();      --> pushes the element onto the red stack            O(1)
	                    (if there is no space it will print overflow error) 
	bluepush();     --> pushes the element onto the blue stack           O(1)
	                    (if there is no space it will print overflow error) 
	redpop();       --> removes element from the top of red stack        O(1)
	                    (if redstack is empty it will give underflow error)
    	bluepop();      --> removes element from the top of red stack        O(1)
                       	    (if redstack is empty it will give error)

******deque.hpp*****

deque uses a cstack to create a double ended queue
any push/pop operation for front uses redStack
any push/pop operation for back uses blueStack
if any stack is empty while the other is non-empty it reorders the elements

1) Deque();	
--> creates a deque using cStack of size 100
2) int size() const
--> returns the number of items in the deque
3) bool empty() const	
--> return true if the deque is empty
4) const E& front() const
--> returns the first element , gives error if deque is empty
5) const E& back() const
--> returns the last element , gives error if deque is empty
6) void insertFront(const E& e)
--> inserts new element at the front
7) void insertBack(const E& e)
--> inserts new element at the back
8) void removeFront()
--> removes first element , error if deque is empty
9) void removeBack()
--> removes last element , error if deque is empty

TIME COMPLEXITY:
size() , front() , back() , insertFront() , insertBack() are all O(1)
removeFront() and removeBack() are O(1)(Average) 
PROOF:
for N remove operations:
first N/2 will be O(1)
next there will be N/2 ordering operations 
next N/4 operations will be O(1)
in this fashion
order will be 
O( (N/2+N/2+N/4+N/4.......)/N ) = O(1)

*****heap.hpp*****
1)Heap()
--> creates a node pointer of type E entered by the user
2) int size() const
--> returns number of elements in the heap
3) bool isEmpty() const
--> returns true if the queue is empty
4) void insert(const E& e)
--> insert element in the heap as well as heapifies
5) const E& min() const
--> returns minimum element of the heap , error if heap is empty
6) void removeMin()
--> remove minimum element from the heap , error if empty
7) Heap* mergeHeaps()
--> merges two heaps
8) void buildHeap(int A[], int size)
--> creates a heap from elements in the array

TIME COMPLEXITY:
size() , isEmpty() , min() , are all O(1)
insert() , removeMin() are order O(logn) as the node will be swapped logn times in worst case
mergeHeaps() is order n , it performs n operations to extract elements from the array and calls buildHeap

buildHeap assign the correct pointers in order n and heapifies which is order n as every element is heapified at most logh times where h is the height of that node , so integral sums down to n

