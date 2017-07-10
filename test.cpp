#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include"GraphMatrix.h"
#include"LinkEdge.h"
using namespace std;

void Test1()
{
	const char*str = "ABCDE";
	GraphMatrix<char, int>g(str, strlen(str), false);
}
void Test2()
{
	const char*str = "ABCDE";
	GraphLink<char, int>gl(str, strlen(str), false);
	//GraphLink<char, int>gl(false);
	gl.AddEdge('A', 'B', 10);
	gl.AddEdge('B', 'C', 10);
	gl.AddEdge('C', 'D', 10);
	gl.AddEdge('D', 'E', 10);
	gl.AddEdge('E', 'A', 10);
	//gl.Print();
	gl.BFS('A');
	gl.DFS('A');
	pair<GraphLink<char ,int >, int>tree = gl.GetminTree();
}

int main()
{
	//Test1();
	Test2();
	system("pause");
	return 0;
}
