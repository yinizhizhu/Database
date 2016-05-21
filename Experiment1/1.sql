create table department
	(dname varchar(12),
	dno int,
	mgrssn char(18),
	mgrstartdata date,
	primary key(dno));

	5个
insert into department
	values("caocaode", 1, "111111111111111", "2016-10-10");

load data local infile "C:/Users/11303/Desktop/LeetCode-Medium/department.txt" into table department;

create table employee
	(ename varchar(12),
	essn char(18),
	address varchar(30),
	salary numeric(8,2),
	superssn char(18),
	dno int,
	primary key(essn),
	foreign key (dno) references department(dno));
	
	50个
insert into employee
	values("小红", "1111111111111111", "哈尔滨", 1000, "111111111111111", 1);
	
load data local infile "C:/Users/11303/Desktop/LeetCode-Medium/employee.txt" into table employee;
	
create table project
	(pname varchar(12),
	pno varchar(12),
	plocation varchar(30),
	dno int,
	primary key(pno),
	foreign key (dno) references department(dno));
	
	10个
insert into project
	values("ene", "P1", "哈尔滨", 1);
	
load data local infile "C:/Users/11303/Desktop/LeetCode-Medium/project.txt" into table project;
	
create table works_on
	(essn char(18),
	pno varchar(12),
	hours int,
	primary key(essn, pno),
	foreign key (essn) references employee(essn),
	foreign key (pno) references project(pno));
	
insert into works_on
	values("111111111", "P1", 12);
	
load data local infile "C:/Users/11303/Desktop/LeetCode-Medium/works_on.txt" into table works_on;
	
describe department;
describe employee;
describe project;
describe works_on;

1.
select distinct ename, pname from project natural join employee;
select distinct ename, pname from project natural join employee where pname = "开黑";

2.
select distinct ename, address, dname, salary from department natural join employee;
select distinct ename, address, dname, salary from department natural join employee where dname = "哈工大" and salary < 1300;

3.
select distinct ename from employee;
select distinct ename from project natural join employee where pno = "P1";
(select distinct ename from employee)except(select ename from project natural join employee where pno = "P1");
select distinct ename from employee where ename not in(select distinct ename from project natural join employee where pno = "P1");

4.
select distinct ename, dname, mgrssn from employee natural join department where mgrssn in (select essn from employee where ename = "马达");

5.
select pno, essn, count(pno) from employee natural join project group by essn having count(pno) > 1;
select essn from employee natural join project where pno = "P1" or pno = "P2" group by essn having count(pno) > 1;

select essn, pno from project natural join employee where pno = "P2" and essn in (select essn from project natural join employee where pno = "P1");

6.
select ename, essn, count(pno) from  employee natural join project group by essn having count(pno) = 3;

7.
select dname, avg(salary) from employee natural join department group by mgrssn having avg(salary) < 1500;

8.
select ename, sum(hours), count(pno) from employee natural join project natural join works_on group by essn;
select ename, sum(hours), count(pno) from employee natural join project natural join works_on group by essn having count(pno) > 2 and sum(hours) > 8;

9.
select ename, essn, avg(salary)/30/sum(hours) from employee natural join department natural join works_on group by mgrssn;

1.select distinct essn from employee natural join project where pno = "P1";
2.select distinct ename from employee natural join project where pname = "开黑";
3.select distinct ename, address from department natural join employee where dname = "哈工大";
4.
select distinct ename, address, dname, salary from department natural join employee where dname = "哈工大" and salary < 1300;


mysql -u root -p