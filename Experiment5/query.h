#pragma once
#if !defined TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <vector>
#define N 100

using namespace std;

typedef struct condition
{
	string pro;
	string op;
	string value;
	struct condition(string a, string b, string c)
	{
		pro = a;
		op = b;
		value = c;
	}
} condition;

typedef struct relation		//the struct of relationship
{
	string name;
	vector<string> pro;
} relation;

typedef struct projection	//the struct of projection
{
	vector<string> pro;
} projection;

typedef struct select		//the struct of select
{
	vector<condition> cond;
} select;

typedef struct join
{
	string name1;
	string name2;
} join;

typedef struct treeNode
{
	int state;	// 1>>join, 2>>select, 3>>projection
	join op1;
	select op2;
	projection op3;
	struct treeNode *next;
} treeNode;

class database
{
public:
	database();
	~database();
	void readInput();			//read the input

	void lexSql();				//lex analysis
	void parseSql();			//syntax analysis: get the basic query tree
	void clearSql();			//clear the sql for the next test

	void optimizeTree();		//optimize the query tree with heri..
	void insertNode(treeNode *node);
	treeNode *getHead();
	treeNode *getLastNode();
	void clearTree(treeNode *node);

	void outputOld();			//output the basic tree
	void outputNew();			//output the optimize tree

	void showDepartment();		//show the pro of department
	void showEmployee();		//show ..
	void showProject();			//show ..
	void showWorks_on();		//show ..
	void showInput();			//show ..
	void showSql();				//show ..
private:
	string input;
	vector<string> sql;
	treeNode *treeHead;
	relation department;
	relation employee;
	relation project;
	relation works_on;
};

#endif