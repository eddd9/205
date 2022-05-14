#include <iostream>
#include <string>
#include<algorithm>
#include <queue>
#include <vector>
#include <stack>
#include<stdio.h>
#include<ctime>

using namespace std;

/*class puzzle1{//To use priority queue,reference is:stl priority_queue of C++ with struct.
private:
   vector <int> p1;
   int g;
   int h;
   int f;
public:
   puzzle1(vector <int> puzzlenow, int g1, int h1)
};
puzzle1::pizzle1(vector <int> puzzlenow, int g1, int h1){
		p1 = puzzlenow;
		g = g1;
		h = h1;
		f = g+ h;
}*/

static const vector <int> target = { 1,2,3,4,5,6,7,8,0 };//The goal state is[1,2,3,4,5,6,7,8,0]
//Here are variables for 8-puzzle.
struct puzzle1 {
	vector <int> p1;
	int g, h, f;
	puzzle1(vector <int> puzzlenow, int g1, int h1) {
		p1 = puzzlenow;
		g = g1;
		h = h1;
		f = g1 + h1;
	}

};
//Manhattan Distance heuristic starts from here.
int Astar_man(vector <int> puzzle) {
	int m = 0;
	int r1 = 1;
	int c1 = 1;
	int r, c, value;
	int s;
	s = puzzle.size();
	int v1, v2;
	int n{};
	while (n < s) {//Get row and column regarding what the value is.
		value = puzzle.at(n);
		switch (value) {
		case 1:r = 1; c = 1; break;
		case 2:r = 1; c = 2; break;
		case 3:r = 2; c = 3; break;
		case 4:r = 2; c = 1; break;
		case 5:r = 2; c = 2; break;
		case 6:r = 3; c = 3; break;
		case 7:r = 3; c = 1; break;
		case 8:r = 3; c = 2; break;
		case 0:r = 3; c = 3; break;
		}
		//Init column to 1.
		if (n != 0 && n % 3 == 0) {
			r1++;
			c1 = 1;
		}
		//Compare puzzle with target puzzle and compute h(n).
		v1 = puzzle.at(n);
		v2 = target.at(n);
		if (v1 != v2)
			m = m + abs(r - r1) + abs(c - c1);
		c1++;
		n++;
	}
	return m;//h(n)=m
}
//Misplaced Tile heuristic starts from here.
int Astar_mis(vector <int> puzzle) {
	int m, n, s, n1, n2;
	m = 0;
	n = 0;
	s = puzzle.size();
	//Compute h(n).
	while (n < s) {
		n1 = puzzle.at(n);
		n2 = target.at(n);
		if (n1 != n2 && n1 != 0)
			m++;
		n++;
	}
	return m;
}
//To use priority queue,reference is:stl priority_queue of C++ with struct.
bool operator<(const puzzle1& n1, const puzzle1& n2) {
	return n1.f > n2.f;
}
//To get all nodes on next level.
vector<puzzle1> NextLevel(puzzle1 thisp, int agm) {
	int value, g, h, i, m, zero;
	vector<int> table1;
	vector<int> table;
	vector<puzzle1> next;
	table = thisp.p1;
	zero = -1;
	i = 0;
	g = 1;
	m = table.size();
	g += thisp.g;
	//Find the position of blank node.
	while (i < m)
	{
		int j = table.at(i);
		if (j == 0) { zero = i; break; }
		i++;
	}
	//0 can go up and down, left and right. 
	//The amount of position that nodes can move to is between 2 to 4.
	//For example,[1,2,3,4,0,5,6,7,8] 0 can go up and down, left and right.
	//[1,2,0,3,4,5,6,7,8]0 can only go left or down.
	//position!=0,1,2  If position of 0 is not in the first row then go up.
	if (zero != 0 && zero != 1 && zero != 2) {
		h = 0;
		value = table.at(static_cast<std::vector<int, std::allocator<int>>::size_type>(zero) - 3);
		table1 = table;
		table1.at(zero) = value;
		table1.at(static_cast<std::vector<int, std::allocator<int>>::size_type>(zero) - 3) = 0;
		switch (agm)
		{
		case 2:h = Astar_mis(table1); break;
		case 3:h = Astar_man(table1); break;
		}
		puzzle1 n(table1, g, h);
		next.push_back(n);
	}
	//position!=6,7,8  If position of 0 is not in the third row then go down.
	if (zero != 6 && zero != 7 && zero != 8) {
		h = 0;
		value = table.at(static_cast<std::vector<int, std::allocator<int>>::size_type>(zero) + 3);
		table1 = table;
		table1.at(zero) = value;
		table1.at(static_cast<std::vector<int, std::allocator<int>>::size_type>(zero) + 3) = 0;
		switch (agm)
		{
		case 2:h = Astar_mis(table1); break;
		case 3:h = Astar_man(table1); break;
		}
		puzzle1 n(table1, g, h);
		next.push_back(n);
	}
	//position=!0,3,6  If position of 0 is not in the third column then go left.
	if (zero != 0 && zero != 3 && zero != 6) {
		h = 0;
		value = table.at(static_cast<std::vector<int, std::allocator<int>>::size_type>(zero) - 1);
		table1 = table;
		table1.at(static_cast<std::vector<int, std::allocator<int>>::size_type>(zero) - 1) = 0;
		table1.at(zero) = value;
		switch (agm)
		{
		case 2:h = Astar_mis(table1); break;
		case 3:h = Astar_man(table1); break;
		}
		puzzle1 n(table1, g, h);
		next.push_back(n);
	}
	//position=!2,5,8  If position of 0 is not in the third column then go right.
	if (zero != 2 && zero != 5 && zero != 8) {
		h = 0;
		value = table.at(static_cast<std::vector<int, std::allocator<int>>::size_type>(zero) + 1);
		table1 = table;
		table1.at(zero) = value;
		table1.at(static_cast<std::vector<int, std::allocator<int>>::size_type>(zero) + 1) = 0;
		switch (agm)
		{
		case 2:h = Astar_mis(table1); break;
		case 3:h = Astar_man(table1); break;
		}
		puzzle1 n(table1, g, h);
		next.push_back(n);
	}

	return next;
}
//general_research Reference:slides of CS205
//Keep computing until the target puzzle are found .
void general_search(vector<int> puzzle, int agm) {
	int max, total, hn{}, g, h;
	vector <int> p;
	puzzle1 table(puzzle, 0, 0);
	vector <puzzle1> table1;
	hn = 0;
	max = 1;
	total = 0;
	switch (agm)
	{
	case 2:hn = Astar_mis(puzzle); break;
	case 3:hn = Astar_man(puzzle); break;
	}
	puzzle1 n1(puzzle, 0, hn);
	priority_queue<puzzle1> puzzle2;
	puzzle2.push(n1);
	int stop;
	for (stop = 1; stop != 0; stop++)
	{
		if (puzzle2.empty()) {
			printf("This puzzle cannot be solved.\n");
			stop = 0;
			break;
		}
		table = puzzle2.top();//To use priority queue,reference is:stl priority_queue of C++ with struct. 
		puzzle2.pop();//To use priority queue,reference is:stl priority_queue of C++ with struct. 
		g = table.g;
		h = table.h;
		p = table.p1;
		if (table.p1 == target) {
			vector <int> result;
			printf("Processing... g(n)=%d, h(n)=%d, puzzle is [1 2 3 4 5 6 7 8 0 ]\n", g, h);
			printf("The result is:\n[1,2,3,\n 4,5,6,\n 7,8,0]\n");
			int depth;
			depth = table.g;
			printf("Here is the result:\n");
			printf("The depth of the solution is %d. The number of nodes used is %d and the maximum number of nodes in the queue is %d.\n", depth, total, max);
			stop == 0;
			break;
		}
		printf("Processing... g(n)=%d, h(n)=%d, puzzle is [", g, h);
		for (int i = 0; i < p.size(); i++) {
			printf("%d ", p[i]);
		}
		printf("]\n");
		table1 = NextLevel(table, agm);
		int s, s1;
		int m;
		m = 0;
		s = table1.size();
		while (m < s) {
			total++;
			s1 = puzzle2.size();
			max = s1 > max ? s1 : max;
			puzzle2.push(table1.at(m));
			m++;
		}
	}
}
//Puzzle [1,3,6][5,0,2][4,7,8] has target puzzle on depth 8.
int main() {
	int i, j;
	vector <int> puzzle;
	clock_t t1, t2;
	t1 = clock();
	vector <int> init = { 1,3,6,5,0,2,4,7,8 };
	printf("CS205 Eight Puzzle\n");
	printf("If you want to use puzzle [1,3,6][5,0,2][4,7,8], please input 1.\n");
	printf("Or you can input 2 to enter any puzzles you want.\n");
	scanf("%d", &i);//Here to input the puzzle you want.
	if (i == 2) {
		int value;
		printf("Please input you puzzle like this:1 3 6 5 0 2 4 7 8\n");
		int s;
		int m;
		m = 0;
		s = target.size();
		while (m < s) {
			cin >> value;
			puzzle.push_back(value);
			m++;
		}
		init = puzzle;
	}
	printf("Please choose one of listed three algorithms:\nInput 1 to choose Uniform Cost Search.\n");
	printf("Input 2 to choose A* with the Misplaced Tile heuristic.\nInput 3 to choose A* with the Manhattan Distance heuristic.\n");
	scanf("%d", &j);//Here to input the algorithm you want.
	switch (j)
	{
	case 1:general_search(init, 1); break;
	case 2:general_search(init, 2); break;
	case 3:general_search(init, 3); break;
	}
	t2 = clock();
	int tt;
	tt = (static_cast<int>(t2) - t1) / CLOCKS_PER_SEC;
	printf("Total time used is %dms.\n", 1000 * tt);
	return 0;
}
