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


