insert into works_on
	values("111111111", "P1", 12);
	
load data local infile "C:/Users/11303/Desktop/LeetCode-Medium/people.txt" into table people;

create table people
	(p_id char(6),
	p_name varchar(12),
	p_sex varchar(6),
	primary key (p_id));
	
load data local infile "C:/Users/11303/Desktop/LeetCode-Medium/people.txt" into table people;

create table supermarket
	(sm_name varchar(12),
	sm_ssn char(6),
	primary key (sm_ssn));
	
load data local infile "C:/Users/11303/Desktop/LeetCode-Medium/supermarket.txt" into table supermarket;

create table goods
	(g_name varchar(12),
	g_ssn char(6),
	g_class varchar(12),
	g_price int,
	primary key (g_ssn));
	
load data local infile "C:/Users/11303/Desktop/LeetCode-Medium/goods.txt" into table goods;

create table work_
	(w_name varchar(12),
	w_ssn char(6),
	w_hour int,
	w_salary numeric(8,2),
	primary key (w_ssn));
	
load data local infile "C:/Users/11303/Desktop/LeetCode-Medium/work_.txt" into table work_;

create table bank
	(b_class varchar(12),
	b_ssn char(6),
	primary key (b_ssn));
	
load data local infile "C:/Users/11303/Desktop/LeetCode-Medium/bank.txt" into table bank;

create table restaurant
	(r_name varchar(12),
	r_ssn char(6),
	primary key (r_ssn));
	
load data local infile "C:/Users/11303/Desktop/LeetCode-Medium/restaurant.txt" into table restaurant;

create table school
	(s_name varchar(12),
	s_ssn char(6),
	s_level varchar(12),
	primary key (s_ssn));
	
load data local infile "C:/Users/11303/Desktop/LeetCode-Medium/school.txt" into table school;

create table hospital
	(h_name varchar(12),
	h_ssn char(6),
	h_level varchar(12),
	primary key (h_ssn));
	
load data local infile "C:/Users/11303/Desktop/LeetCode-Medium/hospital.txt" into table hospital;

