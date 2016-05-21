#!/usr/bin/python
# -*- coding: gbk -*-
# -*- coding: utf-8 -*-
#encoding=UTF-8
import MySQLdb

conn=MySQLdb.connect(
    host="localhost",
    port=3306,
    user="root",
    passwd="",
    db="lee",
    charset='utf8'
    )
cur=conn.cursor()

flag=input("请输入任务编号(1--9): ")
if flag==1:
    pno=raw_input("请输入项目编号:") #参加了项目编号为%PNO%的项目的员工号
    tmp = 'select distinct essn from employee natural join project where pno = "'+pno+'"'
    a1=cur.execute(tmp)
    info = cur.fetchmany(a1)
    print "参加了项目编号为" + pno +"的员工编号为："
    for i in info:
        for j in i:
            print j
            
elif flag==2:
    pname=raw_input("请输入项目名称:")#参加了项目名为%PNAME%的员工名字
    tmp = 'select distinct ename from employee natural join project where pname = "'+pname+'"'
    a2=cur.execute(tmp.decode("gbk").encode("utf8"))
    info = cur.fetchmany(a2)
    print "参加了项目名" + pname +"的员工名字有："
    for i in info:
        for j in i:
            print j

elif flag==3:        
    dname=raw_input("请输入部门名称:")#在%DNAME%工作的所有工作人员的名字和地址
    tmp = 'select distinct ename, address from department natural join employee where dname = "'+dname+'"'
    a3=cur.execute(tmp.decode("gbk").encode("utf8"))
    info = cur.fetchmany(a3)
    print "在" + dname +"部门工作的员工名和地址如下（姓名、地址交替出现）："
    for i in info:
        for j in i:
            print j

elif flag==4:
    dname=raw_input("请输入部门名称:")#在%DNAME%工作且工资低于%SALARY%元的员工名字和地址
    salary=input("请输入工资钱数:")
    tmp = 'select distinct ename, address, dname, salary from department natural join employee where dname = "'+dname+'" '+' and salary < '+str(1300);
    a4=cur.execute(tmp.decode("gbk").encode("utf8"))
    info = cur.fetchmany(a4)
    print "在" + dname +"部门工作且工资低于" + str(salary) +"的员工名和地址如下（姓名、地址交替出现）："
    for i in info:
        for j in i:
            print j

elif flag==5:
    pno=raw_input("请输入项目编号:")#没有参加项目编号为%PNO%的项目的员工姓名
    a5=cur.execute("select distinct ename from employee where essn not in (select essn from works_on where pno=%s)",pno)
    info = cur.fetchmany(a5)
    print "没有参加项目编号为：" + pno + "的员工姓名如下："
    for i in info:
        for j in i:
            print j

elif flag==6:
    ename=raw_input("请输入领导名字:")#由%ENAME%领导的工作人员的姓名和所在部门的名字
    a6=cur.execute("select ename,dname from employee,department where employee.dno=department.dno\
                and superssn=(select essn from employee where ename=%s)",ename)
    info = cur.fetchmany(a6)
    print "由" + ename + "领导的工作人员姓名、所在部门名字如下（姓名、部门名字交替出现）："
    for i in info:
       for j in i:
            print j

elif flag==7:
    pno1=raw_input("请输入第一个项目编号:")#至少参加了项目编号为%PNO1%和%PNO2%的项目的员工号
    pno2=raw_input("请输入第二个项目编号:")
    strall="select essn from employee where essn in (select essn from works_on where " + "pno="+"'"+ pno1 +"'"\
          + " and essn in (select essn from works_on where pno=" + "'" +pno2 + "'))"
    a7=cur.execute(strall)
    info = cur.fetchmany(a7)
    print "至少参加了项目编号为" + pno1 + "和" + pno2 + "的员工编号为："
    for i in info:
        for j in i:
            print j
            
elif flag==8:        
    salary=input("请输入工资钱数:")#员工平均工资低于%SALARY%元的部门名称
    a8=cur.execute("select dname from employee,department where employee.dno=department.dno\
                    group by employee.dno having avg(salary)<%s",salary)
    info = cur.fetchmany(a8)
    print "员工平均工资低于" + str(salary) + "的部门名称有："
    for i in info:
        for j in i:
            print j

elif flag==9:
    num=input("请输入参加项目数:")#至少参与了%N%个项目且工作总时间不超过%HOURS%小时的员工名字
    hours=input("工作总时间:")
    strall="select employee.ename from employee where essn in (select essn from works_on \
            group by essn having count(*)>" + str(num) +" and sum(hours)<=" + str(hours) + ")"
    a9=cur.execute(strall)
    info = cur.fetchmany(a9)
    print "参加了多于" + str(num) + "个项目且工作总时间低于" + str(hours) + "的员工姓名如下："
    for i in info:
        for j in i:
            print j

else:
    print "没有您您输入的任务编号！"
conn.commit()
cur.close()
conn.close()
