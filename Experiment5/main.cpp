#include "query.h"
//#define TEST

int main()
{
	database a;
#ifdef TEST
	a.showDepartment();
	a.showEmployee();
	a.showProject();
	a.showWorks_on();
#endif

	a.readInput();

#ifdef TEST
	a.showInput();
#endif

	a.lexSql();
	a.showSql();
	a.parseSql();
	a.outputOld();
	a.optimizeTree();
	a.outputOld();
	return 0;
}