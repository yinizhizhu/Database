
hospital-people
create table h_p_d
	(h_ssn char(6),
	p_id char(6),
	primary key (h_ssn, p_id),
	foreign key (h_ssn) references hospital(h_ssn) on delete cascade on update cascade,
	foreign key (p_id) references people(p_id) on delete cascade on update cascade);

insert into h_p_d
	values("111111", "111110");
hospital natural join h_p_d natural join people

create table h_p_w
	(h_ssn char(6),
	p_id char(6),
	primary key (p_id),
	foreign key (h_ssn) references hospital(h_ssn) on delete cascade on update cascade,
	foreign key (p_id) references people(p_id) on delete cascade on update cascade);

insert into h_p_w
	values("111111", "111110");
	
create table h_w_o
	(h_ssn char(6),
	w_ssn char(6),
	primary key (h_ssn, w_ssn),
	foreign key (h_ssn) references hospital(h_ssn) on delete cascade on update cascade,
	foreign key (w_ssn) references work_(w_ssn) on delete cascade on update cascade);

insert into h_w_o
	values("111110", "111110");
	
restaurant-people
create table r_p_d
	(r_ssn char(6),
	p_id char(6),
	primary key (r_ssn, p_id),
	foreign key (r_ssn) references restaurant(r_ssn) on delete cascade on update cascade,
	foreign key (p_id) references people(p_id) on delete cascade on update cascade);

r_p_d(r_ssn, p_id)
insert into r_p_d
	values("111110", "111112");
delete from r_p_d;
select * from r_p_d;
111110, 111112
"111110", "111112"

create table r_p_w
	(r_ssn char(6),
	p_id char(6),
	primary key (p_id),
	foreign key (r_ssn) references restaurant(r_ssn) on delete cascade on update cascade,
	foreign key (p_id) references people(p_id) on delete cascade on update cascade);

create table r_w_o
	(r_ssn char(6),
	w_ssn char(6),
	primary key (r_ssn, w_ssn),
	foreign key (r_ssn) references restaurant(r_ssn) on delete cascade on update cascade,
	foreign key (w_ssn) references work_(w_ssn) on delete cascade on update cascade);

restaurant-school
create table r_s_h
	(r_ssn char(6),
	s_ssn char(6),
	primary key (r_ssn),
	foreign key (r_ssn) references restaurant(r_ssn) on delete cascade on update cascade,
	foreign key (s_ssn) references school(s_ssn) on delete cascade on update cascade);

school-people
create table s_p_d
	(s_ssn char(6),
	p_id char(6),
	primary key (s_ssn, p_id),
	foreign key (s_ssn) references school(s_ssn) on delete cascade on update cascade,
	foreign key (p_id) references people(p_id) on delete cascade on update cascade);

create table s_p_w
	(s_ssn char(6),
	p_id char(6),
	primary key (p_id),
	foreign key (s_ssn) references school(s_ssn) on delete cascade on update cascade,
	foreign key (p_id) references people(p_id) on delete cascade on update cascade);

create table s_w_o
	(s_ssn char(6),
	w_ssn char(6),
	primary key (s_ssn, w_ssn),
	foreign key (s_ssn) references school(s_ssn) on delete cascade on update cascade,
	foreign key (w_ssn) references work_(w_ssn) on delete cascade on update cascade);

people-work_
create table p_w_h
	(p_id char(6),
	w_ssn char(6),
	primary key (p_id, w_ssn),
	foreign key (p_id) references people(p_id) on delete cascade on update cascade,
	foreign key (w_ssn) references work_(w_ssn) on delete cascade on update cascade);

people-goods
create table p_g_u
	(g_ssn char(6),
	p_id char(6),
	primary key (g_ssn, p_id),
	foreign key (g_ssn) references goods(g_ssn) on delete cascade on update cascade,
	foreign key (p_id) references people(p_id) on delete cascade on update cascade);

goods-supermarket
create table g_s_p
	(g_ssn char(6),
	sm_ssn char(6),
	primary key (g_ssn, sm_ssn),
	foreign key (g_ssn) references goods(g_ssn) on delete cascade on update cascade,
	foreign key (sm_ssn) references supermarket(sm_ssn) on delete cascade on update cascade);

supermarket-people
create table sm_p_d
	(sm_ssn char(6),
	p_id char(6),
	primary key (sm_ssn, p_id),
	foreign key (sm_ssn) references supermarket(sm_ssn) on delete cascade on update cascade,
	foreign key (p_id) references people(p_id) on delete cascade on update cascade);

create table sm_p_w
	(sm_ssn char(6),
	p_id char(6),
	primary key (p_id),
	foreign key (sm_ssn) references supermarket(sm_ssn) on delete cascade on update cascade,
	foreign key (p_id) references people(p_id) on delete cascade on update cascade);

create table sm_w_o
	(sm_ssn char(6),
	w_ssn char(6),
	primary key (sm_ssn, w_ssn),
	foreign key (sm_ssn) references supermarket(sm_ssn) on delete cascade on update cascade,
	foreign key (w_ssn) references work_(w_ssn) on delete cascade on update cascade);

bank-people
create table b_p_d
	(b_ssn char(6),
	p_id char(6),
	primary key (b_ssn, p_id),
	foreign key (b_ssn) references bank(b_ssn) on delete cascade on update cascade,
	foreign key (p_id) references people(p_id) on delete cascade on update cascade);

create table b_p_w
	(b_ssn char(6),
	p_id char(6),
	primary key (p_id),
	foreign key (b_ssn) references bank(b_ssn) on delete cascade on update cascade,
	foreign key (p_id) references people(p_id) on delete cascade on update cascade);

create table b_w_o
	(b_ssn char(6),
	w_ssn char(6),
	primary key (b_ssn, w_ssn),
	foreign key (b_ssn) references bank(b_ssn) on delete cascade on update cascade,
	foreign key (w_ssn) references work_(w_ssn) on delete cascade on update cascade);