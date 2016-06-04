#include "query.h"

database::database()
{
	department.name = "department";
	department.pro.push_back("dname");
	department.pro.push_back("dno");
	department.pro.push_back("mgrssn");
	department.pro.push_back("mgrstartdate");

	employee.name = "employee";
	employee.pro.push_back("ename");
	employee.pro.push_back("essn");
	employee.pro.push_back("address");
	employee.pro.push_back("salary");
	employee.pro.push_back("superssn");
	employee.pro.push_back("dno");

	project.name = "project";
	project.pro.push_back("pname");
	project.pro.push_back("pno");
	project.pro.push_back("plocation");
	project.pro.push_back("dno");

	works_on.name = "works_on";
	works_on.pro.push_back("essn");
	works_on.pro.push_back("pno");
	works_on.pro.push_back("hours");

	treeHead = NULL;
}

database::~database()
{
	department.pro.clear();
	employee.pro.clear();
	project.pro.clear();
	works_on.pro.clear();
	sql.clear();
}

void database::readInput()
{
	cout << "Please input the sql:";
	getline(cin, input);
	cout << input << endl;
	return;
}

void database::lexSql()
{
	string move = "";
	for (unsigned int i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ')
		{
			if (move.size())
			{
				sql.push_back(move);
				move = "";
			}
		}
		else
			move += input[i];
	}
	if (move.size())
		sql.push_back(move);
	return;
}

//we get the analysis tree to get the result of experiment
void database::parseSql()	//seperate the sql with the key words and the separators
{
	unsigned int i = 0;
	for (; i < sql.size();)
	{
		if (sql[i] == "select")
		{
			cout << "select you are" << endl;
			treeNode *newOne = new treeNode;
			newOne->state = 2;
			i += 2;
			while (sql[i] != "]")
			{
				newOne->op2.cond.push_back(condition(sql[i], sql[i + 1], sql[i + 2]));
				if (sql[i + 3] == "&")
					i += 4;
				else
					i += 3;
			}
			i += 1;
			newOne->next = NULL;
			insertNode(newOne);
		}
		else if (sql[i] == "projection")
		{
			cout << "projection you are" << endl;
			treeNode *newOne = new treeNode;
			newOne->state = 3;
			i += 2;
			while (sql[i] != "]")
			{
				newOne->op3.pro.push_back(sql[i]);
				i += 1;
			}
			i += 1;
			newOne->next = NULL;
			insertNode(newOne);
		}
		else if (sql[i] == "(" || sql[i] == ")")	//other: employee join department
			i+=1;
		else
		{
			cout << "join you are" << endl;
			treeNode *newOne = new treeNode;
			newOne->state = 1;
			newOne->op1.name1 = sql[i];
			newOne->op1.name2 = sql[i + 2];
			newOne->next = NULL;
			insertNode(newOne);
			i += 3;
		}
	}
	return;
}

void database::optimizeTree()
{
	treeNode *head = getHead();
	while (head)
	{
		if (head->state == 2)
		{
			treeNode *lastOne = getLastNode();
			int j = 0;
			lastOne->op1.name1 += "(";
			lastOne->op1.name1 += head->op2.cond[j].pro;
			lastOne->op1.name1 += head->op2.cond[j].op;
			lastOne->op1.name1 += head->op2.cond[j].value;
			lastOne->op1.name1 += ")";
			j = 1;
			if (head->op2.cond.size() == 2)
			{
				lastOne->op1.name2 += "(";
				lastOne->op1.name2 += head->op2.cond[j].pro;
				lastOne->op1.name2 += head->op2.cond[j].op;
				lastOne->op1.name2 += head->op2.cond[j].value;
				lastOne->op1.name2 += ")";
			}
			if (head == getHead())
			{
				treeHead = treeHead->next;
			}
			else
			{
				treeHead->next = head->next;
			}
			break;
		}
		head = head->next;
	}
	return;
}

void database::insertNode(treeNode *node)
{
	cout << "insertNode you are" << endl;
	treeNode *lastNode = getLastNode();
	if (lastNode == NULL)
	{
		treeHead = node;
		return;
	}
	lastNode->next = node;
	return;
}

treeNode *database::getHead()
{
	return treeHead;
}

treeNode *database::getLastNode()
{
	if (treeHead == NULL)
		return NULL;
	treeNode *lastOne = treeHead;
	while (lastOne->next)
		lastOne = lastOne->next;
	return lastOne;
}

void database::clearTree(treeNode *node)
{
	if (node == NULL)
		return;
	treeNode *move = treeHead;
	while (move)
	{
		treeHead = treeHead->next;
		delete[]move;
		move = treeHead;
	}
	return;
}

void database::clearSql()
{
	sql.clear();
	return;
}

void database::outputOld()
{
	cout << endl << endl;
	treeNode *move = getHead();
	while (move)
	{
		//cout << move->state << endl;
		if (move->state == 1)
		{
			cout << "x" << endl;
			cout << move->op1.name1 << " " << move->op1.name2 << endl;
		}
		else if (move->state == 2)
		{
			cout << "theta " << move->op2.cond[0].pro << " " << move->op2.cond[0].op << " " << move->op2.cond[0].value << " ";
			for (unsigned int i = 1; i < move->op2.cond.size(); i++)
				cout << "& " << move->op2.cond[i].pro << " " << move->op2.cond[i].op << " " << move->op2.cond[i].value << " ";
			cout << endl;
		}
		else	//state = 3
		{
			cout << "projection ";
			for (unsigned int i = 0; i < move->op3.pro.size(); i++)
				cout << move->op3.pro[i] << " ";
			cout << endl;
		}
		move = move->next;
	}
	return;
}

void database::outputNew()
{
	return;
}

void database::showDepartment()
{
	cout << endl << endl;
	cout << "The Department is:" << endl;
	for (unsigned int i = 0; i < department.pro.size(); i++)
		cout << department.pro[i] << " ";
	cout << endl << endl;
	return;
}

void database::showEmployee()
{
	cout << endl << endl;
	cout << "The Employee is:" << endl;
	for (unsigned int i = 0; i < employee.pro.size(); i++)
		cout << employee.pro[i] << " ";
	cout << endl << endl;
	return;
}

void database::showProject()
{
	cout << endl << endl;
	cout << "The Project is:" << endl;
	for (unsigned int i = 0; i < project.pro.size(); i++)
		cout << project.pro[i] << " ";
	cout << endl << endl;
	return;
}

void database::showWorks_on()
{
	cout << endl << endl;
	cout << "The Works_on is:" << endl;
	for (unsigned int i = 0; i < works_on.pro.size(); i++)
		cout << works_on.pro[i] << " ";
	cout << endl << endl;
	return;
}

void database::showInput()
{
	cout << endl << endl;
	cout << "The sentence is:" << endl;
	cout << input << endl;
	cout << endl;
	return;
}

void database::showSql()
{
	cout << endl << endl;
	cout << "The sql is:" << endl;
	for (unsigned int i = 0; i < sql.size(); i++)
		cout << sql[i] << endl;
	cout << endl;
	return;
}